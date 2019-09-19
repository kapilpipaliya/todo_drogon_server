/**
 *
 *  WorkPackageJournals.h
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
class WorkPackageJournals
{
  public:
    struct Cols
    {
        static const std::string _id;
        static const std::string _journal_id;
        static const std::string _type_id;
        static const std::string _project_id;
        static const std::string _subject;
        static const std::string _description;
        static const std::string _due_date;
        static const std::string _category_id;
        static const std::string _status_id;
        static const std::string _assigned_to_id;
        static const std::string _priority_id;
        static const std::string _fixed_version_id;
        static const std::string _author_id;
        static const std::string _done_ratio;
        static const std::string _estimated_hours;
        static const std::string _start_date;
        static const std::string _parent_id;
        static const std::string _responsible_id;
        static const std::string _cost_object_id;
        static const std::string _story_points;
        static const std::string _remaining_hours;
        static const std::string _derived_estimated_hours;
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
    explicit WorkPackageJournals(const Row &r, const ssize_t indexOffset = 0) noexcept;

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     */
    explicit WorkPackageJournals(const Json::Value &pJson) noexcept(false);

    /**
     * @brief constructor
     * @param pJson The json object to construct a new instance.
     * @param pMasqueradingVector The aliases of table columns.
     */
    WorkPackageJournals(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false);

    WorkPackageJournals() = default;
    
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

    /**  For column type_id  */
    ///Get the value of the column type_id, returns the default value if the column is null
    const int32_t &getValueOfTypeId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getTypeId() const noexcept;
    ///Set the value of the column type_id
    void setTypeId(const int32_t &pTypeId) noexcept;

    /**  For column project_id  */
    ///Get the value of the column project_id, returns the default value if the column is null
    const int32_t &getValueOfProjectId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getProjectId() const noexcept;
    ///Set the value of the column project_id
    void setProjectId(const int32_t &pProjectId) noexcept;

    /**  For column subject  */
    ///Get the value of the column subject, returns the default value if the column is null
    const std::string &getValueOfSubject() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getSubject() const noexcept;
    ///Set the value of the column subject
    void setSubject(const std::string &pSubject) noexcept;
    void setSubject(std::string &&pSubject) noexcept;

    /**  For column description  */
    ///Get the value of the column description, returns the default value if the column is null
    const std::string &getValueOfDescription() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<std::string> &getDescription() const noexcept;
    ///Set the value of the column description
    void setDescription(const std::string &pDescription) noexcept;
    void setDescription(std::string &&pDescription) noexcept;

    /**  For column due_date  */
    ///Get the value of the column due_date, returns the default value if the column is null
    const ::trantor::Date &getValueOfDueDate() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<::trantor::Date> &getDueDate() const noexcept;
    ///Set the value of the column due_date
    void setDueDate(const ::trantor::Date &pDueDate) noexcept;

    /**  For column category_id  */
    ///Get the value of the column category_id, returns the default value if the column is null
    const int32_t &getValueOfCategoryId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getCategoryId() const noexcept;
    ///Set the value of the column category_id
    void setCategoryId(const int32_t &pCategoryId) noexcept;

    /**  For column status_id  */
    ///Get the value of the column status_id, returns the default value if the column is null
    const int32_t &getValueOfStatusId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getStatusId() const noexcept;
    ///Set the value of the column status_id
    void setStatusId(const int32_t &pStatusId) noexcept;

    /**  For column assigned_to_id  */
    ///Get the value of the column assigned_to_id, returns the default value if the column is null
    const int32_t &getValueOfAssignedToId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getAssignedToId() const noexcept;
    ///Set the value of the column assigned_to_id
    void setAssignedToId(const int32_t &pAssignedToId) noexcept;

    /**  For column priority_id  */
    ///Get the value of the column priority_id, returns the default value if the column is null
    const int32_t &getValueOfPriorityId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getPriorityId() const noexcept;
    ///Set the value of the column priority_id
    void setPriorityId(const int32_t &pPriorityId) noexcept;

    /**  For column fixed_version_id  */
    ///Get the value of the column fixed_version_id, returns the default value if the column is null
    const int32_t &getValueOfFixedVersionId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getFixedVersionId() const noexcept;
    ///Set the value of the column fixed_version_id
    void setFixedVersionId(const int32_t &pFixedVersionId) noexcept;

    /**  For column author_id  */
    ///Get the value of the column author_id, returns the default value if the column is null
    const int32_t &getValueOfAuthorId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getAuthorId() const noexcept;
    ///Set the value of the column author_id
    void setAuthorId(const int32_t &pAuthorId) noexcept;

    /**  For column done_ratio  */
    ///Get the value of the column done_ratio, returns the default value if the column is null
    const int32_t &getValueOfDoneRatio() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getDoneRatio() const noexcept;
    ///Set the value of the column done_ratio
    void setDoneRatio(const int32_t &pDoneRatio) noexcept;

    /**  For column estimated_hours  */
    ///Get the value of the column estimated_hours, returns the default value if the column is null
    const double &getValueOfEstimatedHours() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<double> &getEstimatedHours() const noexcept;
    ///Set the value of the column estimated_hours
    void setEstimatedHours(const double &pEstimatedHours) noexcept;

    /**  For column start_date  */
    ///Get the value of the column start_date, returns the default value if the column is null
    const ::trantor::Date &getValueOfStartDate() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<::trantor::Date> &getStartDate() const noexcept;
    ///Set the value of the column start_date
    void setStartDate(const ::trantor::Date &pStartDate) noexcept;

    /**  For column parent_id  */
    ///Get the value of the column parent_id, returns the default value if the column is null
    const int32_t &getValueOfParentId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getParentId() const noexcept;
    ///Set the value of the column parent_id
    void setParentId(const int32_t &pParentId) noexcept;

    /**  For column responsible_id  */
    ///Get the value of the column responsible_id, returns the default value if the column is null
    const int32_t &getValueOfResponsibleId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getResponsibleId() const noexcept;
    ///Set the value of the column responsible_id
    void setResponsibleId(const int32_t &pResponsibleId) noexcept;

    /**  For column cost_object_id  */
    ///Get the value of the column cost_object_id, returns the default value if the column is null
    const int32_t &getValueOfCostObjectId() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getCostObjectId() const noexcept;
    ///Set the value of the column cost_object_id
    void setCostObjectId(const int32_t &pCostObjectId) noexcept;

    /**  For column story_points  */
    ///Get the value of the column story_points, returns the default value if the column is null
    const int32_t &getValueOfStoryPoints() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<int32_t> &getStoryPoints() const noexcept;
    ///Set the value of the column story_points
    void setStoryPoints(const int32_t &pStoryPoints) noexcept;

    /**  For column remaining_hours  */
    ///Get the value of the column remaining_hours, returns the default value if the column is null
    const double &getValueOfRemainingHours() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<double> &getRemainingHours() const noexcept;
    ///Set the value of the column remaining_hours
    void setRemainingHours(const double &pRemainingHours) noexcept;

    /**  For column derived_estimated_hours  */
    ///Get the value of the column derived_estimated_hours, returns the default value if the column is null
    const double &getValueOfDerivedEstimatedHours() const noexcept;
    ///Return a shared_ptr object pointing to the column const value, or an empty shared_ptr object if the column is null
    const std::shared_ptr<double> &getDerivedEstimatedHours() const noexcept;
    ///Set the value of the column derived_estimated_hours
    void setDerivedEstimatedHours(const double &pDerivedEstimatedHours) noexcept;


    static size_t getColumnNumber() noexcept {  return 22;  }
    static const std::string &getColumnName(size_t index) noexcept(false);

    Json::Value toJson() const;
    Json::Value toMasqueradedJson(const std::vector<std::string> &pMasqueradingVector) const;

  private:
    friend Mapper<WorkPackageJournals>;
    static const std::vector<std::string> &insertColumns() noexcept;
    void outputArgs(drogon::orm::internal::SqlBinder &binder) const;
    const std::vector<std::string> updateColumns() const;
    void updateArgs(drogon::orm::internal::SqlBinder &binder) const;
    ///For mysql or sqlite3
    void updateId(const uint64_t id);
    std::shared_ptr<int32_t> _id;
    std::shared_ptr<int32_t> _journalId;
    std::shared_ptr<int32_t> _typeId;
    std::shared_ptr<int32_t> _projectId;
    std::shared_ptr<std::string> _subject;
    std::shared_ptr<std::string> _description;
    std::shared_ptr<::trantor::Date> _dueDate;
    std::shared_ptr<int32_t> _categoryId;
    std::shared_ptr<int32_t> _statusId;
    std::shared_ptr<int32_t> _assignedToId;
    std::shared_ptr<int32_t> _priorityId;
    std::shared_ptr<int32_t> _fixedVersionId;
    std::shared_ptr<int32_t> _authorId;
    std::shared_ptr<int32_t> _doneRatio;
    std::shared_ptr<double> _estimatedHours;
    std::shared_ptr<::trantor::Date> _startDate;
    std::shared_ptr<int32_t> _parentId;
    std::shared_ptr<int32_t> _responsibleId;
    std::shared_ptr<int32_t> _costObjectId;
    std::shared_ptr<int32_t> _storyPoints;
    std::shared_ptr<double> _remainingHours;
    std::shared_ptr<double> _derivedEstimatedHours;
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
    bool _dirtyFlag[22]={ false };

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
        static const std::string sql="insert into " + tableName + " (journal_id,type_id,project_id,subject,description,due_date,category_id,status_id,assigned_to_id,priority_id,fixed_version_id,author_id,done_ratio,estimated_hours,start_date,parent_id,responsible_id,cost_object_id,story_points,remaining_hours,derived_estimated_hours) values ($1,$2,$3,$4,$5,$6,$7,$8,$9,$10,$11,$12,$13,$14,$15,$16,$17,$18,$19,$20,$21) returning *";
        return sql;   
    }
};
} // namespace openproject6
} // namespace drogon_model
