/**
 *
 *  Roles.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "Roles.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon_model::openproject6;

const std::string Roles::Cols::_id = "id";
const std::string Roles::Cols::_name = "name";
const std::string Roles::Cols::_position = "position";
const std::string Roles::Cols::_assignable = "assignable";
const std::string Roles::Cols::_builtin = "builtin";
const std::string Roles::Cols::_type = "type";
const std::string Roles::primaryKeyName = "id";
const bool Roles::hasPrimaryKey = true;
const std::string Roles::tableName = "roles";

const std::vector<typename Roles::MetaData> Roles::_metaData={
{"id","int32_t","integer",4,1,1,1},
{"name","std::string","character varying",30,0,0,1},
{"position","int32_t","integer",4,0,0,0},
{"assignable","bool","boolean",1,0,0,0},
{"builtin","int32_t","integer",4,0,0,1},
{"type","std::string","character varying",30,0,0,0}
};
const std::string &Roles::getColumnName(size_t index) noexcept(false)
{
    assert(index < _metaData.size());
    return _metaData[index]._colName;
}
Roles::Roles(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
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
        if(!r["assignable"].isNull())
        {
            _assignable=std::make_shared<bool>(r["assignable"].as<bool>());
        }
        if(!r["builtin"].isNull())
        {
            _builtin=std::make_shared<int32_t>(r["builtin"].as<int32_t>());
        }
        if(!r["type"].isNull())
        {
            _type=std::make_shared<std::string>(r["type"].as<std::string>());
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
            _name=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            _position=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            _assignable=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            _builtin=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            _type=std::make_shared<std::string>(r[index].as<std::string>());
        }
    }

}

Roles::Roles(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 6)
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
        _name=std::make_shared<std::string>(pJson[pMasqueradingVector[1]].asString());
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        _position=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[2]].asInt64());
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        _assignable=std::make_shared<bool>(pJson[pMasqueradingVector[3]].asBool());
    }
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        _builtin=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[4]].asInt64());
    }
    if(!pMasqueradingVector[5].empty() && pJson.isMember(pMasqueradingVector[5]))
    {
        _type=std::make_shared<std::string>(pJson[pMasqueradingVector[5]].asString());
    }
}

Roles::Roles(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        _id=std::make_shared<int32_t>((int32_t)pJson["id"].asInt64());
    }
    if(pJson.isMember("name"))
    {
        _name=std::make_shared<std::string>(pJson["name"].asString());
    }
    if(pJson.isMember("position"))
    {
        _position=std::make_shared<int32_t>((int32_t)pJson["position"].asInt64());
    }
    if(pJson.isMember("assignable"))
    {
        _assignable=std::make_shared<bool>(pJson["assignable"].asBool());
    }
    if(pJson.isMember("builtin"))
    {
        _builtin=std::make_shared<int32_t>((int32_t)pJson["builtin"].asInt64());
    }
    if(pJson.isMember("type"))
    {
        _type=std::make_shared<std::string>(pJson["type"].asString());
    }
}

void Roles::updateByMasqueradedJson(const Json::Value &pJson,
                                            const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 6)
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
        _name=std::make_shared<std::string>(pJson[pMasqueradingVector[1]].asString());
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        _dirtyFlag[2] = true;
        _position=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[2]].asInt64());
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        _dirtyFlag[3] = true;
        _assignable=std::make_shared<bool>(pJson[pMasqueradingVector[3]].asBool());
    }
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        _dirtyFlag[4] = true;
        _builtin=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[4]].asInt64());
    }
    if(!pMasqueradingVector[5].empty() && pJson.isMember(pMasqueradingVector[5]))
    {
        _dirtyFlag[5] = true;
        _type=std::make_shared<std::string>(pJson[pMasqueradingVector[5]].asString());
    }
}
                                                                    
void Roles::updateByJson(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        _id=std::make_shared<int32_t>((int32_t)pJson["id"].asInt64());
    }
    if(pJson.isMember("name"))
    {
        _dirtyFlag[1] = true;
        _name=std::make_shared<std::string>(pJson["name"].asString());
    }
    if(pJson.isMember("position"))
    {
        _dirtyFlag[2] = true;
        _position=std::make_shared<int32_t>((int32_t)pJson["position"].asInt64());
    }
    if(pJson.isMember("assignable"))
    {
        _dirtyFlag[3] = true;
        _assignable=std::make_shared<bool>(pJson["assignable"].asBool());
    }
    if(pJson.isMember("builtin"))
    {
        _dirtyFlag[4] = true;
        _builtin=std::make_shared<int32_t>((int32_t)pJson["builtin"].asInt64());
    }
    if(pJson.isMember("type"))
    {
        _dirtyFlag[5] = true;
        _type=std::make_shared<std::string>(pJson["type"].asString());
    }
}

const int32_t &Roles::getValueOfId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_id)
        return *_id;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Roles::getId() const noexcept
{
    return _id;
}
const typename Roles::PrimaryKeyType & Roles::getPrimaryKey() const
{
    assert(_id);
    return *_id;
}

const std::string &Roles::getValueOfName() const noexcept
{
    const static std::string defaultValue = std::string();
    if(_name)
        return *_name;
    return defaultValue;
}
const std::shared_ptr<std::string> &Roles::getName() const noexcept
{
    return _name;
}
void Roles::setName(const std::string &pName) noexcept
{
    _name = std::make_shared<std::string>(pName);
    _dirtyFlag[1] = true;
}
void Roles::setName(std::string &&pName) noexcept
{
    _name = std::make_shared<std::string>(std::move(pName));
    _dirtyFlag[1] = true;
}


const int32_t &Roles::getValueOfPosition() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_position)
        return *_position;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Roles::getPosition() const noexcept
{
    return _position;
}
void Roles::setPosition(const int32_t &pPosition) noexcept
{
    _position = std::make_shared<int32_t>(pPosition);
    _dirtyFlag[2] = true;
}


const bool &Roles::getValueOfAssignable() const noexcept
{
    const static bool defaultValue = bool();
    if(_assignable)
        return *_assignable;
    return defaultValue;
}
const std::shared_ptr<bool> &Roles::getAssignable() const noexcept
{
    return _assignable;
}
void Roles::setAssignable(const bool &pAssignable) noexcept
{
    _assignable = std::make_shared<bool>(pAssignable);
    _dirtyFlag[3] = true;
}


const int32_t &Roles::getValueOfBuiltin() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_builtin)
        return *_builtin;
    return defaultValue;
}
const std::shared_ptr<int32_t> &Roles::getBuiltin() const noexcept
{
    return _builtin;
}
void Roles::setBuiltin(const int32_t &pBuiltin) noexcept
{
    _builtin = std::make_shared<int32_t>(pBuiltin);
    _dirtyFlag[4] = true;
}


const std::string &Roles::getValueOfType() const noexcept
{
    const static std::string defaultValue = std::string();
    if(_type)
        return *_type;
    return defaultValue;
}
const std::shared_ptr<std::string> &Roles::getType() const noexcept
{
    return _type;
}
void Roles::setType(const std::string &pType) noexcept
{
    _type = std::make_shared<std::string>(pType);
    _dirtyFlag[5] = true;
}
void Roles::setType(std::string &&pType) noexcept
{
    _type = std::make_shared<std::string>(std::move(pType));
    _dirtyFlag[5] = true;
}


void Roles::updateId(const uint64_t id)
{
}

const std::vector<std::string> &Roles::insertColumns() noexcept
{
    static const std::vector<std::string> _inCols={
        "name",
        "position",
        "assignable",
        "builtin",
        "type"
    };
    return _inCols;
}

void Roles::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
    if(getAssignable())
    {
        binder << getValueOfAssignable();
    }
    else
    {
        binder << nullptr;
    }
    if(getBuiltin())
    {
        binder << getValueOfBuiltin();
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
}

const std::vector<std::string> Roles::updateColumns() const
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

void Roles::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getAssignable())
        {
            binder << getValueOfAssignable();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[4])
    {
        if(getBuiltin())
        {
            binder << getValueOfBuiltin();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[5])
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
}
Json::Value Roles::toJson() const
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
    if(getAssignable())
    {
        ret["assignable"]=getValueOfAssignable();
    }
    else
    {
        ret["assignable"]=Json::Value();
    }
    if(getBuiltin())
    {
        ret["builtin"]=getValueOfBuiltin();
    }
    else
    {
        ret["builtin"]=Json::Value();
    }
    if(getType())
    {
        ret["type"]=getValueOfType();
    }
    else
    {
        ret["type"]=Json::Value();
    }
    return ret;
}

Json::Value Roles::toMasqueradedJson(
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
            if(getName())
            {
                ret[pMasqueradingVector[1]]=getValueOfName();
            }
            else
            {
                ret[pMasqueradingVector[1]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[2].empty())
        {
            if(getPosition())
            {
                ret[pMasqueradingVector[2]]=getValueOfPosition();
            }
            else
            {
                ret[pMasqueradingVector[2]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[3].empty())
        {
            if(getAssignable())
            {
                ret[pMasqueradingVector[3]]=getValueOfAssignable();
            }
            else
            {
                ret[pMasqueradingVector[3]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[4].empty())
        {
            if(getBuiltin())
            {
                ret[pMasqueradingVector[4]]=getValueOfBuiltin();
            }
            else
            {
                ret[pMasqueradingVector[4]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[5].empty())
        {
            if(getType())
            {
                ret[pMasqueradingVector[5]]=getValueOfType();
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
    if(getAssignable())
    {
        ret["assignable"]=getValueOfAssignable();
    }
    else
    {
        ret["assignable"]=Json::Value();
    }
    if(getBuiltin())
    {
        ret["builtin"]=getValueOfBuiltin();
    }
    else
    {
        ret["builtin"]=Json::Value();
    }
    if(getType())
    {
        ret["type"]=getValueOfType();
    }
    else
    {
        ret["type"]=Json::Value();
    }
    return ret;
}

bool Roles::validateJsonForCreation(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("id"))
    {
        if(!validJsonOfField(0, "id", pJson["id"], err, true))
            return false;
    }
    if(pJson.isMember("name"))
    {
        if(!validJsonOfField(1, "name", pJson["name"], err, true))
            return false;
    }
    if(pJson.isMember("position"))
    {
        if(!validJsonOfField(2, "position", pJson["position"], err, true))
            return false;
    }
    if(pJson.isMember("assignable"))
    {
        if(!validJsonOfField(3, "assignable", pJson["assignable"], err, true))
            return false;
    }
    if(pJson.isMember("builtin"))
    {
        if(!validJsonOfField(4, "builtin", pJson["builtin"], err, true))
            return false;
    }
    if(pJson.isMember("type"))
    {
        if(!validJsonOfField(5, "type", pJson["type"], err, true))
            return false;
    }
    return true;
}
bool Roles::validateMasqueradedJsonForCreation(const Json::Value &pJson,
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
    }
    if(!pMasqueradingVector[5].empty())
    {
        if(pJson.isMember(pMasqueradingVector[5]))
        {
            if(!validJsonOfField(5, pMasqueradingVector[5], pJson[pMasqueradingVector[5]], err, true))
                return false;
        }
    }
    return true;
}
bool Roles::validateJsonForUpdate(const Json::Value &pJson, std::string &err)
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
    if(pJson.isMember("name"))
    {
        if(!validJsonOfField(1, "name", pJson["name"], err, false))
            return false;
    }
    if(pJson.isMember("position"))
    {
        if(!validJsonOfField(2, "position", pJson["position"], err, false))
            return false;
    }
    if(pJson.isMember("assignable"))
    {
        if(!validJsonOfField(3, "assignable", pJson["assignable"], err, false))
            return false;
    }
    if(pJson.isMember("builtin"))
    {
        if(!validJsonOfField(4, "builtin", pJson["builtin"], err, false))
            return false;
    }
    if(pJson.isMember("type"))
    {
        if(!validJsonOfField(5, "type", pJson["type"], err, false))
            return false;
    }
    return true;
}
bool Roles::validateMasqueradedJsonForUpdate(const Json::Value &pJson,
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
bool Roles::validJsonOfField(size_t index,
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
            if(!pJson.isString() && !pJson.isNull())
            {
                err="Type error in the "+fieldName+"field";
                return false;                
            }
            // asString().length() creates a string object, is there any better way to validate the length?
            if(pJson.isString() && pJson.asString().length() > 30)
            {
                err="String length exceeds limit for the " +
                    fieldName +
                    "field (the maximum value is 30 )";
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
            if(!pJson.isBool())
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
            if(!pJson.isString() && !pJson.isNull())
            {
                err="Type error in the "+fieldName+"field";
                return false;                
            }
            // asString().length() creates a string object, is there any better way to validate the length?
            if(pJson.isString() && pJson.asString().length() > 30)
            {
                err="String length exceeds limit for the " +
                    fieldName +
                    "field (the maximum value is 30 )";
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
