#ifndef QUERY_H
#define QUERY_H

#include "objectidentifier.h"

#include <string>
#include <unordered_map>
#include <utility>
#include <vector>
#include "json.hpp"
#include "spdlogfix.h"

#include <drogon/drogon.h>
#include "../jsonfns.h"

#include "json.hpp"

enum PG_TYPES {
  BOOL = 16,
  //    ByTea = 17,
  //    Char = 18,
  INT8 = 20,
  INT4 = 23,
  TEXT = 25,
  //  JSON = 114,
  XML = 142,
  DOUBLE = 701,
  TIMESTAMP = 1114,
  ENUM = 64000,
  // ARRAYINT = 9997, // fix
  // ARRAYTEXT = 9998, // fix
  PSJSON = 9999
};

inline std::string ins_(const std::string& t, const std::string& c,
                        const std::string& v) {
  return "INSERT INTO " + t + " (" + c + ") VALUES (" + v + ")";
}
inline std::string upd_(const std::string& t, const std::string& c,
                        const std::string& v, const std::string& w) {
  return "UPDATE " + t + " SET (" + c + ") = ROW (" + v + ")" + w;
}
inline std::string sel_(const std::string& t, const std::string& c,
                        const std::string& w) {
  return "SELECT " + c + " FROM " + t + " " + w;
}
inline std::string dele_(const std::string& t, const std::string& w) {
  return "DELETE FROM " + t + " " + w;
}

/*
 * This file's classes should not talk to database directly
 * */
namespace sql {

enum SortDirection { Ascending, Descending };

struct SortedColumn {
  SortedColumn(size_t column_, SortDirection direction_)
      : column(column_), direction(direction_) {}

  bool operator==(const SortedColumn& rhs) const {
    return column == rhs.column && direction == rhs.direction;
  }

  size_t column;
  SortDirection direction;
};
struct GroupByColumn {
  GroupByColumn(std::string prefix_, std::string column_)
      : prefix(std::move(prefix_)), column(std::move(column_)) {}

  bool operator==(const GroupByColumn& rhs) const {
    return column == rhs.column && prefix == rhs.prefix;
  }

  std::string prefix;
  std::string column;
};

struct SelectedColumn {
  std::string original_column;
  std::string selector;
  std::string calculated;
  std::string prefix;
  PG_TYPES column_type;
  bool isVisible = true;
  int offset = 0;
  int tooltipOffset = 0;
  bool isEditable = true;
};
struct Join {
  Join(std::string join_type, ObjectIdentifier table, std::string condition)
      : m_table(std::move(table)),
        join_type(std::move(join_type)),
        condition(std::move(condition)) {}
  Join(std::string join_type, std::string lateral, std::string condition)
      : lateral(std::move(lateral)),
        join_type(std::move(join_type)),
        condition(std::move(condition)) {}

  ObjectIdentifier m_table;
  std::string lateral;
  std::string join_type;
  std::string condition;
};
struct SubQuery {
  std::string alias;
  std::vector<SelectedColumn> columns;
};
struct Pagination {
  int limit = 0;
  int offset = 0;
  int current_page = 0;
};

class Query {
 public:
  Query() = default;
  explicit Query(ObjectIdentifier table) : m_table(std::move(table)) {}

  void clear();
  std::string buildQuery(bool withRowid) const;
  std::string buildCountQuery() const;
  std::string buildDeleteQuery() const;
  std::string buildInsQuery(nlohmann::json args) const;
  std::string buildUpdateQuery(nlohmann::json args) const;
  std::string buildUpdateQuery(const std::string& column,
                               const std::string& values,
                               const std::string& where_) const;

  // void setColumNames(const std::vector<std::string>& column_names) {
  // m_column_names = column_names; } std::vector<std::string> columnNames()
  // const { return m_column_names; }

  void setTable(const ObjectIdentifier& table) { m_table = table; }
  ObjectIdentifier table() const { return m_table; }

  // void setRowIdColumns(const std::vector<std::string>& rowids) {
  // m_rowid_columns = rowids; } std::vector<std::string> rowIdColumns() const {
  // return m_rowid_columns; } void setRowIdColumn(const std::string& rowid) {
  // m_rowid_columns = {rowid}; } bool hasCustomRowIdColumn() const { return
  // m_rowid_columns.size() != 1 || (m_rowid_columns.at(0) != "rowid" &&
  // m_rowid_columns.at(0) != "_rowid_"); }

  const std::vector<SelectedColumn>& selectedColumns() const {
    return m_selected_columns;
  }
  void setSelectedColumns(std::vector<SelectedColumn> columns) {
    m_selected_columns = columns;
  }

