/**
 *
 *  Projects.h
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
class Projects
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _name;
        static const std::string _description;
        static const std::string _is_public;
        static const std::string _parent_id;
        static const std::string _created_on;
        static const std::string _updated_on;
        static const std::string _identifier;
        static const std::string _status;
        static const std::string _lft;
        static const std::string _rgt;
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
    explicit Projects(const Row &r, const ssize_t indexOffset = 0) noexcept;

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     */
    explicit Projects(const Json::Value &pJson) noexcept(false);

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     * @param pMasqueradingVector The aliases of table columns.
     */
    Projects(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false);

    Projects() = default;
    
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

    /**  For column name  */
    ///Get the value of the column name, returns the default value if the column is null
    const std::string &getValueOfName() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getName() const noexcept;
    ///Set the value of the column name
    void setName(const std::string &pName) noexcept;
    void setName(std::string &&pName) noexcept;

    /**  For column description  */
    ///Get the value of the column description, returns the default value if the column is null
    const std::string &getValueOfDescription() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getDescription() const noexcept;
    ///Set the value of the column description
    void setDescription(const std::string &pDescription) noexcept;
    void setDescription(std::string &&pDescription) noexcept;

    /**  For column is_public  */
    ///Get the value of the column is_public, returns the default value if the column is null
    const bool &getValueOfIsPublic() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<bool> &getIsPublic() const noexcept;
    ///Set the value of the column is_public
    void setIsPublic(const bool &pIsPublic) noexcept;

    /**  For column parent_id  */
    ///Get the value of the column parent_id, returns the default value if the column is null
    const int32_t &getValueOfParentId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getParentId() const noexcept;
    ///Set the value of the column parent_id
    void setParentId(const int32_t &pParentId) noexcept;

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

    /**  For column identifier  */
    ///Get the value of the column identifier, returns the default value if the column is null
    const std::string &getValueOfIdentifier() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getIdentifier() const noexcept;
    ///Set the value of the column identifier
    void setIdentifier(const std::string &pIdentifier) noexcept;
    void setIdentifier(std::string &&pIdentifier) noexcept;

    /**  For column status  */
    ///Get the value of the column status, returns the default value if the column is null
    const int32_t &getValueOfStatus() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getStatus() const noexcept;
    ///Set the value of the column status
    void setStatus(const int32_t &pStatus) noexcept;

    /**  For column lft  */
    ///Get the value of the column lft, returns the default value if the column is null
    const int32_t &getValueOfLft() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getLft() const noexcept;
    ///Set the value of the column lft
    void setLft(const int32_t &pLft) noexcept;

    /**  For column rgt  */
    ///Get the value of the column rgt, returns the default value if the column is null
    const int32_t &getValueOfRgt() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getRgt() const noexcept;
    ///Set the value of the column rgt
    void setRgt(const int32_t &pRgt) noexcept;


    static size_t getColumnNumber() noexcept {  return 11;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

    Json::Value toJson() const;
    Json::Value toMasqueradedJson(const std::vector<std::string> &pMasqueradingVector) const;

  private:
    friend Mapper<Projects>;
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<int32_t> _id;
    std::shared_ptr<std::string> _name;
    std::shared_ptr<std::string> _description;
    std::shared_ptr<bool> _isPublic;
    std::shared_ptr<int32_t> _parentId;
    std::shared_ptr<::trantor::Date> _createdOn;
    std::shared_ptr<::trantor::Date> _updatedOn;
    std::shared_ptr<std::string> _identifier;
    std::shared_ptr<int32_t> _status;
    std::shared_ptr<int32_t> _lft;
    std::shared_ptr<int32_t> _rgt;
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
    bool _dirtyFlag[11]={ false };

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
        static const std::string sql="insert into " + tableName + " (name,description,is_public,parent_id,created_on,updated_on,identifier,status,lft,rgt) values ($1,$2,$3,$4,$5,$6,$7,$8,$9,$10) returning *";
        return sql;   
    }
};
} // namespace openproject6
} // namespace drogon_model
