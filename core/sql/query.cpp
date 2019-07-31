#include "query.h"

#include <algorithm>

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

        // Remove last ' AND '
        where.erase(where.size() - 5);
    }

    return where;
}

std::string Query::buildQuery(bool withRowid) const
{
    // Selector and display formats
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

    if(m_selected_columns.empty()) {
        selector += "*";
    } else {
        for(const auto& it : m_selected_columns) {
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
    // Join
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

    // Filter
    std::string where = buildWherePart();

    // Group
    std::string group_by;
    for(const auto& group_by_column : m_group) {
        group_by += group_by_column.prefix + "." + sqlb::escapeIdentifier(group_by_column.column) + " " + ",";
    }
    if(!group_by.empty()) {
        group_by.pop_back();
        group_by = "GROUP BY " + group_by;
    }

    // Sorting
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

    //Pagination
    std::string pagination;
    if (m_pagination.limit != 0) pagination += " LIMIT " + std::to_string(m_pagination.limit);

    return "SELECT " + selector + " FROM " + m_table.toString() + " " + m_table.as() + " " + join + where + " " + group_by + order_by + pagination;
}

std::string Query::buildCountQuery() const
{
    // Build simplest count query for this (filtered) table
    return "SELECT COUNT(*) FROM " + m_table.toString() + " " + buildWherePart();
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

}
