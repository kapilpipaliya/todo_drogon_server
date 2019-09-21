/**
 *
 *  AttachableJournals.h
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
#include <trantor/utils/Logger.h>
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
class AttachableJournals
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _journal_id;
        static const std::string _attachment_id;
        static const std::string _filename;
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
    explicit AttachableJournals(const Row &r, const ssize_t indexOffset = 0) noexcept;

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     */
    explicit AttachableJournals(const Json::Value &pJson) noexcept(false);

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     * @param pMasqueradingVector The aliases of table columns.
     */
    AttachableJournals(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false);

    AttachableJournals() = default;
    
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

    /**  For column journal_id  */
    ///Get the value of the column journal_id, returns the default value if the column is null
    const int32_t &getValueOfJournalId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getJournalId() const noexcept;
    ///Set the value of the column journal_id
    void setJournalId(const int32_t &pJournalId) noexcept;

    /**  For column attachment_id  */
    ///Get the value of the column attachment_id, returns the default value if the column is null
    const int32_t &getValueOfAttachmentId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getAttachmentId() const noexcept;
    ///Set the value of the column attachment_id
    void setAttachmentId(const int32_t &pAttachmentId) noexcept;

    /**  For column filename  */
    ///Get the value of the column filename, returns the default value if the column is null
    const std::string &getValueOfFilename() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getFilename() const noexcept;
    ///Set the value of the column filename
    void setFilename(const std::string &pFilename) noexcept;
    void setFilename(std::string &&pFilename) noexcept;


    static size_t getColumnNumber() noexcept {  return 4;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

    Json::Value toJson() const;
    Json::Value toMasqueradedJson(const std::vector<std::string> &pMasqueradingVector) const;

  private:
    friend Mapper<AttachableJournals>;
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<int32_t> _id;
    std::shared_ptr<int32_t> _journalId;
    std::shared_ptr<int32_t> _attachmentId;
    std::shared_ptr<std::string> _filename;
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
    std::string sqlForInserting(bool &needSelection) const
    {
        std::string sql="insert into " + tableName + " (";
        size_t parametersCount = 0;
        needSelection = false;
            sql += "id,";
            ++parametersCount;
        if(_dirtyFlag[1])
        {
            sql += "journal_id,";
            ++parametersCount;
        }
        if(_dirtyFlag[2])
        {
            sql += "attachment_id,";
            ++parametersCount;
        }
        sql += "filename,";
        ++parametersCount;
        if(!_dirtyFlag[3])
        {
            needSelection=true;
        }
        needSelection=true;
        if(parametersCount > 0)
        {
            sql[sql.length()-1]=')';
            sql += " values (";
        }
        else
            sql += ") values (";
        
        int placeholder=1;
        char placeholderStr[64];
        size_t n=0;
        sql +="default,";
        if(_dirtyFlag[1])
        {
            n = sprintf(placeholderStr,"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        } 
        if(_dirtyFlag[2])
        {
            n = sprintf(placeholderStr,"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        } 
        if(_dirtyFlag[3])
        {
            n = sprintf(placeholderStr,"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        } 
        else
        {
            sql +="default,";
        }
        if(parametersCount > 0)
        {
            sql.resize(sql.length() - 1);
        }
        if(needSelection)
        {
            sql.append(") returning *");
        }
        else
        {
            sql.append(1, ')');
        }
        LOG_TRACE << sql;
        return sql;   
    }
};
} // namespace openproject6
} // namespace drogon_model
