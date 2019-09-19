/**
 *
 *  Messages.h
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
class Messages
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _forum_id;
        static const std::string _parent_id;
        static const std::string _subject;
        static const std::string _content;
        static const std::string _author_id;
        static const std::string _replies_count;
        static const std::string _last_reply_id;
        static const std::string _created_on;
        static const std::string _updated_on;
        static const std::string _locked;
        static const std::string _sticky;
        static const std::string _sticked_on;
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
    explicit Messages(const Row &r, const ssize_t indexOffset = 0) noexcept;

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     */
    explicit Messages(const Json::Value &pJson) noexcept(false);

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     * @param pMasqueradingVector The aliases of table columns.
     */
    Messages(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false);

    Messages() = default;
    
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

    /**  For column forum_id  */
    ///Get the value of the column forum_id, returns the default value if the column is null
    const int32_t &getValueOfForumId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getForumId() const noexcept;
    ///Set the value of the column forum_id
    void setForumId(const int32_t &pForumId) noexcept;

    /**  For column parent_id  */
    ///Get the value of the column parent_id, returns the default value if the column is null
    const int32_t &getValueOfParentId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getParentId() const noexcept;
    ///Set the value of the column parent_id
    void setParentId(const int32_t &pParentId) noexcept;

    /**  For column subject  */
    ///Get the value of the column subject, returns the default value if the column is null
    const std::string &getValueOfSubject() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getSubject() const noexcept;
    ///Set the value of the column subject
    void setSubject(const std::string &pSubject) noexcept;
    void setSubject(std::string &&pSubject) noexcept;

    /**  For column content  */
    ///Get the value of the column content, returns the default value if the column is null
    const std::string &getValueOfContent() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getContent() const noexcept;
    ///Set the value of the column content
    void setContent(const std::string &pContent) noexcept;
    void setContent(std::string &&pContent) noexcept;

    /**  For column author_id  */
    ///Get the value of the column author_id, returns the default value if the column is null
    const int32_t &getValueOfAuthorId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getAuthorId() const noexcept;
    ///Set the value of the column author_id
    void setAuthorId(const int32_t &pAuthorId) noexcept;

    /**  For column replies_count  */
    ///Get the value of the column replies_count, returns the default value if the column is null
    const int32_t &getValueOfRepliesCount() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getRepliesCount() const noexcept;
    ///Set the value of the column replies_count
    void setRepliesCount(const int32_t &pRepliesCount) noexcept;

    /**  For column last_reply_id  */
    ///Get the value of the column last_reply_id, returns the default value if the column is null
    const int32_t &getValueOfLastReplyId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getLastReplyId() const noexcept;
    ///Set the value of the column last_reply_id
    void setLastReplyId(const int32_t &pLastReplyId) noexcept;

    /**  For column created_on  */
    ///Get the value of the column created_on, returns the default value if the column is null
    const ::trantor::Date &getValueOfCreatedOn() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<::trantor::Date> &getCreatedOn() const noexcept;
    ///Set the value of the column created_on
    void setCreatedOn(const ::trantor::Date &pCreatedOn) noexcept;

    /**  For column updated_on  */
    ///Get the value of the column updated_on, returns the default value if the column is null
    const ::trantor::Date &getValueOfUpdatedOn() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<::trantor::Date> &getUpdatedOn() const noexcept;
    ///Set the value of the column updated_on
    void setUpdatedOn(const ::trantor::Date &pUpdatedOn) noexcept;

    /**  For column locked  */
    ///Get the value of the column locked, returns the default value if the column is null
    const bool &getValueOfLocked() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<bool> &getLocked() const noexcept;
    ///Set the value of the column locked
    void setLocked(const bool &pLocked) noexcept;

    /**  For column sticky  */
    ///Get the value of the column sticky, returns the default value if the column is null
    const int32_t &getValueOfSticky() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getSticky() const noexcept;
    ///Set the value of the column sticky
    void setSticky(const int32_t &pSticky) noexcept;

    /**  For column sticked_on  */
    ///Get the value of the column sticked_on, returns the default value if the column is null
    const ::trantor::Date &getValueOfStickedOn() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<::trantor::Date> &getStickedOn() const noexcept;
    ///Set the value of the column sticked_on
    void setStickedOn(const ::trantor::Date &pStickedOn) noexcept;


    static size_t getColumnNumber() noexcept {  return 13;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

    Json::Value toJson() const;
    Json::Value toMasqueradedJson(const std::vector<std::string> &pMasqueradingVector) const;

  private:
    friend Mapper<Messages>;
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<int32_t> _id;
    std::shared_ptr<int32_t> _forumId;
    std::shared_ptr<int32_t> _parentId;
    std::shared_ptr<std::string> _subject;
    std::shared_ptr<std::string> _content;
    std::shared_ptr<int32_t> _authorId;
    std::shared_ptr<int32_t> _repliesCount;
    std::shared_ptr<int32_t> _lastReplyId;
    std::shared_ptr<::trantor::Date> _createdOn;
    std::shared_ptr<::trantor::Date> _updatedOn;
    std::shared_ptr<bool> _locked;
    std::shared_ptr<int32_t> _sticky;
    std::shared_ptr<::trantor::Date> _stickedOn;
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
    bool _dirtyFlag[13]={ false };

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
        static const std::string sql="insert into " + tableName + " (forum_id,parent_id,subject,content,author_id,replies_count,last_reply_id,created_on,updated_on,locked,sticky,sticked_on) values ($1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12) returning *";
        return sql;   
    }
};
} // namespace openproject6
} // namespace drogon_model
