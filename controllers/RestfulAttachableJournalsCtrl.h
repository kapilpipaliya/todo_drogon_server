/**
 *
 *  RestfulAttachableJournalsCtrl.h
 *  This file is generated by drogon_ctl
 *
 */

#pragma once

#include <drogon/HttpController.h>
#include "RestfulAttachableJournalsCtrlBase.h"

#include "AttachableJournals.h"
using namespace drogon;

using namespace drogon_model::openproject6;

/**
 * @brief this class is created by the drogon_ctl command.
 * this class is a restful API controller for reading and writing the attachable_journals table.
 */

class RestfulAttachableJournalsCtrl: public drogon::HttpController<RestfulAttachableJournalsCtrl>, public RestfulAttachableJournalsCtrlBase
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(RestfulAttachableJournalsCtrl::getOne,"/attachablejournals/{1}",Get,Options);
    ADD_METHOD_TO(RestfulAttachableJournalsCtrl::updateOne,"/attachablejournals/{1}",Put,Options);
    ADD_METHOD_TO(RestfulAttachableJournalsCtrl::deleteOne,"/attachablejournals/{1}",Delete,Options);
    ADD_METHOD_TO(RestfulAttachableJournalsCtrl::get,"/attachablejournals",Get,Options);
    ADD_METHOD_TO(RestfulAttachableJournalsCtrl::create,"/attachablejournals",Post,Options);
    //ADD_METHOD_TO(RestfulAttachableJournalsCtrl::update,"/attachablejournals",Put,Options);
    METHOD_LIST_END
    
    /**
     * Uncomment the following methods to customize for business logic.
     */
     /*
    void getOne(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback,
                AttachableJournals::PrimaryKeyType &&id);
    void updateOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   AttachableJournals::PrimaryKeyType &&id);
    void deleteOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   AttachableJournals::PrimaryKeyType &&id);
    void get(const HttpRequestPtr &req,
             std::function<void(const HttpResponsePtr &)> &&callback);
    void create(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback);
    */
};
