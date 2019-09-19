/**
 *
 *  Statuses.h
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
class Statuses
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _name;
        static const std::string _is_closed;
        static const std::string _is_default;
        static const std::string _position;
        static const std::string _default_done_ratio;
        static const std::string _created_at;
        static const std::string _updated_at;
        static const std::string _color_id;
        static const std::string _is_readonly;
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
    explicit Statuses(const Row &r, const ssize_t indexOffset = 0) noexcept;

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     */
    explicit Statuses(const Json::Value &pJson) noexcept(false);

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     * @param pMasqueradingVector The aliases of table columns.
     */
    Statuses(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false);

    Statuses() = default;
    
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

    /**  For column is_closed  */
    ///Get the value of the column is_closed, returns the default value if the column is null
    const bool &getValueOfIsClosed() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<bool> &getIsClosed() const noexcept;
    ///Set the value of the column is_closed
    void setIsClosed(const bool &pIsClosed) noexcept;

    /**  For column is_default  */
    ///Get the value of the column is_default, returns the default value if the column is null
    const bool &getValueOfIsDefault() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<bool> &getIsDefault() const noexcept;
    ///Set the value of the column is_default
    void setIsDefault(const bool &pIsDefault) noexcept;

    /**  For column position  */
    ///Get the value of the column position, returns the default value if the column is null
    const int32_t &getValueOfPosition() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getPosition() const noexcept;
    ///Set the value of the column position
    void setPosition(const int32_t &pPosition) noexcept;

    /**  For column default_done_ratio  */
    ///Get the value of the column default_done_ratio, returns the default value if the column is null
    const int32_t &getValueOfDefaultDoneRatio() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getDefaultDoneRatio() const noexcept;
    ///Set the value of the column default_done_ratio
    void setDefaultDoneRatio(const int32_t &pDefaultDoneRatio) noexcept;

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

    /**  For column color_id  */
    ///Get the value of the column color_id, returns the default value if the column is null
    const int32_t &getValueOfColorId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getColorId() const noexcept;
    ///Set the value of the column color_id
    void setColorId(const int32_t &pColorId) noexcept;

    /**  For column is_readonly  */
    ///Get the value of the column is_readonly, returns the default value if the column is null
    const bool &getValueOfIsReadonly() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<bool> &getIsReadonly() const noexcept;
    ///Set the value of the column is_readonly
    void setIsReadonly(const bool &pIsReadonly) noexcept;


    static size_t getColumnNumber() noexcept {  return 10;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

    Json::Value toJson() const;
    Json::Value toMasqueradedJson(const std::vector<std::string> &pMasqueradingVector) const;

  private:
    friend Mapper<Statuses>;
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<int32_t> _id;
    std::shared_ptr<std::string> _name;
    std::shared_ptr<bool> _isClosed;
    std::shared_ptr<bool> _isDefault;
    std::shared_ptr<int32_t> _position;
    std::shared_ptr<int32_t> _defaultDoneRatio;
    std::shared_ptr<::trantor::Date> _createdAt;
    std::shared_ptr<::trantor::Date> _updatedAt;
    std::shared_ptr<int32_t> _colorId;
    std::shared_ptr<bool> _isReadonly;
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
    bool _dirtyFlag[10]={ false };

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
        static const std::string sql="insert into " + tableName + " (name,is_closed,is_default,position,default_done_ratio,created_at,updated_at,color_id,is_readonly) values ($1,$2,$3,$4,$5,$6,$7,$8,$9) returning *";
        return sql;   
    }
};
} // namespace openproject6
} // namespace drogon_model
