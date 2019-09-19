/**
 *
 *  RestfulTokensCtrlBase.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl automatically.
 *  Users should implement business logic in the derived class.
 */

#include "RestfulTokensCtrl.h"
#include <string>




void RestfulTokensCtrlBase::getOne(const HttpRequestPtr &req,
                                   std::function<void(const HttpResponsePtr &)> &&callback,
                                   Tokens::PrimaryKeyType &&id)
{

    auto dbClientPtr = getDbClient();
    auto callbackPtr =
        std::make_shared<std::function<void(const HttpResponsePtr &)>>(
            std::move(callback));
    drogon::orm::Mapper<Tokens> mapper(dbClientPtr);
    mapper.findByPrimaryKey(
        id,
        [callbackPtr, this](Tokens r) {
            if(_masquerading)
            {
                (*callbackPtr)(HttpResponse::newHttpJsonResponse(
                    r.toMasqueradedJson(_masqueradingVector)));
            }
            else
            {
                (*callbackPtr)(HttpResponse::newHttpJsonResponse(r.toJson()));
            }
        },
        [callbackPtr](const DrogonDbException &e) {
            const drogon::orm::UnexpectedRows *s=dynamic_cast<const drogon::orm::UnexpectedRows *>(&e.base());
            if(s)
            {
                auto resp = HttpResponse::newHttpResponse();
                resp->setStatusCode(k404NotFound);
                (*callbackPtr)(resp);
                return;
            }
            LOG_ERROR<<e.base().what();
            Json::Value ret;
            ret["error"] = "database error";
            auto resp = HttpResponse::newHttpJsonResponse(ret);
            resp->setStatusCode(k500InternalServerError);
            (*callbackPtr)(resp);
        });
}


void RestfulTokensCtrlBase::updateOne(const HttpRequestPtr &req,
                                      std::function<void(const HttpResponsePtr &)> &&callback,
                                      Tokens::PrimaryKeyType &&id)
{
    auto jsonPtr=req->jsonObject();
    if(!jsonPtr)
    {
        Json::Value ret;
        ret["error"]="No json object is found in the request";
        auto resp= HttpResponse::newHttpJsonResponse(ret);
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;
    }
    Tokens object;
    try
    {
        if(_masquerading)
        {
            object.updateByMasqueradedJson(*jsonPtr, _masqueradingVector);
        }
        else
        {
            object.updateByJson(*jsonPtr);
        }
    }
    catch(const Json::Exception &e)
    {
        LOG_ERROR << e.what();
        Json::Value ret;
        ret["error"]="Field type error";
        auto resp= HttpResponse::newHttpJsonResponse(ret);
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;        
    }
    if(object.getPrimaryKey() != id)
    {
        Json::Value ret;
        ret["error"]="Bad primary key";
        auto resp= HttpResponse::newHttpJsonResponse(ret);
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;
    }

    auto dbClientPtr = getDbClient();
    auto callbackPtr =
        std::make_shared<std::function<void(const HttpResponsePtr &)>>(
            std::move(callback));
    drogon::orm::Mapper<Tokens> mapper(dbClientPtr);

    mapper.update(
        object,
        [callbackPtr](const size_t count) 
        {
            if(count == 1)
            {
                auto resp = HttpResponse::newHttpResponse();
                resp->setStatusCode(k202Accepted);
                (*callbackPtr)(resp);
            }
            else if(count == 0)
            {
                Json::Value ret;
                ret["error"]="No resources are updated";
                auto resp = HttpResponse::newHttpJsonResponse(ret);
                resp->setStatusCode(k404NotFound);
                (*callbackPtr)(resp);
            }
            else
            {
                LOG_FATAL << "More than one resource is updated: " << count;
                Json::Value ret;
                ret["error"] = "database error";
                auto resp = HttpResponse::newHttpJsonResponse(ret);
                resp->setStatusCode(k500InternalServerError);
                (*callbackPtr)(resp);
            }
        },
        [callbackPtr](const DrogonDbException &e) {
            LOG_ERROR << e.base().what();
            Json::Value ret;
            ret["error"] = "database error";
            auto resp = HttpResponse::newHttpJsonResponse(ret);
            resp->setStatusCode(k500InternalServerError);
            (*callbackPtr)(resp);
        });
}


void RestfulTokensCtrlBase::deleteOne(const HttpRequestPtr &req,
                                      std::function<void(const HttpResponsePtr &)> &&callback,
                                      Tokens::PrimaryKeyType &&id)
{

    auto dbClientPtr = getDbClient();
    auto callbackPtr =
        std::make_shared<std::function<void(const HttpResponsePtr &)>>(
            std::move(callback));
    drogon::orm::Mapper<Tokens> mapper(dbClientPtr);
    mapper.deleteByPrimaryKey(
        id,
        [callbackPtr](const size_t count) {
            if(count == 1)
            {
                auto resp = HttpResponse::newHttpResponse();
                resp->setStatusCode(k204NoContent);
                (*callbackPtr)(resp);
            }
            else if(count == 0)
            {
                Json::Value ret;
                ret["error"] = "No resources deleted";
                auto resp = HttpResponse::newHttpJsonResponse(ret);
                resp->setStatusCode(k404NotFound);
                (*callbackPtr)(resp);
            }
            else
            {
                LOG_FATAL << "Delete more than one records: " << count;
                Json::Value ret;
                ret["error"] = "Database error";
                auto resp = HttpResponse::newHttpJsonResponse(ret);
                resp->setStatusCode(k500InternalServerError);
                (*callbackPtr)(resp);
            }
        },
        [callbackPtr](const DrogonDbException &e) {
            LOG_ERROR << e.base().what();
            Json::Value ret;
            ret["error"] = "database error";
            auto resp = HttpResponse::newHttpJsonResponse(ret);
            resp->setStatusCode(k500InternalServerError);
            (*callbackPtr)(resp);
        });
}

