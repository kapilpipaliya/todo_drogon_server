/**
 *
 *  GridWidgets.h
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#pragma once
#include <drogon/orm/Result.h>
#include <drogon/orm/Row.h>
#include <drogon/orm/Field.h>
#include <drogon/orm/SqlBinder.h>
#include <drogon/orm/Mapper.h>
#include <trantor/utils/Date.h>
#include <json/json.h>
#include <string>
#include <memory>
#include <vector>
#include <tuple>
#include <stdint.h>
#include <iostream>

using namespace drogon::orm;

namespace drogon_model
{
namespace openproject6 
{
class GridWidgets
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _start_row;
        static const std::string _end_row;
        static const std::string _start_column;
        static const std::string _end_column;
        static const std::string _identifier;
        static const std::string _options;
        static const std::string _grid_id;
    };

    const static int primaryKeyNumber;
    const static std::string tableName;
    const static bool hasPrimaryKey;
    const static std::string primaryKeyName;
    typedef int64_t PrimaryKeyType;
    const PrimaryKeyType &getPrimaryKey() const;

    /**
     * @brief constructor
     * @param r One row of records in the SQL query result.
     * @param indexOffset Set the offset to -1 to access all columns by column names, 
     * otherwise access all columns by offsets.
     * @note If the SQL is not a style of 'select * from table_name ...' (select all 
     * columns by an asterisk), please set the offset to -1.
     */
    explicit GridWidgets(const Row &r, const ssize_t indexOffset = 0) noexcept;

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     */
    explicit GridWidgets(const Json::Value &pJson) noexcept(false);

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     * @param pMasqueradingVector The aliases of table columns.
     */
    GridWidgets(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false);

    GridWidgets() = default;
    
    void updateByJson(const Json::Value &pJson) noexcept(false);
    void updateByMasqueradedJson(const Json::Value &pJson,
                                 const std::vector<std::string> &pMasqueradingVector) noexcept(false);
    bool validateJsonForCreation(const Json::Value &pJson, std::string &err);
    bool validateMasqueradedJsonForCreation(const Json::Value &,
                                            const std::vector<std::string> &pMasqueradingVector,
                                            std::string &err);
    bool validateJsonForUpdate(const Json::Value &pJson, std::string &err);
    bool validateMasqueradedJsonForUpdate(const Json::Value &,
                                          const std::vector<std::string> &pMasqueradingVector,
                                          std::string &err);
    bool validJsonOfField(size_t index,
                          const std::string &fieldName,
                          const Json::Value &pJson, 
                          std::string &err, 
                          bool isForCreation);

    /**  For column id  */
    ///Get the value of the column id, returns the default value if the column is null
    const int64_t &getValueOfId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int64_t> &getId() const noexcept;

    /**  For column start_row  */
    ///Get the value of the column start_row, returns the default value if the column is null
    const int32_t &getValueOfStartRow() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getStartRow() const noexcept;
    ///Set the value of the column start_row
    void setStartRow(const int32_t &pStartRow) noexcept;

    /**  For column end_row  */
    ///Get the value of the column end_row, returns the default value if the column is null
    const int32_t &getValueOfEndRow() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getEndRow() const noexcept;
    ///Set the value of the column end_row
    void setEndRow(const int32_t &pEndRow) noexcept;

    /**  For column start_column  */
    ///Get the value of the column start_column, returns the default value if the column is null
    const int32_t &getValueOfStartColumn() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getStartColumn() const noexcept;
    ///Set the value of the column start_column
    void setStartColumn(const int32_t &pStartColumn) noexcept;

    /**  For column end_column  */
    ///Get the value of the column end_column, returns the default value if the column is null
    const int32_t &getValueOfEndColumn() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getEndColumn() const noexcept;
    ///Set the value of the column end_column
    void setEndColumn(const int32_t &pEndColumn) noexcept;

    /**  For column identifier  */
    ///Get the value of the column identifier, returns the default value if the column is null
    const std::string &getValueOfIdentifier() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getIdentifier() const noexcept;
    ///Set the value of the column identifier
    void setIdentifier(const std::string &pIdentifier) noexcept;
    void setIdentifier(std::string &&pIdentifier) noexcept;

    /**  For column options  */
    ///Get the value of the column options, returns the default value if the column is null
    const std::string &getValueOfOptions() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getOptions() const noexcept;
    ///Set the value of the column options
    void setOptions(const std::string &pOptions) noexcept;
    void setOptions(std::string &&pOptions) noexcept;

    /**  For column grid_id  */
    ///Get the value of the column grid_id, returns the default value if the column is null
    const int64_t &getValueOfGridId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int64_t> &getGridId() const noexcept;
    ///Set the value of the column grid_id
    void setGridId(const int64_t &pGridId) noexcept;


    static size_t getColumnNumber() noexcept {  return 8;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

    Json::Value toJson() const;
    Json::Value toMasqueradedJson(const std::vector<std::string> &pMasqueradingVector) const;

  private:
    friend Mapper<GridWidgets>;
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<int64_t> _id;
    std::shared_ptr<int32_t> _startRow;
    std::shared_ptr<int32_t> _endRow;
    std::shared_ptr<int32_t> _startColumn;
    std::shared_ptr<int32_t> _endColumn;
    std::shared_ptr<std::string> _identifier;
    std::shared_ptr<std::string> _options;
    std::shared_ptr<int64_t> _gridId;
    struct MetaData
    {
        const std::string _colName;
        const std::string _colType;
        const std::string _colDatabaseType;
        const ssize_t _colLength;
        const bool _isAutoVal;
        const bool _isPrimaryKey;
        const bool _notNull;
    };
    static const std::vector<MetaData> _metaData;
    bool _dirtyFlag[8]={ false };

  public:
    static const std::string &sqlForFindingByPrimaryKey()
    {
        static const std::string sql="select * from " + tableName + " where id = $1";
        return sql;                   
    }

    static const std::string &sqlForDeletingByPrimaryKey()
    {
        static const std::string sql="delete from " + tableName + " where id = $1";
        return sql;                   
    }

    static const std::string &sqlForInserting()
    {
        static const std::string sql="insert into " + tableName + " (start_row,end_row,start_column,end_column,identifier,options,grid_id) values ($1,$2,$3,$4,$5,$6,$7) returning *";
        return sql;   
    }
};
} // namespace openproject6
} // namespace drogon_model