  const std::vector<Join>& joins() { return m_joins; }
  void setJoins(const std::vector<Join>& join) { m_joins = join; }
  const std::unordered_map<size_t, std::string>& where() const {
    return m_where;
  }
  void setWhere(const std::unordered_map<size_t, std::string>& where) {
    m_where = where;
  }
  const std::vector<SortedColumn>& orderBy() const { return m_sort; }
  void setOrderBy(const std::vector<SortedColumn>& columns) {
    m_sort = columns;
  }
  const Pagination& pagination() { return m_pagination; }
  void setPagination(const Pagination& p) { m_pagination = p; }
  const std::vector<GroupByColumn>& groupBy() const { return m_group; }
  void setGroupBy(const std::vector<GroupByColumn>& columns) {
    m_group = columns;
  }
  const SubQuery& subquery() const { return m_subquery; }
  void setSubquery(const SubQuery& query) { m_subquery = query; }
  const std::string& cusm_where() { return m_custm_where; }
  void setCustomWhere(const std::string& custom) { m_custm_where = custom; }
  size_t filterCount() const;
  bool select();
  std::string getHeaderName(unsigned long column) const;
  void sort(const std::vector<SortedColumn>& columns);

  nlohmann::json getJsonHeaderData();
  nlohmann::json getJsonData();

  nlohmann::json getAllData(nlohmann::json& args);

  void updateFilterBase(nlohmann::json filters);
  void updateSortBase(nlohmann::json filters);
  void updatePaginationBase(nlohmann::json filters);
  void updateFilter(int column, const std::string& whereClause);

  nlohmann::json headerData(nlohmann::json event, const nlohmann::json& args);
  nlohmann::json allData(nlohmann::json event, nlohmann::json args);
  nlohmann::json ins(nlohmann::json event, nlohmann::json args);
  nlohmann::json upd(nlohmann::json event, nlohmann::json args);
  nlohmann::json del(nlohmann::json event, nlohmann::json args);
  nlohmann::json count(nlohmann::json event, nlohmann::json args);
  // std::string quote(std::string s){return "'" + addslashes(s) + "'";}
  // std::string quoteForLike(std::string format, std::string s) {return '\''.
  // sprintf($format, $s). '\'';}
  // bool table_exists(std::string table) {}

  template <class... Args>
  nlohmann::json insBase(const nlohmann::json& event,
                         const nlohmann::json& /*args*/,
                         const std::string& column, const std::string& values,
                         Args... args_bind) {
    std::string strSql = "INSERT INTO " + table().toString() + " (" + column +
                         ") values(" + values + ")";

    try {
      auto clientPtr = drogon::app().getDbClient("sce");
      clientPtr->execSqlSync(strSql, args_bind...);
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

  template <class... Args>
  nlohmann::json updBase(const nlohmann::json& event, nlohmann::json args,
                         const std::string& column, const std::string& values,
                         Args... args_bind) {
    updateFilterBase(args[1]);
    std::string strSql = buildUpdateQuery(column, values, "");
    try {
      auto clientPtr = drogon::app().getDbClient("sce");
      clientPtr->execSqlSync(strSql, args_bind...);
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

 private:
  // std::vector<std::string> m_column_names;
  ObjectIdentifier m_table;
  // std::vector<std::string> m_rowid_columns;
  std::vector<SelectedColumn> m_selected_columns;
  std::unordered_map<size_t, std::string> m_where;
  std::vector<SortedColumn> m_sort;
  std::vector<GroupByColumn> m_group;
  std::vector<Join> m_joins;
  Pagination m_pagination;
  SubQuery m_subquery;
  std::string m_custm_where{""};
  drogon::orm::Result result{nullptr};

  std::vector<SelectedColumn>::iterator findSelectedColumnByName(
      const std::string& name);
  std::vector<SelectedColumn>::const_iterator findSelectedColumnByName(
      const std::string& name) const;
  std::vector<SelectedColumn>::iterator findSelectedColumnBySelector(
      const std::string& name);
  std::vector<SelectedColumn>::const_iterator findSelectedColumnBySelector(
      const std::string& name) const;
  std::string buildWherePart() const;
  std::string buildJoinPart() const;
  std::string buildGroupByPart() const;
  std::string buildOrderByByPart() const;
  std::string buildPaginationPart() const;
  std::string buildSelectorPart(
      std::vector<SelectedColumn>& m_selected_columns_) const;
};

}  // namespace sql

#endif
