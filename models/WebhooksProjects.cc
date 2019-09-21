/**
 *
 *  WebhooksProjects.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "WebhooksProjects.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon_model::openproject6;

const std::string WebhooksProjects::Cols::_id = "id";
const std::string WebhooksProjects::Cols::_project_id = "project_id";
const std::string WebhooksProjects::Cols::_webhooks_webhook_id = "webhooks_webhook_id";
const std::string WebhooksProjects::primaryKeyName = "id";
const bool WebhooksProjects::hasPrimaryKey = true;
const std::string WebhooksProjects::tableName = "webhooks_projects";

const std::vector<typename WebhooksProjects::MetaData> WebhooksProjects::_metaData={
{"id","int32_t","integer",4,1,1,1},
{"project_id","int32_t","integer",4,0,0,0},
{"webhooks_webhook_id","int32_t","integer",4,0,0,0}
};
const std::string &WebhooksProjects::getColumnName(size_t index) noexcept(false)
{
    assert(index < _metaData.size());
    return _metaData[index]._colName;
}
WebhooksProjects::WebhooksProjects(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            _id=std::make_shared<int32_t>(r["id"].as<int32_t>());
        }
        if(!r["project_id"].isNull())
        {
            _projectId=std::make_shared<int32_t>(r["project_id"].as<int32_t>());
        }
        if(!r["webhooks_webhook_id"].isNull())
        {
            _webhooksWebhookId=std::make_shared<int32_t>(r["webhooks_webhook_id"].as<int32_t>());
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 3 > r.size())
        {
            LOG_FATAL << "Invalid SQL result for this model";
            return;
        }
        size_t index;
        index = offset + 0;
        if(!r[index].isNull())
        {
            _id=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 1;
        if(!r[index].isNull())
        {
            _projectId=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            _webhooksWebhookId=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
    }

}

WebhooksProjects::WebhooksProjects(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 3)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        _dirtyFlag[0] = true;
        if(!pJson[pMasqueradingVector[0]].isNull())
        {
            _id=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[0]].asInt64());
        }
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        _dirtyFlag[1] = true;
        if(!pJson[pMasqueradingVector[1]].isNull())
        {
            _projectId=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[1]].asInt64());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        _dirtyFlag[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            _webhooksWebhookId=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[2]].asInt64());
        }
    }
}

WebhooksProjects::WebhooksProjects(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        _dirtyFlag[0]=true;
        if(!pJson["id"].isNull())
        {
            _id=std::make_shared<int32_t>((int32_t)pJson["id"].asInt64());
        }
    }
    if(pJson.isMember("project_id"))
    {
        _dirtyFlag[1]=true;
        if(!pJson["project_id"].isNull())
        {
            _projectId=std::make_shared<int32_t>((int32_t)pJson["project_id"].asInt64());
        }
    }
    if(pJson.isMember("webhooks_webhook_id"))
    {
        _dirtyFlag[2]=true;
        if(!pJson["webhooks_webhook_id"].isNull())
        {
            _webhooksWebhookId=std::make_shared<int32_t>((int32_t)pJson["webhooks_webhook_id"].asInt64());
        }
    }
}

void WebhooksProjects::updateByMasqueradedJson(const Json::Value &pJson,
                                            const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 3)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        if(!pJson[pMasqueradingVector[0]].isNull())
        {
            _id=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[0]].asInt64());
        }
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        _dirtyFlag[1] = true;
        if(!pJson[pMasqueradingVector[1]].isNull())
        {
            _projectId=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[1]].asInt64());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        _dirtyFlag[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            _webhooksWebhookId=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[2]].asInt64());
        }
    }
}
                                                                    
void WebhooksProjects::updateByJson(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        if(!pJson["id"].isNull())
        {
            _id=std::make_shared<int32_t>((int32_t)pJson["id"].asInt64());
        }
    }
    if(pJson.isMember("project_id"))
    {
        _dirtyFlag[1] = true;
        if(!pJson["project_id"].isNull())
        {
            _projectId=std::make_shared<int32_t>((int32_t)pJson["project_id"].asInt64());
        }
    }
    if(pJson.isMember("webhooks_webhook_id"))
    {
        _dirtyFlag[2] = true;
        if(!pJson["webhooks_webhook_id"].isNull())
        {
            _webhooksWebhookId=std::make_shared<int32_t>((int32_t)pJson["webhooks_webhook_id"].asInt64());
        }
    }
}

const int32_t &WebhooksProjects::getValueOfId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_id)
        return *_id;
    return defaultValue;
}
const std::shared_ptr<int32_t> &WebhooksProjects::getId() const noexcept
{
    return _id;
}
const typename WebhooksProjects::PrimaryKeyType & WebhooksProjects::getPrimaryKey() const
{
    assert(_id);
    return *_id;
}

const int32_t &WebhooksProjects::getValueOfProjectId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_projectId)
        return *_projectId;
    return defaultValue;
}
const std::shared_ptr<int32_t> &WebhooksProjects::getProjectId() const noexcept
{
    return _projectId;
}
void WebhooksProjects::setProjectId(const int32_t &pProjectId) noexcept
{
    _projectId = std::make_shared<int32_t>(pProjectId);
    _dirtyFlag[1] = true;
}


const int32_t &WebhooksProjects::getValueOfWebhooksWebhookId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_webhooksWebhookId)
        return *_webhooksWebhookId;
    return defaultValue;
}
const std::shared_ptr<int32_t> &WebhooksProjects::getWebhooksWebhookId() const noexcept
{
    return _webhooksWebhookId;
}
void WebhooksProjects::setWebhooksWebhookId(const int32_t &pWebhooksWebhookId) noexcept
{
    _webhooksWebhookId = std::make_shared<int32_t>(pWebhooksWebhookId);
    _dirtyFlag[2] = true;
}


void WebhooksProjects::updateId(const uint64_t id)
{
}

const std::vector<std::string> &WebhooksProjects::insertColumns() noexcept
{
    static const std::vector<std::string> _inCols={
        "project_id",
        "webhooks_webhook_id"
    };
    return _inCols;
}

void WebhooksProjects::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(_dirtyFlag[1])
    {
        if(getProjectId())
        {
            binder << getValueOfProjectId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[2])
    {
        if(getWebhooksWebhookId())
        {
            binder << getValueOfWebhooksWebhookId();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> WebhooksProjects::updateColumns() const
{
    std::vector<std::string> ret;
    for(size_t i=0;i<sizeof(_dirtyFlag);i++)
    {
        if(_dirtyFlag[i])
        {
            ret.push_back(getColumnName(i));
        }
    }
    return ret;
}

void WebhooksProjects::updateArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(_dirtyFlag[1])
    {
        if(getProjectId())
        {
            binder << getValueOfProjectId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[2])
    {
        if(getWebhooksWebhookId())
        {
            binder << getValueOfWebhooksWebhookId();
        }
        else
        {
            binder << nullptr;
        }
    }
}
Json::Value WebhooksProjects::toJson() const
{
    Json::Value ret;
    if(getId())
    {
        ret["id"]=getValueOfId();
    }
    else
    {
        ret["id"]=Json::Value();
    }
    if(getProjectId())
    {
        ret["project_id"]=getValueOfProjectId();
    }
    else
    {
        ret["project_id"]=Json::Value();
    }
    if(getWebhooksWebhookId())
    {
        ret["webhooks_webhook_id"]=getValueOfWebhooksWebhookId();
    }
    else
    {
        ret["webhooks_webhook_id"]=Json::Value();
    }
    return ret;
}

Json::Value WebhooksProjects::toMasqueradedJson(
    const std::vector<std::string> &pMasqueradingVector) const
{
    Json::Value ret;
    if(pMasqueradingVector.size() == 3)
    {
        if(!pMasqueradingVector[0].empty())
        {
            if(getId())
            {
                ret[pMasqueradingVector[0]]=getValueOfId();
            }
            else
            {
                ret[pMasqueradingVector[0]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[1].empty())
        {
            if(getProjectId())
            {
                ret[pMasqueradingVector[1]]=getValueOfProjectId();
            }
            else
            {
                ret[pMasqueradingVector[1]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[2].empty())
        {
            if(getWebhooksWebhookId())
            {
                ret[pMasqueradingVector[2]]=getValueOfWebhooksWebhookId();
            }
            else
            {
                ret[pMasqueradingVector[2]]=Json::Value();
            }
        }
        return ret;
    }
    LOG_ERROR << "Masquerade failed";
    if(getId())
    {
        ret["id"]=getValueOfId();
    }
    else
    {
        ret["id"]=Json::Value();
    }
    if(getProjectId())
    {
        ret["project_id"]=getValueOfProjectId();
    }
    else
    {
        ret["project_id"]=Json::Value();
    }
    if(getWebhooksWebhookId())
    {
        ret["webhooks_webhook_id"]=getValueOfWebhooksWebhookId();
    }
    else
    {
        ret["webhooks_webhook_id"]=Json::Value();
    }
    return ret;
}

bool WebhooksProjects::validateJsonForCreation(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("id"))
    {
        if(!validJsonOfField(0, "id", pJson["id"], err, true))
            return false;
    }
    if(pJson.isMember("project_id"))
    {
        if(!validJsonOfField(1, "project_id", pJson["project_id"], err, true))
            return false;
    }
    if(pJson.isMember("webhooks_webhook_id"))
    {
        if(!validJsonOfField(2, "webhooks_webhook_id", pJson["webhooks_webhook_id"], err, true))
            return false;
    }
    return true;
}
bool WebhooksProjects::validateMasqueradedJsonForCreation(const Json::Value &pJson,
                                                          const std::vector<std::string> &pMasqueradingVector,
                                                          std::string &err)
{
    if(pMasqueradingVector.size() != 3)
    {
        err = "Bad masquerading vector";
        return false;
    }
    if(!pMasqueradingVector[0].empty())
    {
        if(pJson.isMember(pMasqueradingVector[0]))
        {
            if(!validJsonOfField(0, pMasqueradingVector[0], pJson[pMasqueradingVector[0]], err, true))
                return false;
        }
    }
    if(!pMasqueradingVector[1].empty())
    {
        if(pJson.isMember(pMasqueradingVector[1]))
        {
            if(!validJsonOfField(1, pMasqueradingVector[1], pJson[pMasqueradingVector[1]], err, true))
                return false;
        }
    }
    if(!pMasqueradingVector[2].empty())
    {
        if(pJson.isMember(pMasqueradingVector[2]))
        {
            if(!validJsonOfField(2, pMasqueradingVector[2], pJson[pMasqueradingVector[2]], err, true))
                return false;
        }
    }
    return true;
}
bool WebhooksProjects::validateJsonForUpdate(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("id"))
    {
        if(!validJsonOfField(0, "id", pJson["id"], err, false))
            return false;
    }
    else
    {
        err = "The value of primary key must be set in the json object for update";
        return false;
    }
    if(pJson.isMember("project_id"))
    {
        if(!validJsonOfField(1, "project_id", pJson["project_id"], err, false))
            return false;
    }
    if(pJson.isMember("webhooks_webhook_id"))
    {
        if(!validJsonOfField(2, "webhooks_webhook_id", pJson["webhooks_webhook_id"], err, false))
            return false;
    }
    return true;
}
bool WebhooksProjects::validateMasqueradedJsonForUpdate(const Json::Value &pJson,
                                                        const std::vector<std::string> &pMasqueradingVector,
                                                        std::string &err)
{
    if(pMasqueradingVector.size() != 3)
    {
        err = "Bad masquerading vector";
        return false;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        if(!validJsonOfField(0, pMasqueradingVector[0], pJson[pMasqueradingVector[0]], err, false))
            return false;
    }
    else
    {
        err = "The value of primary key must be set in the json object for update";
        return false;
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        if(!validJsonOfField(1, pMasqueradingVector[1], pJson[pMasqueradingVector[1]], err, false))
            return false;
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        if(!validJsonOfField(2, pMasqueradingVector[2], pJson[pMasqueradingVector[2]], err, false))
            return false;
    }
    return true;
}
bool WebhooksProjects::validJsonOfField(size_t index,
                                        const std::string &fieldName,
                                        const Json::Value &pJson, 
                                        std::string &err, 
                                        bool isForCreation)
{
    switch(index)
    {
        case 0:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(isForCreation)
            {
                err="The automatic primary key cannot be set";
                return false;
            }        
            if(!pJson.isInt())
            {
                err="Type error in the "+fieldName+"field";
                return false;
            }
            break;
        case 1:
            if(!pJson.isInt())
            {
                err="Type error in the "+fieldName+"field";
                return false;
            }
            break;
        case 2:
            if(!pJson.isInt())
            {
                err="Type error in the "+fieldName+"field";
                return false;
            }
            break;
     
        default:
            err="Internal error in the server";
            return false;
            break;
    }
    return true;
}
