/**
 *
 *  Enumerations.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "Enumerations.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon_model::openproject4;

const std::string Enumerations::Cols::_id = "id";
const std::string Enumerations::Cols::_name = "name";
const std::string Enumerations::Cols::_position = "position";
const std::string Enumerations::Cols::_is_default = "is_default";
const std::string Enumerations::Cols::_type = "type";
const std::string Enumerations::Cols::_active = "active";
const std::string Enumerations::Cols::_project_id = "project_id";
const std::string Enumerations::Cols::_parent_id = "parent_id";
const std::string Enumerations::Cols::_created_at = "created_at";
const std::string Enumerations::Cols::_updated_at = "updated_at";
const std::string Enumerations::Cols::_color_id = "color_id";
const std::string Enumerations::primaryKeyName = "id";
const bool Enumerations::hasPrimaryKey = true;
const std::string Enumerations::tableName = "enumerations";

const std::vector<typename Enumerations::MetaData> Enumerations::_metaData={
{"id","int32_t","integer",4,1,1,1},
{"name","std::string","character varying",30,0,0,1},
{"position","int32_t","integer",4,0,0,0},
{"is_default","bool","boolean",1,0,0,1},
{"type","std::string","character varying",0,0,0,0},
{"active","bool","boolean",1,0,0,1},
{"project_id","int32_t","integer",4,0,0,0},
{"parent_id","int32_t","integer",4,0,0,0},
{"created_at","::trantor::Date","timestamp without time zone",0,0,0,1},
{"updated_at","::trantor::Date","timestamp without time zone",0,0,0,1},
{"color_id","int32_t","integer",4,0,0,0}
};
const std::string &Enumerations::getColumnName(size_t index) noexcept(false)
{
    assert(index < _metaData.size());
    return _metaData[index]._colName;
}
Enumerations::Enumerations(const Row &r) noexcept
{
        if(!r["id"].isNull())
        {
            _id=std::make_shared<int32_t>(r["id"].as<int32_t>());
        }
        if(!r["name"].isNull())
        {
            _name=std::make_shared<std::string>(r["name"].as<std::string>());
        }
        if(!r["position"].isNull())
        {
            _position=std::make_shared<int32_t>(r["position"].as<int32_t>());
        }
        if(!r["is_default"].isNull())
        {
            _isDefault=std::make_shared<bool>(r["is_default"].as<bool>());
        }
        if(!r["type"].isNull())
        {
            _type=std::make_shared<std::string>(r["type"].as<std::string>());
        }
        if(!r["active"].isNull())
        {
            _active=std::make_shared<bool>(r["active"].as<bool>());
        }
        if(!r["project_id"].isNull())
        {
            _projectId=std::make_shared<int32_t>(r["project_id"].as<int32_t>());
        }
        if(!r["parent_id"].isNull())
        {
            _parentId=std::make_shared<int32_t>(r["parent_id"].as<int32_t>());
        }
        if(!r["created_at"].isNull())
        {
            auto timeStr = r["created_at"].as<std::string>();
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
            _createdAt=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
        }
        if(!r["updated_at"].isNull())
        {
            auto timeStr = r["updated_at"].as<std::string>();
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
            _updatedAt=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
        }
        if(!r["color_id"].isNull())
        {
            _colorId=std::make_shared<int32_t>(r["color_id"].as<int32_t>());
        }
}
const int32_t &Enumerations::getValueOfId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_id)
        return *_id;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Enumerations::getId() const noexcept
{
    return _id;
}
const typename Enumerations::PrimaryKeyType & Enumerations::getPrimaryKey() const
{
    assert(_id);
    return *_id;
}

const std::string &Enumerations::getValueOfName() const noexcept
{
    const static std::string defaultValue = std::string();
    if(_name)
        return *_name;
    return defaultValue;
}
const std::shared_ptr<std::string> &Enumerations::getName() const noexcept
{
    return _name;
}
void Enumerations::setName(const std::string &pName) noexcept
{
    _name = std::make_shared<std::string>(pName);
    _dirtyFlag[1] = true;
}
void Enumerations::setName(std::string &&pName) noexcept
{
    _name = std::make_shared<std::string>(std::move(pName));
    _dirtyFlag[1] = true;
}


const int32_t &Enumerations::getValueOfPosition() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_position)
        return *_position;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Enumerations::getPosition() const noexcept
{
    return _position;
}
void Enumerations::setPosition(const int32_t &pPosition) noexcept
{
    _position = std::make_shared<int32_t>(pPosition);
    _dirtyFlag[2] = true;
}


const bool &Enumerations::getValueOfIsDefault() const noexcept
{
    const static bool defaultValue = bool();
    if(_isDefault)
        return *_isDefault;
    return defaultValue;
}
const std::shared_ptr<bool> &Enumerations::getIsDefault() const noexcept
{
    return _isDefault;
}
void Enumerations::setIsDefault(const bool &pIsDefault) noexcept
{
    _isDefault = std::make_shared<bool>(pIsDefault);
    _dirtyFlag[3] = true;
}


const std::string &Enumerations::getValueOfType() const noexcept
{
    const static std::string defaultValue = std::string();
    if(_type)
        return *_type;
    return defaultValue;
}
const std::shared_ptr<std::string> &Enumerations::getType() const noexcept
{
    return _type;
}
void Enumerations::setType(const std::string &pType) noexcept
{
    _type = std::make_shared<std::string>(pType);
    _dirtyFlag[4] = true;
}
void Enumerations::setType(std::string &&pType) noexcept
{
    _type = std::make_shared<std::string>(std::move(pType));
    _dirtyFlag[4] = true;
}


const bool &Enumerations::getValueOfActive() const noexcept
{
    const static bool defaultValue = bool();
    if(_active)
        return *_active;
    return defaultValue;
}
const std::shared_ptr<bool> &Enumerations::getActive() const noexcept
{
    return _active;
}
void Enumerations::setActive(const bool &pActive) noexcept
{
    _active = std::make_shared<bool>(pActive);
    _dirtyFlag[5] = true;
}


const int32_t &Enumerations::getValueOfProjectId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_projectId)
        return *_projectId;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Enumerations::getProjectId() const noexcept
{
    return _projectId;
}
void Enumerations::setProjectId(const int32_t &pProjectId) noexcept
{
    _projectId = std::make_shared<int32_t>(pProjectId);
    _dirtyFlag[6] = true;
}


const int32_t &Enumerations::getValueOfParentId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_parentId)
        return *_parentId;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Enumerations::getParentId() const noexcept
{
    return _parentId;
}
void Enumerations::setParentId(const int32_t &pParentId) noexcept
{
    _parentId = std::make_shared<int32_t>(pParentId);
    _dirtyFlag[7] = true;
}


const ::trantor::Date &Enumerations::getValueOfCreatedAt() const noexcept
{
    const static ::trantor::Date defaultValue = ::trantor::Date();
    if(_createdAt)
        return *_createdAt;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Enumerations::getCreatedAt() const noexcept
{
    return _createdAt;
}
void Enumerations::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    _createdAt = std::make_shared<::trantor::Date>(pCreatedAt);
    _dirtyFlag[8] = true;
}


const ::trantor::Date &Enumerations::getValueOfUpdatedAt() const noexcept
{
    const static ::trantor::Date defaultValue = ::trantor::Date();
    if(_updatedAt)
        return *_updatedAt;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Enumerations::getUpdatedAt() const noexcept
{
    return _updatedAt;
}
void Enumerations::setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept
{
    _updatedAt = std::make_shared<::trantor::Date>(pUpdatedAt);
    _dirtyFlag[9] = true;
}


const int32_t &Enumerations::getValueOfColorId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_colorId)
        return *_colorId;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Enumerations::getColorId() const noexcept
{
    return _colorId;
}
void Enumerations::setColorId(const int32_t &pColorId) noexcept
{
    _colorId = std::make_shared<int32_t>(pColorId);
    _dirtyFlag[10] = true;
}


void Enumerations::updateId(const uint64_t id)
{
}

const std::vector<std::string> &Enumerations::insertColumns() noexcept
{
    static const std::vector<std::string> _inCols={
        "name",
        "position",
        "is_default",
        "type",
        "active",
        "project_id",
        "parent_id",
        "created_at",
        "updated_at",
        "color_id"
    };
    return _inCols;
}

void Enumerations::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(getName())
    {
        binder << getValueOfName();
    }
    else
    {
        binder << nullptr;
    }
    if(getPosition())
    {
        binder << getValueOfPosition();
    }
    else
    {
        binder << nullptr;
    }
    if(getIsDefault())
    {
        binder << getValueOfIsDefault();
    }
    else
    {
        binder << nullptr;
    }
    if(getType())
    {
        binder << getValueOfType();
    }
    else
    {
        binder << nullptr;
    }
    if(getActive())
    {
        binder << getValueOfActive();
    }
    else
    {
        binder << nullptr;
    }
    if(getProjectId())
    {
        binder << getValueOfProjectId();
    }
    else
    {
        binder << nullptr;
    }
    if(getParentId())
    {
        binder << getValueOfParentId();
    }
    else
    {
        binder << nullptr;
    }
    if(getCreatedAt())
    {
        binder << getValueOfCreatedAt();
    }
    else
    {
        binder << nullptr;
    }
    if(getUpdatedAt())
    {
        binder << getValueOfUpdatedAt();
    }
    else
    {
        binder << nullptr;
    }
    if(getColorId())
    {
        binder << getValueOfColorId();
    }
    else
    {
        binder << nullptr;
    }
}

const std::vector<std::string> Enumerations::updateColumns() const
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

void Enumerations::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getPosition())
        {
            binder << getValueOfPosition();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[3])
    {
        if(getIsDefault())
        {
            binder << getValueOfIsDefault();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[4])
    {
        if(getType())
        {
            binder << getValueOfType();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[5])
    {
        if(getActive())
        {
            binder << getValueOfActive();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[6])
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
    if(_dirtyFlag[7])
    {
        if(getParentId())
        {
            binder << getValueOfParentId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[8])
    {
        if(getCreatedAt())
        {
            binder << getValueOfCreatedAt();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[9])
    {
        if(getUpdatedAt())
        {
            binder << getValueOfUpdatedAt();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[10])
    {
        if(getColorId())
        {
            binder << getValueOfColorId();
        }
        else
        {
            binder << nullptr;
        }
    }
}
Json::Value Enumerations::toJson() const
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
    if(getPosition())
    {
        ret["position"]=getValueOfPosition();
    }
    else
    {
        ret["position"]=Json::Value();
    }
    if(getIsDefault())
    {
        ret["is_default"]=getValueOfIsDefault();
    }
    else
    {
        ret["is_default"]=Json::Value();
    }
    if(getType())
    {
        ret["type"]=getValueOfType();
    }
    else
    {
        ret["type"]=Json::Value();
    }
    if(getActive())
    {
        ret["active"]=getValueOfActive();
    }
    else
    {
        ret["active"]=Json::Value();
    }
    if(getProjectId())
    {
        ret["project_id"]=getValueOfProjectId();
    }
    else
    {
        ret["project_id"]=Json::Value();
    }
    if(getParentId())
    {
        ret["parent_id"]=getValueOfParentId();
    }
    else
    {
        ret["parent_id"]=Json::Value();
    }
    if(getCreatedAt())
    {
        ret["created_at"]=getCreatedAt()->toDbStringLocal();
    }
    else
    {
        ret["created_at"]=Json::Value();
    }
    if(getUpdatedAt())
    {
        ret["updated_at"]=getUpdatedAt()->toDbStringLocal();
    }
    else
    {
        ret["updated_at"]=Json::Value();
    }
    if(getColorId())
    {
        ret["color_id"]=getValueOfColorId();
    }
    else
    {
        ret["color_id"]=Json::Value();
    }
    return ret;
}
