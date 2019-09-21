/**
 *
 *  ExportCardConfigurations.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "ExportCardConfigurations.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon_model::openproject6;

const std::string ExportCardConfigurations::Cols::_id = "id";
const std::string ExportCardConfigurations::Cols::_name = "name";
const std::string ExportCardConfigurations::Cols::_per_page = "per_page";
const std::string ExportCardConfigurations::Cols::_page_size = "page_size";
const std::string ExportCardConfigurations::Cols::_orientation = "orientation";
const std::string ExportCardConfigurations::Cols::_rows = "rows";
const std::string ExportCardConfigurations::Cols::_active = "active";
const std::string ExportCardConfigurations::Cols::_description = "description";
const std::string ExportCardConfigurations::primaryKeyName = "id";
const bool ExportCardConfigurations::hasPrimaryKey = true;
const std::string ExportCardConfigurations::tableName = "export_card_configurations";

const std::vector<typename ExportCardConfigurations::MetaData> ExportCardConfigurations::_metaData={
{"id","int32_t","integer",4,1,1,1},
{"name","std::string","character varying",0,0,0,0},
{"per_page","int32_t","integer",4,0,0,0},
{"page_size","std::string","character varying",0,0,0,0},
{"orientation","std::string","character varying",0,0,0,0},
{"rows","std::string","text",0,0,0,0},
{"active","bool","boolean",1,0,0,0},
{"description","std::string","text",0,0,0,0}
};
const std::string &ExportCardConfigurations::getColumnName(size_t index) noexcept(false)
{
    assert(index < _metaData.size());
    return _metaData[index]._colName;
}
ExportCardConfigurations::ExportCardConfigurations(const Row &r, const ssize_t indexOffset) noexcept
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
        if(!r["per_page"].isNull())
        {
            _perPage=std::make_shared<int32_t>(r["per_page"].as<int32_t>());
        }
        if(!r["page_size"].isNull())
        {
            _pageSize=std::make_shared<std::string>(r["page_size"].as<std::string>());
        }
        if(!r["orientation"].isNull())
        {
            _orientation=std::make_shared<std::string>(r["orientation"].as<std::string>());
        }
        if(!r["rows"].isNull())
        {
            _rows=std::make_shared<std::string>(r["rows"].as<std::string>());
        }
        if(!r["active"].isNull())
        {
            _active=std::make_shared<bool>(r["active"].as<bool>());
        }
        if(!r["description"].isNull())
        {
            _description=std::make_shared<std::string>(r["description"].as<std::string>());
        }
    }
    else
    {
        size_t offset = (size_t)indexOffset;
        if(offset + 8 > r.size())
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
            _perPage=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            _pageSize=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            _orientation=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            _rows=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            _active=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            _description=std::make_shared<std::string>(r[index].as<std::string>());
        }
    }

}

ExportCardConfigurations::ExportCardConfigurations(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 8)
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
            _name=std::make_shared<std::string>(pJson[pMasqueradingVector[1]].asString());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        _dirtyFlag[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            _perPage=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[2]].asInt64());
        }
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        _dirtyFlag[3] = true;
        if(!pJson[pMasqueradingVector[3]].isNull())
        {
            _pageSize=std::make_shared<std::string>(pJson[pMasqueradingVector[3]].asString());
        }
    }
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        _dirtyFlag[4] = true;
        if(!pJson[pMasqueradingVector[4]].isNull())
        {
            _orientation=std::make_shared<std::string>(pJson[pMasqueradingVector[4]].asString());
        }
    }
    if(!pMasqueradingVector[5].empty() && pJson.isMember(pMasqueradingVector[5]))
    {
        _dirtyFlag[5] = true;
        if(!pJson[pMasqueradingVector[5]].isNull())
        {
            _rows=std::make_shared<std::string>(pJson[pMasqueradingVector[5]].asString());
        }
    }
    if(!pMasqueradingVector[6].empty() && pJson.isMember(pMasqueradingVector[6]))
    {
        _dirtyFlag[6] = true;
        if(!pJson[pMasqueradingVector[6]].isNull())
        {
            _active=std::make_shared<bool>(pJson[pMasqueradingVector[6]].asBool());
        }
    }
    if(!pMasqueradingVector[7].empty() && pJson.isMember(pMasqueradingVector[7]))
    {
        _dirtyFlag[7] = true;
        if(!pJson[pMasqueradingVector[7]].isNull())
        {
            _description=std::make_shared<std::string>(pJson[pMasqueradingVector[7]].asString());
        }
    }
}

ExportCardConfigurations::ExportCardConfigurations(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        _dirtyFlag[0]=true;
        if(!pJson["id"].isNull())
        {
            _id=std::make_shared<int32_t>((int32_t)pJson["id"].asInt64());
        }
    }
    if(pJson.isMember("name"))
    {
        _dirtyFlag[1]=true;
        if(!pJson["name"].isNull())
        {
            _name=std::make_shared<std::string>(pJson["name"].asString());
        }
    }
    if(pJson.isMember("per_page"))
    {
        _dirtyFlag[2]=true;
        if(!pJson["per_page"].isNull())
        {
            _perPage=std::make_shared<int32_t>((int32_t)pJson["per_page"].asInt64());
        }
    }
    if(pJson.isMember("page_size"))
    {
        _dirtyFlag[3]=true;
        if(!pJson["page_size"].isNull())
        {
            _pageSize=std::make_shared<std::string>(pJson["page_size"].asString());
        }
    }
    if(pJson.isMember("orientation"))
    {
        _dirtyFlag[4]=true;
        if(!pJson["orientation"].isNull())
        {
            _orientation=std::make_shared<std::string>(pJson["orientation"].asString());
        }
    }
    if(pJson.isMember("rows"))
    {
        _dirtyFlag[5]=true;
        if(!pJson["rows"].isNull())
        {
            _rows=std::make_shared<std::string>(pJson["rows"].asString());
        }
    }
    if(pJson.isMember("active"))
    {
        _dirtyFlag[6]=true;
        if(!pJson["active"].isNull())
        {
            _active=std::make_shared<bool>(pJson["active"].asBool());
        }
    }
    if(pJson.isMember("description"))
    {
        _dirtyFlag[7]=true;
        if(!pJson["description"].isNull())
        {
            _description=std::make_shared<std::string>(pJson["description"].asString());
        }
    }
}

void ExportCardConfigurations::updateByMasqueradedJson(const Json::Value &pJson,
                                            const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 8)
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
            _name=std::make_shared<std::string>(pJson[pMasqueradingVector[1]].asString());
        }
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        _dirtyFlag[2] = true;
        if(!pJson[pMasqueradingVector[2]].isNull())
        {
            _perPage=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[2]].asInt64());
        }
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        _dirtyFlag[3] = true;
        if(!pJson[pMasqueradingVector[3]].isNull())
        {
            _pageSize=std::make_shared<std::string>(pJson[pMasqueradingVector[3]].asString());
        }
    }
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        _dirtyFlag[4] = true;
        if(!pJson[pMasqueradingVector[4]].isNull())
        {
            _orientation=std::make_shared<std::string>(pJson[pMasqueradingVector[4]].asString());
        }
    }
    if(!pMasqueradingVector[5].empty() && pJson.isMember(pMasqueradingVector[5]))
    {
        _dirtyFlag[5] = true;
        if(!pJson[pMasqueradingVector[5]].isNull())
        {
            _rows=std::make_shared<std::string>(pJson[pMasqueradingVector[5]].asString());
        }
    }
    if(!pMasqueradingVector[6].empty() && pJson.isMember(pMasqueradingVector[6]))
    {
        _dirtyFlag[6] = true;
        if(!pJson[pMasqueradingVector[6]].isNull())
        {
            _active=std::make_shared<bool>(pJson[pMasqueradingVector[6]].asBool());
        }
    }
    if(!pMasqueradingVector[7].empty() && pJson.isMember(pMasqueradingVector[7]))
    {
        _dirtyFlag[7] = true;
        if(!pJson[pMasqueradingVector[7]].isNull())
        {
            _description=std::make_shared<std::string>(pJson[pMasqueradingVector[7]].asString());
        }
    }
}
                                                                    
void ExportCardConfigurations::updateByJson(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        if(!pJson["id"].isNull())
        {
            _id=std::make_shared<int32_t>((int32_t)pJson["id"].asInt64());
        }
    }
    if(pJson.isMember("name"))
    {
        _dirtyFlag[1] = true;
        if(!pJson["name"].isNull())
        {
            _name=std::make_shared<std::string>(pJson["name"].asString());
        }
    }
    if(pJson.isMember("per_page"))
    {
        _dirtyFlag[2] = true;
        if(!pJson["per_page"].isNull())
        {
            _perPage=std::make_shared<int32_t>((int32_t)pJson["per_page"].asInt64());
        }
    }
    if(pJson.isMember("page_size"))
    {
        _dirtyFlag[3] = true;
        if(!pJson["page_size"].isNull())
        {
            _pageSize=std::make_shared<std::string>(pJson["page_size"].asString());
        }
    }
    if(pJson.isMember("orientation"))
    {
        _dirtyFlag[4] = true;
        if(!pJson["orientation"].isNull())
        {
            _orientation=std::make_shared<std::string>(pJson["orientation"].asString());
        }
    }
    if(pJson.isMember("rows"))
    {
        _dirtyFlag[5] = true;
        if(!pJson["rows"].isNull())
        {
            _rows=std::make_shared<std::string>(pJson["rows"].asString());
        }
    }
    if(pJson.isMember("active"))
    {
        _dirtyFlag[6] = true;
        if(!pJson["active"].isNull())
        {
            _active=std::make_shared<bool>(pJson["active"].asBool());
        }
    }
    if(pJson.isMember("description"))
    {
        _dirtyFlag[7] = true;
        if(!pJson["description"].isNull())
        {
            _description=std::make_shared<std::string>(pJson["description"].asString());
        }
    }
}

const int32_t &ExportCardConfigurations::getValueOfId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_id)
        return *_id;
    return defaultValue;
}
const std::shared_ptr<int32_t> &ExportCardConfigurations::getId() const noexcept
{
    return _id;
}
const typename ExportCardConfigurations::PrimaryKeyType & ExportCardConfigurations::getPrimaryKey() const
{
    assert(_id);
    return *_id;
}

const std::string &ExportCardConfigurations::getValueOfName() const noexcept
{
    const static std::string defaultValue = std::string();
    if(_name)
        return *_name;
    return defaultValue;
}
const std::shared_ptr<std::string> &ExportCardConfigurations::getName() const noexcept
{
    return _name;
}
void ExportCardConfigurations::setName(const std::string &pName) noexcept
{
    _name = std::make_shared<std::string>(pName);
    _dirtyFlag[1] = true;
}
void ExportCardConfigurations::setName(std::string &&pName) noexcept
{
    _name = std::make_shared<std::string>(std::move(pName));
    _dirtyFlag[1] = true;
}


const int32_t &ExportCardConfigurations::getValueOfPerPage() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_perPage)
        return *_perPage;
    return defaultValue;
}
const std::shared_ptr<int32_t> &ExportCardConfigurations::getPerPage() const noexcept
{
    return _perPage;
}
void ExportCardConfigurations::setPerPage(const int32_t &pPerPage) noexcept
{
    _perPage = std::make_shared<int32_t>(pPerPage);
    _dirtyFlag[2] = true;
}


const std::string &ExportCardConfigurations::getValueOfPageSize() const noexcept
{
    const static std::string defaultValue = std::string();
    if(_pageSize)
        return *_pageSize;
    return defaultValue;
}
const std::shared_ptr<std::string> &ExportCardConfigurations::getPageSize() const noexcept
{
    return _pageSize;
}
void ExportCardConfigurations::setPageSize(const std::string &pPageSize) noexcept
{
    _pageSize = std::make_shared<std::string>(pPageSize);
    _dirtyFlag[3] = true;
}
void ExportCardConfigurations::setPageSize(std::string &&pPageSize) noexcept
{
    _pageSize = std::make_shared<std::string>(std::move(pPageSize));
    _dirtyFlag[3] = true;
}


const std::string &ExportCardConfigurations::getValueOfOrientation() const noexcept
{
    const static std::string defaultValue = std::string();
    if(_orientation)
        return *_orientation;
    return defaultValue;
}
const std::shared_ptr<std::string> &ExportCardConfigurations::getOrientation() const noexcept
{
    return _orientation;
}
void ExportCardConfigurations::setOrientation(const std::string &pOrientation) noexcept
{
    _orientation = std::make_shared<std::string>(pOrientation);
    _dirtyFlag[4] = true;
}
void ExportCardConfigurations::setOrientation(std::string &&pOrientation) noexcept
{
    _orientation = std::make_shared<std::string>(std::move(pOrientation));
    _dirtyFlag[4] = true;
}


const std::string &ExportCardConfigurations::getValueOfRows() const noexcept
{
    const static std::string defaultValue = std::string();
    if(_rows)
        return *_rows;
    return defaultValue;
}
const std::shared_ptr<std::string> &ExportCardConfigurations::getRows() const noexcept
{
    return _rows;
}
void ExportCardConfigurations::setRows(const std::string &pRows) noexcept
{
    _rows = std::make_shared<std::string>(pRows);
    _dirtyFlag[5] = true;
}
void ExportCardConfigurations::setRows(std::string &&pRows) noexcept
{
    _rows = std::make_shared<std::string>(std::move(pRows));
    _dirtyFlag[5] = true;
}


const bool &ExportCardConfigurations::getValueOfActive() const noexcept
{
    const static bool defaultValue = bool();
    if(_active)
        return *_active;
    return defaultValue;
}
const std::shared_ptr<bool> &ExportCardConfigurations::getActive() const noexcept
{
    return _active;
}
void ExportCardConfigurations::setActive(const bool &pActive) noexcept
{
    _active = std::make_shared<bool>(pActive);
    _dirtyFlag[6] = true;
}


const std::string &ExportCardConfigurations::getValueOfDescription() const noexcept
{
    const static std::string defaultValue = std::string();
    if(_description)
        return *_description;
    return defaultValue;
}
const std::shared_ptr<std::string> &ExportCardConfigurations::getDescription() const noexcept
{
    return _description;
}
void ExportCardConfigurations::setDescription(const std::string &pDescription) noexcept
{
    _description = std::make_shared<std::string>(pDescription);
    _dirtyFlag[7] = true;
}
void ExportCardConfigurations::setDescription(std::string &&pDescription) noexcept
{
    _description = std::make_shared<std::string>(std::move(pDescription));
    _dirtyFlag[7] = true;
}


void ExportCardConfigurations::updateId(const uint64_t id)
{
}

const std::vector<std::string> &ExportCardConfigurations::insertColumns() noexcept
{
    static const std::vector<std::string> _inCols={
        "name",
        "per_page",
        "page_size",
        "orientation",
        "rows",
        "active",
        "description"
    };
    return _inCols;
}

void ExportCardConfigurations::outputArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getPerPage())
        {
            binder << getValueOfPerPage();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[3])
    {
        if(getPageSize())
        {
            binder << getValueOfPageSize();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[4])
    {
        if(getOrientation())
        {
            binder << getValueOfOrientation();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[5])
    {
        if(getRows())
        {
            binder << getValueOfRows();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[6])
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
    if(_dirtyFlag[7])
    {
        if(getDescription())
        {
            binder << getValueOfDescription();
        }
        else
        {
            binder << nullptr;
        }
    }
}

const std::vector<std::string> ExportCardConfigurations::updateColumns() const
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

void ExportCardConfigurations::updateArgs(drogon::orm::internal::SqlBinder &binder) const
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
        if(getPerPage())
        {
            binder << getValueOfPerPage();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[3])
    {
        if(getPageSize())
        {
            binder << getValueOfPageSize();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[4])
    {
        if(getOrientation())
        {
            binder << getValueOfOrientation();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[5])
    {
        if(getRows())
        {
            binder << getValueOfRows();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[6])
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
    if(_dirtyFlag[7])
    {
        if(getDescription())
        {
            binder << getValueOfDescription();
        }
        else
        {
            binder << nullptr;
        }
    }
}
Json::Value ExportCardConfigurations::toJson() const
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
    if(getPerPage())
    {
        ret["per_page"]=getValueOfPerPage();
    }
    else
    {
        ret["per_page"]=Json::Value();
    }
    if(getPageSize())
    {
        ret["page_size"]=getValueOfPageSize();
    }
    else
    {
        ret["page_size"]=Json::Value();
    }
    if(getOrientation())
    {
        ret["orientation"]=getValueOfOrientation();
    }
    else
    {
        ret["orientation"]=Json::Value();
    }
    if(getRows())
    {
        ret["rows"]=getValueOfRows();
    }
    else
    {
        ret["rows"]=Json::Value();
    }
    if(getActive())
    {
        ret["active"]=getValueOfActive();
    }
    else
    {
        ret["active"]=Json::Value();
    }
    if(getDescription())
    {
        ret["description"]=getValueOfDescription();
    }
    else
    {
        ret["description"]=Json::Value();
    }
    return ret;
}

Json::Value ExportCardConfigurations::toMasqueradedJson(
    const std::vector<std::string> &pMasqueradingVector) const
{
    Json::Value ret;
    if(pMasqueradingVector.size() == 8)
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
            if(getPerPage())
            {
                ret[pMasqueradingVector[2]]=getValueOfPerPage();
            }
            else
            {
                ret[pMasqueradingVector[2]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[3].empty())
        {
            if(getPageSize())
            {
                ret[pMasqueradingVector[3]]=getValueOfPageSize();
            }
            else
            {
                ret[pMasqueradingVector[3]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[4].empty())
        {
            if(getOrientation())
            {
                ret[pMasqueradingVector[4]]=getValueOfOrientation();
            }
            else
            {
                ret[pMasqueradingVector[4]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[5].empty())
        {
            if(getRows())
            {
                ret[pMasqueradingVector[5]]=getValueOfRows();
            }
            else
            {
                ret[pMasqueradingVector[5]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[6].empty())
        {
            if(getActive())
            {
                ret[pMasqueradingVector[6]]=getValueOfActive();
            }
            else
            {
                ret[pMasqueradingVector[6]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[7].empty())
        {
            if(getDescription())
            {
                ret[pMasqueradingVector[7]]=getValueOfDescription();
            }
            else
            {
                ret[pMasqueradingVector[7]]=Json::Value();
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
    if(getPerPage())
    {
        ret["per_page"]=getValueOfPerPage();
    }
    else
    {
        ret["per_page"]=Json::Value();
    }
    if(getPageSize())
    {
        ret["page_size"]=getValueOfPageSize();
    }
    else
    {
        ret["page_size"]=Json::Value();
    }
    if(getOrientation())
    {
        ret["orientation"]=getValueOfOrientation();
    }
    else
    {
        ret["orientation"]=Json::Value();
    }
    if(getRows())
    {
        ret["rows"]=getValueOfRows();
    }
    else
    {
        ret["rows"]=Json::Value();
    }
    if(getActive())
    {
        ret["active"]=getValueOfActive();
    }
    else
    {
        ret["active"]=Json::Value();
    }
    if(getDescription())
    {
        ret["description"]=getValueOfDescription();
    }
    else
    {
        ret["description"]=Json::Value();
    }
    return ret;
}

bool ExportCardConfigurations::validateJsonForCreation(const Json::Value &pJson, std::string &err)
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
    if(pJson.isMember("per_page"))
    {
        if(!validJsonOfField(2, "per_page", pJson["per_page"], err, true))
            return false;
    }
    if(pJson.isMember("page_size"))
    {
        if(!validJsonOfField(3, "page_size", pJson["page_size"], err, true))
            return false;
    }
    if(pJson.isMember("orientation"))
    {
        if(!validJsonOfField(4, "orientation", pJson["orientation"], err, true))
            return false;
    }
    if(pJson.isMember("rows"))
    {
        if(!validJsonOfField(5, "rows", pJson["rows"], err, true))
            return false;
    }
    if(pJson.isMember("active"))
    {
        if(!validJsonOfField(6, "active", pJson["active"], err, true))
            return false;
    }
    if(pJson.isMember("description"))
    {
        if(!validJsonOfField(7, "description", pJson["description"], err, true))
            return false;
    }
    return true;
}
bool ExportCardConfigurations::validateMasqueradedJsonForCreation(const Json::Value &pJson,
                                                                  const std::vector<std::string> &pMasqueradingVector,
                                                                  std::string &err)
{
    if(pMasqueradingVector.size() != 8)
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
    if(!pMasqueradingVector[7].empty())
    {
        if(pJson.isMember(pMasqueradingVector[7]))
        {
            if(!validJsonOfField(7, pMasqueradingVector[7], pJson[pMasqueradingVector[7]], err, true))
                return false;
        }
    }
    return true;
}
bool ExportCardConfigurations::validateJsonForUpdate(const Json::Value &pJson, std::string &err)
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
    if(pJson.isMember("per_page"))
    {
        if(!validJsonOfField(2, "per_page", pJson["per_page"], err, false))
            return false;
    }
    if(pJson.isMember("page_size"))
    {
        if(!validJsonOfField(3, "page_size", pJson["page_size"], err, false))
            return false;
    }
    if(pJson.isMember("orientation"))
    {
        if(!validJsonOfField(4, "orientation", pJson["orientation"], err, false))
            return false;
    }
    if(pJson.isMember("rows"))
    {
        if(!validJsonOfField(5, "rows", pJson["rows"], err, false))
            return false;
    }
    if(pJson.isMember("active"))
    {
        if(!validJsonOfField(6, "active", pJson["active"], err, false))
            return false;
    }
    if(pJson.isMember("description"))
    {
        if(!validJsonOfField(7, "description", pJson["description"], err, false))
            return false;
    }
    return true;
}
bool ExportCardConfigurations::validateMasqueradedJsonForUpdate(const Json::Value &pJson,
                                                                const std::vector<std::string> &pMasqueradingVector,
                                                                std::string &err)
{
    if(pMasqueradingVector.size() != 8)
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
    if(!pMasqueradingVector[7].empty() && pJson.isMember(pMasqueradingVector[7]))
    {
        if(!validJsonOfField(7, pMasqueradingVector[7], pJson[pMasqueradingVector[7]], err, false))
            return false;
    }
    return true;
}
bool ExportCardConfigurations::validJsonOfField(size_t index,
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
        case 5:
            if(!pJson.isString() && !pJson.isNull())
            {
                err="Type error in the "+fieldName+"field";
                return false;                
            }
            break;
        case 6:
            if(!pJson.isBool())
            {
                err="Type error in the "+fieldName+"field";
                return false;
            }
            break;
        case 7:
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
