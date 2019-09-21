/**
 *
 *  Relations.h
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
class Relations
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _from_id;
        static const std::string _to_id;
        static const std::string _delay;
        static const std::string _description;
        static const std::string _hierarchy;
        static const std::string _relates;
        static const std::string _duplicates;
        static const std::string _blocks;
        static const std::string _follows;
        static const std::string _includes;
        static const std::string _requires;
        static const std::string _count;
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
    explicit Relations(const Row &r, const ssize_t indexOffset = 0) noexcept;

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     */
    explicit Relations(const Json::Value &pJson) noexcept(false);

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     * @param pMasqueradingVector The aliases of table columns.
     */
    Relations(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false);

    Relations() = default;
    
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

    /**  For column from_id  */
    ///Get the value of the column from_id, returns the default value if the column is null
    const int32_t &getValueOfFromId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getFromId() const noexcept;
    ///Set the value of the column from_id
    void setFromId(const int32_t &pFromId) noexcept;

    /**  For column to_id  */
    ///Get the value of the column to_id, returns the default value if the column is null
    const int32_t &getValueOfToId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getToId() const noexcept;
    ///Set the value of the column to_id
    void setToId(const int32_t &pToId) noexcept;

    /**  For column delay  */
    ///Get the value of the column delay, returns the default value if the column is null
    const int32_t &getValueOfDelay() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getDelay() const noexcept;
    ///Set the value of the column delay
    void setDelay(const int32_t &pDelay) noexcept;

    /**  For column description  */
    ///Get the value of the column description, returns the default value if the column is null
    const std::string &getValueOfDescription() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getDescription() const noexcept;
    ///Set the value of the column description
    void setDescription(const std::string &pDescription) noexcept;
    void setDescription(std::string &&pDescription) noexcept;

    /**  For column hierarchy  */
    ///Get the value of the column hierarchy, returns the default value if the column is null
    const int32_t &getValueOfHierarchy() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getHierarchy() const noexcept;
    ///Set the value of the column hierarchy
    void setHierarchy(const int32_t &pHierarchy) noexcept;

    /**  For column relates  */
    ///Get the value of the column relates, returns the default value if the column is null
    const int32_t &getValueOfRelates() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getRelates() const noexcept;
    ///Set the value of the column relates
    void setRelates(const int32_t &pRelates) noexcept;

    /**  For column duplicates  */
    ///Get the value of the column duplicates, returns the default value if the column is null
    const int32_t &getValueOfDuplicates() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getDuplicates() const noexcept;
    ///Set the value of the column duplicates
    void setDuplicates(const int32_t &pDuplicates) noexcept;

    /**  For column blocks  */
    ///Get the value of the column blocks, returns the default value if the column is null
    const int32_t &getValueOfBlocks() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getBlocks() const noexcept;
    ///Set the value of the column blocks
    void setBlocks(const int32_t &pBlocks) noexcept;

    /**  For column follows  */
    ///Get the value of the column follows, returns the default value if the column is null
    const int32_t &getValueOfFollows() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getFollows() const noexcept;
    ///Set the value of the column follows
    void setFollows(const int32_t &pFollows) noexcept;

    /**  For column includes  */
    ///Get the value of the column includes, returns the default value if the column is null
    const int32_t &getValueOfIncludes() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getIncludes() const noexcept;
    ///Set the value of the column includes
    void setIncludes(const int32_t &pIncludes) noexcept;

    /**  For column requires  */
    ///Get the value of the column requires, returns the default value if the column is null
    const int32_t &getValueOfRequires() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getRequires() const noexcept;
    ///Set the value of the column requires
    void setRequires(const int32_t &pRequires) noexcept;

    /**  For column count  */
    ///Get the value of the column count, returns the default value if the column is null
    const int32_t &getValueOfCount() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getCount() const noexcept;
    ///Set the value of the column count
    void setCount(const int32_t &pCount) noexcept;


    static size_t getColumnNumber() noexcept {  return 13;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

    Json::Value toJson() const;
    Json::Value toMasqueradedJson(const std::vector<std::string> &pMasqueradingVector) const;

  private:
    friend Mapper<Relations>;
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<int32_t> _id;
    std::shared_ptr<int32_t> _fromId;
    std::shared_ptr<int32_t> _toId;
    std::shared_ptr<int32_t> _delay;
    std::shared_ptr<std::string> _description;
    std::shared_ptr<int32_t> _hierarchy;
    std::shared_ptr<int32_t> _relates;
    std::shared_ptr<int32_t> _duplicates;
    std::shared_ptr<int32_t> _blocks;
    std::shared_ptr<int32_t> _follows;
    std::shared_ptr<int32_t> _includes;
    std::shared_ptr<int32_t> _requires;
    std::shared_ptr<int32_t> _count;
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
    std::string sqlForInserting(bool &needSelection) const
    {
        std::string sql="insert into " + tableName + " (";
        size_t parametersCount = 0;
        needSelection = false;
            sql += "id,";
            ++parametersCount;
        if(_dirtyFlag[1])
        {
            sql += "from_id,";
            ++parametersCount;
        }
        if(_dirtyFlag[2])
        {
            sql += "to_id,";
            ++parametersCount;
        }
        if(_dirtyFlag[3])
        {
            sql += "delay,";
            ++parametersCount;
        }
        if(_dirtyFlag[4])
        {
            sql += "description,";
            ++parametersCount;
        }
        sql += "hierarchy,";
        ++parametersCount;
        if(!_dirtyFlag[5])
        {
            needSelection=true;
        }
        sql += "relates,";
        ++parametersCount;
        if(!_dirtyFlag[6])
        {
            needSelection=true;
        }
        sql += "duplicates,";
        ++parametersCount;
        if(!_dirtyFlag[7])
        {
            needSelection=true;
        }
        sql += "blocks,";
        ++parametersCount;
        if(!_dirtyFlag[8])
        {
            needSelection=true;
        }
        sql += "follows,";
        ++parametersCount;
        if(!_dirtyFlag[9])
        {
            needSelection=true;
        }
        sql += "includes,";
        ++parametersCount;
        if(!_dirtyFlag[10])
        {
            needSelection=true;
        }
        sql += "requires,";
        ++parametersCount;
        if(!_dirtyFlag[11])
        {
            needSelection=true;
        }
        sql += "count,";
        ++parametersCount;
        if(!_dirtyFlag[12])
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
        else
        {
            sql +="default,";
        }
        if(_dirtyFlag[6])
        {
            n = sprintf(placeholderStr,"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        } 
        else
        {
            sql +="default,";
        }
        if(_dirtyFlag[7])
        {
            n = sprintf(placeholderStr,"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        } 
        else
        {
            sql +="default,";
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
        else
        {
            sql +="default,";
        }
        if(_dirtyFlag[11])
        {
            n = sprintf(placeholderStr,"$%d,",placeholder++);
            sql.append(placeholderStr, n);
        } 
        else
        {
            sql +="default,";
        }
        if(_dirtyFlag[12])
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
