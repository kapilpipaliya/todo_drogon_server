/**
 *
 *  MaterialBudgetItems.h
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
class MaterialBudgetItems
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _cost_object_id;
        static const std::string _units;
        static const std::string _cost_type_id;
        static const std::string _comments;
        static const std::string _budget;
    };

    const static int primaryKeyNumber;
    const static std::string tableName;
    const static bool hasPrimaryKey;
    const static std::string primaryKeyName;
    typedef int32_t PrimaryKeyType;
    const PrimaryKeyType &getPrimaryKey() const;

    /**
     * @brief constructor
     * @param r One row of records in the SQL query result.
     * @param indexOffset Set the offset to -1 to access all columns by column names, 
     * otherwise access all columns by offsets.
     * @note If the SQL is not a style of 'select * from table_name ...' (select all 
     * columns by an asterisk), please set the offset to -1.
     */
    explicit MaterialBudgetItems(const Row &r, const ssize_t indexOffset = 0) noexcept;

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     */
    explicit MaterialBudgetItems(const Json::Value &pJson) noexcept(false);

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     * @param pMasqueradingVector The aliases of table columns.
     */
    MaterialBudgetItems(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false);

    MaterialBudgetItems() = default;
    
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
    const int32_t &getValueOfId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getId() const noexcept;

    /**  For column cost_object_id  */
    ///Get the value of the column cost_object_id, returns the default value if the column is null
    const int32_t &getValueOfCostObjectId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getCostObjectId() const noexcept;
    ///Set the value of the column cost_object_id
    void setCostObjectId(const int32_t &pCostObjectId) noexcept;

    /**  For column units  */
    ///Get the value of the column units, returns the default value if the column is null
    const double &getValueOfUnits() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<double> &getUnits() const noexcept;
    ///Set the value of the column units
    void setUnits(const double &pUnits) noexcept;

    /**  For column cost_type_id  */
    ///Get the value of the column cost_type_id, returns the default value if the column is null
    const int32_t &getValueOfCostTypeId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getCostTypeId() const noexcept;
    ///Set the value of the column cost_type_id
    void setCostTypeId(const int32_t &pCostTypeId) noexcept;

    /**  For column comments  */
    ///Get the value of the column comments, returns the default value if the column is null
    const std::string &getValueOfComments() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getComments() const noexcept;
    ///Set the value of the column comments
    void setComments(const std::string &pComments) noexcept;
    void setComments(std::string &&pComments) noexcept;

    /**  For column budget  */
    ///Get the value of the column budget, returns the default value if the column is null
    const int64_t &getValueOfBudget() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int64_t> &getBudget() const noexcept;
    ///Set the value of the column budget
    void setBudget(const int64_t &pBudget) noexcept;


    static size_t getColumnNumber() noexcept {  return 6;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

    Json::Value toJson() const;
    Json::Value toMasqueradedJson(const std::vector<std::string> &pMasqueradingVector) const;

  private:
    friend Mapper<MaterialBudgetItems>;
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<int32_t> _id;
    std::shared_ptr<int32_t> _costObjectId;
    std::shared_ptr<double> _units;
    std::shared_ptr<int32_t> _costTypeId;
    std::shared_ptr<std::string> _comments;
    std::shared_ptr<int64_t> _budget;
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
    bool _dirtyFlag[6]={ false };

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
        static const std::string sql="insert into " + tableName + " (cost_object_id,units,cost_type_id,comments,budget) values ($1,$2,$3,$4,$5) returning *";
        return sql;   
    }
};
} // namespace openproject6
} // namespace drogon_model
