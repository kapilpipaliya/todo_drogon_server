/**
 *
 *  RestfulWikiRedirectsCtrl.h
 *  This file is generated by drogon_ctl
 *
 */

#pragma once

#include <drogon/HttpController.h>
#include "RestfulWikiRedirectsCtrlBase.h"

#include "WikiRedirects.h"
using namespace drogon;

using namespace drogon_model::openproject6;

/**
 * @brief this class is created by the drogon_ctl command.
 * this class is a restful API controller for reading and writing the wiki_redirects table.
 */

class RestfulWikiRedirectsCtrl: public drogon::HttpController<RestfulWikiRedirectsCtrl>, public RestfulWikiRedirectsCtrlBase
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(RestfulWikiRedirectsCtrl::getOne,"/wikiredirects/{1}",Get,Options);
    ADD_METHOD_TO(RestfulWikiRedirectsCtrl::updateOne,"/wikiredirects/{1}",Put,Options);
    ADD_METHOD_TO(RestfulWikiRedirectsCtrl::deleteOne,"/wikiredirects/{1}",Delete,Options);
    ADD_METHOD_TO(RestfulWikiRedirectsCtrl::get,"/wikiredirects",Get,Options);
    ADD_METHOD_TO(RestfulWikiRedirectsCtrl::create,"/wikiredirects",Post,Options);
    //ADD_METHOD_TO(RestfulWikiRedirectsCtrl::update,"/wikiredirects",Put,Options);
    METHOD_LIST_END
    
    /**
     * Uncomment the following methods to customize for business logic.
     */
     /*
    void getOne(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback,
                WikiRedirects::PrimaryKeyType &&id);
    void updateOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   WikiRedirects::PrimaryKeyType &&id);
    void deleteOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   WikiRedirects::PrimaryKeyType &&id);
    void get(const HttpRequestPtr &req,
             std::function<void(const HttpResponsePtr &)> &&callback);
    void create(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback);
    */
};
