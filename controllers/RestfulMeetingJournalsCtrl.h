/**
 *
 *  RestfulMeetingJournalsCtrl.h
 *  This file is generated by drogon_ctl
 *
 */

#pragma once

#include <drogon/HttpController.h>
#include "RestfulMeetingJournalsCtrlBase.h"

#include "MeetingJournals.h"
using namespace drogon;

using namespace drogon_model::openproject6;

/**
 * @brief this class is created by the drogon_ctl command.
 * this class is a restful API controller for reading and writing the meeting_journals table.
 */

class RestfulMeetingJournalsCtrl: public drogon::HttpController<RestfulMeetingJournalsCtrl>, public RestfulMeetingJournalsCtrlBase
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(RestfulMeetingJournalsCtrl::getOne,"/meetingjournals/{1}",Get,Options);
    ADD_METHOD_TO(RestfulMeetingJournalsCtrl::updateOne,"/meetingjournals/{1}",Put,Options);
    ADD_METHOD_TO(RestfulMeetingJournalsCtrl::deleteOne,"/meetingjournals/{1}",Delete,Options);
    ADD_METHOD_TO(RestfulMeetingJournalsCtrl::get,"/meetingjournals",Get,Options);
    ADD_METHOD_TO(RestfulMeetingJournalsCtrl::create,"/meetingjournals",Post,Options);
    //ADD_METHOD_TO(RestfulMeetingJournalsCtrl::update,"/meetingjournals",Put,Options);
    METHOD_LIST_END
    
    /**
     * Uncomment the following methods to customize for business logic.
     */
     /*
    void getOne(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback,
                MeetingJournals::PrimaryKeyType &&id);
    void updateOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   MeetingJournals::PrimaryKeyType &&id);
    void deleteOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   MeetingJournals::PrimaryKeyType &&id);
    void get(const HttpRequestPtr &req,
             std::function<void(const HttpResponsePtr &)> &&callback);
    void create(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback);
    */
};
