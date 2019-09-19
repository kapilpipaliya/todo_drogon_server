/**
 *
 *  RestfulGroupUsersCtrl.h
 *  This file is generated by drogon_ctl
 *
 */

#pragma once

#include <drogon/HttpController.h>
#include "RestfulGroupUsersCtrlBase.h"

#include "GroupUsers.h"
using namespace drogon;

using namespace drogon_model::openproject6;

/**
 * @brief this class is created by the drogon_ctl command.
 * this class is a restful API controller for reading and writing the group_users table.
 */

class RestfulGroupUsersCtrl: public drogon::HttpController<RestfulGroupUsersCtrl>, public RestfulGroupUsersCtrlBase
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(RestfulGroupUsersCtrl::get,"/groupusers",Get,Options);
    ADD_METHOD_TO(RestfulGroupUsersCtrl::create,"/groupusers",Post,Options);
    //ADD_METHOD_TO(RestfulGroupUsersCtrl::update,"/groupusers",Put,Options);
    METHOD_LIST_END
    
    /**
     * Uncomment the following methods to customize for business logic.
     */
     /*
    void get(const HttpRequestPtr &req,
             std::function<void(const HttpResponsePtr &)> &&callback);
    void create(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback);
    */
};
