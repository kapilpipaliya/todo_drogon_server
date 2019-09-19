/**
 *
 *  RestfulNewsJournalsCtrl.h
 *  This file is generated by drogon_ctl
 *
 */

#pragma once

#include <drogon/HttpController.h>
#include "RestfulNewsJournalsCtrlBase.h"

#include "NewsJournals.h"
using namespace drogon;

using namespace drogon_model::openproject6;

/**
 * @brief this class is created by the drogon_ctl command.
 * this class is a restful API controller for reading and writing the news_journals table.
 */

class RestfulNewsJournalsCtrl: public drogon::HttpController<RestfulNewsJournalsCtrl>, public RestfulNewsJournalsCtrlBase
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(RestfulNewsJournalsCtrl::getOne,"/newsjournals/{1}",Get,Options);
    ADD_METHOD_TO(RestfulNewsJournalsCtrl::updateOne,"/newsjournals/{1}",Put,Options);
    ADD_METHOD_TO(RestfulNewsJournalsCtrl::deleteOne,"/newsjournals/{1}",Delete,Options);
    ADD_METHOD_TO(RestfulNewsJournalsCtrl::get,"/newsjournals",Get,Options);
    ADD_METHOD_TO(RestfulNewsJournalsCtrl::create,"/newsjournals",Post,Options);
    //ADD_METHOD_TO(RestfulNewsJournalsCtrl::update,"/newsjournals",Put,Options);
    METHOD_LIST_END
    
    /**
     * Uncomment the following methods to customize for business logic.
     */
     /*
    void getOne(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback,
                NewsJournals::PrimaryKeyType &&id);
    void updateOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   NewsJournals::PrimaryKeyType &&id);
    void deleteOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   NewsJournals::PrimaryKeyType &&id);
    void get(const HttpRequestPtr &req,
             std::function<void(const HttpResponsePtr &)> &&callback);
    void create(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback);
    */
};
