/**
 *
 *  LaborBudgetItems.h
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
namespace openproject4 
{
class LaborBudgetItems
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _cost_object_id;
        static const std::string _hours;
        static const std::string _user_id;
        static const std::string _comments;
        static const std::string _budget;
    };

    const static int primaryKeyNumber;
    const static std::string tableName;
    const static bool hasPrimaryKey;
    const static std::string primaryKeyName;
    typedef int32_t PrimaryKeyType;
    const PrimaryKeyType &getPrimaryKey() const;
    explicit LaborBudgetItems(const Row &r) noexcept;
    LaborBudgetItems() = default;
    
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

    /**  For column hours  */
    ///Get the value of the column hours, returns the default value if the column is null
    const double &getValueOfHours() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<double> &getHours() const noexcept;
    ///Set the value of the column hours
    void setHours(const double &pHours) noexcept;

    /**  For column user_id  */
    ///Get the value of the column user_id, returns the default value if the column is null
    const int32_t &getValueOfUserId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getUserId() const noexcept;
    ///Set the value of the column user_id
    void setUserId(const int32_t &pUserId) noexcept;

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

  private:
    friend Mapper<LaborBudgetItems>;
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<int32_t> _id;
    std::shared_ptr<int32_t> _costObjectId;
    std::shared_ptr<double> _hours;
    std::shared_ptr<int32_t> _userId;
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
};
} // namespace openproject4
} // namespace drogon_model
