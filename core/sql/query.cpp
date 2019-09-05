#include "query.h"

#include <algorithm>
#include "spdlogfix.h"

namespace sqlb
{

void Query::clear()
{
    m_table.clear();
    //m_rowid_columns = {"id"};
    m_selected_columns.clear();
    m_where.clear();
    m_sort.clear();
}

std::string Query::buildWherePart() const
{
    std::string where;

    if(!m_where.empty()) {
        where = "WHERE ";

        for(const auto & i : m_where) {
            // I dont know why this lengthy process.
            //            const auto it = findSelectedColumnByName(m_selected_columns.at(i->first).selector);

            std::string column = m_selected_columns.at(i.first).prefix + "." + sqlb::escapeIdentifier(m_selected_columns.at(i.first).selector);

            // if findbyname then use it..
//            if(it != m_selected_columns.cend() && it->selector != column)
//               column = it->selector;

            where += column + " " + i.second + " AND ";
        }

        if(!m_custm_where.empty()) {
                where += m_custm_where;
        } else {
            // Remove last ' AND '
            where.erase(where.size() - 5);
        }
    } else{
        if(!m_custm_where.empty()) {
              where = "WHERE ";
              where += m_custm_where;
        }
    }
    return where;
}

std::string Query::buildJoinPart() const
{
    std::string join;
    if(m_joins.empty()) {
        join += "";
    } else {
        for(const auto& it : m_joins) {
            join += it.join_type + " join ";
            if (it.lateral.empty()){
                join += it.m_table.toString() + " as " + it.m_table.as();
            } else {
                join += it.lateral;
            }
            join += + " on " + it.condition + " ";
        }
    }
    return join;
}

std::string Query::buildGroupByPart() const
{
    std::string group_by;
    for(const auto& group_by_column : m_group) {
        group_by += group_by_column.prefix + "." + sqlb::escapeIdentifier(group_by_column.column) + " " + ",";
    }
    if(!group_by.empty()) {
        group_by.pop_back();
        group_by = "GROUP BY " + group_by;
    }
    return group_by;
}

std::string Query::buildOrderByByPart() const // Sorting
{
    std::string order_by;
    for(const auto& sorted_column : m_sort) {
        if(sorted_column.column < m_selected_columns.size()) {
            auto c2 = m_selected_columns.at(sorted_column.column);
            order_by += c2.prefix + "." + sqlb::escapeIdentifier(c2.selector) + " "
                        + (sorted_column.direction == sqlb::Ascending ? "ASC" : "DESC") + ",";
        }
    }
    if(!order_by.empty()) {
        order_by.pop_back();
        order_by = "ORDER BY " + order_by;
    }
    return order_by;
}

std::string Query::buildPaginationPart() const
{
    std::string pagination;
    if (m_pagination.limit > 0) pagination += " LIMIT " + std::to_string(m_pagination.limit);

    int offset = 0;
    if(m_pagination.offset == 0){
        if(m_pagination.current_page > 1) {
            offset = m_pagination.limit * (m_pagination.current_page - 1);
        }
    }
    if(offset) {
        pagination += " OFFSET " + std::to_string(offset);
    }

    return  pagination;
}

std::string Query::buildSelectorPart(std::vector<SelectedColumn> &m_selected_columns_) const
{
    std::string selector;
    /*
    if (withRowid)
    {
        // We select the rowid data into a JSON array in case there are multiple rowid columns in order to have all values at hand.
        // If there is only one rowid column, we leave it as is.
        if(m_rowid_columns.size() == 1)
        {
            selector = m_table.as() + "." + sqlb::escapeIdentifier(m_rowid_columns.at(0)) + ",";
        } else {
            selector += "sqlb_make_single_value(";
            for(size_t i=0;i<m_rowid_columns.size();i++)
                selector += sqlb::escapeIdentifier(m_rowid_columns.at(i)) + ",";
            selector.pop_back();    // Remove the last comma
            selector += "),";
        }
    }*/

    if(m_selected_columns_.empty()) {
        selector += "*";
    } else {
        for(const auto& it : m_selected_columns_) {
            if(it.calculated.empty()) {
                if(!it.prefix.empty()) selector += it.prefix + ".";
                if (it.original_column != it.selector)
                    // note not escapeIdentifier selector here!
                    selector += it.selector + " AS " + sqlb::escapeIdentifier(it.original_column) + ",";
                else
                    selector += sqlb::escapeIdentifier(it.original_column) + ",";
            } else {
                selector += it.calculated + ",";
            }
        }
        selector.pop_back();
    }
    return selector;
}

std::string Query::buildQuery(bool  /*withRowid*/) const
{
    // Selector and display formats
    std::string selector = buildSelectorPart(const_cast<std::vector<SelectedColumn> &>(m_selected_columns));
    std::string join = buildJoinPart();
    // Filter
    std::string where = buildWherePart();
    std::string group_by = buildGroupByPart();
    std::string order_by = buildOrderByByPart();
    std::string pagination = buildPaginationPart();

    return "SELECT " + selector + " FROM " + m_table.toString() + " " + m_table.as() + " " + join + where + " " + group_by + order_by + pagination;
}

std::string Query::buildCountQuery() const
{
    // Build simplest count query for this (filtered) table
    // limit always applies last, and by that time there is only one row
    // cant add order by
    std::string q = "SELECT COUNT(*) FROM " + m_table.toString() + " " + m_table.as() + " " +  buildJoinPart() + buildWherePart() + " " + buildGroupByPart();
    //SPDLOG_TRACE(q);
    return q;
}

std::string Query::buildDeleteQuery() const
{
    std::string join = buildJoinPart();
    // Filter
    std::string where = buildWherePart();
    std::string group_by = buildGroupByPart();

    //return "DELETE FROM " + m_table.toString() + " " + m_table.as() + " " + join + where + " " + group_by;
    // Fix delete query currently not working for join table.
    //DELETE FROM [ ONLY ] table_name [ * ] [ [ AS ] alias ] [ USING using_list ] [ WHERE condition | WHERE CURRENT OF cursor_name ] [ RETURNING * | output_expression [ [ AS ] output_name ]
    return "DELETE FROM " + m_table.toString() + " " + m_table.as() + " " + where + " " + group_by;
}

std::string Query::buildInsQuery(nlohmann::json args) const
{
    std::string column;
    std::string values;
    auto o = args[0];
    if(o.type() == nlohmann::json::object()){
        for (auto& [key, val] : o.items())
        {
            std::string key_ = key;
           auto it =  std::find_if(m_selected_columns.begin(), m_selected_columns.end(), [&](const SelectedColumn& c) {
                    return key_ == c.selector;
                });
           if(it != m_selected_columns.end()){
               column += key_ + " ,";
               std::string v;
               if (val.is_null()) {
                   v  = "null";
                   values += v + " ,";
               } else if(val.type() == nlohmann::json::value_t::number_integer ||  val.type() == nlohmann::json::value_t::number_unsigned) {
                   v = std::to_string(val.get<long>());
                   values += v + " ,";
               } else if (val.type() == nlohmann::json::value_t::number_float) {
                   v = std::to_string(val.get<float>());
                   values += v + " ,";
               } else if(val.type() == nlohmann::json::value_t::boolean) {
                   v = val.get<bool>() ? "true" : "false";
                   values += v + " ,";
               } else if (val.type() == nlohmann::json::value_t::string) {
                   v = val.get<std::string>();
                   values += "'" + v + "'" + " ,";
               } else {
                   v = " ";
                   //value += v + " ,";
               }
           }
        }
        if(!column.empty()) column.pop_back();
        if(!values.empty()) values.pop_back();
        if(!column.empty() && !values.empty()){
            return "INSERT INTO " + m_table.toString() + " " +  " (" + column + ") values(" + values + ")";
        }
    }
    return "";
}

std::string Query::buildUpdateQuery(nlohmann::json args) const
{
    std::string column;
    std::string values;
    auto o = args[0];
    if(o.type() == nlohmann::json::object()){
        for (auto& [key, val] : o.items())
        {
            std::string key_ = key;
           auto it =  std::find_if(m_selected_columns.begin(), m_selected_columns.end(), [&](const SelectedColumn& c) {
                    return key_ == c.selector;
                });
           if(it != m_selected_columns.end()){
               column += key_ + " ,";
               std::string v;
               if (val.is_null()) {
                   v  = "null";
                   values += v + " ,";
               } else if(val.type() == nlohmann::json::value_t::number_integer ||  val.type() == nlohmann::json::value_t::number_unsigned) {
                   v = std::to_string(val.get<long>());
                   values += v + " ,";
               } else if (val.type() == nlohmann::json::value_t::number_float) {
                   v = std::to_string(val.get<float>());
                   values += v + " ,";
               } else if(val.type() == nlohmann::json::value_t::boolean) {
                   v = val.get<bool>() ? "true" : "false";
                   values += v + " ,";
               } else if (val.type() == nlohmann::json::value_t::string) {
                   v = val.get<std::string>();
                   values += "'" + v + "'" + " ,";
               } else {
                   v = " ";
                   //value += v + " ,";
               }
           }
        }
        if(!column.empty()) column.pop_back();
        if(!values.empty()) values.pop_back();
        if(!column.empty() && !values.empty()){
            // Filter
            std::string where = buildWherePart();
            return "UPDATE " + m_table.toString()  + " " + m_table.as() + " SET " +  " (" + column + ") =ROW(" + values + ") " +   where ;
        }
    }
    return "";
}

std::string Query::buildUpdateQuery(const std::string& column, const std::string& values, const std::string& where_) const
{
    std::string join = buildJoinPart();
    if(!join.empty()){
        join = " FROM " + join;
    }
    // Filter
    std::string where;
    if(!where_.empty()) {
        where = where_;
    } else {
        where = buildWherePart();
    }
    //if(where.empty()){ throw("can't update all rows.."); }
    std::string group_by = buildGroupByPart();
    //return "UPDATE " + m_table.toString() + " " + m_table.as() + " SET (" + column +  ") = ROW(" + values + ") " +  join + where + " " + group_by;
    return "UPDATE " + m_table.toString() + " " + m_table.as() + " SET (" + column +  ") = ROW(" + values + ") " +   where + " " + group_by;
}

std::vector<SelectedColumn>::iterator Query::findSelectedColumnByName(const std::string& name)
{
    return std::find_if(m_selected_columns.begin(), m_selected_columns.end(), [name](const SelectedColumn& c) {
        return name == c.original_column;
    });
}

std::vector<SelectedColumn>::const_iterator Query::findSelectedColumnByName(const std::string& name) const
{
    return std::find_if(m_selected_columns.cbegin(), m_selected_columns.cend(), [name](const SelectedColumn& c) {
        return name == c.original_column;
    });
}

std::vector<SelectedColumn>::iterator Query::findSelectedColumnBySelector(const std::string &name)
{
    return std::find_if(m_selected_columns.begin(), m_selected_columns.end(), [name](const SelectedColumn& c) {
        return name == c.selector;
    });
}

std::vector<SelectedColumn>::const_iterator Query::findSelectedColumnBySelector(const std::string &name) const
{
    return std::find_if(m_selected_columns.begin(), m_selected_columns.end(), [name](const SelectedColumn& c) {
        return name == c.selector;
    });
}

}
