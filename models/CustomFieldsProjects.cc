/**
 *
 *  CustomFieldsProjects.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "CustomFieldsProjects.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon_model::openproject6;

const std::string CustomFieldsProjects::Cols::_custom_field_id = "custom_field_id";
const std::string CustomFieldsProjects::Cols::_project_id = "project_id";
const std::string CustomFieldsProjects::primaryKeyName = "";
const bool CustomFieldsProjects::hasPrimaryKey = false;
const std::string CustomFieldsProjects::tableName = "custom_fields_projects";

const std::vector<typename CustomFieldsProjects::MetaData> CustomFieldsProjects::_metaData={
{"custom_field_id","int32_t","integer",4,0,0,1},
{"project_id","int32_t","integer",4,0,0,1}
};
const std::string &CustomFieldsProjects::getColumnName(size_t index) noexcept(false)
{
    assert(index < _metaData.size());
    return _metaData[index]._colName;
}
CustomFieldsProjects::CustomFieldsProjects(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["custom_field_id"].isNull())
        {
            _customFieldId=std::make_shared<int32_t>(r["custom_field_id"].as<int32_t>());
        }
        if(!r["project_id"].isNull())
        {
            _projectId=std::make_shared<int32_t>(r["project_id"].as<int32_t>());
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 2 > r.size())
        {
            LOG_FATAL << "Invalid SQL result for this model";
            return;
        }
        size_t index;
        index = offset + 0;
        if(!r[index].isNull())
        {
            _customFieldId=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 1;
        if(!r[index].isNull())
        {
            _projectId=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
    }

}

CustomFieldsProjects::CustomFieldsProjects(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 2)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        _dirtyFlag[0] = true;
        if(!pJson[pMasqueradingVector[0]].isNull())
        {
            _customFieldId=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[0]].asInt64());
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
}

CustomFieldsProjects::CustomFieldsProjects(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("custom_field_id"))
    {
        _dirtyFlag[0]=true;
        if(!pJson["custom_field_id"].isNull())
        {
            _customFieldId=std::make_shared<int32_t>((int32_t)pJson["custom_field_id"].asInt64());
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
}

void CustomFieldsProjects::updateByMasqueradedJson(const Json::Value &pJson,
                                            const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 2)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        _dirtyFlag[0] = true;
        if(!pJson[pMasqueradingVector[0]].isNull())
        {
            _customFieldId=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[0]].asInt64());
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
}
                                                                    
void CustomFieldsProjects::updateByJson(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("custom_field_id"))
    {
        _dirtyFlag[0] = true;
        if(!pJson["custom_field_id"].isNull())
        {
            _customFieldId=std::make_shared<int32_t>((int32_t)pJson["custom_field_id"].asInt64());
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
}

const int32_t &CustomFieldsProjects::getValueOfCustomFieldId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_customFieldId)
        return *_customFieldId;
    return defaultValue;
}
const std::shared_ptr<int32_t> &CustomFieldsProjects::getCustomFieldId() const noexcept
{
    return _customFieldId;
}
void CustomFieldsProjects::setCustomFieldId(const int32_t &pCustomFieldId) noexcept
{
    _customFieldId = std::make_shared<int32_t>(pCustomFieldId);
    _dirtyFlag[0] = true;
}


const int32_t &CustomFieldsProjects::getValueOfProjectId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_projectId)
        return *_projectId;
    return defaultValue;
}
const std::shared_ptr<int32_t> &CustomFieldsProjects::getProjectId() const noexcept
{
    return _projectId;
}
void CustomFieldsProjects::setProjectId(const int32_t &pProjectId) noexcept
{
    _projectId = std::make_shared<int32_t>(pProjectId);
    _dirtyFlag[1] = true;
}


void CustomFieldsProjects::updateId(const uint64_t id)
{
}

const std::vector<std::string> &CustomFieldsProjects::insertColumns() noexcept
{
    static const std::vector<std::string> _inCols={
        "custom_field_id",
        "project_id"
    };
    return _inCols;
}

void CustomFieldsProjects::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(_dirtyFlag[0])
    {
        if(getCustomFieldId())
        {
            binder << getValueOfCustomFieldId();
        }
        else
        {
            binder << nullptr;
        }
    }
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
}

const std::vector<std::string> CustomFieldsProjects::updateColumns() const
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

void CustomFieldsProjects::updateArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(_dirtyFlag[0])
    {
        if(getCustomFieldId())
        {
            binder << getValueOfCustomFieldId();
        }
        else
        {
            binder << nullptr;
        }
    }
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
}
Json::Value CustomFieldsProjects::toJson() const
{
    Json::Value ret;
    if(getCustomFieldId())
    {
        ret["custom_field_id"]=getValueOfCustomFieldId();
    }
    else
    {
        ret["custom_field_id"]=Json::Value();
    }
    if(getProjectId())
    {
        ret["project_id"]=getValueOfProjectId();
    }
    else
    {
        ret["project_id"]=Json::Value();
    }
    return ret;
}

Json::Value CustomFieldsProjects::toMasqueradedJson(
    const std::vector<std::string> &pMasqueradingVector) const
{
    Json::Value ret;
    if(pMasqueradingVector.size() == 2)
    {
        if(!pMasqueradingVector[0].empty())
        {
            if(getCustomFieldId())
            {
                ret[pMasqueradingVector[0]]=getValueOfCustomFieldId();
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
        return ret;
    }
    LOG_ERROR << "Masquerade failed";
    if(getCustomFieldId())
    {
        ret["custom_field_id"]=getValueOfCustomFieldId();
    }
    else
    {
        ret["custom_field_id"]=Json::Value();
    }
    if(getProjectId())
    {
        ret["project_id"]=getValueOfProjectId();
    }
    else
    {
        ret["project_id"]=Json::Value();
    }
    return ret;
}

bool CustomFieldsProjects::validateJsonForCreation(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("custom_field_id"))
    {
        if(!validJsonOfField(0, "custom_field_id", pJson["custom_field_id"], err, true))
            return false;
    }
    if(pJson.isMember("project_id"))
    {
        if(!validJsonOfField(1, "project_id", pJson["project_id"], err, true))
            return false;
    }
    return true;
}
bool CustomFieldsProjects::validateMasqueradedJsonForCreation(const Json::Value &pJson,
                                                              const std::vector<std::string> &pMasqueradingVector,
                                                              std::string &err)
{
    if(pMasqueradingVector.size() != 2)
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
    return true;
}
bool CustomFieldsProjects::validateJsonForUpdate(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("custom_field_id"))
    {
        if(!validJsonOfField(0, "custom_field_id", pJson["custom_field_id"], err, false))
            return false;
    }
    if(pJson.isMember("project_id"))
    {
        if(!validJsonOfField(1, "project_id", pJson["project_id"], err, false))
            return false;
    }
    return true;
}
bool CustomFieldsProjects::validateMasqueradedJsonForUpdate(const Json::Value &pJson,
                                                            const std::vector<std::string> &pMasqueradingVector,
                                                            std::string &err)
{
    if(pMasqueradingVector.size() != 2)
    {
        err = "Bad masquerading vector";
        return false;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        if(!validJsonOfField(0, pMasqueradingVector[0], pJson[pMasqueradingVector[0]], err, false))
            return false;
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        if(!validJsonOfField(1, pMasqueradingVector[1], pJson[pMasqueradingVector[1]], err, false))
            return false;
    }
    return true;
}
bool CustomFieldsProjects::validJsonOfField(size_t index,
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
            if(!pJson.isInt())
            {
                err="Type error in the "+fieldName+"field";
                return false;
            }
            break;
        case 1:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
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
