/**
 *
 *  WikiPages.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "WikiPages.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon_model::openproject6;

const std::string WikiPages::Cols::_id = "id";
const std::string WikiPages::Cols::_wiki_id = "wiki_id";
const std::string WikiPages::Cols::_title = "title";
const std::string WikiPages::Cols::_created_on = "created_on";
const std::string WikiPages::Cols::_protected = "protected";
const std::string WikiPages::Cols::_parent_id = "parent_id";
const std::string WikiPages::Cols::_slug = "slug";
const std::string WikiPages::Cols::_updated_at = "updated_at";
const std::string WikiPages::primaryKeyName = "id";
const bool WikiPages::hasPrimaryKey = true;
const std::string WikiPages::tableName = "wiki_pages";

const std::vector<typename WikiPages::MetaData> WikiPages::_metaData={
{"id","int32_t","integer",4,1,1,1},
{"wiki_id","int32_t","integer",4,0,0,1},
{"title","std::string","character varying",0,0,0,1},
{"created_on","::trantor::Date","timestamp without time zone",0,0,0,1},
{"protected","bool","boolean",1,0,0,1},
{"parent_id","int32_t","integer",4,0,0,0},
{"slug","std::string","character varying",0,0,0,1},
{"updated_at","::trantor::Date","timestamp without time zone",0,0,0,1}
};
const std::string &WikiPages::getColumnName(size_t index) noexcept(false)
{
    assert(index < _metaData.size());
    return _metaData[index]._colName;
}
WikiPages::WikiPages(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            _id=std::make_shared<int32_t>(r["id"].as<int32_t>());
        }
        if(!r["wiki_id"].isNull())
        {
            _wikiId=std::make_shared<int32_t>(r["wiki_id"].as<int32_t>());
        }
        if(!r["title"].isNull())
        {
            _title=std::make_shared<std::string>(r["title"].as<std::string>());
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
        if(!r["protected"].isNull())
        {
            _protected=std::make_shared<bool>(r["protected"].as<bool>());
        }
        if(!r["parent_id"].isNull())
        {
            _parentId=std::make_shared<int32_t>(r["parent_id"].as<int32_t>());
        }
        if(!r["slug"].isNull())
        {
            _slug=std::make_shared<std::string>(r["slug"].as<std::string>());
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
            _wikiId=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            _title=std::make_shared<std::string>(r[index].as<std::string>());
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
            _createdOn=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            _protected=std::make_shared<bool>(r[index].as<bool>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            _parentId=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 6;
        if(!r[index].isNull())
        {
            _slug=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 7;
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

WikiPages::WikiPages(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 8)
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
        _wikiId=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[1]].asInt64());
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        _title=std::make_shared<std::string>(pJson[pMasqueradingVector[2]].asString());
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
        _createdOn=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
    }
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        _protected=std::make_shared<bool>(pJson[pMasqueradingVector[4]].asBool());
    }
    if(!pMasqueradingVector[5].empty() && pJson.isMember(pMasqueradingVector[5]))
    {
        _parentId=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[5]].asInt64());
    }
    if(!pMasqueradingVector[6].empty() && pJson.isMember(pMasqueradingVector[6]))
    {
        _slug=std::make_shared<std::string>(pJson[pMasqueradingVector[6]].asString());
    }
    if(!pMasqueradingVector[7].empty() && pJson.isMember(pMasqueradingVector[7]))
    {
        auto timeStr = pJson[pMasqueradingVector[7]].asString();
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

WikiPages::WikiPages(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        _id=std::make_shared<int32_t>((int32_t)pJson["id"].asInt64());
    }
    if(pJson.isMember("wiki_id"))
    {
        _wikiId=std::make_shared<int32_t>((int32_t)pJson["wiki_id"].asInt64());
    }
    if(pJson.isMember("title"))
    {
        _title=std::make_shared<std::string>(pJson["title"].asString());
    }
    if(pJson.isMember("created_on"))
    {
        auto timeStr = pJson["created_on"].asString();
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
    if(pJson.isMember("protected"))
    {
        _protected=std::make_shared<bool>(pJson["protected"].asBool());
    }
    if(pJson.isMember("parent_id"))
    {
        _parentId=std::make_shared<int32_t>((int32_t)pJson["parent_id"].asInt64());
    }
    if(pJson.isMember("slug"))
    {
        _slug=std::make_shared<std::string>(pJson["slug"].asString());
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

void WikiPages::updateByMasqueradedJson(const Json::Value &pJson,
                                            const std::vector<std::string> &pMasqueradingVector) noexcept(false)
{
    if(pMasqueradingVector.size() != 8)
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
        _wikiId=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[1]].asInt64());
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        _dirtyFlag[2] = true;
        _title=std::make_shared<std::string>(pJson[pMasqueradingVector[2]].asString());
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
        _createdOn=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
    }
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        _dirtyFlag[4] = true;
        _protected=std::make_shared<bool>(pJson[pMasqueradingVector[4]].asBool());
    }
    if(!pMasqueradingVector[5].empty() && pJson.isMember(pMasqueradingVector[5]))
    {
        _dirtyFlag[5] = true;
        _parentId=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[5]].asInt64());
    }
    if(!pMasqueradingVector[6].empty() && pJson.isMember(pMasqueradingVector[6]))
    {
        _dirtyFlag[6] = true;
        _slug=std::make_shared<std::string>(pJson[pMasqueradingVector[6]].asString());
    }
    if(!pMasqueradingVector[7].empty() && pJson.isMember(pMasqueradingVector[7]))
    {
        _dirtyFlag[7] = true;
        auto timeStr = pJson[pMasqueradingVector[7]].asString();
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
                                                                    
void WikiPages::updateByJson(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        _id=std::make_shared<int32_t>((int32_t)pJson["id"].asInt64());
    }
    if(pJson.isMember("wiki_id"))
    {
        _dirtyFlag[1] = true;
        _wikiId=std::make_shared<int32_t>((int32_t)pJson["wiki_id"].asInt64());
    }
    if(pJson.isMember("title"))
    {
        _dirtyFlag[2] = true;
        _title=std::make_shared<std::string>(pJson["title"].asString());
    }
    if(pJson.isMember("created_on"))
    {
        _dirtyFlag[3] = true;
        auto timeStr = pJson["created_on"].asString();
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
    if(pJson.isMember("protected"))
    {
        _dirtyFlag[4] = true;
        _protected=std::make_shared<bool>(pJson["protected"].asBool());
    }
    if(pJson.isMember("parent_id"))
    {
        _dirtyFlag[5] = true;
        _parentId=std::make_shared<int32_t>((int32_t)pJson["parent_id"].asInt64());
    }
    if(pJson.isMember("slug"))
    {
        _dirtyFlag[6] = true;
        _slug=std::make_shared<std::string>(pJson["slug"].asString());
    }
    if(pJson.isMember("updated_at"))
    {
        _dirtyFlag[7] = true;
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

const int32_t &WikiPages::getValueOfId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_id)
        return *_id;
    return defaultValue;
}
const std::shared_ptr<int32_t> &WikiPages::getId() const noexcept
{
    return _id;
}
const typename WikiPages::PrimaryKeyType & WikiPages::getPrimaryKey() const
{
    assert(_id);
    return *_id;
}

const int32_t &WikiPages::getValueOfWikiId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_wikiId)
        return *_wikiId;
    return defaultValue;
}
const std::shared_ptr<int32_t> &WikiPages::getWikiId() const noexcept
{
    return _wikiId;
}
void WikiPages::setWikiId(const int32_t &pWikiId) noexcept
{
    _wikiId = std::make_shared<int32_t>(pWikiId);
    _dirtyFlag[1] = true;
}


const std::string &WikiPages::getValueOfTitle() const noexcept
{
    const static std::string defaultValue = std::string();
    if(_title)
        return *_title;
    return defaultValue;
}
const std::shared_ptr<std::string> &WikiPages::getTitle() const noexcept
{
    return _title;
}
void WikiPages::setTitle(const std::string &pTitle) noexcept
{
    _title = std::make_shared<std::string>(pTitle);
    _dirtyFlag[2] = true;
}
void WikiPages::setTitle(std::string &&pTitle) noexcept
{
    _title = std::make_shared<std::string>(std::move(pTitle));
    _dirtyFlag[2] = true;
}


const ::trantor::Date &WikiPages::getValueOfCreatedOn() const noexcept
{
    const static ::trantor::Date defaultValue = ::trantor::Date();
    if(_createdOn)
        return *_createdOn;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &WikiPages::getCreatedOn() const noexcept
{
    return _createdOn;
}
void WikiPages::setCreatedOn(const ::trantor::Date &pCreatedOn) noexcept
{
    _createdOn = std::make_shared<::trantor::Date>(pCreatedOn);
    _dirtyFlag[3] = true;
}


const bool &WikiPages::getValueOfProtected() const noexcept
{
    const static bool defaultValue = bool();
    if(_protected)
        return *_protected;
    return defaultValue;
}
const std::shared_ptr<bool> &WikiPages::getProtected() const noexcept
{
    return _protected;
}
void WikiPages::setProtected(const bool &pProtected) noexcept
{
    _protected = std::make_shared<bool>(pProtected);
    _dirtyFlag[4] = true;
}


const int32_t &WikiPages::getValueOfParentId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_parentId)
        return *_parentId;
    return defaultValue;
}
const std::shared_ptr<int32_t> &WikiPages::getParentId() const noexcept
{
    return _parentId;
}
void WikiPages::setParentId(const int32_t &pParentId) noexcept
{
    _parentId = std::make_shared<int32_t>(pParentId);
    _dirtyFlag[5] = true;
}


const std::string &WikiPages::getValueOfSlug() const noexcept
{
    const static std::string defaultValue = std::string();
    if(_slug)
        return *_slug;
    return defaultValue;
}
const std::shared_ptr<std::string> &WikiPages::getSlug() const noexcept
{
    return _slug;
}
void WikiPages::setSlug(const std::string &pSlug) noexcept
{
    _slug = std::make_shared<std::string>(pSlug);
    _dirtyFlag[6] = true;
}
void WikiPages::setSlug(std::string &&pSlug) noexcept
{
    _slug = std::make_shared<std::string>(std::move(pSlug));
    _dirtyFlag[6] = true;
}


const ::trantor::Date &WikiPages::getValueOfUpdatedAt() const noexcept
{
    const static ::trantor::Date defaultValue = ::trantor::Date();
    if(_updatedAt)
        return *_updatedAt;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &WikiPages::getUpdatedAt() const noexcept
{
    return _updatedAt;
}
void WikiPages::setUpdatedAt(const ::trantor::Date &pUpdatedAt) noexcept
{
    _updatedAt = std::make_shared<::trantor::Date>(pUpdatedAt);
    _dirtyFlag[7] = true;
}


void WikiPages::updateId(const uint64_t id)
{
}

const std::vector<std::string> &WikiPages::insertColumns() noexcept
{
    static const std::vector<std::string> _inCols={
        "wiki_id",
        "title",
        "created_on",
        "protected",
        "parent_id",
        "slug",
        "updated_at"
    };
    return _inCols;
}

void WikiPages::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(getWikiId())
    {
        binder << getValueOfWikiId();
    }
    else
    {
        binder << nullptr;
    }
    if(getTitle())
    {
        binder << getValueOfTitle();
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
    if(getProtected())
    {
        binder << getValueOfProtected();
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
    if(getSlug())
    {
        binder << getValueOfSlug();
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

const std::vector<std::string> WikiPages::updateColumns() const
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

void WikiPages::updateArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(_dirtyFlag[1])
    {
        if(getWikiId())
        {
            binder << getValueOfWikiId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[2])
    {
        if(getTitle())
        {
            binder << getValueOfTitle();
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
        if(getProtected())
        {
            binder << getValueOfProtected();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[5])
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
    if(_dirtyFlag[6])
    {
        if(getSlug())
        {
            binder << getValueOfSlug();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[7])
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
Json::Value WikiPages::toJson() const
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
    if(getWikiId())
    {
        ret["wiki_id"]=getValueOfWikiId();
    }
    else
    {
        ret["wiki_id"]=Json::Value();
    }
    if(getTitle())
    {
        ret["title"]=getValueOfTitle();
    }
    else
    {
        ret["title"]=Json::Value();
    }
    if(getCreatedOn())
    {
        ret["created_on"]=getCreatedOn()->toDbStringLocal();
    }
    else
    {
        ret["created_on"]=Json::Value();
    }
    if(getProtected())
    {
        ret["protected"]=getValueOfProtected();
    }
    else
    {
        ret["protected"]=Json::Value();
    }
    if(getParentId())
    {
        ret["parent_id"]=getValueOfParentId();
    }
    else
    {
        ret["parent_id"]=Json::Value();
    }
    if(getSlug())
    {
        ret["slug"]=getValueOfSlug();
    }
    else
    {
        ret["slug"]=Json::Value();
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

Json::Value WikiPages::toMasqueradedJson(
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
            if(getWikiId())
            {
                ret[pMasqueradingVector[1]]=getValueOfWikiId();
            }
            else
            {
                ret[pMasqueradingVector[1]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[2].empty())
        {
            if(getTitle())
            {
                ret[pMasqueradingVector[2]]=getValueOfTitle();
            }
            else
            {
                ret[pMasqueradingVector[2]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[3].empty())
        {
            if(getCreatedOn())
            {
                ret[pMasqueradingVector[3]]=getCreatedOn()->toDbStringLocal();
            }
            else
            {
                ret[pMasqueradingVector[3]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[4].empty())
        {
            if(getProtected())
            {
                ret[pMasqueradingVector[4]]=getValueOfProtected();
            }
            else
            {
                ret[pMasqueradingVector[4]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[5].empty())
        {
            if(getParentId())
            {
                ret[pMasqueradingVector[5]]=getValueOfParentId();
            }
            else
            {
                ret[pMasqueradingVector[5]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[6].empty())
        {
            if(getSlug())
            {
                ret[pMasqueradingVector[6]]=getValueOfSlug();
            }
            else
            {
                ret[pMasqueradingVector[6]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[7].empty())
        {
            if(getUpdatedAt())
            {
                ret[pMasqueradingVector[7]]=getUpdatedAt()->toDbStringLocal();
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
    if(getWikiId())
    {
        ret["wiki_id"]=getValueOfWikiId();
    }
    else
    {
        ret["wiki_id"]=Json::Value();
    }
    if(getTitle())
    {
        ret["title"]=getValueOfTitle();
    }
    else
    {
        ret["title"]=Json::Value();
    }
    if(getCreatedOn())
    {
        ret["created_on"]=getCreatedOn()->toDbStringLocal();
    }
    else
    {
        ret["created_on"]=Json::Value();
    }
    if(getProtected())
    {
        ret["protected"]=getValueOfProtected();
    }
    else
    {
        ret["protected"]=Json::Value();
    }
    if(getParentId())
    {
        ret["parent_id"]=getValueOfParentId();
    }
    else
    {
        ret["parent_id"]=Json::Value();
    }
    if(getSlug())
    {
        ret["slug"]=getValueOfSlug();
    }
    else
    {
        ret["slug"]=Json::Value();
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

bool WikiPages::validateJsonForCreation(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("id"))
    {
        if(!validJsonOfField(0, "id", pJson["id"], err, true))
            return false;
    }
    if(pJson.isMember("wiki_id"))
    {
        if(!validJsonOfField(1, "wiki_id", pJson["wiki_id"], err, true))
            return false;
    }
    else
    {
        err="The wiki_id column cannot be null";
        return false;
    }
    if(pJson.isMember("title"))
    {
        if(!validJsonOfField(2, "title", pJson["title"], err, true))
            return false;
    }
    else
    {
        err="The title column cannot be null";
        return false;
    }
    if(pJson.isMember("created_on"))
    {
        if(!validJsonOfField(3, "created_on", pJson["created_on"], err, true))
            return false;
    }
    else
    {
        err="The created_on column cannot be null";
        return false;
    }
    if(pJson.isMember("protected"))
    {
        if(!validJsonOfField(4, "protected", pJson["protected"], err, true))
            return false;
    }
    if(pJson.isMember("parent_id"))
    {
        if(!validJsonOfField(5, "parent_id", pJson["parent_id"], err, true))
            return false;
    }
    if(pJson.isMember("slug"))
    {
        if(!validJsonOfField(6, "slug", pJson["slug"], err, true))
            return false;
    }
    else
    {
        err="The slug column cannot be null";
        return false;
    }
    if(pJson.isMember("updated_at"))
    {
        if(!validJsonOfField(7, "updated_at", pJson["updated_at"], err, true))
            return false;
    }
    else
    {
        err="The updated_at column cannot be null";
        return false;
    }
    return true;
}
bool WikiPages::validateMasqueradedJsonForCreation(const Json::Value &pJson,
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
        else
        {
            err="The " + pMasqueradingVector[1] + " column cannot be null";
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
        else
        {
            err="The " + pMasqueradingVector[2] + " column cannot be null";
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
        else
        {
            err="The " + pMasqueradingVector[3] + " column cannot be null";
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
        else
        {
            err="The " + pMasqueradingVector[6] + " column cannot be null";
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
        else
        {
            err="The " + pMasqueradingVector[7] + " column cannot be null";
            return false;
        }
    }
    return true;
}
bool WikiPages::validateJsonForUpdate(const Json::Value &pJson, std::string &err)
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
    if(pJson.isMember("wiki_id"))
    {
        if(!validJsonOfField(1, "wiki_id", pJson["wiki_id"], err, false))
            return false;
    }
    if(pJson.isMember("title"))
    {
        if(!validJsonOfField(2, "title", pJson["title"], err, false))
            return false;
    }
    if(pJson.isMember("created_on"))
    {
        if(!validJsonOfField(3, "created_on", pJson["created_on"], err, false))
            return false;
    }
    if(pJson.isMember("protected"))
    {
        if(!validJsonOfField(4, "protected", pJson["protected"], err, false))
            return false;
    }
    if(pJson.isMember("parent_id"))
    {
        if(!validJsonOfField(5, "parent_id", pJson["parent_id"], err, false))
            return false;
    }
    if(pJson.isMember("slug"))
    {
        if(!validJsonOfField(6, "slug", pJson["slug"], err, false))
            return false;
    }
    if(pJson.isMember("updated_at"))
    {
        if(!validJsonOfField(7, "updated_at", pJson["updated_at"], err, false))
            return false;
    }
    return true;
}
bool WikiPages::validateMasqueradedJsonForUpdate(const Json::Value &pJson,
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
bool WikiPages::validJsonOfField(size_t index,
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
            if(!pJson.isString() && !pJson.isNull())
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
            if(!pJson.isString() && !pJson.isNull())
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
            if(!pJson.isBool())
            {
                err="Type error in the "+fieldName+"field";
                return false;
            }
            break;
        case 5:
            if(!pJson.isInt())
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
            if(!pJson.isString() && !pJson.isNull())
            {
                err="Type error in the "+fieldName+"field";
                return false;                
            }
            break;
        case 7:
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
