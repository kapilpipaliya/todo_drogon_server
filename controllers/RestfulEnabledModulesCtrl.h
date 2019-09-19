/**
 *
 *  RestfulEnabledModulesCtrl.h
 *  This file is generated by drogon_ctl
 *
 */

#pragma once

#include <drogon/HttpController.h>
#include "RestfulEnabledModulesCtrlBase.h"

#include "EnabledModules.h"
using namespace drogon;

using namespace drogon_model::openproject6;

/**
 * @brief this class is created by the drogon_ctl command.
 * this class is a restful API controller for reading and writing the enabled_modules table.
 */

class RestfulEnabledModulesCtrl: public drogon::HttpController<RestfulEnabledModulesCtrl>, public RestfulEnabledModulesCtrlBase
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(RestfulEnabledModulesCtrl::getOne,"/enabledmodules/{1}",Get,Options);
    ADD_METHOD_TO(RestfulEnabledModulesCtrl::updateOne,"/enabledmodules/{1}",Put,Options);
    ADD_METHOD_TO(RestfulEnabledModulesCtrl::deleteOne,"/enabledmodules/{1}",Delete,Options);
    ADD_METHOD_TO(RestfulEnabledModulesCtrl::get,"/enabledmodules",Get,Options);
    ADD_METHOD_TO(RestfulEnabledModulesCtrl::create,"/enabledmodules",Post,Options);
    //ADD_METHOD_TO(RestfulEnabledModulesCtrl::update,"/enabledmodules",Put,Options);
    METHOD_LIST_END
    
    /**
     * Uncomment the following methods to customize for business logic.
     */
     /*
    void getOne(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback,
                EnabledModules::PrimaryKeyType &&id);
    void updateOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   EnabledModules::PrimaryKeyType &&id);
    void deleteOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   EnabledModules::PrimaryKeyType &&id);
    void get(const HttpRequestPtr &req,
             std::function<void(const HttpResponsePtr &)> &&callback);
    void create(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback);
    */
};
