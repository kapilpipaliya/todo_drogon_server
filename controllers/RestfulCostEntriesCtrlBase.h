/**
 *
 *  RestfulCostEntriesCtrlBase.h
 *  DO NOT EDIT. This file is generated by drogon_ctl automatically.
 *  Users should implement business logic in the derived class.
 */

#pragma once

#include "CostEntries.h"
using namespace drogon;

using namespace drogon_model::openproject6;

/**
 * @brief this class is created by the drogon_ctl command.
 * this class is a restful API controller for reading and writing the cost_entries table.
 */

class RestfulCostEntriesCtrlBase
{
  public:
    void getOne(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback,
                CostEntries::PrimaryKeyType &&id);
    void updateOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   CostEntries::PrimaryKeyType &&id);
    void deleteOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   CostEntries::PrimaryKeyType &&id);
    void get(const HttpRequestPtr &req,
             std::function<void(const HttpResponsePtr &)> &&callback);
    void create(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback);


//    void update(const HttpRequestPtr &req,
//                std::function<void(const HttpResponsePtr &)> &&callback);

    orm::DbClientPtr getDbClient() 
    {
        return drogon::app().getDbClient(_dbClientName);
    }
    void enableMasquerading(const std::vector<std::string> &pMasqueradingVector)
    {
        _masquerading = true;
        _masqueradingVector = pMasqueradingVector;
    }
    void disableMasquerading()
    {
        _masquerading = false;
    }
  protected:
    const std::string _dbClientName = "sce";
    bool _masquerading = true;
    /**
     * The items in the vector are aliases of column names in the table.
     * if one item is set to an empty string, the related column is not sent to clients.
     */
    std::vector<std::string> _masqueradingVector={
          "id", // the alias for the id column.
          "user_id", // the alias for the user_id column.
          "project_id", // the alias for the project_id column.
          "work_package_id", // the alias for the work_package_id column.
          "cost_type_id", // the alias for the cost_type_id column.
          "units", // the alias for the units column.
          "spent_on", // the alias for the spent_on column.
          "created_on", // the alias for the created_on column.
          "updated_on", // the alias for the updated_on column.
          "comments", // the alias for the comments column.
          "blocked", // the alias for the blocked column.
          "overridden_costs", // the alias for the overridden_costs column.
          "costs", // the alias for the costs column.
          "rate_id", // the alias for the rate_id column.
          "tyear", // the alias for the tyear column.
          "tmonth", // the alias for the tmonth column.
          "tweek"  // the alias for the tweek column.
    };
};
