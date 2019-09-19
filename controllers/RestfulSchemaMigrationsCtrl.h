/**
 *
 *  RestfulSchemaMigrationsCtrl.h
 *  This file is generated by drogon_ctl
 *
 */

#pragma once

#include <drogon/HttpController.h>
#include "RestfulSchemaMigrationsCtrlBase.h"

#include "SchemaMigrations.h"
using namespace drogon;

using namespace drogon_model::openproject6;

/**
 * @brief this class is created by the drogon_ctl command.
 * this class is a restful API controller for reading and writing the schema_migrations table.
 */

class RestfulSchemaMigrationsCtrl: public drogon::HttpController<RestfulSchemaMigrationsCtrl>, public RestfulSchemaMigrationsCtrlBase
{
  public:
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(RestfulSchemaMigrationsCtrl::getOne,"/schemamigrations/{1}",Get,Options);
    ADD_METHOD_TO(RestfulSchemaMigrationsCtrl::updateOne,"/schemamigrations/{1}",Put,Options);
    ADD_METHOD_TO(RestfulSchemaMigrationsCtrl::deleteOne,"/schemamigrations/{1}",Delete,Options);
    ADD_METHOD_TO(RestfulSchemaMigrationsCtrl::get,"/schemamigrations",Get,Options);
    ADD_METHOD_TO(RestfulSchemaMigrationsCtrl::create,"/schemamigrations",Post,Options);
    //ADD_METHOD_TO(RestfulSchemaMigrationsCtrl::update,"/schemamigrations",Put,Options);
    METHOD_LIST_END
    
    /**
     * Uncomment the following methods to customize for business logic.
     */
     /*
    void getOne(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback,
                SchemaMigrations::PrimaryKeyType &&id);
    void updateOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   SchemaMigrations::PrimaryKeyType &&id);
    void deleteOne(const HttpRequestPtr &req,
                   std::function<void(const HttpResponsePtr &)> &&callback,
                   SchemaMigrations::PrimaryKeyType &&id);
    void get(const HttpRequestPtr &req,
             std::function<void(const HttpResponsePtr &)> &&callback);
    void create(const HttpRequestPtr &req,
                std::function<void(const HttpResponsePtr &)> &&callback);
    */
};
