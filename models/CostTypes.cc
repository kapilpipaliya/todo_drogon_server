/**
 *
 *  CostTypes.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "CostTypes.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon_model::openproject4;

const std::string CostTypes::Cols::_id = "id";
const std::string CostTypes::Cols::_name = "name";
const std::string CostTypes::Cols::_unit = "unit";
const std::string CostTypes::Cols::_unit_plural = "unit_plural";
const std::string CostTypes::Cols::_default = "default";
const std::string CostTypes::Cols::_deleted_at = "deleted_at";
const std::string CostTypes::primaryKeyName = "id";
const bool CostTypes::hasPrimaryKey = true;
const std::string CostTypes::tableName = "cost_types";

const std::vector<typename CostTypes::MetaData> CostTypes::_metaData={
{"id","int32_t","integer",4,1,1,1},
{"name","std::string","character varying",0,0,0,1},
{"unit","std::string","character varying",0,0,0,1},
{"unit_plural","std::string","character varying",0,0,0,1},
{"default","bool","boolean",1,0,0,1},
{"deleted_at","::trantor::Date","timestamp without time zone",0,0,0,0}
};
const std::string &CostTypes::getColumnName(size_t index) noexcept(false)
{
    assert(index < _metaData.size());
    return _metaData[index]._colName;
}
CostTypes::CostTypes(const Row &r) noexcept
{
        if(!r["id"].isNull())
        {
            _id=std::make_shared<int32_t>(r["id"].as<int32_t>());
        }
        if(!r["name"].isNull())
        {
            _name=std::make_shared<std::string>(r["name"].as<std::string>());
        }
        if(!r["unit"].isNull())
        {
            _unit=std::make_shared<std::string>(r["unit"].as<std::string>());
        }
        if(!r["unit_plural"].isNull())
        {
            _unitPlural=std::make_shared<std::string>(r["unit_plural"].as<std::string>());
        }
        if(!r["default"].isNull())
        {
            _default=std::make_shared<bool>(r["default"].as<bool>());
        }
        if(!r["deleted_at"].isNull())
        {
            auto timeStr = r["deleted_at"].as<std::string>();
            struct tm stm;
            memset(&stm,0,sizeof(stm));
            auto p = strptime(timeStr.c_str(),"%Y-%m-%d %H:%M:%S",&stm);
            size_t t = timelocal(&stm);
            size_t decimalNum = 0;
            if(*p=='.')
            {
                std::string decimals(p+1,&timeStr[timeStr.length()]);
                while(decimals.length()<6)
                {
                    decimals += "0";
                }
                decimalNum = (size_t)atol(decimals.c_str());
            }
            _deletedAt=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
        }
}
const int32_t &CostTypes::getValueOfId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_id)
        return *_id;
    return defaultValue;
}
const std::shared_ptr<int32_t> &CostTypes::getId() const noexcept
{
    return _id;
}
const typename CostTypes::PrimaryKeyType & CostTypes::getPrimaryKey() const
{
    assert(_id);
    return *_id;
}

const std::string &CostTypes::getValueOfName() const noexcept
{
    const static std::string defaultValue = std::string();
    if(_name)
        return *_name;
    return defaultValue;
}
const std::shared_ptr<std::string> &CostTypes::getName() const noexcept
{
    return _name;
}
void CostTypes::setName(const std::string &pName) noexcept
{
    _name = std::make_shared<std::string>(pName);
    _dirtyFlag[1] = true;
}
void CostTypes::setName(std::string &&pName) noexcept
{
    _name = std::make_shared<std::string>(std::move(pName));
    _dirtyFlag[1] = true;
}


const std::string &CostTypes::getValueOfUnit() const noexcept
{
    const static std::string defaultValue = std::string();
    if(_unit)
        return *_unit;
    return defaultValue;
}
const std::shared_ptr<std::string> &CostTypes::getUnit() const noexcept
{
    return _unit;
}
void CostTypes::setUnit(const std::string &pUnit) noexcept
{
    _unit = std::make_shared<std::string>(pUnit);
    _dirtyFlag[2] = true;
}
void CostTypes::setUnit(std::string &&pUnit) noexcept
{
    _unit = std::make_shared<std::string>(std::move(pUnit));
    _dirtyFlag[2] = true;
}


const std::string &CostTypes::getValueOfUnitPlural() const noexcept
{
    const static std::string defaultValue = std::string();
    if(_unitPlural)
        return *_unitPlural;
    return defaultValue;
}
const std::shared_ptr<std::string> &CostTypes::getUnitPlural() const noexcept
{
    return _unitPlural;
}
void CostTypes::setUnitPlural(const std::string &pUnitPlural) noexcept
{
    _unitPlural = std::make_shared<std::string>(pUnitPlural);
    _dirtyFlag[3] = true;
}
void CostTypes::setUnitPlural(std::string &&pUnitPlural) noexcept
{
    _unitPlural = std::make_shared<std::string>(std::move(pUnitPlural));
    _dirtyFlag[3] = true;
}


const bool &CostTypes::getValueOfDefault() const noexcept
{
    const static bool defaultValue = bool();
    if(_default)
        return *_default;
    return defaultValue;
}
const std::shared_ptr<bool> &CostTypes::getDefault() const noexcept
{
    return _default;
}
void CostTypes::setDefault(const bool &pDefault) noexcept
{
    _default = std::make_shared<bool>(pDefault);
    _dirtyFlag[4] = true;
}


const ::trantor::Date &CostTypes::getValueOfDeletedAt() const noexcept
{
    const static ::trantor::Date defaultValue = ::trantor::Date();
    if(_deletedAt)
        return *_deletedAt;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &CostTypes::getDeletedAt() const noexcept
{
    return _deletedAt;
}
void CostTypes::setDeletedAt(const ::trantor::Date &pDeletedAt) noexcept
{
    _deletedAt = std::make_shared<::trantor::Date>(pDeletedAt);
    _dirtyFlag[5] = true;
}


void CostTypes::updateId(const uint64_t id)
{
}

const std::vector<std::string> &CostTypes::insertColumns() noexcept
{
    static const std::vector<std::string> _inCols={
        "name",
        "unit",
        "unit_plural",
        "default",
        "deleted_at"
    };
    return _inCols;
}

void CostTypes::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(getName())
    {
        binder << getValueOfName();
    }
    else
    {
        binder << nullptr;
    }
    if(getUnit())
    {
        binder << getValueOfUnit();
    }
    else
    {
        binder << nullptr;
    }
    if(getUnitPlural())
    {
        binder << getValueOfUnitPlural();
    }
    else
    {
        binder << nullptr;
    }
    if(getDefault())
    {
        binder << getValueOfDefault();
    }
    else
    {
        binder << nullptr;
    }
    if(getDeletedAt())
    {
        binder << getValueOfDeletedAt();
    }
    else
    {
        binder << nullptr;
    }
}

const std::vector<std::string> CostTypes::updateColumns() const
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

void CostTypes::updateArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(_dirtyFlag[1])
    {
        if(getName())
        {
            binder << getValueOfName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[2])
    {
        if(getUnit())
        {
            binder << getValueOfUnit();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[3])
    {
        if(getUnitPlural())
        {
            binder << getValueOfUnitPlural();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[4])
    {
        if(getDefault())
        {
            binder << getValueOfDefault();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[5])
    {
        if(getDeletedAt())
        {
            binder << getValueOfDeletedAt();
        }
        else
        {
            binder << nullptr;
        }
    }
}
Json::Value CostTypes::toJson() const
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
    if(getName())
    {
        ret["name"]=getValueOfName();
    }
    else
    {
        ret["name"]=Json::Value();
    }
    if(getUnit())
    {
        ret["unit"]=getValueOfUnit();
    }
    else
    {
        ret["unit"]=Json::Value();
    }
    if(getUnitPlural())
    {
        ret["unit_plural"]=getValueOfUnitPlural();
    }
    else
    {
        ret["unit_plural"]=Json::Value();
    }
    if(getDefault())
    {
        ret["default"]=getValueOfDefault();
    }
    else
    {
        ret["default"]=Json::Value();
    }
    if(getDeletedAt())
    {
        ret["deleted_at"]=getDeletedAt()->toDbStringLocal();
    }
    else
    {
        ret["deleted_at"]=Json::Value();
    }
    return ret;
}
