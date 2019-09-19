/**
 *
 *  Categories.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "Categories.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon_model::openproject4;

const std::string Categories::Cols::_id = "id";
const std::string Categories::Cols::_project_id = "project_id";
const std::string Categories::Cols::_name = "name";
const std::string Categories::Cols::_assigned_to_id = "assigned_to_id";
const std::string Categories::Cols::_created_at = "created_at";
const std::string Categories::Cols::_updated_at = "updated_at";
const std::string Categories::primaryKeyName = "id";
const bool Categories::hasPrimaryKey = true;
const std::string Categories::tableName = "categories";

const std::vector<typename Categories::MetaData> Categories::_metaData={
{"id","int32_t","integer",4,1,1,1},
{"project_id","int32_t","integer",4,0,0,1},
{"name","std::string","character varying",256,0,0,1},
{"assigned_to_id","int32_t","integer",4,0,0,0},
{"created_at","::trantor::Date","timestamp without time zone",0,0,0,1},
{"updated_at","::trantor::Date","timestamp without time zone",0,0,0,1}
};
const std::string &Categories::getColumnName(size_t index) noexcept(false)
{
    assert(index < _metaData.size());
    return _metaData[index]._colName;
}
Categories::Categories(const Row &r) noexcept
{
        if(!r["id"].isNull())
        {
            _id=std::make_shared<int32_t>(r["id"].as<int32_t>());
        }
        if(!r["project_id"].isNull())
        {
            _projectId=std::make_shared<int32_t>(r["project_id"].as<int32_t>());
        }
        if(!r["name"].isNull())
        {
            _name=std::make_shared<std::string>(r["name"].as<std::string>());
        }
        if(!r["assigned_to_id"].isNull())
        {
            _assignedToId=std::make_shared<int32_t>(r["assigned_to_id"].as<int32_t>());
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
}
const int32_t &Categories::getValueOfId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_id)
        return *_id;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Categories::getId() const noexcept
{
    return _id;
}
const typename Categories::PrimaryKeyType & Categories::getPrimaryKey() const
{
    assert(_id);
    return *_id;
}

const int32_t &Categories::getValueOfProjectId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_projectId)
        return *_projectId;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Categories::getProjectId() const noexcept
{
    return _projectId;
}
void Categories::setProjectId(const int32_t &pProjectId) noexcept
{
    _projectId = std::make_shared<int32_t>(pProjectId);
    _dirtyFlag[1] = true;
}


const std::string &Categories::getValueOfName() const noexcept
{
    const static std::string defaultValue = std::string();
    if(_name)
        return *_name;
    return defaultValue;
}
const std::shared_ptr<std::string> &Categories::getName() const noexcept
{
    return _name;
}
void Categories::setName(const std::string &pName) noexcept
{
    _name = std::make_shared<std::string>(pName);
    _dirtyFlag[2] = true;
}
void Categories::setName(std::string &&pName) noexcept
{
    _name = std::make_shared<std::string>(std::move(pName));
    _dirtyFlag[2] = true;
}


const int32_t &Categories::getValueOfAssignedToId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_assignedToId)
        return *_assignedToId;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Categories::getAssignedToId() const noexcept
{
    return _assignedToId;
}
void Categories::setAssignedToId(const int32_t &pAssignedToId) noexcept
{
    _assignedToId = std::make_shared<int32_t>(pAssignedToId);
    _dirtyFlag[3] = true;
}


const ::trantor::Date &Categories::getValueOfCreatedAt() const noexcept
{
    const static ::trantor::Date defaultValue = ::trantor::Date();
    if(_createdAt)
        return *_createdAt;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Categories::getCreatedAt() const noexcept
{
    return _createdAt;
}
void Categories::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    _createdAt = std::make_shared<::trantor::Date>(pCreatedAt);
    _dirtyFlag[4] = true;
}


const ::trantor::Date &Categories::getValueOfUpdatedAt() const noexcept
{
    const static ::trantor::Date defaultValue = ::trantor::Date();
    if(_updatedAt)
        return *_updatedAt;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Categories::getUpdatedAt() const noexcept
{
    return _updatedAt;
}
void Categories::setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept
{
    _updatedAt = std::make_shared<::trantor::Date>(pUpdatedAt);
    _dirtyFlag[5] = true;
}


void Categories::updateId(const uint64_t id)
{
}

const std::vector<std::string> &Categories::insertColumns() noexcept
{
    static const std::vector<std::string> _inCols={
        "project_id",
        "name",
        "assigned_to_id",
        "created_at",
        "updated_at"
    };
    return _inCols;
}

void Categories::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(getProjectId())
    {
        binder << getValueOfProjectId();
    }
    else
    {
        binder << nullptr;
    }
    if(getName())
    {
        binder << getValueOfName();
    }
    else
    {
        binder << nullptr;
    }
    if(getAssignedToId())
    {
        binder << getValueOfAssignedToId();
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
}

const std::vector<std::string> Categories::updateColumns() const
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

void Categories::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getName())
        {
            binder << getValueOfName();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[3])
    {
        if(getAssignedToId())
        {
            binder << getValueOfAssignedToId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[4])
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
    if(_dirtyFlag[5])
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
}
Json::Value Categories::toJson() const
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
    if(getName())
    {
        ret["name"]=getValueOfName();
    }
    else
    {
        ret["name"]=Json::Value();
    }
    if(getAssignedToId())
    {
        ret["assigned_to_id"]=getValueOfAssignedToId();
    }
    else
    {
        ret["assigned_to_id"]=Json::Value();
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
    return ret;
}
