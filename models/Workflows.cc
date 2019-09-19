/**
 *
 *  Workflows.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "Workflows.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon_model::openproject4;

const std::string Workflows::Cols::_id = "id";
const std::string Workflows::Cols::_type_id = "type_id";
const std::string Workflows::Cols::_old_status_id = "old_status_id";
const std::string Workflows::Cols::_new_status_id = "new_status_id";
const std::string Workflows::Cols::_role_id = "role_id";
const std::string Workflows::Cols::_assignee = "assignee";
const std::string Workflows::Cols::_author = "author";
const std::string Workflows::primaryKeyName = "id";
const bool Workflows::hasPrimaryKey = true;
const std::string Workflows::tableName = "workflows";

const std::vector<typename Workflows::MetaData> Workflows::_metaData={
{"id","int32_t","integer",4,1,1,1},
{"type_id","int32_t","integer",4,0,0,1},
{"old_status_id","int32_t","integer",4,0,0,1},
{"new_status_id","int32_t","integer",4,0,0,1},
{"role_id","int32_t","integer",4,0,0,1},
{"assignee","bool","boolean",1,0,0,1},
{"author","bool","boolean",1,0,0,1}
};
const std::string &Workflows::getColumnName(size_t index) noexcept(false)
{
    assert(index < _metaData.size());
    return _metaData[index]._colName;
}
Workflows::Workflows(const Row &r) noexcept
{
        if(!r["id"].isNull())
        {
            _id=std::make_shared<int32_t>(r["id"].as<int32_t>());
        }
        if(!r["type_id"].isNull())
        {
            _typeId=std::make_shared<int32_t>(r["type_id"].as<int32_t>());
        }
        if(!r["old_status_id"].isNull())
        {
            _oldStatusId=std::make_shared<int32_t>(r["old_status_id"].as<int32_t>());
        }
        if(!r["new_status_id"].isNull())
        {
            _newStatusId=std::make_shared<int32_t>(r["new_status_id"].as<int32_t>());
        }
        if(!r["role_id"].isNull())
        {
            _roleId=std::make_shared<int32_t>(r["role_id"].as<int32_t>());
        }
        if(!r["assignee"].isNull())
        {
            _assignee=std::make_shared<bool>(r["assignee"].as<bool>());
        }
        if(!r["author"].isNull())
        {
            _author=std::make_shared<bool>(r["author"].as<bool>());
        }
}
const int32_t &Workflows::getValueOfId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_id)
        return *_id;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Workflows::getId() const noexcept
{
    return _id;
}
const typename Workflows::PrimaryKeyType & Workflows::getPrimaryKey() const
{
    assert(_id);
    return *_id;
}

const int32_t &Workflows::getValueOfTypeId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_typeId)
        return *_typeId;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Workflows::getTypeId() const noexcept
{
    return _typeId;
}
void Workflows::setTypeId(const int32_t &pTypeId) noexcept
{
    _typeId = std::make_shared<int32_t>(pTypeId);
    _dirtyFlag[1] = true;
}


const int32_t &Workflows::getValueOfOldStatusId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_oldStatusId)
        return *_oldStatusId;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Workflows::getOldStatusId() const noexcept
{
    return _oldStatusId;
}
void Workflows::setOldStatusId(const int32_t &pOldStatusId) noexcept
{
    _oldStatusId = std::make_shared<int32_t>(pOldStatusId);
    _dirtyFlag[2] = true;
}


const int32_t &Workflows::getValueOfNewStatusId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_newStatusId)
        return *_newStatusId;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Workflows::getNewStatusId() const noexcept
{
    return _newStatusId;
}
void Workflows::setNewStatusId(const int32_t &pNewStatusId) noexcept
{
    _newStatusId = std::make_shared<int32_t>(pNewStatusId);
    _dirtyFlag[3] = true;
}


const int32_t &Workflows::getValueOfRoleId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_roleId)
        return *_roleId;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Workflows::getRoleId() const noexcept
{
    return _roleId;
}
void Workflows::setRoleId(const int32_t &pRoleId) noexcept
{
    _roleId = std::make_shared<int32_t>(pRoleId);
    _dirtyFlag[4] = true;
}


const bool &Workflows::getValueOfAssignee() const noexcept
{
    const static bool defaultValue = bool();
    if(_assignee)
        return *_assignee;
    return defaultValue;
}
const std::shared_ptr<bool> &Workflows::getAssignee() const noexcept
{
    return _assignee;
}
void Workflows::setAssignee(const bool &pAssignee) noexcept
{
    _assignee = std::make_shared<bool>(pAssignee);
    _dirtyFlag[5] = true;
}


const bool &Workflows::getValueOfAuthor() const noexcept
{
    const static bool defaultValue = bool();
    if(_author)
        return *_author;
    return defaultValue;
}
const std::shared_ptr<bool> &Workflows::getAuthor() const noexcept
{
    return _author;
}
void Workflows::setAuthor(const bool &pAuthor) noexcept
{
    _author = std::make_shared<bool>(pAuthor);
    _dirtyFlag[6] = true;
}


void Workflows::updateId(const uint64_t id)
{
}

const std::vector<std::string> &Workflows::insertColumns() noexcept
{
    static const std::vector<std::string> _inCols={
        "type_id",
        "old_status_id",
        "new_status_id",
        "role_id",
        "assignee",
        "author"
    };
    return _inCols;
}

void Workflows::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(getTypeId())
    {
        binder << getValueOfTypeId();
    }
    else
    {
        binder << nullptr;
    }
    if(getOldStatusId())
    {
        binder << getValueOfOldStatusId();
    }
    else
    {
        binder << nullptr;
    }
    if(getNewStatusId())
    {
        binder << getValueOfNewStatusId();
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
    if(getAssignee())
    {
        binder << getValueOfAssignee();
    }
    else
    {
        binder << nullptr;
    }
    if(getAuthor())
    {
        binder << getValueOfAuthor();
    }
    else
    {
        binder << nullptr;
    }
}

const std::vector<std::string> Workflows::updateColumns() const
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

void Workflows::updateArgs(drogon::orm::internal::SqlBinder &binder) const
{
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
    if(_dirtyFlag[2])
    {
        if(getOldStatusId())
        {
            binder << getValueOfOldStatusId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[3])
    {
        if(getNewStatusId())
        {
            binder << getValueOfNewStatusId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[4])
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
    if(_dirtyFlag[5])
    {
        if(getAssignee())
        {
            binder << getValueOfAssignee();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[6])
    {
        if(getAuthor())
        {
            binder << getValueOfAuthor();
        }
        else
        {
            binder << nullptr;
        }
    }
}
Json::Value Workflows::toJson() const
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
    if(getTypeId())
    {
        ret["type_id"]=getValueOfTypeId();
    }
    else
    {
        ret["type_id"]=Json::Value();
    }
    if(getOldStatusId())
    {
        ret["old_status_id"]=getValueOfOldStatusId();
    }
    else
    {
        ret["old_status_id"]=Json::Value();
    }
    if(getNewStatusId())
    {
        ret["new_status_id"]=getValueOfNewStatusId();
    }
    else
    {
        ret["new_status_id"]=Json::Value();
    }
    if(getRoleId())
    {
        ret["role_id"]=getValueOfRoleId();
    }
    else
    {
        ret["role_id"]=Json::Value();
    }
    if(getAssignee())
    {
        ret["assignee"]=getValueOfAssignee();
    }
    else
    {
        ret["assignee"]=Json::Value();
    }
    if(getAuthor())
    {
        ret["author"]=getValueOfAuthor();
    }
    else
    {
        ret["author"]=Json::Value();
    }
    return ret;
}
