/**
 *
 *  RestfulRecaptchaEntriesCtrl.h
 *  This file is generated by drogon_ctl
 *
 */

#pragma once

#include <drogon/HttpController.h>
#include "RestfulRecaptchaEntriesCtrlBase.h"

#include "RecaptchaEntries.h"
using namespace drogon;

using namespace drogon_model::openproject6;

/**
 * @brief this class is created by the drogon_ctl command.
 * this class is a restful API controller for reading and writing the recaptcha_entries table.
 */

class RestfulRecaptchaEntriesCtrl: public drogon::HttpController<RestfulRecaptchaEntriesCtrl>, public RestfulRecaptchaEntriesCtrlBase
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(RestfulRecaptchaEntriesCtrl::getOne,"/recaptchaentries/{1}",Get,Options);
    ADD_METHOD_TO(RestfulRecaptchaEntriesCtrl::updateOne,"/recaptchaentries/{1}",Put,Options);
    ADD_METHOD_TO(RestfulRecaptchaEntriesCtrl::deleteOne,"/recaptchaentries/{1}",Delete,Options);
    ADD_METHOD_TO(RestfulRecaptchaEntriesCtrl::get,"/recaptchaentries",Get,Options);
    ADD_METHOD_TO(RestfulRecaptchaEntriesCtrl::create,"/recaptchaentries",Post,Options);
    //ADD_METHOD_TO(RestfulRecaptchaEntriesCtrl::update,"/recaptchaentries",Put,Options);
    METHOD_LIST_END
    
    /**
     * Uncomment the following methods to customize for business logic.
     */
     /*
    void getOne(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback,
                RecaptchaEntries::PrimaryKeyType &&id);
    void updateOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   RecaptchaEntries::PrimaryKeyType &&id);
    void deleteOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   RecaptchaEntries::PrimaryKeyType &&id);
    void get(const HttpRequestPtr &req,
             std::function<void(const HttpResponsePtr &)> &&callback);
    void create(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback);
    */
};
