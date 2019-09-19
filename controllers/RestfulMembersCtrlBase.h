/**
 *
 *  RestfulMembersCtrlBase.h
 *  DO NOT EDIT. This file is generated by drogon_ctl automatically.
 *  Users should implement business logic in the derived class.
 */

#pragma once

#include "Members.h"
using namespace drogon;

using namespace drogon_model::openproject6;

/**
 * @brief this class is created by the drogon_ctl command.
 * this class is a restful API controller for reading and writing the members table.
 */

class RestfulMembersCtrlBase
{
  public:
    void getOne(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback,
                Members::PrimaryKeyType &&id);
    void updateOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   Members::PrimaryKeyType &&id);
    void deleteOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   Members::PrimaryKeyType &&id);
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
          "created_on", // the alias for the created_on column.
          "mail_notification"  // the alias for the mail_notification column.
    };
};
