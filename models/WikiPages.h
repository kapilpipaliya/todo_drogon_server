/**
 *
 *  WikiPages.h
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
class WikiPages
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _wiki_id;
        static const std::string _title;
        static const std::string _created_on;
        static const std::string _protected;
        static const std::string _parent_id;
        static const std::string _slug;
        static const std::string _updated_at;
    };

    const static int primaryKeyNumber;
    const static std::string tableName;
    const static bool hasPrimaryKey;
    const static std::string primaryKeyName;
    typedef int32_t PrimaryKeyType;
    const PrimaryKeyType &getPrimaryKey() const;
    explicit WikiPages(const Row &r) noexcept;
    WikiPages() = default;
    
    /**  For column id  */
    ///Get the value of the column id, returns the default value if the column is null
    const int32_t &getValueOfId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getId() const noexcept;

    /**  For column wiki_id  */
    ///Get the value of the column wiki_id, returns the default value if the column is null
    const int32_t &getValueOfWikiId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getWikiId() const noexcept;
    ///Set the value of the column wiki_id
    void setWikiId(const int32_t &pWikiId) noexcept;

    /**  For column title  */
    ///Get the value of the column title, returns the default value if the column is null
    const std::string &getValueOfTitle() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getTitle() const noexcept;
    ///Set the value of the column title
    void setTitle(const std::string &pTitle) noexcept;
    void setTitle(std::string &&pTitle) noexcept;

    /**  For column created_on  */
    ///Get the value of the column created_on, returns the default value if the column is null
    const ::trantor::Date &getValueOfCreatedOn() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<::trantor::Date> &getCreatedOn() const noexcept;
    ///Set the value of the column created_on
    void setCreatedOn(const ::trantor::Date &pCreatedOn) noexcept;

    /**  For column protected  */
    ///Get the value of the column protected, returns the default value if the column is null
    const bool &getValueOfProtected() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<bool> &getProtected() const noexcept;
    ///Set the value of the column protected
    void setProtected(const bool &pProtected) noexcept;

    /**  For column parent_id  */
    ///Get the value of the column parent_id, returns the default value if the column is null
    const int32_t &getValueOfParentId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getParentId() const noexcept;
    ///Set the value of the column parent_id
    void setParentId(const int32_t &pParentId) noexcept;

    /**  For column slug  */
    ///Get the value of the column slug, returns the default value if the column is null
    const std::string &getValueOfSlug() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getSlug() const noexcept;
    ///Set the value of the column slug
    void setSlug(const std::string &pSlug) noexcept;
    void setSlug(std::string &&pSlug) noexcept;

    /**  For column updated_at  */
    ///Get the value of the column updated_at, returns the default value if the column is null
    const ::trantor::Date &getValueOfUpdatedAt() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<::trantor::Date> &getUpdatedAt() const noexcept;
    ///Set the value of the column updated_at
    void setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept;


    static size_t getColumnNumber() noexcept {  return 8;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

    Json::Value toJson() const;

  private:
    friend Mapper<WikiPages>;
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<int32_t> _id;
    std::shared_ptr<int32_t> _wikiId;
    std::shared_ptr<std::string> _title;
    std::shared_ptr<::trantor::Date> _createdOn;
    std::shared_ptr<bool> _protected;
    std::shared_ptr<int32_t> _parentId;
    std::shared_ptr<std::string> _slug;
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
    bool _dirtyFlag[8]={ false };
};
} // namespace openproject4
} // namespace drogon_model
