/**
 *
 *  RestfulTimeEntryJournalsCtrl.h
 *  This file is generated by drogon_ctl
 *
 */

#pragma once

#include <drogon/HttpController.h>
#include "RestfulTimeEntryJournalsCtrlBase.h"

#include "TimeEntryJournals.h"
using namespace drogon;

using namespace drogon_model::openproject6;

/**
 * @brief this class is created by the drogon_ctl command.
 * this class is a restful API controller for reading and writing the time_entry_journals table.
 */

class RestfulTimeEntryJournalsCtrl: public drogon::HttpController<RestfulTimeEntryJournalsCtrl>, public RestfulTimeEntryJournalsCtrlBase
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(RestfulTimeEntryJournalsCtrl::getOne,"/timeentryjournals/{1}",Get,Options);
    ADD_METHOD_TO(RestfulTimeEntryJournalsCtrl::updateOne,"/timeentryjournals/{1}",Put,Options);
    ADD_METHOD_TO(RestfulTimeEntryJournalsCtrl::deleteOne,"/timeentryjournals/{1}",Delete,Options);
    ADD_METHOD_TO(RestfulTimeEntryJournalsCtrl::get,"/timeentryjournals",Get,Options);
    ADD_METHOD_TO(RestfulTimeEntryJournalsCtrl::create,"/timeentryjournals",Post,Options);
    //ADD_METHOD_TO(RestfulTimeEntryJournalsCtrl::update,"/timeentryjournals",Put,Options);
    METHOD_LIST_END
    
    /**
     * Uncomment the following methods to customize for business logic.
     */
     /*
    void getOne(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback,
                TimeEntryJournals::PrimaryKeyType &&id);
    void updateOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   TimeEntryJournals::PrimaryKeyType &&id);
    void deleteOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   TimeEntryJournals::PrimaryKeyType &&id);
    void get(const HttpRequestPtr &req,
             std::function<void(const HttpResponsePtr &)> &&callback);
    void create(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback);
    */
};
