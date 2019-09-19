/**
 *
 *  Watchers.h
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
class Watchers
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _watchable_type;
        static const std::string _watchable_id;
        static const std::string _user_id;
    };

    const static int primaryKeyNumber;
    const static std::string tableName;
    const static bool hasPrimaryKey;
    const static std::string primaryKeyName;
    typedef int32_t PrimaryKeyType;
    const PrimaryKeyType &getPrimaryKey() const;
    explicit Watchers(const Row &r) noexcept;
    Watchers() = default;
    
    /**  For column id  */
    ///Get the value of the column id, returns the default value if the column is null
    const int32_t &getValueOfId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getId() const noexcept;

    /**  For column watchable_type  */
    ///Get the value of the column watchable_type, returns the default value if the column is null
    const std::string &getValueOfWatchableType() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getWatchableType() const noexcept;
    ///Set the value of the column watchable_type
    void setWatchableType(const std::string &pWatchableType) noexcept;
    void setWatchableType(std::string &&pWatchableType) noexcept;

    /**  For column watchable_id  */
    ///Get the value of the column watchable_id, returns the default value if the column is null
    const int32_t &getValueOfWatchableId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getWatchableId() const noexcept;
    ///Set the value of the column watchable_id
    void setWatchableId(const int32_t &pWatchableId) noexcept;

    /**  For column user_id  */
    ///Get the value of the column user_id, returns the default value if the column is null
    const int32_t &getValueOfUserId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getUserId() const noexcept;
    ///Set the value of the column user_id
    void setUserId(const int32_t &pUserId) noexcept;


    static size_t getColumnNumber() noexcept {  return 4;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

    Json::Value toJson() const;

  private:
    friend Mapper<Watchers>;
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<int32_t> _id;
    std::shared_ptr<std::string> _watchableType;
    std::shared_ptr<int32_t> _watchableId;
    std::shared_ptr<int32_t> _userId;
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
    bool _dirtyFlag[4]={ false };
};
} // namespace openproject4
} // namespace drogon_model
