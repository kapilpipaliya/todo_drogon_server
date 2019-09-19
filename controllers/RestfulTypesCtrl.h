/**
 *
 *  RestfulTypesCtrl.h
 *  This file is generated by drogon_ctl
 *
 */

#pragma once

#include <drogon/HttpController.h>
#include "RestfulTypesCtrlBase.h"

#include "Types.h"
using namespace drogon;

using namespace drogon_model::openproject6;

/**
 * @brief this class is created by the drogon_ctl command.
 * this class is a restful API controller for reading and writing the types table.
 */

class RestfulTypesCtrl: public drogon::HttpController<RestfulTypesCtrl>, public RestfulTypesCtrlBase
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(RestfulTypesCtrl::getOne,"/types/{1}",Get,Options);
    ADD_METHOD_TO(RestfulTypesCtrl::updateOne,"/types/{1}",Put,Options);
    ADD_METHOD_TO(RestfulTypesCtrl::deleteOne,"/types/{1}",Delete,Options);
    ADD_METHOD_TO(RestfulTypesCtrl::get,"/types",Get,Options);
    ADD_METHOD_TO(RestfulTypesCtrl::create,"/types",Post,Options);
    //ADD_METHOD_TO(RestfulTypesCtrl::update,"/types",Put,Options);
    METHOD_LIST_END
    
    /**
     * Uncomment the following methods to customize for business logic.
     */
     /*
    void getOne(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback,
                Types::PrimaryKeyType &&id);
    void updateOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   Types::PrimaryKeyType &&id);
    void deleteOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   Types::PrimaryKeyType &&id);
    void get(const HttpRequestPtr &req,
             std::function<void(const HttpResponsePtr &)> &&callback);
    void create(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback);
    */
};
