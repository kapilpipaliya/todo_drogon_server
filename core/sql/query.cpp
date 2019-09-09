#include "query.h"

#include <algorithm>
#include "../service/dba.h"
#include "condformat.h"
#include "spdlogfix.h"

namespace sqlb {

void Query::clear() {
  m_table.clear();
  // m_rowid_columns = {"id"};
  m_selected_columns.clear();
  m_where.clear();
  m_sort.clear();
}

std::string Query::buildWherePart() const {
  std::string where;

  if (!m_where.empty()) {
    where = "WHERE ";

    for (const auto& i : m_where) {
      // I dont know why this lengthy process.
      //            const auto it =
      //            findSelectedColumnByName(m_selected_columns.at(i->first).selector);

      std::string column =
          m_selected_columns.at(i.first).prefix + "." +
          sqlb::escapeIdentifier(m_selected_columns.at(i.first).selector);

      // if findbyname then use it..
      //            if(it != m_selected_columns.cend() && it->selector !=
      //            column)
      //               column = it->selector;

      where += column + " " + i.second + " AND ";
    }

    if (!m_custm_where.empty()) {
      where += m_custm_where;
    } else {
      // Remove last ' AND '
      where.erase(where.size() - 5);
    }
  } else {
    if (!m_custm_where.empty()) {
      where = "WHERE ";
      where += m_custm_where;
    }
  }
  return where;
}

std::string Query::buildJoinPart() const {
  std::string join;
  if (m_joins.empty()) {
    join += "";
  } else {
    for (const auto& it : m_joins) {
      join += it.join_type + " join ";
      if (it.lateral.empty()) {
        join += it.m_table.toString() + " as " + it.m_table.as();
      } else {
        join += it.lateral;
      }
      join += +" on " + it.condition + " ";
    }
  }
  return join;
}

std::string Query::buildGroupByPart() const {
  std::string group_by;
  for (const auto& group_by_column : m_group) {
    group_by += group_by_column.prefix + "." +
                sqlb::escapeIdentifier(group_by_column.column) + " " + ",";
  }
  if (!group_by.empty()) {
    group_by.pop_back();
    group_by = "GROUP BY " + group_by;
  }
  return group_by;
}

std::string Query::buildOrderByByPart() const  // Sorting
{
  std::string order_by;
  for (const auto& sorted_column : m_sort) {
    if (sorted_column.column < m_selected_columns.size()) {
      auto c2 = m_selected_columns.at(sorted_column.column);
      order_by +=
          c2.prefix + "." + sqlb::escapeIdentifier(c2.selector) + " " +
          (sorted_column.direction == sqlb::Ascending ? "ASC" : "DESC") + ",";
    }
  }
  if (!order_by.empty()) {
    order_by.pop_back();
    order_by = "ORDER BY " + order_by;
  }
  return order_by;
}

std::string Query::buildPaginationPart() const {
  std::string pagination;
  if (m_pagination.limit > 0)
    pagination += " LIMIT " + std::to_string(m_pagination.limit);

  int offset = 0;
  if (m_pagination.offset == 0) {
    if (m_pagination.current_page > 1) {
      offset = m_pagination.limit * (m_pagination.current_page - 1);
    }
  }
  if (offset) {
    pagination += " OFFSET " + std::to_string(offset);
  }

  return pagination;
}

std::string Query::buildSelectorPart(
    std::vector<SelectedColumn>& m_selected_columns_) const {
  std::string selector;
  /*
  if (withRowid)
  {
      // We select the rowid data into a JSON array in case there are multiple
  rowid columns in order to have all values at hand.
      // If there is only one rowid column, we leave it as is.
      if(m_rowid_columns.size() == 1)
      {
          selector = m_table.as() + "." +
  sqlb::escapeIdentifier(m_rowid_columns.at(0)) + ","; } else { selector +=
  "sqlb_make_single_value("; for(size_t i=0;i<m_rowid_columns.size();i++)
              selector += sqlb::escapeIdentifier(m_rowid_columns.at(i)) + ",";
          selector.pop_back();    // Remove the last comma
          selector += "),";
      }
  }*/

  if (m_selected_columns_.empty()) {
    selector += "*";
  } else {
    for (const auto& it : m_selected_columns_) {
      if (it.calculated.empty()) {
        if (!it.prefix.empty()) selector += it.prefix + ".";
        if (it.original_column != it.selector)
          // note not escapeIdentifier selector here!
          selector += it.selector + " AS " +
                      sqlb::escapeIdentifier(it.original_column) + ",";
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

std::string Query::buildQuery(bool /*withRowid*/) const {
  // Selector and display formats
  std::string selector = buildSelectorPart(
      const_cast<std::vector<SelectedColumn>&>(m_selected_columns));
  std::string join = buildJoinPart();
  // Filter
  std::string where = buildWherePart();
  std::string group_by = buildGroupByPart();
  std::string order_by = buildOrderByByPart();
  std::string pagination = buildPaginationPart();

  return "SELECT " + selector + " FROM " + m_table.toString() + " " +
         m_table.as() + " " + join + where + " " + group_by + order_by +
         pagination;
}

std::string Query::buildCountQuery() const {
  // Build simplest count query for this (filtered) table
  // limit always applies last, and by that time there is only one row
  // cant add order by
  std::string q = "SELECT COUNT(*) FROM " + m_table.toString() + " " +
                  m_table.as() + " " + buildJoinPart() + buildWherePart() +
                  " " + buildGroupByPart();
  // SPDLOG_TRACE(q);
  return q;
}

std::string Query::buildDeleteQuery() const {
  std::string join = buildJoinPart();
  // Filter
  std::string where = buildWherePart();
  std::string group_by = buildGroupByPart();

  // return "DELETE FROM " + m_table.toString() + " " + m_table.as() + " " +
  // join + where + " " + group_by;
  // Fix delete query currently not working for join table.
  // DELETE FROM [ ONLY ] table_name [ * ] [ [ AS ] alias ] [ USING using_list ]
  // [ WHERE condition | WHERE CURRENT OF cursor_name ] [ RETURNING * |
  // output_expression [ [ AS ] output_name ]
  return "DELETE FROM " + m_table.toString() + " " + m_table.as() + " " +
         where + " " + group_by;
}

std::string Query::buildInsQuery(nlohmann::json args) const {
  std::string column;
  std::string values;
  auto o = args[0];
  if (o.type() == nlohmann::json::object()) {
    for (auto& [key, val] : o.items()) {
      std::string key_ = key;
      auto it = std::find_if(
          m_selected_columns.begin(), m_selected_columns.end(),
          [&](const SelectedColumn& c) { return key_ == c.selector; });
      if (it != m_selected_columns.end()) {
        column += key_ + " ,";
        std::string v;
        if (val.is_null()) {
          v = "null";
          values += v + " ,";
        } else if (val.type() == nlohmann::json::value_t::number_integer ||
                   val.type() == nlohmann::json::value_t::number_unsigned) {
          v = std::to_string(val.get<long>());
          values += v + " ,";
        } else if (val.type() == nlohmann::json::value_t::number_float) {
          v = std::to_string(val.get<float>());
          values += v + " ,";
        } else if (val.type() == nlohmann::json::value_t::boolean) {
          v = val.get<bool>() ? "true" : "false";
          values += v + " ,";
        } else if (val.type() == nlohmann::json::value_t::string) {
          v = val.get<std::string>();
          values += "'" + v + "'" + " ,";
        } else {
          v = " ";
          // value += v + " ,";
        }
      }
    }
    if (!column.empty()) column.pop_back();
    if (!values.empty()) values.pop_back();
    if (!column.empty() && !values.empty()) {
      return "INSERT INTO " + m_table.toString() + " " + " (" + column +
             ") values(" + values + ")";
    }
  }
  return "";
}

std::string Query::buildUpdateQuery(nlohmann::json args) const {
  std::string column;
  std::string values;
  auto o = args[0];
  if (o.type() == nlohmann::json::object()) {
    for (auto& [key, val] : o.items()) {
      std::string key_ = key;
      auto it = std::find_if(
          m_selected_columns.begin(), m_selected_columns.end(),
          [&](const SelectedColumn& c) { return key_ == c.selector; });
      if (it != m_selected_columns.end()) {
        column += key_ + " ,";
        std::string v;
        if (val.is_null()) {
          v = "null";
          values += v + " ,";
        } else if (val.type() == nlohmann::json::value_t::number_integer ||
                   val.type() == nlohmann::json::value_t::number_unsigned) {
          v = std::to_string(val.get<long>());
          values += v + " ,";
        } else if (val.type() == nlohmann::json::value_t::number_float) {
          v = std::to_string(val.get<float>());
          values += v + " ,";
        } else if (val.type() == nlohmann::json::value_t::boolean) {
          v = val.get<bool>() ? "true" : "false";
          values += v + " ,";
        } else if (val.type() == nlohmann::json::value_t::string) {
          v = val.get<std::string>();
          values += "'" + v + "'" + " ,";
        } else {
          v = " ";
          // value += v + " ,";
        }
      }
    }
    if (!column.empty()) column.pop_back();
    if (!values.empty()) values.pop_back();
    if (!column.empty() && !values.empty()) {
      // Filter
      std::string where = buildWherePart();
      return "UPDATE " + m_table.toString() + " " + m_table.as() + " SET " +
             " (" + column + ") =ROW(" + values + ") " + where;
    }
  }
  return "";
}

std::string Query::buildUpdateQuery(const std::string& column,
                                    const std::string& values,
                                    const std::string& where_) const {
  std::string join = buildJoinPart();
  if (!join.empty()) {
    join = " FROM " + join;
  }
  // Filter
  std::string where;
  if (!where_.empty()) {
    where = where_;
  } else {
    where = buildWherePart();
  }
  // if(where.empty()){ throw("can't update all rows.."); }
  std::string group_by = buildGroupByPart();
  // return "UPDATE " + m_table.toString() + " " + m_table.as() + " SET (" +
  // column +  ") = ROW(" + values + ") " +  join + where + " " + group_by;
  return "UPDATE " + m_table.toString() + " " + m_table.as() + " SET (" +
         column + ") = ROW(" + values + ") " + where + " " + group_by;
}

std::vector<SelectedColumn>::iterator Query::findSelectedColumnByName(
    const std::string& name) {
  return std::find_if(
      m_selected_columns.begin(), m_selected_columns.end(),
      [name](const SelectedColumn& c) { return name == c.original_column; });
}

std::vector<SelectedColumn>::const_iterator Query::findSelectedColumnByName(
    const std::string& name) const {
  return std::find_if(
      m_selected_columns.cbegin(), m_selected_columns.cend(),
      [name](const SelectedColumn& c) { return name == c.original_column; });
}

std::vector<SelectedColumn>::iterator Query::findSelectedColumnBySelector(
    const std::string& name) {
  return std::find_if(
      m_selected_columns.begin(), m_selected_columns.end(),
      [name](const SelectedColumn& c) { return name == c.selector; });
}

std::vector<SelectedColumn>::const_iterator Query::findSelectedColumnBySelector(
    const std::string& name) const {
  return std::find_if(
      m_selected_columns.begin(), m_selected_columns.end(),
      [name](const SelectedColumn& c) { return name == c.selector; });
}
size_t Query::filterCount() const { return where().size(); }
bool Query::select() {
  auto q = buildQuery(true);
  // SPDLOG_TRACE(q);
  // crash !! auto clientPtr = drogon::app().getFastDbClient("sce");
  auto clientPtr = drogon::app().getDbClient("sce");
  *clientPtr << q << drogon::orm::Mode::Blocking >>
      [this](const drogon::orm::Result& r) { result = r; } >>
      [q](const drogon::orm::DrogonDbException& e) {
        SPDLOG_TRACE("query: {}", q);
        SPDLOG_TRACE(e.base().what());
        // testOutput(false, "DbClient streaming-type interface(0)");
        throw;
      };
  return true;
}

std::string Query::getHeaderName(const unsigned long column) const {
  return selectedColumns().at(column).original_column;
}

void Query::sort(const std::vector<SortedColumn>& columns) {
  // Don't do anything when the sort order hasn't changed
  if (orderBy() == columns) return;

  // Save sort order
  m_sort = columns;

  // Set the new query (but only if a table has already been set

  if (!table().isEmpty())
    // buildQuery();
    select();
}

nlohmann::json Query::getJsonHeaderData() {
  nlohmann::json ret(nlohmann::json::array());

  nlohmann::json jsonHeaderRow(nlohmann::json::array());
  nlohmann::json jsonFormHeaderRow(nlohmann::json::array());
  nlohmann::json jsonFormColumnTypesRow(nlohmann::json::array());
  nlohmann::json jsonFormVisibleColumnsRow(nlohmann::json::array());
  nlohmann::json jsonFormOffsetColumnsRow(nlohmann::json::array());
  nlohmann::json jsonFormTooltipOffsetColumnsRow(nlohmann::json::array());

  for (unsigned long c = 0; c < selectedColumns().size(); c++) {
    jsonHeaderRow[c] = getHeaderName(c);
    auto column = selectedColumns().at(c);
    jsonFormColumnTypesRow[c] = column.column_type;
    jsonFormVisibleColumnsRow[c] = column.isVisible;
    jsonFormOffsetColumnsRow[c] = column.offset;
    jsonFormTooltipOffsetColumnsRow[c] = column.tooltipOffset;

    if (column.prefix.empty()) {
      jsonFormHeaderRow[c] = column.original_column;  // can change case
    } else {
      if (column.prefix == table().as()) {
        jsonFormHeaderRow[c] = column.selector;
      } else {
        jsonFormHeaderRow[c] = column.prefix + "_" + column.selector;
      }
    }
  }
  ret.push_back(jsonHeaderRow);
  ret.push_back(jsonFormHeaderRow);
  ret.push_back(jsonFormColumnTypesRow);
  ret.push_back(jsonFormVisibleColumnsRow);
  ret.push_back(jsonFormOffsetColumnsRow);
  ret.push_back(jsonFormTooltipOffsetColumnsRow);
  return ret;
}

nlohmann::json Query::getJsonData() {
  nlohmann::json jresult = nlohmann::json::array();

  for (unsigned long row = 0; row < result.size(); row++) {
    nlohmann::json jsonRow;
    auto columns = result.columns();
    for (unsigned long column = 0; column < columns; column++) {
      if (result[row][column].isNull()) {
        nlohmann::json j(nullptr);
        jsonRow[column] = j;
        continue;
      }
      auto ctype = selectedColumns().at(column).column_type;
      switch (ctype) {
        case PG_TYPES::INT4:
        case PG_TYPES::INT8:
          // jsonRow[column] = (long)strtolong(row, column);
          jsonRow[column] = result[row][column].as<long>();
          break;
        case PG_TYPES::BOOL: {
          // jsonRow[column] = strbool(row, column);
          auto r5 = result[row][column].as<std::string>();
          // jsonRow[column] = result[row][column].as<bool>();
          jsonRow[column] = result[row][column].as<std::string>() == "t";
          break;
        }
          //          case PG_TYPES::
        case PG_TYPES::DOUBLE:
          // jsonRow[column] = strbool(row, column);
          jsonRow[column] = result[row][column].as<double>();
          break;
        /*case PG_TYPES::ARRAYINT: {
            auto jsonArray = json(nlohmann::json::array());
            auto ar = result[row][column].as_array();
            auto jnc = ar.get_next();
            while (jnc.first != array_parser::done) {
                if(jnc.first == array_parser::string_value) {
                    int myint = stoi(jnc.second);
                    jsonArray.push_back(myint);
                }
                jnc = ar.get_next();

            }
            jsonRow[column] = jsonArray;
        }
        break;
        case PG_TYPES::ARRAYTEXT: {
            auto jsonArray = json(nlohmann::json::array());
            auto ar = result[row][column].as_array();
            auto jnc = ar.get_next();
            while (jnc.first != array_parser::done) {
                if(jnc.first == array_parser::string_value)
                    jsonArray.push_back(jnc.second);
                jnc = ar.get_next();

            }
            jsonRow[column] = jsonArray;
        }
        break;*/
        case PG_TYPES::PSJSON: {
          auto valin = nlohmann::json::parse(result[row][column].c_str());
          jsonRow[column] = valin;
        } break;
        case PG_TYPES::TEXT:
        default:
          // jsonRow[column] = getValue(row, column);
          jsonRow[column] = result[row][column].c_str();
      }
    }
    jresult.push_back(jsonRow);
  }
  return jresult;
}

nlohmann::json Query::getAllData(nlohmann::json& args) {
  updateFilterBase(args[0]);
  updateSortBase(args[1]);
  updatePaginationBase(args[2]);
  select();
  return getJsonData();
}

void Query::updateFilterBase(nlohmann::json filters) {
  if (filters.is_null() || filters.empty() || !filters.is_array()) {
    return;
  }
  for (unsigned int i = 0; i < filters.size(); i++) {
    //         == json::value_t::string
    std::string v;
    if (filters[i].is_null()) {
      v = "";
    } else if (filters[i].type() == nlohmann::json::value_t::number_integer ||
               filters[i].type() == nlohmann::json::value_t::number_unsigned) {
      v = std::to_string(filters[i].get<long>());
    } else if (filters[i].type() == nlohmann::json::value_t::number_float) {
      v = std::to_string(filters[i].get<float>());
    } else if (filters[i].type() == nlohmann::json::value_t::boolean) {
      v = filters[i].get<bool>() ? "true" : "false";
    } else if (filters[i].type() == nlohmann::json::value_t::string) {
      v = filters[i].get<std::string>();
    } else {
      v = "";
    }
    std::string whereClause = CondFormat::filterToSqlCondition(
        v, selectedColumns().at(i).column_type, "");
    // If the value was set to an empty string remove any filter for this
    // column. Otherwise insert a new filter rule or replace the old one if
    // there is already one
    if (whereClause.empty())
      m_where.erase(static_cast<size_t>(i));
    else
      m_where[static_cast<size_t>(i)] = whereClause;
  }
}

void Query::updateSortBase(nlohmann::json filters) {
  if (filters.is_null() || filters.empty() || !filters.is_array()) {
    return;
  }
  for (unsigned int i = 0; i < filters.size(); i++) {
    if (filters[i].is_null()) {
      continue;
    }
    if (filters[i].get<int>() == 0) {
      m_sort.emplace_back(i, sqlb::Ascending);
    } else {
      m_sort.emplace_back(i, sqlb::Descending);
    }
  }
}

void Query::updatePaginationBase(nlohmann::json filters) {
  if (filters.is_null() || filters.empty() || !filters.is_array()) {
    return;
  }
  if (!filters[0].is_null()) {
    m_pagination.limit = filters[0].get<int>();
  }
  if (!filters[1].is_null()) {
    m_pagination.offset = filters[1].get<int>();
  }
  if (!filters[2].is_null()) {
    m_pagination.current_page = filters[2].get<int>();
  }
}

void Query::updateFilter(int column, const std::string& whereClause) {
  // If the value was set to an empty string remove any filter for this column.
  // Otherwise insert a new filter rule or replace the old one if there is
  // already one
  if (whereClause.empty())
    m_where.erase(static_cast<size_t>(column));
  else
    m_where[static_cast<size_t>(column)] = whereClause;
  // Build the new query
  // buildQuery();

  select();
}

nlohmann::json Query::headerData(nlohmann::json event,
                                 const nlohmann::json& args) {
  nlohmann::json jresult;
  jresult[0] = std::move(event);
  jresult[1] = getJsonHeaderData();
  nlohmann::json ret;
  ret[0] = jresult;
  return ret;
}

nlohmann::json Query::allData(nlohmann::json event, nlohmann::json args) {
  nlohmann::json jresult;
  jresult[0] = std::move(event);
  jresult[1] = getAllData(args);
  nlohmann::json ret;
  ret[0] = jresult;
  return ret;
}

nlohmann::json Query::ins(nlohmann::json event, nlohmann::json args) {
  std::string strSql;
  try {
    strSql = buildInsQuery(std::move(args));
    if (strSql.empty()) {
      nlohmann::json ret;
      ret[0] = simpleJsonSaveResult(event, false, "UnValid Arguments");
      return ret;
    }
  } catch (const std::exception& e) {
    SPDLOG_TRACE("error: {0}, sql: {1}", e.what(), strSql);
    throw;
  }
  try {
    auto clientPtr = drogon::app().getDbClient("sce");
    clientPtr->execSqlSync(strSql);
    nlohmann::json ret;
    ret[0] = simpleJsonSaveResult(event, true, "Done");
    return ret;
  } catch (const std::exception& e) {
    SPDLOG_TRACE("error: {0}, sql: {1}", e.what(), strSql);
    nlohmann::json ret;
    ret[0] = simpleJsonSaveResult(event, false, e.what());
    return ret;
  }
}

nlohmann::json Query::upd(nlohmann::json event, nlohmann::json args) {
  updateFilterBase(args[1]);
  std::string strSql = buildUpdateQuery(args);
  if (strSql.empty()) {
    nlohmann::json ret;
    ret[0] = simpleJsonSaveResult(event, false, "UnValid Arguments");
    return ret;
  }
  try {
    auto clientPtr = drogon::app().getDbClient("sce");
    auto res = clientPtr->execSqlSync(strSql);
    if (res.size() > 1) {
      SPDLOG_TRACE("error: Argus Must update one row");
      throw("not valid arguments");
    }
    nlohmann::json ret;
    ret[0] = simpleJsonSaveResult(event, true, "Done");
    return ret;
  } catch (const std::exception& e) {
    SPDLOG_TRACE("error: {0}, sql: {1}", e.what(), strSql);
    nlohmann::json ret;
    ret[0] = simpleJsonSaveResult(event, false, e.what());
    return ret;
  }
}

nlohmann::json Query::del(nlohmann::json event, nlohmann::json args) {
  try {
    auto clientPtr = drogon::app().getDbClient("sce");
    auto transPtr = clientPtr->newTransaction();
    updateFilterBase(args[0]);
    auto res = Dba::writeInTrans(transPtr, buildDeleteQuery());
    if (res.size() > 1) {
      throw("not valid arguments");
    }
    // affected rows should be returned too.
    // Dba::writeInTrans(transPtr, "DELETE FROM " +
    // m_table.toDisplayString()
    // + " WHERE id = $1", args[0]);
    nlohmann::json ret;
    ret[0] = simpleJsonSaveResult(event, true, "Done");
    return ret;
  } catch (const std::exception& e) {
    SPDLOG_TRACE(e.what());
    nlohmann::json ret;
    ret[0] = simpleJsonSaveResult(event, false, e.what());
    return ret;
  }
}

nlohmann::json Query::count(nlohmann::json event, nlohmann::json args) {
  try {
    auto clientPtr = drogon::app().getDbClient("sce");
    auto transPtr = clientPtr->newTransaction();
    updateFilterBase(args[0]);
    updateSortBase(args[1]);
    updatePaginationBase(args[2]);
    // SPDLOG_TRACE(buildCountQuery());
    auto res = Dba::writeInTrans(transPtr, buildCountQuery());
    // affected rows should be returned too.
    // Dba::writeInTrans(transPtr, "DELETE FROM " +
    // m_table.toDisplayString()
    // + " WHERE id = $1", args[0]);
    nlohmann::json ret;
    ret[0] = nlohmann::json::array({event, res[0]["count"].as<long>()});
    return ret;
  } catch (const std::exception& e) {
    SPDLOG_TRACE(e.what());
    nlohmann::json ret;
    ret[0] = simpleJsonSaveResult(event, false, e.what());
    return ret;
  }
}
}  // namespace sqlb
   /*
    #include "../strfns.h"
   // Convert a number to string using the Unicode superscript characters
   template <class T>
   static std::string toSuperScript(T number) {
     std::string superScript = std::to_string(number);
     ReplaceAll2(superScript, "0", "⁰");
     ReplaceAll2(superScript, "1", "¹");
     ReplaceAll2(superScript, "2", "²");
     ReplaceAll2(superScript, "3", "³");
     ReplaceAll2(superScript, "4", "⁴");
     ReplaceAll2(superScript, "5", "⁵");
     ReplaceAll2(superScript, "6", "⁶");
     ReplaceAll2(superScript, "7", "⁷");
     ReplaceAll2(superScript, "8", "⁸");
     ReplaceAll2(superScript, "9", "⁹");
     return superScript;
   }*/
