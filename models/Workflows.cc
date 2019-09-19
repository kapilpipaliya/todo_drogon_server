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
using namespace drogon_model::openproject6;

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
Workflows::Workflows(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
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
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 7 > r.size())
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
            _typeId=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            _oldStatusId=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            _newStatusId=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            _roleId=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            _assignee=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            _author=std::make_shared<bool>(r[index].as<bool>());
        }
    }

}

Workflows::Workflows(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 7)
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
        _typeId=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[1]].asInt64());
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        _oldStatusId=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[2]].asInt64());
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        _newStatusId=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[3]].asInt64());
    }
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        _roleId=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[4]].asInt64());
    }
    if(!pMasqueradingVector[5].empty() && pJson.isMember(pMasqueradingVector[5]))
    {
        _assignee=std::make_shared<bool>(pJson[pMasqueradingVector[5]].asBool());
    }
    if(!pMasqueradingVector[6].empty() && pJson.isMember(pMasqueradingVector[6]))
    {
        _author=std::make_shared<bool>(pJson[pMasqueradingVector[6]].asBool());
    }
}

Workflows::Workflows(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        _id=std::make_shared<int32_t>((int32_t)pJson["id"].asInt64());
    }
    if(pJson.isMember("type_id"))
    {
        _typeId=std::make_shared<int32_t>((int32_t)pJson["type_id"].asInt64());
    }
    if(pJson.isMember("old_status_id"))
    {
        _oldStatusId=std::make_shared<int32_t>((int32_t)pJson["old_status_id"].asInt64());
    }
    if(pJson.isMember("new_status_id"))
    {
        _newStatusId=std::make_shared<int32_t>((int32_t)pJson["new_status_id"].asInt64());
    }
    if(pJson.isMember("role_id"))
    {
        _roleId=std::make_shared<int32_t>((int32_t)pJson["role_id"].asInt64());
    }
    if(pJson.isMember("assignee"))
    {
        _assignee=std::make_shared<bool>(pJson["assignee"].asBool());
    }
    if(pJson.isMember("author"))
    {
        _author=std::make_shared<bool>(pJson["author"].asBool());
    }
}

void Workflows::updateByMasqueradedJson(const Json::Value &pJson,
                                            const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 7)
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
        _typeId=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[1]].asInt64());
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        _dirtyFlag[2] = true;
        _oldStatusId=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[2]].asInt64());
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        _dirtyFlag[3] = true;
        _newStatusId=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[3]].asInt64());
    }
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        _dirtyFlag[4] = true;
        _roleId=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[4]].asInt64());
    }
    if(!pMasqueradingVector[5].empty() && pJson.isMember(pMasqueradingVector[5]))
    {
        _dirtyFlag[5] = true;
        _assignee=std::make_shared<bool>(pJson[pMasqueradingVector[5]].asBool());
    }
    if(!pMasqueradingVector[6].empty() && pJson.isMember(pMasqueradingVector[6]))
    {
        _dirtyFlag[6] = true;
        _author=std::make_shared<bool>(pJson[pMasqueradingVector[6]].asBool());
    }
}
                                                                    
