/**
 *
 *  RolePermissions.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "RolePermissions.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon_model::openproject6;

const std::string RolePermissions::Cols::_id = "id";
const std::string RolePermissions::Cols::_permission = "permission";
const std::string RolePermissions::Cols::_role_id = "role_id";
const std::string RolePermissions::Cols::_created_at = "created_at";
const std::string RolePermissions::Cols::_updated_at = "updated_at";
const std::string RolePermissions::primaryKeyName = "id";
const bool RolePermissions::hasPrimaryKey = true;
const std::string RolePermissions::tableName = "role_permissions";

const std::vector<typename RolePermissions::MetaData> RolePermissions::_metaData={
{"id","int32_t","integer",4,1,1,1},
{"permission","std::string","character varying",0,0,0,0},
{"role_id","int32_t","integer",4,0,0,0},
{"created_at","::trantor::Date","timestamp without time zone",0,0,0,0},
{"updated_at","::trantor::Date","timestamp without time zone",0,0,0,0}
};
const std::string &RolePermissions::getColumnName(size_t index) noexcept(false)
{
    assert(index < _metaData.size());
    return _metaData[index]._colName;
}
RolePermissions::RolePermissions(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            _id=std::make_shared<int32_t>(r["id"].as<int32_t>());
        }
        if(!r["permission"].isNull())
        {
            _permission=std::make_shared<std::string>(r["permission"].as<std::string>());
        }
        if(!r["role_id"].isNull())
        {
            _roleId=std::make_shared<int32_t>(r["role_id"].as<int32_t>());
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
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 5 > r.size())
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
            _permission=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            _roleId=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            auto timeStr = r[index].as<std::string>();
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
        index = offset + 4;
        if(!r[index].isNull())
        {
            auto timeStr = r[index].as<std::string>();
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

}

RolePermissions::RolePermissions(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 5)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        _id=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[0]].asInt64());
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        _permission=std::make_shared<std::string>(pJson[pMasqueradingVector[1]].asString());
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        _roleId=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[2]].asInt64());
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        auto timeStr = pJson[pMasqueradingVector[3]].asString();
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
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        auto timeStr = pJson[pMasqueradingVector[4]].asString();
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

RolePermissions::RolePermissions(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        _id=std::make_shared<int32_t>((int32_t)pJson["id"].asInt64());
    }
    if(pJson.isMember("permission"))
    {
        _permission=std::make_shared<std::string>(pJson["permission"].asString());
    }
    if(pJson.isMember("role_id"))
    {
        _roleId=std::make_shared<int32_t>((int32_t)pJson["role_id"].asInt64());
    }
    if(pJson.isMember("created_at"))
    {
        auto timeStr = pJson["created_at"].asString();
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
    if(pJson.isMember("updated_at"))
    {
        auto timeStr = pJson["updated_at"].asString();
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

void RolePermissions::updateByMasqueradedJson(const Json::Value &pJson,
                                            const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 5)
    {
        LOG_ERROR << "Bad masquerading vector";
        return;
    }
    if(!pMasqueradingVector[0].empty() && pJson.isMember(pMasqueradingVector[0]))
    {
        _id=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[0]].asInt64());
    }
    if(!pMasqueradingVector[1].empty() && pJson.isMember(pMasqueradingVector[1]))
    {
        _dirtyFlag[1] = true;
        _permission=std::make_shared<std::string>(pJson[pMasqueradingVector[1]].asString());
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        _dirtyFlag[2] = true;
        _roleId=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[2]].asInt64());
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        _dirtyFlag[3] = true;
        auto timeStr = pJson[pMasqueradingVector[3]].asString();
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
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        _dirtyFlag[4] = true;
        auto timeStr = pJson[pMasqueradingVector[4]].asString();
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
                                                                    
void RolePermissions::updateByJson(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        _id=std::make_shared<int32_t>((int32_t)pJson["id"].asInt64());
    }
    if(pJson.isMember("permission"))
    {
        _dirtyFlag[1] = true;
        _permission=std::make_shared<std::string>(pJson["permission"].asString());
    }
    if(pJson.isMember("role_id"))
    {
        _dirtyFlag[2] = true;
        _roleId=std::make_shared<int32_t>((int32_t)pJson["role_id"].asInt64());
    }
    if(pJson.isMember("created_at"))
    {
        _dirtyFlag[3] = true;
        auto timeStr = pJson["created_at"].asString();
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
    if(pJson.isMember("updated_at"))
    {
        _dirtyFlag[4] = true;
        auto timeStr = pJson["updated_at"].asString();
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

const int32_t &RolePermissions::getValueOfId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_id)
        return *_id;
    return defaultValue;
}
const std::shared_ptr<int32_t> &RolePermissions::getId() const noexcept
{
    return _id;
}
const typename RolePermissions::PrimaryKeyType & RolePermissions::getPrimaryKey() const
{
    assert(_id);
    return *_id;
}

const std::string &RolePermissions::getValueOfPermission() const noexcept
{
    const static std::string defaultValue = std::string();
    if(_permission)
        return *_permission;
    return defaultValue;
}
const std::shared_ptr<std::string> &RolePermissions::getPermission() const noexcept
{
    return _permission;
}
void RolePermissions::setPermission(const std::string &pPermission) noexcept
{
    _permission = std::make_shared<std::string>(pPermission);
    _dirtyFlag[1] = true;
}
void RolePermissions::setPermission(std::string &&pPermission) noexcept
{
    _permission = std::make_shared<std::string>(std::move(pPermission));
    _dirtyFlag[1] = true;
}


const int32_t &RolePermissions::getValueOfRoleId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_roleId)
        return *_roleId;
    return defaultValue;
}
const std::shared_ptr<int32_t> &RolePermissions::getRoleId() const noexcept
{
    return _roleId;
}
void RolePermissions::setRoleId(const int32_t &pRoleId) noexcept
{
    _roleId = std::make_shared<int32_t>(pRoleId);
    _dirtyFlag[2] = true;
}


const ::trantor::Date &RolePermissions::getValueOfCreatedAt() const noexcept
{
    const static ::trantor::Date defaultValue = ::trantor::Date();
    if(_createdAt)
        return *_createdAt;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &RolePermissions::getCreatedAt() const noexcept
{
    return _createdAt;
}
void RolePermissions::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    _createdAt = std::make_shared<::trantor::Date>(pCreatedAt);
    _dirtyFlag[3] = true;
}


const ::trantor::Date &RolePermissions::getValueOfUpdatedAt() const noexcept
{
    const static ::trantor::Date defaultValue = ::trantor::Date();
    if(_updatedAt)
        return *_updatedAt;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &RolePermissions::getUpdatedAt() const noexcept
{
    return _updatedAt;
}
void RolePermissions::setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept
{
    _updatedAt = std::make_shared<::trantor::Date>(pUpdatedAt);
    _dirtyFlag[4] = true;
}


void RolePermissions::updateId(const uint64_t id)
{
}

const std::vector<std::string> &RolePermissions::insertColumns() noexcept
{
    static const std::vector<std::string> _inCols={
        "permission",
        "role_id",
        "created_at",
        "updated_at"
    };
    return _inCols;
}

void RolePermissions::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(getPermission())
    {
        binder << getValueOfPermission();
    }
    else
    {
        binder << nullptr;
    }
    if(getRoleId())
    {
        binder << getValueOfRoleId();
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

const std::vector<std::string> RolePermissions::updateColumns() const
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

void RolePermissions::updateArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(_dirtyFlag[1])
    {
        if(getPermission())
        {
            binder << getValueOfPermission();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[2])
    {
        if(getRoleId())
        {
            binder << getValueOfRoleId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[3])
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
    if(_dirtyFlag[4])
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
Json::Value RolePermissions::toJson() const
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
    if(getPermission())
    {
        ret["permission"]=getValueOfPermission();
    }
    else
    {
        ret["permission"]=Json::Value();
    }
    if(getRoleId())
    {
        ret["role_id"]=getValueOfRoleId();
    }
    else
    {
        ret["role_id"]=Json::Value();
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

Json::Value RolePermissions::toMasqueradedJson(
    const std::vector<std::string> &pMasqueradingVector) const
{
    Json::Value ret;
    if(pMasqueradingVector.size() == 5)
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
            if(getPermission())
            {
                ret[pMasqueradingVector[1]]=getValueOfPermission();
            }
            else
            {
                ret[pMasqueradingVector[1]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[2].empty())
        {
            if(getRoleId())
            {
                ret[pMasqueradingVector[2]]=getValueOfRoleId();
            }
            else
            {
                ret[pMasqueradingVector[2]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[3].empty())
        {
            if(getCreatedAt())
            {
                ret[pMasqueradingVector[3]]=getCreatedAt()->toDbStringLocal();
            }
            else
            {
                ret[pMasqueradingVector[3]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[4].empty())
        {
            if(getUpdatedAt())
            {
                ret[pMasqueradingVector[4]]=getUpdatedAt()->toDbStringLocal();
            }
            else
            {
                ret[pMasqueradingVector[4]]=Json::Value();
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
    if(getPermission())
    {
        ret["permission"]=getValueOfPermission();
    }
    else
    {
        ret["permission"]=Json::Value();
    }
    if(getRoleId())
    {
        ret["role_id"]=getValueOfRoleId();
    }
    else
    {
        ret["role_id"]=Json::Value();
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

bool RolePermissions::validateJsonForCreation(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("id"))
    {
        if(!validJsonOfField(0, "id", pJson["id"], err, true))
            return false;
    }
    if(pJson.isMember("permission"))
    {
        if(!validJsonOfField(1, "permission", pJson["permission"], err, true))
            return false;
    }
    if(pJson.isMember("role_id"))
    {
        if(!validJsonOfField(2, "role_id", pJson["role_id"], err, true))
            return false;
    }
    if(pJson.isMember("created_at"))
    {
        if(!validJsonOfField(3, "created_at", pJson["created_at"], err, true))
            return false;
    }
    if(pJson.isMember("updated_at"))
    {
        if(!validJsonOfField(4, "updated_at", pJson["updated_at"], err, true))
            return false;
    }
    return true;
}
bool RolePermissions::validateMasqueradedJsonForCreation(const Json::Value &pJson,
                                                         const std::vector<std::string> &pMasqueradingVector,
                                                         std::string &err)
{
    if(pMasqueradingVector.size() != 5)
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
    if(!pMasqueradingVector[3].empty())
    {
        if(pJson.isMember(pMasqueradingVector[3]))
        {
            if(!validJsonOfField(3, pMasqueradingVector[3], pJson[pMasqueradingVector[3]], err, true))
                return false;
        }
    }
    if(!pMasqueradingVector[4].empty())
    {
        if(pJson.isMember(pMasqueradingVector[4]))
        {
            if(!validJsonOfField(4, pMasqueradingVector[4], pJson[pMasqueradingVector[4]], err, true))
                return false;
        }
    }
    return true;
}
bool RolePermissions::validateJsonForUpdate(const Json::Value &pJson, std::string &err)
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
    if(pJson.isMember("permission"))
    {
        if(!validJsonOfField(1, "permission", pJson["permission"], err, false))
            return false;
    }
    if(pJson.isMember("role_id"))
    {
        if(!validJsonOfField(2, "role_id", pJson["role_id"], err, false))
            return false;
    }
    if(pJson.isMember("created_at"))
    {
        if(!validJsonOfField(3, "created_at", pJson["created_at"], err, false))
            return false;
    }
    if(pJson.isMember("updated_at"))
    {
        if(!validJsonOfField(4, "updated_at", pJson["updated_at"], err, false))
            return false;
    }
    return true;
}
bool RolePermissions::validateMasqueradedJsonForUpdate(const Json::Value &pJson,
                                                       const std::vector<std::string> &pMasqueradingVector,
                                                       std::string &err)
{
    if(pMasqueradingVector.size() != 5)
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
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        if(!validJsonOfField(3, pMasqueradingVector[3], pJson[pMasqueradingVector[3]], err, false))
            return false;
    }
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        if(!validJsonOfField(4, pMasqueradingVector[4], pJson[pMasqueradingVector[4]], err, false))
            return false;
    }
    return true;
}
bool RolePermissions::validJsonOfField(size_t index,
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
            if(!pJson.isString() && !pJson.isNull())
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
        case 3:
            if(!pJson.isString() && !pJson.isNull())
            {
                err="Type error in the "+fieldName+"field";
                return false;                
            }
            break;
        case 4:
            if(!pJson.isString() && !pJson.isNull())
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
