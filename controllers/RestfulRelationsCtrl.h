/**
 *
 *  RestfulRelationsCtrl.h
 *  This file is generated by drogon_ctl
 *
 */

#pragma once

#include <drogon/HttpController.h>
#include "RestfulRelationsCtrlBase.h"

#include "Relations.h"
using namespace drogon;

using namespace drogon_model::openproject6;

/**
 * @brief this class is created by the drogon_ctl command.
 * this class is a restful API controller for reading and writing the relations table.
 */

class RestfulRelationsCtrl: public drogon::HttpController<RestfulRelationsCtrl>, public RestfulRelationsCtrlBase
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(RestfulRelationsCtrl::getOne,"/relations/{1}",Get,Options);
    ADD_METHOD_TO(RestfulRelationsCtrl::updateOne,"/relations/{1}",Put,Options);
    ADD_METHOD_TO(RestfulRelationsCtrl::deleteOne,"/relations/{1}",Delete,Options);
    ADD_METHOD_TO(RestfulRelationsCtrl::get,"/relations",Get,Options);
    ADD_METHOD_TO(RestfulRelationsCtrl::create,"/relations",Post,Options);
    //ADD_METHOD_TO(RestfulRelationsCtrl::update,"/relations",Put,Options);
    METHOD_LIST_END
    
    /**
     * Uncomment the following methods to customize for business logic.
     */
     /*
    void getOne(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback,
                Relations::PrimaryKeyType &&id);
    void updateOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   Relations::PrimaryKeyType &&id);
    void deleteOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   Relations::PrimaryKeyType &&id);
    void get(const HttpRequestPtr &req,
             std::function<void(const HttpResponsePtr &)> &&callback);
    void create(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback);
    */
};