void Workflows::updateByJson(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        _id=std::make_shared<int32_t>((int32_t)pJson["id"].asInt64());
    }
    if(pJson.isMember("type_id"))
    {
        _dirtyFlag[1] = true;
        _typeId=std::make_shared<int32_t>((int32_t)pJson["type_id"].asInt64());
    }
    if(pJson.isMember("old_status_id"))
    {
        _dirtyFlag[2] = true;
        _oldStatusId=std::make_shared<int32_t>((int32_t)pJson["old_status_id"].asInt64());
    }
    if(pJson.isMember("new_status_id"))
    {
        _dirtyFlag[3] = true;
        _newStatusId=std::make_shared<int32_t>((int32_t)pJson["new_status_id"].asInt64());
    }
    if(pJson.isMember("role_id"))
    {
        _dirtyFlag[4] = true;
        _roleId=std::make_shared<int32_t>((int32_t)pJson["role_id"].asInt64());
    }
    if(pJson.isMember("assignee"))
    {
        _dirtyFlag[5] = true;
        _assignee=std::make_shared<bool>(pJson["assignee"].asBool());
    }
    if(pJson.isMember("author"))
    {
        _dirtyFlag[6] = true;
        _author=std::make_shared<bool>(pJson["author"].asBool());
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

Json::Value Workflows::toMasqueradedJson(
    const std::vector<std::string> &pMasqueradingVector) const
{
    Json::Value ret;
    if(pMasqueradingVector.size() == 7)
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
            if(getTypeId())
            {
                ret[pMasqueradingVector[1]]=getValueOfTypeId();
            }
            else
            {
                ret[pMasqueradingVector[1]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[2].empty())
        {
            if(getOldStatusId())
            {
                ret[pMasqueradingVector[2]]=getValueOfOldStatusId();
            }
            else
            {
                ret[pMasqueradingVector[2]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[3].empty())
        {
            if(getNewStatusId())
            {
                ret[pMasqueradingVector[3]]=getValueOfNewStatusId();
            }
            else
            {
                ret[pMasqueradingVector[3]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[4].empty())
        {
            if(getRoleId())
            {
                ret[pMasqueradingVector[4]]=getValueOfRoleId();
            }
            else
            {
                ret[pMasqueradingVector[4]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[5].empty())
        {
            if(getAssignee())
            {
                ret[pMasqueradingVector[5]]=getValueOfAssignee();
            }
            else
            {
                ret[pMasqueradingVector[5]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[6].empty())
        {
            if(getAuthor())
            {
                ret[pMasqueradingVector[6]]=getValueOfAuthor();
            }
            else
            {
                ret[pMasqueradingVector[6]]=Json::Value();
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

bool Workflows::validateJsonForCreation(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("id"))
    {
        if(!validJsonOfField(0, "id", pJson["id"], err, true))
            return false;
    }
    if(pJson.isMember("type_id"))
    {
        if(!validJsonOfField(1, "type_id", pJson["type_id"], err, true))
            return false;
    }
    if(pJson.isMember("old_status_id"))
    {
        if(!validJsonOfField(2, "old_status_id", pJson["old_status_id"], err, true))
            return false;
    }
    if(pJson.isMember("new_status_id"))
    {
        if(!validJsonOfField(3, "new_status_id", pJson["new_status_id"], err, true))
            return false;
    }
    if(pJson.isMember("role_id"))
    {
        if(!validJsonOfField(4, "role_id", pJson["role_id"], err, true))
            return false;
    }
    if(pJson.isMember("assignee"))
    {
        if(!validJsonOfField(5, "assignee", pJson["assignee"], err, true))
            return false;
    }
    if(pJson.isMember("author"))
    {
        if(!validJsonOfField(6, "author", pJson["author"], err, true))
            return false;
    }
    return true;
}
bool Workflows::validateMasqueradedJsonForCreation(const Json::Value &pJson,
                                                   const std::vector<std::string> &pMasqueradingVector,
                                                   std::string &err)
{
    if(pMasqueradingVector.size() != 7)
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
    if(!pMasqueradingVector[5].empty())
    {
        if(pJson.isMember(pMasqueradingVector[5]))
        {
            if(!validJsonOfField(5, pMasqueradingVector[5], pJson[pMasqueradingVector[5]], err, true))
                return false;
        }
    }
    if(!pMasqueradingVector[6].empty())
    {
        if(pJson.isMember(pMasqueradingVector[6]))
        {
            if(!validJsonOfField(6, pMasqueradingVector[6], pJson[pMasqueradingVector[6]], err, true))
                return false;
        }
    }
    return true;
}
bool Workflows::validateJsonForUpdate(const Json::Value &pJson, std::string &err)
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
    if(pJson.isMember("type_id"))
    {
        if(!validJsonOfField(1, "type_id", pJson["type_id"], err, false))
            return false;
    }
    if(pJson.isMember("old_status_id"))
    {
        if(!validJsonOfField(2, "old_status_id", pJson["old_status_id"], err, false))
            return false;
    }
    if(pJson.isMember("new_status_id"))
    {
        if(!validJsonOfField(3, "new_status_id", pJson["new_status_id"], err, false))
            return false;
    }
    if(pJson.isMember("role_id"))
    {
        if(!validJsonOfField(4, "role_id", pJson["role_id"], err, false))
            return false;
    }
    if(pJson.isMember("assignee"))
    {
        if(!validJsonOfField(5, "assignee", pJson["assignee"], err, false))
            return false;
    }
    if(pJson.isMember("author"))
    {
        if(!validJsonOfField(6, "author", pJson["author"], err, false))
            return false;
    }
    return true;
}
bool Workflows::validateMasqueradedJsonForUpdate(const Json::Value &pJson,
                                                 const std::vector<std::string> &pMasqueradingVector,
                                                 std::string &err)
{
    if(pMasqueradingVector.size() != 7)
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
    if(!pMasqueradingVector[6].empty() && pJson.isMember(pMasqueradingVector[6]))
    {
        if(!validJsonOfField(6, pMasqueradingVector[6], pJson[pMasqueradingVector[6]], err, false))
            return false;
    }
    return true;
}
bool Workflows::validJsonOfField(size_t index,
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
        case 2:
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
        case 3:
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
        case 4:
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
        case 5:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(!pJson.isBool())
            {
                err="Type error in the "+fieldName+"field";
                return false;
            }
            break;
        case 6:
            if(pJson.isNull())
            {
                err="The " + fieldName + " column cannot be null";
                return false;
            }
            if(!pJson.isBool())
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
