/**
 *
 *  LdapGroupsSynchronizedGroups.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "LdapGroupsSynchronizedGroups.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon_model::openproject6;

const std::string LdapGroupsSynchronizedGroups::Cols::_id = "id";
const std::string LdapGroupsSynchronizedGroups::Cols::_entry = "entry";
const std::string LdapGroupsSynchronizedGroups::Cols::_group_id = "group_id";
const std::string LdapGroupsSynchronizedGroups::Cols::_auth_source_id = "auth_source_id";
const std::string LdapGroupsSynchronizedGroups::Cols::_created_at = "created_at";
const std::string LdapGroupsSynchronizedGroups::Cols::_updated_at = "updated_at";
const std::string LdapGroupsSynchronizedGroups::primaryKeyName = "id";
const bool LdapGroupsSynchronizedGroups::hasPrimaryKey = true;
const std::string LdapGroupsSynchronizedGroups::tableName = "ldap_groups_synchronized_groups";

const std::vector<typename LdapGroupsSynchronizedGroups::MetaData> LdapGroupsSynchronizedGroups::_metaData={
{"id","int32_t","integer",4,1,1,1},
{"entry","std::string","character varying",0,0,0,0},
{"group_id","int32_t","integer",4,0,0,0},
{"auth_source_id","int32_t","integer",4,0,0,0},
{"created_at","::trantor::Date","timestamp without time zone",0,0,0,1},
{"updated_at","::trantor::Date","timestamp without time zone",0,0,0,1}
};
const std::string &LdapGroupsSynchronizedGroups::getColumnName(size_t index) noexcept(false)
{
    assert(index < _metaData.size());
    return _metaData[index]._colName;
}
LdapGroupsSynchronizedGroups::LdapGroupsSynchronizedGroups(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            _id=std::make_shared<int32_t>(r["id"].as<int32_t>());
        }
        if(!r["entry"].isNull())
        {
            _entry=std::make_shared<std::string>(r["entry"].as<std::string>());
        }
        if(!r["group_id"].isNull())
        {
            _groupId=std::make_shared<int32_t>(r["group_id"].as<int32_t>());
        }
        if(!r["auth_source_id"].isNull())
        {
            _authSourceId=std::make_shared<int32_t>(r["auth_source_id"].as<int32_t>());
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
        if(offset + 6 > r.size())
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
            _entry=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            _groupId=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            _authSourceId=std::make_shared<int32_t>(r[index].as<int32_t>());
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
            _createdAt=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
        }
        index = offset + 5;
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

LdapGroupsSynchronizedGroups::LdapGroupsSynchronizedGroups(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 6)
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
            _entry=std::make_shared<std::string>(pJson[pMasqueradingVector[1]].asString());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        _dirtyFlag[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            _groupId=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[2]].asInt64());
        }
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        _dirtyFlag[3] = true;
        if(!pJson[pMasqueradingVector[3]].isNull())
        {
            _authSourceId=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[3]].asInt64());
        }
    }
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        _dirtyFlag[4] = true;
        if(!pJson[pMasqueradingVector[4]].isNull())
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
            _createdAt=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
        }
    }
    if(!pMasqueradingVector[5].empty() && pJson.isMember(pMasqueradingVector[5]))
    {
        _dirtyFlag[5] = true;
        if(!pJson[pMasqueradingVector[5]].isNull())
        {
            auto timeStr = pJson[pMasqueradingVector[5]].asString();
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

LdapGroupsSynchronizedGroups::LdapGroupsSynchronizedGroups(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        _dirtyFlag[0]=true;
        if(!pJson["id"].isNull())
        {
            _id=std::make_shared<int32_t>((int32_t)pJson["id"].asInt64());
        }
    }
    if(pJson.isMember("entry"))
    {
        _dirtyFlag[1]=true;
        if(!pJson["entry"].isNull())
        {
            _entry=std::make_shared<std::string>(pJson["entry"].asString());
        }
    }
    if(pJson.isMember("group_id"))
    {
        _dirtyFlag[2]=true;
        if(!pJson["group_id"].isNull())
        {
            _groupId=std::make_shared<int32_t>((int32_t)pJson["group_id"].asInt64());
        }
    }
    if(pJson.isMember("auth_source_id"))
    {
        _dirtyFlag[3]=true;
        if(!pJson["auth_source_id"].isNull())
        {
            _authSourceId=std::make_shared<int32_t>((int32_t)pJson["auth_source_id"].asInt64());
        }
    }
    if(pJson.isMember("created_at"))
    {
        _dirtyFlag[4]=true;
        if(!pJson["created_at"].isNull())
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
    }
    if(pJson.isMember("updated_at"))
    {
        _dirtyFlag[5]=true;
        if(!pJson["updated_at"].isNull())
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
}

void LdapGroupsSynchronizedGroups::updateByMasqueradedJson(const Json::Value &pJson,
                                            const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 6)
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
            _entry=std::make_shared<std::string>(pJson[pMasqueradingVector[1]].asString());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        _dirtyFlag[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            _groupId=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[2]].asInt64());
        }
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        _dirtyFlag[3] = true;
        if(!pJson[pMasqueradingVector[3]].isNull())
        {
            _authSourceId=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[3]].asInt64());
        }
    }
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        _dirtyFlag[4] = true;
        if(!pJson[pMasqueradingVector[4]].isNull())
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
            _createdAt=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
        }
    }
    if(!pMasqueradingVector[5].empty() && pJson.isMember(pMasqueradingVector[5]))
    {
        _dirtyFlag[5] = true;
        if(!pJson[pMasqueradingVector[5]].isNull())
        {
            auto timeStr = pJson[pMasqueradingVector[5]].asString();
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
                                                                    
void LdapGroupsSynchronizedGroups::updateByJson(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        if(!pJson["id"].isNull())
        {
            _id=std::make_shared<int32_t>((int32_t)pJson["id"].asInt64());
        }
    }
    if(pJson.isMember("entry"))
    {
        _dirtyFlag[1] = true;
        if(!pJson["entry"].isNull())
        {
            _entry=std::make_shared<std::string>(pJson["entry"].asString());
        }
    }
    if(pJson.isMember("group_id"))
    {
        _dirtyFlag[2] = true;
        if(!pJson["group_id"].isNull())
        {
            _groupId=std::make_shared<int32_t>((int32_t)pJson["group_id"].asInt64());
        }
    }
    if(pJson.isMember("auth_source_id"))
    {
        _dirtyFlag[3] = true;
        if(!pJson["auth_source_id"].isNull())
        {
            _authSourceId=std::make_shared<int32_t>((int32_t)pJson["auth_source_id"].asInt64());
        }
    }
    if(pJson.isMember("created_at"))
    {
        _dirtyFlag[4] = true;
        if(!pJson["created_at"].isNull())
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
    }
    if(pJson.isMember("updated_at"))
    {
        _dirtyFlag[5] = true;
        if(!pJson["updated_at"].isNull())
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
}

const int32_t &LdapGroupsSynchronizedGroups::getValueOfId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_id)
        return *_id;
    return defaultValue;
}
const std::shared_ptr<int32_t> &LdapGroupsSynchronizedGroups::getId() const noexcept
{
    return _id;
}
const typename LdapGroupsSynchronizedGroups::PrimaryKeyType & LdapGroupsSynchronizedGroups::getPrimaryKey() const
{
    assert(_id);
    return *_id;
}

const std::string &LdapGroupsSynchronizedGroups::getValueOfEntry() const noexcept
{
    const static std::string defaultValue = std::string();
    if(_entry)
        return *_entry;
    return defaultValue;
}
const std::shared_ptr<std::string> &LdapGroupsSynchronizedGroups::getEntry() const noexcept
{
    return _entry;
}
void LdapGroupsSynchronizedGroups::setEntry(const std::string &pEntry) noexcept
{
    _entry = std::make_shared<std::string>(pEntry);
    _dirtyFlag[1] = true;
}
void LdapGroupsSynchronizedGroups::setEntry(std::string &&pEntry) noexcept
{
    _entry = std::make_shared<std::string>(std::move(pEntry));
    _dirtyFlag[1] = true;
}


const int32_t &LdapGroupsSynchronizedGroups::getValueOfGroupId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_groupId)
        return *_groupId;
    return defaultValue;
}
const std::shared_ptr<int32_t> &LdapGroupsSynchronizedGroups::getGroupId() const noexcept
{
    return _groupId;
}
void LdapGroupsSynchronizedGroups::setGroupId(const int32_t &pGroupId) noexcept
{
    _groupId = std::make_shared<int32_t>(pGroupId);
    _dirtyFlag[2] = true;
}


const int32_t &LdapGroupsSynchronizedGroups::getValueOfAuthSourceId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_authSourceId)
        return *_authSourceId;
    return defaultValue;
}
const std::shared_ptr<int32_t> &LdapGroupsSynchronizedGroups::getAuthSourceId() const noexcept
{
    return _authSourceId;
}
void LdapGroupsSynchronizedGroups::setAuthSourceId(const int32_t &pAuthSourceId) noexcept
{
    _authSourceId = std::make_shared<int32_t>(pAuthSourceId);
    _dirtyFlag[3] = true;
}


const ::trantor::Date &LdapGroupsSynchronizedGroups::getValueOfCreatedAt() const noexcept
{
    const static ::trantor::Date defaultValue = ::trantor::Date();
    if(_createdAt)
        return *_createdAt;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &LdapGroupsSynchronizedGroups::getCreatedAt() const noexcept
{
    return _createdAt;
}
void LdapGroupsSynchronizedGroups::setCreatedAt(const ::trantor::Date &pCreatedAt) noexcept
{
    _createdAt = std::make_shared<::trantor::Date>(pCreatedAt);
    _dirtyFlag[4] = true;
}


const ::trantor::Date &LdapGroupsSynchronizedGroups::getValueOfUpdatedAt() const noexcept
{
    const static ::trantor::Date defaultValue = ::trantor::Date();
    if(_updatedAt)
        return *_updatedAt;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &LdapGroupsSynchronizedGroups::getUpdatedAt() const noexcept
{
    return _updatedAt;
}
void LdapGroupsSynchronizedGroups::setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept
{
    _updatedAt = std::make_shared<::trantor::Date>(pUpdatedAt);
    _dirtyFlag[5] = true;
}


void LdapGroupsSynchronizedGroups::updateId(const uint64_t id)
{
}

const std::vector<std::string> &LdapGroupsSynchronizedGroups::insertColumns() noexcept
{
    static const std::vector<std::string> _inCols={
        "entry",
        "group_id",
        "auth_source_id",
        "created_at",
        "updated_at"
    };
    return _inCols;
}

void LdapGroupsSynchronizedGroups::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(_dirtyFlag[1])
    {
        if(getEntry())
        {
            binder << getValueOfEntry();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[2])
    {
        if(getGroupId())
        {
            binder << getValueOfGroupId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[3])
    {
        if(getAuthSourceId())
        {
            binder << getValueOfAuthSourceId();
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

const std::vector<std::string> LdapGroupsSynchronizedGroups::updateColumns() const
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

void LdapGroupsSynchronizedGroups::updateArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(_dirtyFlag[1])
    {
        if(getEntry())
        {
            binder << getValueOfEntry();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[2])
    {
        if(getGroupId())
        {
            binder << getValueOfGroupId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[3])
    {
        if(getAuthSourceId())
        {
            binder << getValueOfAuthSourceId();
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
Json::Value LdapGroupsSynchronizedGroups::toJson() const
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
    if(getEntry())
    {
        ret["entry"]=getValueOfEntry();
    }
    else
    {
        ret["entry"]=Json::Value();
    }
    if(getGroupId())
    {
        ret["group_id"]=getValueOfGroupId();
    }
    else
    {
        ret["group_id"]=Json::Value();
    }
    if(getAuthSourceId())
    {
        ret["auth_source_id"]=getValueOfAuthSourceId();
    }
    else
    {
        ret["auth_source_id"]=Json::Value();
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

Json::Value LdapGroupsSynchronizedGroups::toMasqueradedJson(
    const std::vector<std::string> &pMasqueradingVector) const
{
    Json::Value ret;
    if(pMasqueradingVector.size() == 6)
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
            if(getEntry())
            {
                ret[pMasqueradingVector[1]]=getValueOfEntry();
            }
            else
            {
                ret[pMasqueradingVector[1]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[2].empty())
        {
            if(getGroupId())
            {
                ret[pMasqueradingVector[2]]=getValueOfGroupId();
            }
            else
            {
                ret[pMasqueradingVector[2]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[3].empty())
        {
            if(getAuthSourceId())
            {
                ret[pMasqueradingVector[3]]=getValueOfAuthSourceId();
            }
            else
            {
                ret[pMasqueradingVector[3]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[4].empty())
        {
            if(getCreatedAt())
            {
                ret[pMasqueradingVector[4]]=getCreatedAt()->toDbStringLocal();
            }
            else
            {
                ret[pMasqueradingVector[4]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[5].empty())
        {
            if(getUpdatedAt())
            {
                ret[pMasqueradingVector[5]]=getUpdatedAt()->toDbStringLocal();
            }
            else
            {
                ret[pMasqueradingVector[5]]=Json::Value();
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
    if(getEntry())
    {
        ret["entry"]=getValueOfEntry();
    }
    else
    {
        ret["entry"]=Json::Value();
    }
    if(getGroupId())
    {
        ret["group_id"]=getValueOfGroupId();
    }
    else
    {
        ret["group_id"]=Json::Value();
    }
    if(getAuthSourceId())
    {
        ret["auth_source_id"]=getValueOfAuthSourceId();
    }
    else
    {
        ret["auth_source_id"]=Json::Value();
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

bool LdapGroupsSynchronizedGroups::validateJsonForCreation(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("id"))
    {
        if(!validJsonOfField(0, "id", pJson["id"], err, true))
            return false;
    }
    if(pJson.isMember("entry"))
    {
        if(!validJsonOfField(1, "entry", pJson["entry"], err, true))
            return false;
    }
    if(pJson.isMember("group_id"))
    {
        if(!validJsonOfField(2, "group_id", pJson["group_id"], err, true))
            return false;
    }
    if(pJson.isMember("auth_source_id"))
    {
        if(!validJsonOfField(3, "auth_source_id", pJson["auth_source_id"], err, true))
            return false;
    }
    if(pJson.isMember("created_at"))
    {
        if(!validJsonOfField(4, "created_at", pJson["created_at"], err, true))
            return false;
    }
    else
    {
        err="The created_at column cannot be null";
        return false;
    }
    if(pJson.isMember("updated_at"))
    {
        if(!validJsonOfField(5, "updated_at", pJson["updated_at"], err, true))
            return false;
    }
    else
    {
        err="The updated_at column cannot be null";
        return false;
    }
    return true;
}
bool LdapGroupsSynchronizedGroups::validateMasqueradedJsonForCreation(const Json::Value &pJson,
                                                                      const std::vector<std::string> &pMasqueradingVector,
                                                                      std::string &err)
{
    if(pMasqueradingVector.size() != 6)
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
        else
        {
            err="The " + pMasqueradingVector[4] + " column cannot be null";
            return false;
        }
    }
    if(!pMasqueradingVector[5].empty())
    {
        if(pJson.isMember(pMasqueradingVector[5]))
        {
            if(!validJsonOfField(5, pMasqueradingVector[5], pJson[pMasqueradingVector[5]], err, true))
                return false;
        }
        else
        {
            err="The " + pMasqueradingVector[5] + " column cannot be null";
            return false;
        }
    }
    return true;
}
bool LdapGroupsSynchronizedGroups::validateJsonForUpdate(const Json::Value &pJson, std::string &err)
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
    if(pJson.isMember("entry"))
    {
        if(!validJsonOfField(1, "entry", pJson["entry"], err, false))
            return false;
    }
    if(pJson.isMember("group_id"))
    {
        if(!validJsonOfField(2, "group_id", pJson["group_id"], err, false))
            return false;
    }
    if(pJson.isMember("auth_source_id"))
    {
        if(!validJsonOfField(3, "auth_source_id", pJson["auth_source_id"], err, false))
            return false;
    }
    if(pJson.isMember("created_at"))
    {
        if(!validJsonOfField(4, "created_at", pJson["created_at"], err, false))
            return false;
    }
    if(pJson.isMember("updated_at"))
    {
        if(!validJsonOfField(5, "updated_at", pJson["updated_at"], err, false))
            return false;
    }
    return true;
}
bool LdapGroupsSynchronizedGroups::validateMasqueradedJsonForUpdate(const Json::Value &pJson,
                                                                    const std::vector<std::string> &pMasqueradingVector,
                                                                    std::string &err)
{
    if(pMasqueradingVector.size() != 6)
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
    if(!pMasqueradingVector[5].empty() && pJson.isMember(pMasqueradingVector[5]))
    {
        if(!validJsonOfField(5, pMasqueradingVector[5], pJson[pMasqueradingVector[5]], err, false))
            return false;
    }
    return true;
}
bool LdapGroupsSynchronizedGroups::validJsonOfField(size_t index,
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
            if(!pJson.isInt())
            {
                err="Type error in the "+fieldName+"field";
                return false;
            }
            break;
        case 4:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(!pJson.isString() && !pJson.isNull())
            {
                err="Type error in the "+fieldName+"field";
                return false;                
            }
            break;
        case 5:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
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
