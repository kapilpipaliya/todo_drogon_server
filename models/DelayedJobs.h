/**
 *
 *  DelayedJobs.h
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
class DelayedJobs
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _priority;
        static const std::string _attempts;
        static const std::string _handler;
        static const std::string _last_error;
        static const std::string _run_at;
        static const std::string _locked_at;
        static const std::string _failed_at;
        static const std::string _locked_by;
        static const std::string _created_at;
        static const std::string _updated_at;
        static const std::string _queue;
    };

    const static int primaryKeyNumber;
    const static std::string tableName;
    const static bool hasPrimaryKey;
    const static std::string primaryKeyName;
    typedef int32_t PrimaryKeyType;
    const PrimaryKeyType &getPrimaryKey() const;
    explicit DelayedJobs(const Row &r) noexcept;
    DelayedJobs() = default;
    
    /**  For column id  */
    ///Get the value of the column id, returns the default value if the column is null
    const int32_t &getValueOfId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getId() const noexcept;

    /**  For column priority  */
    ///Get the value of the column priority, returns the default value if the column is null
    const int32_t &getValueOfPriority() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getPriority() const noexcept;
    ///Set the value of the column priority
    void setPriority(const int32_t &pPriority) noexcept;

    /**  For column attempts  */
    ///Get the value of the column attempts, returns the default value if the column is null
    const int32_t &getValueOfAttempts() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getAttempts() const noexcept;
    ///Set the value of the column attempts
    void setAttempts(const int32_t &pAttempts) noexcept;

    /**  For column handler  */
    ///Get the value of the column handler, returns the default value if the column is null
    const std::string &getValueOfHandler() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getHandler() const noexcept;
    ///Set the value of the column handler
    void setHandler(const std::string &pHandler) noexcept;
    void setHandler(std::string &&pHandler) noexcept;

    /**  For column last_error  */
    ///Get the value of the column last_error, returns the default value if the column is null
    const std::string &getValueOfLastError() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getLastError() const noexcept;
    ///Set the value of the column last_error
    void setLastError(const std::string &pLastError) noexcept;
    void setLastError(std::string &&pLastError) noexcept;

    /**  For column run_at  */
    ///Get the value of the column run_at, returns the default value if the column is null
    const ::trantor::Date &getValueOfRunAt() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<::trantor::Date> &getRunAt() const noexcept;
    ///Set the value of the column run_at
    void setRunAt(const ::trantor::Date &pRunAt) noexcept;

    /**  For column locked_at  */
    ///Get the value of the column locked_at, returns the default value if the column is null
    const ::trantor::Date &getValueOfLockedAt() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<::trantor::Date> &getLockedAt() const noexcept;
    ///Set the value of the column locked_at
    void setLockedAt(const ::trantor::Date &pLockedAt) noexcept;

    /**  For column failed_at  */
    ///Get the value of the column failed_at, returns the default value if the column is null
    const ::trantor::Date &getValueOfFailedAt() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<::trantor::Date> &getFailedAt() const noexcept;
    ///Set the value of the column failed_at
    void setFailedAt(const ::trantor::Date &pFailedAt) noexcept;

    /**  For column locked_by  */
    ///Get the value of the column locked_by, returns the default value if the column is null
    const std::string &getValueOfLockedBy() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getLockedBy() const noexcept;
    ///Set the value of the column locked_by
    void setLockedBy(const std::string &pLockedBy) noexcept;
    void setLockedBy(std::string &&pLockedBy) noexcept;

    /**  For column created_at  */
    ///Get the value of the column created_at, returns the default value if the column is null
    const ::trantor::Date &getValueOfCreatedAt() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<::trantor::Date> &getCreatedAt() const noexcept;
    ///Set the value of the column created_at
    void setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept;

    /**  For column updated_at  */
    ///Get the value of the column updated_at, returns the default value if the column is null
    const ::trantor::Date &getValueOfUpdatedAt() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<::trantor::Date> &getUpdatedAt() const noexcept;
    ///Set the value of the column updated_at
    void setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept;

    /**  For column queue  */
    ///Get the value of the column queue, returns the default value if the column is null
    const std::string &getValueOfQueue() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getQueue() const noexcept;
    ///Set the value of the column queue
    void setQueue(const std::string &pQueue) noexcept;
    void setQueue(std::string &&pQueue) noexcept;


    static size_t getColumnNumber() noexcept {  return 12;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

    Json::Value toJson() const;

  private:
    friend Mapper<DelayedJobs>;
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<int32_t> _id;
    std::shared_ptr<int32_t> _priority;
    std::shared_ptr<int32_t> _attempts;
    std::shared_ptr<std::string> _handler;
    std::shared_ptr<std::string> _lastError;
    std::shared_ptr<::trantor::Date> _runAt;
    std::shared_ptr<::trantor::Date> _lockedAt;
    std::shared_ptr<::trantor::Date> _failedAt;
    std::shared_ptr<std::string> _lockedBy;
    std::shared_ptr<::trantor::Date> _createdAt;
    std::shared_ptr<::trantor::Date> _updatedAt;
    std::shared_ptr<std::string> _queue;
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
    bool _dirtyFlag[12]={ false };
};
} // namespace openproject4
} // namespace drogon_model
