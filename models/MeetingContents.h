/**
 *
 *  MeetingContents.h
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
class MeetingContents
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _type;
        static const std::string _meeting_id;
        static const std::string _author_id;
        static const std::string _text;
        static const std::string _lock_version;
        static const std::string _created_at;
        static const std::string _updated_at;
        static const std::string _locked;
    };

    const static int primaryKeyNumber;
    const static std::string tableName;
    const static bool hasPrimaryKey;
    const static std::string primaryKeyName;
    typedef int32_t PrimaryKeyType;
    const PrimaryKeyType &getPrimaryKey() const;
    explicit MeetingContents(const Row &r) noexcept;
    MeetingContents() = default;
    
    /**  For column id  */
    ///Get the value of the column id, returns the default value if the column is null
    const int32_t &getValueOfId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getId() const noexcept;

    /**  For column type  */
    ///Get the value of the column type, returns the default value if the column is null
    const std::string &getValueOfType() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getType() const noexcept;
    ///Set the value of the column type
    void setType(const std::string &pType) noexcept;
    void setType(std::string &&pType) noexcept;

    /**  For column meeting_id  */
    ///Get the value of the column meeting_id, returns the default value if the column is null
    const int32_t &getValueOfMeetingId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getMeetingId() const noexcept;
    ///Set the value of the column meeting_id
    void setMeetingId(const int32_t &pMeetingId) noexcept;

    /**  For column author_id  */
    ///Get the value of the column author_id, returns the default value if the column is null
    const int32_t &getValueOfAuthorId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getAuthorId() const noexcept;
    ///Set the value of the column author_id
    void setAuthorId(const int32_t &pAuthorId) noexcept;

    /**  For column text  */
    ///Get the value of the column text, returns the default value if the column is null
    const std::string &getValueOfText() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getText() const noexcept;
    ///Set the value of the column text
    void setText(const std::string &pText) noexcept;
    void setText(std::string &&pText) noexcept;

    /**  For column lock_version  */
    ///Get the value of the column lock_version, returns the default value if the column is null
    const int32_t &getValueOfLockVersion() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getLockVersion() const noexcept;
    ///Set the value of the column lock_version
    void setLockVersion(const int32_t &pLockVersion) noexcept;

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

    /**  For column locked  */
    ///Get the value of the column locked, returns the default value if the column is null
    const bool &getValueOfLocked() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<bool> &getLocked() const noexcept;
    ///Set the value of the column locked
    void setLocked(const bool &pLocked) noexcept;


    static size_t getColumnNumber() noexcept {  return 9;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

    Json::Value toJson() const;

  private:
    friend Mapper<MeetingContents>;
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<int32_t> _id;
    std::shared_ptr<std::string> _type;
    std::shared_ptr<int32_t> _meetingId;
    std::shared_ptr<int32_t> _authorId;
    std::shared_ptr<std::string> _text;
    std::shared_ptr<int32_t> _lockVersion;
    std::shared_ptr<::trantor::Date> _createdAt;
    std::shared_ptr<::trantor::Date> _updatedAt;
    std::shared_ptr<bool> _locked;
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
    bool _dirtyFlag[9]={ false };
};
} // namespace openproject4
} // namespace drogon_model
