/**
 *
 *  Documents.h
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
class Documents
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _project_id;
        static const std::string _category_id;
        static const std::string _title;
        static const std::string _description;
        static const std::string _created_on;
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
    explicit Documents(const Row &r, const ssize_t indexOffset = 0) noexcept;

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     */
    explicit Documents(const Json::Value &pJson) noexcept(false);

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     * @param pMasqueradingVector The aliases of table columns.
     */
    Documents(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false);

    Documents() = default;
    
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

    /**  For column category_id  */
    ///Get the value of the column category_id, returns the default value if the column is null
    const int32_t &getValueOfCategoryId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getCategoryId() const noexcept;
    ///Set the value of the column category_id
    void setCategoryId(const int32_t &pCategoryId) noexcept;

    /**  For column title  */
    ///Get the value of the column title, returns the default value if the column is null
    const std::string &getValueOfTitle() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getTitle() const noexcept;
    ///Set the value of the column title
    void setTitle(const std::string &pTitle) noexcept;
    void setTitle(std::string &&pTitle) noexcept;

    /**  For column description  */
    ///Get the value of the column description, returns the default value if the column is null
    const std::string &getValueOfDescription() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getDescription() const noexcept;
    ///Set the value of the column description
    void setDescription(const std::string &pDescription) noexcept;
    void setDescription(std::string &&pDescription) noexcept;

    /**  For column created_on  */
    ///Get the value of the column created_on, returns the default value if the column is null
    const ::trantor::Date &getValueOfCreatedOn() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<::trantor::Date> &getCreatedOn() const noexcept;
    ///Set the value of the column created_on
    void setCreatedOn(const ::trantor::Date &pCreatedOn) noexcept;


    static size_t getColumnNumber() noexcept {  return 6;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

    Json::Value toJson() const;
    Json::Value toMasqueradedJson(const std::vector<std::string> &pMasqueradingVector) const;

  private:
    friend Mapper<Documents>;
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<int32_t> _id;
    std::shared_ptr<int32_t> _projectId;
    std::shared_ptr<int32_t> _categoryId;
    std::shared_ptr<std::string> _title;
    std::shared_ptr<std::string> _description;
    std::shared_ptr<::trantor::Date> _createdOn;
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
        static const std::string sql="insert into " + tableName + " (project_id,category_id,title,description,created_on) values ($1,$2,$3,$4,$5) returning *";
        return sql;   
    }
};
} // namespace openproject6
} // namespace drogon_model
