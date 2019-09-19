/**
 *
 *  RestfulJournalsCtrl.h
 *  This file is generated by drogon_ctl
 *
 */

#pragma once

#include <drogon/HttpController.h>
#include "RestfulJournalsCtrlBase.h"

#include "Journals.h"
using namespace drogon;

using namespace drogon_model::openproject6;

/**
 * @brief this class is created by the drogon_ctl command.
 * this class is a restful API controller for reading and writing the journals table.
 */

class RestfulJournalsCtrl: public drogon::HttpController<RestfulJournalsCtrl>, public RestfulJournalsCtrlBase
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(RestfulJournalsCtrl::getOne,"/journals/{1}",Get,Options);
    ADD_METHOD_TO(RestfulJournalsCtrl::updateOne,"/journals/{1}",Put,Options);
    ADD_METHOD_TO(RestfulJournalsCtrl::deleteOne,"/journals/{1}",Delete,Options);
    ADD_METHOD_TO(RestfulJournalsCtrl::get,"/journals",Get,Options);
    ADD_METHOD_TO(RestfulJournalsCtrl::create,"/journals",Post,Options);
    //ADD_METHOD_TO(RestfulJournalsCtrl::update,"/journals",Put,Options);
    METHOD_LIST_END
    
    /**
     * Uncomment the following methods to customize for business logic.
     */
     /*
    void getOne(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback,
                Journals::PrimaryKeyType &&id);
    void updateOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   Journals::PrimaryKeyType &&id);
    void deleteOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   Journals::PrimaryKeyType &&id);
    void get(const HttpRequestPtr &req,
             std::function<void(const HttpResponsePtr &)> &&callback);
    void create(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback);
    */
};
