/**
 *
 *  RestfulEnterpriseTokensCtrl.h
 *  This file is generated by drogon_ctl
 *
 */

#pragma once

#include <drogon/HttpController.h>
#include "RestfulEnterpriseTokensCtrlBase.h"

#include "EnterpriseTokens.h"
using namespace drogon;

using namespace drogon_model::openproject6;

/**
 * @brief this class is created by the drogon_ctl command.
 * this class is a restful API controller for reading and writing the enterprise_tokens table.
 */

class RestfulEnterpriseTokensCtrl: public drogon::HttpController<RestfulEnterpriseTokensCtrl>, public RestfulEnterpriseTokensCtrlBase
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(RestfulEnterpriseTokensCtrl::getOne,"/enterprisetokens/{1}",Get,Options);
    ADD_METHOD_TO(RestfulEnterpriseTokensCtrl::updateOne,"/enterprisetokens/{1}",Put,Options);
    ADD_METHOD_TO(RestfulEnterpriseTokensCtrl::deleteOne,"/enterprisetokens/{1}",Delete,Options);
    ADD_METHOD_TO(RestfulEnterpriseTokensCtrl::get,"/enterprisetokens",Get,Options);
    ADD_METHOD_TO(RestfulEnterpriseTokensCtrl::create,"/enterprisetokens",Post,Options);
    //ADD_METHOD_TO(RestfulEnterpriseTokensCtrl::update,"/enterprisetokens",Put,Options);
    METHOD_LIST_END
    
    /**
     * Uncomment the following methods to customize for business logic.
     */
     /*
    void getOne(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback,
                EnterpriseTokens::PrimaryKeyType &&id);
    void updateOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   EnterpriseTokens::PrimaryKeyType &&id);
    void deleteOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   EnterpriseTokens::PrimaryKeyType &&id);
    void get(const HttpRequestPtr &req,
             std::function<void(const HttpResponsePtr &)> &&callback);
    void create(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback);
    */
};
