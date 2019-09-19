/**
 *
 *  CustomFieldsTypes.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "CustomFieldsTypes.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon_model::openproject6;

const std::string CustomFieldsTypes::Cols::_custom_field_id = "custom_field_id";
const std::string CustomFieldsTypes::Cols::_type_id = "type_id";
const std::string CustomFieldsTypes::primaryKeyName = "";
const bool CustomFieldsTypes::hasPrimaryKey = false;
const std::string CustomFieldsTypes::tableName = "custom_fields_types";

const std::vector<typename CustomFieldsTypes::MetaData> CustomFieldsTypes::_metaData={
{"custom_field_id","int32_t","integer",4,0,0,1},
{"type_id","int32_t","integer",4,0,0,1}
};
const std::string &CustomFieldsTypes::getColumnName(size_t index) noexcept(false)
{
    assert(index < _metaData.size());
    return _metaData[index]._colName;
}
CustomFieldsTypes::CustomFieldsTypes(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["custom_field_id"].isNull())
        {
            _customFieldId=std::make_shared<int32_t>(r["custom_field_id"].as<int32_t>());
        }
        if(!r["type_id"].isNull())
        {
            _typeId=std::make_shared<int32_t>(r["type_id"].as<int32_t>());
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
            _typeId=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
    }

}

CustomFieldsTypes::CustomFieldsTypes(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 2)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        _customFieldId=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[0]].asInt64());
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        _typeId=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[1]].asInt64());
    }
}

CustomFieldsTypes::CustomFieldsTypes(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("custom_field_id"))
    {
        _customFieldId=std::make_shared<int32_t>((int32_t)pJson["custom_field_id"].asInt64());
    }
    if(pJson.isMember("type_id"))
    {
        _typeId=std::make_shared<int32_t>((int32_t)pJson["type_id"].asInt64());
    }
}

void CustomFieldsTypes::updateByMasqueradedJson(const Json::Value &pJson,
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
        _customFieldId=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[0]].asInt64());
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        _dirtyFlag[1] = true;
        _typeId=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[1]].asInt64());
    }
}
                                                                    
void CustomFieldsTypes::updateByJson(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("custom_field_id"))
    {
        _dirtyFlag[0] = true;
        _customFieldId=std::make_shared<int32_t>((int32_t)pJson["custom_field_id"].asInt64());
    }
    if(pJson.isMember("type_id"))
    {
        _dirtyFlag[1] = true;
        _typeId=std::make_shared<int32_t>((int32_t)pJson["type_id"].asInt64());
    }
}

const int32_t &CustomFieldsTypes::getValueOfCustomFieldId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_customFieldId)
        return *_customFieldId;
    return defaultValue;
}
const std::shared_ptr<int32_t> &CustomFieldsTypes::getCustomFieldId() const noexcept
{
    return _customFieldId;
}
void CustomFieldsTypes::setCustomFieldId(const int32_t &pCustomFieldId) noexcept
{
    _customFieldId = std::make_shared<int32_t>(pCustomFieldId);
    _dirtyFlag[0] = true;
}


const int32_t &CustomFieldsTypes::getValueOfTypeId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_typeId)
        return *_typeId;
    return defaultValue;
}
const std::shared_ptr<int32_t> &CustomFieldsTypes::getTypeId() const noexcept
{
    return _typeId;
}
void CustomFieldsTypes::setTypeId(const int32_t &pTypeId) noexcept
{
    _typeId = std::make_shared<int32_t>(pTypeId);
    _dirtyFlag[1] = true;
}


void CustomFieldsTypes::updateId(const uint64_t id)
{
}

const std::vector<std::string> &CustomFieldsTypes::insertColumns() noexcept
{
    static const std::vector<std::string> _inCols={
        "custom_field_id",
        "type_id"
    };
    return _inCols;
}

void CustomFieldsTypes::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(getCustomFieldId())
    {
        binder << getValueOfCustomFieldId();
    }
    else
    {
        binder << nullptr;
    }
    if(getTypeId())
    {
        binder << getValueOfTypeId();
    }
    else
    {
        binder << nullptr;
    }
}

const std::vector<std::string> CustomFieldsTypes::updateColumns() const
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

void CustomFieldsTypes::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getTypeId())
        {
            binder << getValueOfTypeId();
        }
        else
        {
            binder << nullptr;
        }
    }
}
Json::Value CustomFieldsTypes::toJson() const
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
    if(getTypeId())
    {
        ret["type_id"]=getValueOfTypeId();
    }
    else
    {
        ret["type_id"]=Json::Value();
    }
    return ret;
}

Json::Value CustomFieldsTypes::toMasqueradedJson(
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
            if(getTypeId())
            {
                ret[pMasqueradingVector[1]]=getValueOfTypeId();
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
    if(getTypeId())
    {
        ret["type_id"]=getValueOfTypeId();
    }
    else
    {
        ret["type_id"]=Json::Value();
    }
    return ret;
}

bool CustomFieldsTypes::validateJsonForCreation(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("custom_field_id"))
    {
        if(!validJsonOfField(0, "custom_field_id", pJson["custom_field_id"], err, true))
            return false;
    }
    if(pJson.isMember("type_id"))
    {
        if(!validJsonOfField(1, "type_id", pJson["type_id"], err, true))
            return false;
    }
    return true;
}
bool CustomFieldsTypes::validateMasqueradedJsonForCreation(const Json::Value &pJson,
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
bool CustomFieldsTypes::validateJsonForUpdate(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("custom_field_id"))
    {
        if(!validJsonOfField(0, "custom_field_id", pJson["custom_field_id"], err, false))
            return false;
    }
    if(pJson.isMember("type_id"))
    {
        if(!validJsonOfField(1, "type_id", pJson["type_id"], err, false))
            return false;
    }
    return true;
}
bool CustomFieldsTypes::validateMasqueradedJsonForUpdate(const Json::Value &pJson,
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
bool CustomFieldsTypes::validJsonOfField(size_t index,
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
