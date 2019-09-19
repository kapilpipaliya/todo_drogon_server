/**
 *
 *  Members.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "Members.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon_model::openproject4;

const std::string Members::Cols::_id = "id";
const std::string Members::Cols::_user_id = "user_id";
const std::string Members::Cols::_project_id = "project_id";
const std::string Members::Cols::_created_on = "created_on";
const std::string Members::Cols::_mail_notification = "mail_notification";
const std::string Members::primaryKeyName = "id";
const bool Members::hasPrimaryKey = true;
const std::string Members::tableName = "members";

const std::vector<typename Members::MetaData> Members::_metaData={
{"id","int32_t","integer",4,1,1,1},
{"user_id","int32_t","integer",4,0,0,1},
{"project_id","int32_t","integer",4,0,0,1},
{"created_on","::trantor::Date","timestamp without time zone",0,0,0,0},
{"mail_notification","bool","boolean",1,0,0,1}
};
const std::string &Members::getColumnName(size_t index) noexcept(false)
{
    assert(index < _metaData.size());
    return _metaData[index]._colName;
}
Members::Members(const Row &r) noexcept
{
        if(!r["id"].isNull())
        {
            _id=std::make_shared<int32_t>(r["id"].as<int32_t>());
        }
        if(!r["user_id"].isNull())
        {
            _userId=std::make_shared<int32_t>(r["user_id"].as<int32_t>());
        }
        if(!r["project_id"].isNull())
        {
            _projectId=std::make_shared<int32_t>(r["project_id"].as<int32_t>());
        }
        if(!r["created_on"].isNull())
        {
            auto timeStr = r["created_on"].as<std::string>();
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
            _createdOn=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
        }
        if(!r["mail_notification"].isNull())
        {
            _mailNotification=std::make_shared<bool>(r["mail_notification"].as<bool>());
        }
}
const int32_t &Members::getValueOfId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_id)
        return *_id;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Members::getId() const noexcept
{
    return _id;
}
const typename Members::PrimaryKeyType & Members::getPrimaryKey() const
{
    assert(_id);
    return *_id;
}

const int32_t &Members::getValueOfUserId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_userId)
        return *_userId;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Members::getUserId() const noexcept
{
    return _userId;
}
void Members::setUserId(const int32_t &pUserId) noexcept
{
    _userId = std::make_shared<int32_t>(pUserId);
    _dirtyFlag[1] = true;
}


const int32_t &Members::getValueOfProjectId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_projectId)
        return *_projectId;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Members::getProjectId() const noexcept
{
    return _projectId;
}
void Members::setProjectId(const int32_t &pProjectId) noexcept
{
    _projectId = std::make_shared<int32_t>(pProjectId);
    _dirtyFlag[2] = true;
}


const ::trantor::Date &Members::getValueOfCreatedOn() const noexcept
{
    const static ::trantor::Date defaultValue = ::trantor::Date();
    if(_createdOn)
        return *_createdOn;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &Members::getCreatedOn() const noexcept
{
    return _createdOn;
}
void Members::setCreatedOn(const ::trantor::Date &pCreatedOn) noexcept
{
    _createdOn = std::make_shared<::trantor::Date>(pCreatedOn);
    _dirtyFlag[3] = true;
}


const bool &Members::getValueOfMailNotification() const noexcept
{
    const static bool defaultValue = bool();
    if(_mailNotification)
        return *_mailNotification;
    return defaultValue;
}
const std::shared_ptr<bool> &Members::getMailNotification() const noexcept
{
    return _mailNotification;
}
void Members::setMailNotification(const bool &pMailNotification) noexcept
{
    _mailNotification = std::make_shared<bool>(pMailNotification);
    _dirtyFlag[4] = true;
}


void Members::updateId(const uint64_t id)
{
}

const std::vector<std::string> &Members::insertColumns() noexcept
{
    static const std::vector<std::string> _inCols={
        "user_id",
        "project_id",
        "created_on",
        "mail_notification"
    };
    return _inCols;
}

void Members::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(getUserId())
    {
        binder << getValueOfUserId();
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
    if(getCreatedOn())
    {
        binder << getValueOfCreatedOn();
    }
    else
    {
        binder << nullptr;
    }
    if(getMailNotification())
    {
        binder << getValueOfMailNotification();
    }
    else
    {
        binder << nullptr;
    }
}

const std::vector<std::string> Members::updateColumns() const
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

void Members::updateArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(_dirtyFlag[1])
    {
        if(getUserId())
        {
            binder << getValueOfUserId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[2])
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
    if(_dirtyFlag[3])
    {
        if(getCreatedOn())
        {
            binder << getValueOfCreatedOn();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[4])
    {
        if(getMailNotification())
        {
            binder << getValueOfMailNotification();
        }
        else
        {
            binder << nullptr;
        }
    }
}
Json::Value Members::toJson() const
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
    if(getUserId())
    {
        ret["user_id"]=getValueOfUserId();
    }
    else
    {
        ret["user_id"]=Json::Value();
    }
    if(getProjectId())
    {
        ret["project_id"]=getValueOfProjectId();
    }
    else
    {
        ret["project_id"]=Json::Value();
    }
    if(getCreatedOn())
    {
        ret["created_on"]=getCreatedOn()->toDbStringLocal();
    }
    else
    {
        ret["created_on"]=Json::Value();
    }
    if(getMailNotification())
    {
        ret["mail_notification"]=getValueOfMailNotification();
    }
    else
    {
        ret["mail_notification"]=Json::Value();
    }
    return ret;
}
