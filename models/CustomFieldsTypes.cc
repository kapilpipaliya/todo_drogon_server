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
using namespace drogon_model::openproject4;

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
CustomFieldsTypes::CustomFieldsTypes(const Row &r) noexcept
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
