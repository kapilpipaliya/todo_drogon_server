/**
 *
 *  OauthApplications.h
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
class OauthApplications
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _name;
        static const std::string _uid;
        static const std::string _secret;
        static const std::string _owner_type;
        static const std::string _owner_id;
        static const std::string _client_credentials_user_id;
        static const std::string _redirect_uri;
        static const std::string _scopes;
        static const std::string _confidential;
        static const std::string _created_at;
        static const std::string _updated_at;
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
    explicit OauthApplications(const Row &r, const ssize_t indexOffset = 0) noexcept;

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     */
    explicit OauthApplications(const Json::Value &pJson) noexcept(false);

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     * @param pMasqueradingVector The aliases of table columns.
     */
    OauthApplications(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false);

    OauthApplications() = default;
    
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

    /**  For column name  */
    ///Get the value of the column name, returns the default value if the column is null
    const std::string &getValueOfName() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getName() const noexcept;
    ///Set the value of the column name
    void setName(const std::string &pName) noexcept;
    void setName(std::string &&pName) noexcept;

    /**  For column uid  */
    ///Get the value of the column uid, returns the default value if the column is null
    const std::string &getValueOfUid() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getUid() const noexcept;
    ///Set the value of the column uid
    void setUid(const std::string &pUid) noexcept;
    void setUid(std::string &&pUid) noexcept;

    /**  For column secret  */
    ///Get the value of the column secret, returns the default value if the column is null
    const std::string &getValueOfSecret() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getSecret() const noexcept;
    ///Set the value of the column secret
    void setSecret(const std::string &pSecret) noexcept;
    void setSecret(std::string &&pSecret) noexcept;

    /**  For column owner_type  */
    ///Get the value of the column owner_type, returns the default value if the column is null
    const std::string &getValueOfOwnerType() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getOwnerType() const noexcept;
    ///Set the value of the column owner_type
    void setOwnerType(const std::string &pOwnerType) noexcept;
    void setOwnerType(std::string &&pOwnerType) noexcept;

    /**  For column owner_id  */
    ///Get the value of the column owner_id, returns the default value if the column is null
    const int32_t &getValueOfOwnerId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getOwnerId() const noexcept;
    ///Set the value of the column owner_id
    void setOwnerId(const int32_t &pOwnerId) noexcept;

    /**  For column client_credentials_user_id  */
    ///Get the value of the column client_credentials_user_id, returns the default value if the column is null
    const int32_t &getValueOfClientCredentialsUserId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getClientCredentialsUserId() const noexcept;
    ///Set the value of the column client_credentials_user_id
    void setClientCredentialsUserId(const int32_t &pClientCredentialsUserId) noexcept;

    /**  For column redirect_uri  */
    ///Get the value of the column redirect_uri, returns the default value if the column is null
    const std::string &getValueOfRedirectUri() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getRedirectUri() const noexcept;
    ///Set the value of the column redirect_uri
    void setRedirectUri(const std::string &pRedirectUri) noexcept;
    void setRedirectUri(std::string &&pRedirectUri) noexcept;

    /**  For column scopes  */
    ///Get the value of the column scopes, returns the default value if the column is null
    const std::string &getValueOfScopes() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getScopes() const noexcept;
    ///Set the value of the column scopes
    void setScopes(const std::string &pScopes) noexcept;
    void setScopes(std::string &&pScopes) noexcept;

    /**  For column confidential  */
    ///Get the value of the column confidential, returns the default value if the column is null
    const bool &getValueOfConfidential() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<bool> &getConfidential() const noexcept;
    ///Set the value of the column confidential
    void setConfidential(const bool &pConfidential) noexcept;

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


    static size_t getColumnNumber() noexcept {  return 12;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

    Json::Value toJson() const;
    Json::Value toMasqueradedJson(const std::vector<std::string> &pMasqueradingVector) const;

  private:
    friend Mapper<OauthApplications>;
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<int64_t> _id;
    std::shared_ptr<std::string> _name;
    std::shared_ptr<std::string> _uid;
    std::shared_ptr<std::string> _secret;
    std::shared_ptr<std::string> _ownerType;
    std::shared_ptr<int32_t> _ownerId;
    std::shared_ptr<int32_t> _clientCredentialsUserId;
    std::shared_ptr<std::string> _redirectUri;
    std::shared_ptr<std::string> _scopes;
    std::shared_ptr<bool> _confidential;
    std::shared_ptr<::trantor::Date> _createdAt;
    std::shared_ptr<::trantor::Date> _updatedAt;
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
            sql += "name,";
            ++parametersCount;
        }
        if(_dirtyFlag[2])
        {
            sql += "uid,";
            ++parametersCount;
        }
        if(_dirtyFlag[3])
        {
            sql += "secret,";
            ++parametersCount;
        }
        if(_dirtyFlag[4])
        {
            sql += "owner_type,";
            ++parametersCount;
        }
        if(_dirtyFlag[5])
        {
            sql += "owner_id,";
            ++parametersCount;
        }
        if(_dirtyFlag[6])
        {
            sql += "client_credentials_user_id,";
            ++parametersCount;
        }
        if(_dirtyFlag[7])
        {
            sql += "redirect_uri,";
            ++parametersCount;
        }
        sql += "scopes,";
        ++parametersCount;
        if(!_dirtyFlag[8])
        {
            needSelection=true;
        }
        sql += "confidential,";
        ++parametersCount;
        if(!_dirtyFlag[9])
        {
            needSelection=true;
        }
        if(_dirtyFlag[10])
        {
            sql += "created_at,";
            ++parametersCount;
        }
        if(_dirtyFlag[11])
        {
            sql += "updated_at,";
            ++parametersCount;
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
        if(_dirtyFlag[4])
        {
            n = sprintf(placeholderStr,"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        } 
        if(_dirtyFlag[5])
        {
            n = sprintf(placeholderStr,"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        } 
        if(_dirtyFlag[6])
        {
            n = sprintf(placeholderStr,"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        } 
        if(_dirtyFlag[7])
        {
            n = sprintf(placeholderStr,"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        } 
        if(_dirtyFlag[8])
        {
            n = sprintf(placeholderStr,"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        } 
        else
        {
            sql +="default,";
        }
        if(_dirtyFlag[9])
        {
            n = sprintf(placeholderStr,"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        } 
        else
        {
            sql +="default,";
        }
        if(_dirtyFlag[10])
        {
            n = sprintf(placeholderStr,"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        } 
        if(_dirtyFlag[11])
        {
            n = sprintf(placeholderStr,"$%d,",placeholder++);
            sql.append(placeholderStr, n);
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
