#ifndef TABLE_H
#define TABLE_H

#include <memory>
#include <vector>

#include "core/sql/objectidentifier.h"
#include "core/sql/query.h"

#include <json/json.h>
#include <drogon/orm/DbClient.h>
using namespace drogon::orm;

class Table
{
public:
    explicit Table();
    virtual ~Table();
    //in the subclass, you actuallly don't need to mark the overriden methods as slots.
public:
    virtual bool select();
    /// reset to state after construction
    virtual void reset();
    virtual int rowCount() const;
    virtual int columnCount() const;
    virtual void clear();
    virtual std::string &lastError() const;
    virtual const char *columnName(int columnNumber) const;
    virtual bool isEditableColumn(int column) const;
    virtual void sort(const std::vector<sqlb::SortedColumn>& columns);
    virtual std::string getHeaderName(const int column) const;
    Json::Value getJsonHeaderData();
    Json::Value getJsonData();
    size_t filterCount() const;
    sqlb::ObjectIdentifier currentTableName() const { return m_query.table(); }
    bool hasPseudoPk() const;
    //bool isBinary(const QModelIndex& index) const;
    // Add quotes to an identifier
    //std::string escapeIdentifier2(const std::string& id);
    Json::Value getAllData(Json::Value &args);
public:
    sqlb::ObjectIdentifier m_table;
    sqlb::Query m_query;
    std::string m_sQuery;
    bool saveCache = false;
    std::string insertError;

    void updateFilterBase(Json::Value filters);
    void updateSortBase(Json::Value filters);
    void updatePaginationBase(Json::Value filters);
    void updateFilter(int column, const std::string& whereClause);

    drogon::orm::Result result{nullptr};
};
#endif // TABLE_H
