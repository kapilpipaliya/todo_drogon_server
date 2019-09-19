/**
 *
 *  RestfulMeetingParticipantsCtrl.h
 *  This file is generated by drogon_ctl
 *
 */

#pragma once

#include <drogon/HttpController.h>
#include "RestfulMeetingParticipantsCtrlBase.h"

#include "MeetingParticipants.h"
using namespace drogon;

using namespace drogon_model::openproject6;

/**
 * @brief this class is created by the drogon_ctl command.
 * this class is a restful API controller for reading and writing the meeting_participants table.
 */

class RestfulMeetingParticipantsCtrl: public drogon::HttpController<RestfulMeetingParticipantsCtrl>, public RestfulMeetingParticipantsCtrlBase
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(RestfulMeetingParticipantsCtrl::getOne,"/meetingparticipants/{1}",Get,Options);
    ADD_METHOD_TO(RestfulMeetingParticipantsCtrl::updateOne,"/meetingparticipants/{1}",Put,Options);
    ADD_METHOD_TO(RestfulMeetingParticipantsCtrl::deleteOne,"/meetingparticipants/{1}",Delete,Options);
    ADD_METHOD_TO(RestfulMeetingParticipantsCtrl::get,"/meetingparticipants",Get,Options);
    ADD_METHOD_TO(RestfulMeetingParticipantsCtrl::create,"/meetingparticipants",Post,Options);
    //ADD_METHOD_TO(RestfulMeetingParticipantsCtrl::update,"/meetingparticipants",Put,Options);
    METHOD_LIST_END
    
    /**
     * Uncomment the following methods to customize for business logic.
     */
     /*
    void getOne(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback,
                MeetingParticipants::PrimaryKeyType &&id);
    void updateOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   MeetingParticipants::PrimaryKeyType &&id);
    void deleteOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   MeetingParticipants::PrimaryKeyType &&id);
    void get(const HttpRequestPtr &req,
             std::function<void(const HttpResponsePtr &)> &&callback);
    void create(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback);
    */
};
