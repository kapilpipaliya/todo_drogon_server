/**
 *
 *  CustomActionsRoles.h
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
class CustomActionsRoles
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _role_id;
        static const std::string _custom_action_id;
    };

    const static int primaryKeyNumber;
    const static std::string tableName;
    const static bool hasPrimaryKey;
    const static std::string primaryKeyName;
    typedef int32_t PrimaryKeyType;
    const PrimaryKeyType &getPrimaryKey() const;
    explicit CustomActionsRoles(const Row &r) noexcept;
    CustomActionsRoles() = default;
    
    /**  For column id  */
    ///Get the value of the column id, returns the default value if the column is null
    const int32_t &getValueOfId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getId() const noexcept;

    /**  For column role_id  */
    ///Get the value of the column role_id, returns the default value if the column is null
    const int64_t &getValueOfRoleId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int64_t> &getRoleId() const noexcept;
    ///Set the value of the column role_id
    void setRoleId(const int64_t &pRoleId) noexcept;

    /**  For column custom_action_id  */
    ///Get the value of the column custom_action_id, returns the default value if the column is null
    const int64_t &getValueOfCustomActionId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int64_t> &getCustomActionId() const noexcept;
    ///Set the value of the column custom_action_id
    void setCustomActionId(const int64_t &pCustomActionId) noexcept;


    static size_t getColumnNumber() noexcept {  return 3;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

    Json::Value toJson() const;

  private:
    friend Mapper<CustomActionsRoles>;
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<int32_t> _id;
    std::shared_ptr<int64_t> _roleId;
    std::shared_ptr<int64_t> _customActionId;
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
    bool _dirtyFlag[3]={ false };
};
} // namespace openproject4
} // namespace drogon_model
