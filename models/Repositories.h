/**
 *
 *  Repositories.h
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
class Repositories
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _project_id;
        static const std::string _url;
        static const std::string _login;
        static const std::string _password;
        static const std::string _root_url;
        static const std::string _type;
        static const std::string _path_encoding;
        static const std::string _log_encoding;
        static const std::string _scm_type;
        static const std::string _required_storage_bytes;
        static const std::string _storage_updated_at;
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
    explicit Repositories(const Row &r, const ssize_t indexOffset = 0) noexcept;

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     */
    explicit Repositories(const Json::Value &pJson) noexcept(false);

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     * @param pMasqueradingVector The aliases of table columns.
     */
    Repositories(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false);

    Repositories() = default;
    
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

    /**  For column project_id  */
    ///Get the value of the column project_id, returns the default value if the column is null
    const int32_t &getValueOfProjectId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getProjectId() const noexcept;
    ///Set the value of the column project_id
    void setProjectId(const int32_t &pProjectId) noexcept;

    /**  For column url  */
    ///Get the value of the column url, returns the default value if the column is null
    const std::string &getValueOfUrl() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getUrl() const noexcept;
    ///Set the value of the column url
    void setUrl(const std::string &pUrl) noexcept;
    void setUrl(std::string &&pUrl) noexcept;

    /**  For column login  */
    ///Get the value of the column login, returns the default value if the column is null
    const std::string &getValueOfLogin() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getLogin() const noexcept;
    ///Set the value of the column login
    void setLogin(const std::string &pLogin) noexcept;
    void setLogin(std::string &&pLogin) noexcept;

    /**  For column password  */
    ///Get the value of the column password, returns the default value if the column is null
    const std::string &getValueOfPassword() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getPassword() const noexcept;
    ///Set the value of the column password
    void setPassword(const std::string &pPassword) noexcept;
    void setPassword(std::string &&pPassword) noexcept;

    /**  For column root_url  */
    ///Get the value of the column root_url, returns the default value if the column is null
    const std::string &getValueOfRootUrl() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getRootUrl() const noexcept;
    ///Set the value of the column root_url
    void setRootUrl(const std::string &pRootUrl) noexcept;
    void setRootUrl(std::string &&pRootUrl) noexcept;

    /**  For column type  */
    ///Get the value of the column type, returns the default value if the column is null
    const std::string &getValueOfType() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getType() const noexcept;
    ///Set the value of the column type
    void setType(const std::string &pType) noexcept;
    void setType(std::string &&pType) noexcept;

    /**  For column path_encoding  */
    ///Get the value of the column path_encoding, returns the default value if the column is null
    const std::string &getValueOfPathEncoding() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getPathEncoding() const noexcept;
    ///Set the value of the column path_encoding
    void setPathEncoding(const std::string &pPathEncoding) noexcept;
    void setPathEncoding(std::string &&pPathEncoding) noexcept;

    /**  For column log_encoding  */
    ///Get the value of the column log_encoding, returns the default value if the column is null
    const std::string &getValueOfLogEncoding() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getLogEncoding() const noexcept;
    ///Set the value of the column log_encoding
    void setLogEncoding(const std::string &pLogEncoding) noexcept;
    void setLogEncoding(std::string &&pLogEncoding) noexcept;

    /**  For column scm_type  */
    ///Get the value of the column scm_type, returns the default value if the column is null
    const std::string &getValueOfScmType() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getScmType() const noexcept;
    ///Set the value of the column scm_type
    void setScmType(const std::string &pScmType) noexcept;
    void setScmType(std::string &&pScmType) noexcept;

    /**  For column required_storage_bytes  */
    ///Get the value of the column required_storage_bytes, returns the default value if the column is null
    const int64_t &getValueOfRequiredStorageBytes() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int64_t> &getRequiredStorageBytes() const noexcept;
    ///Set the value of the column required_storage_bytes
    void setRequiredStorageBytes(const int64_t &pRequiredStorageBytes) noexcept;

    /**  For column storage_updated_at  */
    ///Get the value of the column storage_updated_at, returns the default value if the column is null
    const ::trantor::Date &getValueOfStorageUpdatedAt() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<::trantor::Date> &getStorageUpdatedAt() const noexcept;
    ///Set the value of the column storage_updated_at
    void setStorageUpdatedAt(const ::trantor::Date &pStorageUpdatedAt) noexcept;


    static size_t getColumnNumber() noexcept {  return 12;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

    Json::Value toJson() const;
    Json::Value toMasqueradedJson(const std::vector<std::string> &pMasqueradingVector) const;

  private:
    friend Mapper<Repositories>;
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<int32_t> _id;
    std::shared_ptr<int32_t> _projectId;
    std::shared_ptr<std::string> _url;
    std::shared_ptr<std::string> _login;
    std::shared_ptr<std::string> _password;
    std::shared_ptr<std::string> _rootUrl;
    std::shared_ptr<std::string> _type;
    std::shared_ptr<std::string> _pathEncoding;
    std::shared_ptr<std::string> _logEncoding;
    std::shared_ptr<std::string> _scmType;
    std::shared_ptr<int64_t> _requiredStorageBytes;
    std::shared_ptr<::trantor::Date> _storageUpdatedAt;
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

    static const std::string &sqlForInserting()
    {
        static const std::string sql="insert into " + tableName + " (project_id,url,login,password,root_url,type,path_encoding,log_encoding,scm_type,required_storage_bytes,storage_updated_at) values ($1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11) returning *";
        return sql;   
    }
};
} // namespace openproject6
} // namespace drogon_model
