/**
 *
 *  DoneStatusesForProject.h
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
class DoneStatusesForProject
{
  public:
    struct Cols
    {
        static const std::string _project_id;
        static const std::string _status_id;
    };

    const static int primaryKeyNumber;
    const static std::string tableName;
    const static bool hasPrimaryKey;
    const static std::string primaryKeyName;
    typedef void PrimaryKeyType;
    explicit DoneStatusesForProject(const Row &r) noexcept;
    DoneStatusesForProject() = default;
    
    /**  For column project_id  */
    ///Get the value of the column project_id, returns the default value if the column is null
    const int32_t &getValueOfProjectId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getProjectId() const noexcept;
    ///Set the value of the column project_id
    void setProjectId(const int32_t &pProjectId) noexcept;

    /**  For column status_id  */
    ///Get the value of the column status_id, returns the default value if the column is null
    const int32_t &getValueOfStatusId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getStatusId() const noexcept;
    ///Set the value of the column status_id
    void setStatusId(const int32_t &pStatusId) noexcept;


    static size_t getColumnNumber() noexcept {  return 2;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

    Json::Value toJson() const;

  private:
    friend Mapper<DoneStatusesForProject>;
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<int32_t> _projectId;
    std::shared_ptr<int32_t> _statusId;
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
    bool _dirtyFlag[2]={ false };
};
} // namespace openproject4
} // namespace drogon_model
