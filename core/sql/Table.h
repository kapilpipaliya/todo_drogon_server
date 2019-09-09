#ifndef TABLE_H
#define TABLE_H

#include <memory>
#include <vector>

#include "objectidentifier.h"
#include "query.h"

#include "json.hpp"
using nlohmann::json;

#include <drogon/orm/DbClient.h>
using namespace drogon::orm;

class Table {
 public:
  explicit Table();
  virtual ~Table();
  // in the subclass, you actuallly don't need to mark the overriden methods as
  virtual bool select();
  /// reset to state after construction
  virtual void reset();
  virtual unsigned long rowCount() const;
  virtual unsigned long columnCount() const;
  virtual void clear();
  virtual const char* columnName(unsigned long columnNumber) const;
  virtual bool isEditableColumn(unsigned long column) const;
  virtual void sort(const std::vector<sqlb::SortedColumn>& columns);
  virtual std::string getHeaderName(const unsigned long column) const;

  json getJsonHeaderData();
  json getJsonData();
  size_t filterCount() const;
  sqlb::ObjectIdentifier currentTableName() const { return m_query.table(); }
  bool hasPseudoPk() const;
  // bool isBinary(const QModelIndex& index) const;
  // Add quotes to an identifier
  // std::string escapeIdentifier2(const std::string& id);
  json getAllData(json& args);

  void updateFilterBase(json filters);
  void updateSortBase(json filters);
  void updatePaginationBase(json filters);
  void updateFilter(int column, const std::string& whereClause);
  sqlb::Query& query() { return m_query; }

 private:
  sqlb::Query m_query;
  drogon::orm::Result result{nullptr};
};
#endif  // TABLE_H