void RestfulTokensCtrlBase::get(const HttpRequestPtr &req,
                                std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto dbClientPtr = getDbClient();
    drogon::orm::Mapper<Tokens> mapper(dbClientPtr);
    auto &parameters = req->parameters();
    auto iter = parameters.find("sort");
    if(iter != parameters.end())
    {
        auto sortFields = drogon::utils::splitString(iter->second, ",");
        for(auto &field : sortFields)
        {
            if(field.empty())
                continue;
            if(field[0] == '+')
            {
                field = field.substr(1);
                mapper.orderBy(field, SortOrder::ASC);
            }
            else if(field[0] == '-')
            {
                field = field.substr(1);
                mapper.orderBy(field, SortOrder::DESC);
            }
            else
            {
                mapper.orderBy(field, SortOrder::ASC);
            }
        }
    }
    iter = parameters.find("offset");
    if(iter != parameters.end())
    {
        try{
            auto offset = std::stoll(iter->second);
            mapper.offset(offset);
        }
        catch(...)
        {
            auto resp = HttpResponse::newHttpResponse();
            resp->setStatusCode(k400BadRequest);
            callback(resp);
            return;
        }
    }
    iter = parameters.find("limit");
    if(iter != parameters.end())
    {
        try{
            auto limit = std::stoll(iter->second);
            mapper.limit(limit);
        }
        catch(...)
        {
            auto resp = HttpResponse::newHttpResponse();
            resp->setStatusCode(k400BadRequest);
            callback(resp);
            return;
        }
    }    
    auto callbackPtr =
        std::make_shared<std::function<void(const HttpResponsePtr &)>>(
            std::move(callback));
    mapper.findAll([callbackPtr, this](const std::vector<Tokens> &v) {
            Json::Value ret;
            ret.resize(0);
            for (auto &obj : v)
            {
                if(_masquerading)
                {
                    ret.append(obj.toMasqueradedJson(_masqueradingVector));
                }
                else
                {
                    ret.append(obj.toJson());
                }
            }
            (*callbackPtr)(HttpResponse::newHttpJsonResponse(ret));
        },
        [callbackPtr](const DrogonDbException &e) { 
            LOG_ERROR << e.base().what();
            Json::Value ret;
            ret["error"] = "database error";
            auto resp = HttpResponse::newHttpJsonResponse(ret);
            resp->setStatusCode(k500InternalServerError);
            (*callbackPtr)(resp);    
        });
}

void RestfulTokensCtrlBase::create(const HttpRequestPtr &req,
                                   std::function<void(const HttpResponsePtr &)> &&callback)
{
    auto jsonPtr=req->jsonObject();
    if(!jsonPtr)
    {
        Json::Value ret;
        ret["error"]="No json object is found in the request";
        auto resp= HttpResponse::newHttpJsonResponse(ret);
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;
    }
    try 
    {
        Tokens object = 
            (_masquerading? 
             Tokens(*jsonPtr, _masqueradingVector) : 
             Tokens(*jsonPtr));
        auto dbClientPtr = getDbClient();
        auto callbackPtr =
            std::make_shared<std::function<void(const HttpResponsePtr &)>>(
                std::move(callback));
        drogon::orm::Mapper<Tokens> mapper(dbClientPtr);
        mapper.insert(
            object,
            [callbackPtr, this](Tokens newObject){
                if(_masquerading)
                {
                    (*callbackPtr)(HttpResponse::newHttpJsonResponse(
                        newObject.toMasqueradedJson(_masqueradingVector)));
                }
                else
                {
                    (*callbackPtr)(HttpResponse::newHttpJsonResponse(newObject.toJson()));
                }
            },
            [callbackPtr](const DrogonDbException &e){
                LOG_ERROR << e.base().what();
                Json::Value ret;
                ret["error"] = "database error";
                auto resp = HttpResponse::newHttpJsonResponse(ret);
                resp->setStatusCode(k500InternalServerError);
                (*callbackPtr)(resp);   
            });
    }
    catch(const Json::Exception &e)
    {
        LOG_ERROR << e.what();
        Json::Value ret;
        ret["error"]="Field type error";
        auto resp= HttpResponse::newHttpJsonResponse(ret);
        resp->setStatusCode(k400BadRequest);
        callback(resp);
        return;        
    }   
}

/*
void RestfulTokensCtrlBase::update(const HttpRequestPtr &req,
                                   std::function<void(const HttpResponsePtr &)> &&callback)
{

}*/
