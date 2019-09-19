/**
 *
 *  MeetingJournals.cc
 *  DO NOT EDIT. This file is generated by drogon_ctl
 *
 */

#include "MeetingJournals.h"
#include <drogon/utils/Utilities.h>
#include <string>

using namespace drogon;
using namespace drogon_model::openproject6;

const std::string MeetingJournals::Cols::_id = "id";
const std::string MeetingJournals::Cols::_journal_id = "journal_id";
const std::string MeetingJournals::Cols::_title = "title";
const std::string MeetingJournals::Cols::_author_id = "author_id";
const std::string MeetingJournals::Cols::_project_id = "project_id";
const std::string MeetingJournals::Cols::_location = "location";
const std::string MeetingJournals::Cols::_start_time = "start_time";
const std::string MeetingJournals::Cols::_duration = "duration";
const std::string MeetingJournals::primaryKeyName = "id";
const bool MeetingJournals::hasPrimaryKey = true;
const std::string MeetingJournals::tableName = "meeting_journals";

const std::vector<typename MeetingJournals::MetaData> MeetingJournals::_metaData={
{"id","int32_t","integer",4,1,1,1},
{"journal_id","int32_t","integer",4,0,0,1},
{"title","std::string","character varying",0,0,0,0},
{"author_id","int32_t","integer",4,0,0,0},
{"project_id","int32_t","integer",4,0,0,0},
{"location","std::string","character varying",0,0,0,0},
{"start_time","::trantor::Date","timestamp without time zone",0,0,0,0},
{"duration","double","double precision",8,0,0,0}
};
const std::string &MeetingJournals::getColumnName(size_t index) noexcept(false)
{
    assert(index < _metaData.size());
    return _metaData[index]._colName;
}
MeetingJournals::MeetingJournals(const Row &r, const ssize_t indexOffset) noexcept
{
    if(indexOffset < 0)
    {
        if(!r["id"].isNull())
        {
            _id=std::make_shared<int32_t>(r["id"].as<int32_t>());
        }
        if(!r["journal_id"].isNull())
        {
            _journalId=std::make_shared<int32_t>(r["journal_id"].as<int32_t>());
        }
        if(!r["title"].isNull())
        {
            _title=std::make_shared<std::string>(r["title"].as<std::string>());
        }
        if(!r["author_id"].isNull())
        {
            _authorId=std::make_shared<int32_t>(r["author_id"].as<int32_t>());
        }
        if(!r["project_id"].isNull())
        {
            _projectId=std::make_shared<int32_t>(r["project_id"].as<int32_t>());
        }
        if(!r["location"].isNull())
        {
            _location=std::make_shared<std::string>(r["location"].as<std::string>());
        }
        if(!r["start_time"].isNull())
        {
            auto timeStr = r["start_time"].as<std::string>();
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
            _startTime=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
        }
        if(!r["duration"].isNull())
        {
            _duration=std::make_shared<double>(r["duration"].as<double>());
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
            _journalId=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 2;
        if(!r[index].isNull())
        {
            _title=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 3;
        if(!r[index].isNull())
        {
            _authorId=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 4;
        if(!r[index].isNull())
        {
            _projectId=std::make_shared<int32_t>(r[index].as<int32_t>());
        }
        index = offset + 5;
        if(!r[index].isNull())
        {
            _location=std::make_shared<std::string>(r[index].as<std::string>());
        }
        index = offset + 6;
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
            _startTime=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
        }
        index = offset + 7;
        if(!r[index].isNull())
        {
            _duration=std::make_shared<double>(r[index].as<double>());
        }
    }

}

MeetingJournals::MeetingJournals(const Json::Value &pJson, const std::vector<std::string> &pMasqueradingVector) noexcept(false)
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
        _journalId=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[1]].asInt64());
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        _title=std::make_shared<std::string>(pJson[pMasqueradingVector[2]].asString());
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        _authorId=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[3]].asInt64());
    }
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        _projectId=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[4]].asInt64());
    }
    if(!pMasqueradingVector[5].empty() && pJson.isMember(pMasqueradingVector[5]))
    {
        _location=std::make_shared<std::string>(pJson[pMasqueradingVector[5]].asString());
    }
    if(!pMasqueradingVector[6].empty() && pJson.isMember(pMasqueradingVector[6]))
    {
        auto timeStr = pJson[pMasqueradingVector[6]].asString();
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
        _startTime=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
    }
    if(!pMasqueradingVector[7].empty() && pJson.isMember(pMasqueradingVector[7]))
    {
        _duration=std::make_shared<double>(pJson[pMasqueradingVector[7]].asDouble());
    }
}

MeetingJournals::MeetingJournals(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        _id=std::make_shared<int32_t>((int32_t)pJson["id"].asInt64());
    }
    if(pJson.isMember("journal_id"))
    {
        _journalId=std::make_shared<int32_t>((int32_t)pJson["journal_id"].asInt64());
    }
    if(pJson.isMember("title"))
    {
        _title=std::make_shared<std::string>(pJson["title"].asString());
    }
    if(pJson.isMember("author_id"))
    {
        _authorId=std::make_shared<int32_t>((int32_t)pJson["author_id"].asInt64());
    }
    if(pJson.isMember("project_id"))
    {
        _projectId=std::make_shared<int32_t>((int32_t)pJson["project_id"].asInt64());
    }
    if(pJson.isMember("location"))
    {
        _location=std::make_shared<std::string>(pJson["location"].asString());
    }
    if(pJson.isMember("start_time"))
    {
        auto timeStr = pJson["start_time"].asString();
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
        _startTime=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
    }
    if(pJson.isMember("duration"))
    {
        _duration=std::make_shared<double>(pJson["duration"].asDouble());
    }
}

void MeetingJournals::updateByMasqueradedJson(const Json::Value &pJson,
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
        _journalId=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[1]].asInt64());
    }
    if(!pMasqueradingVector[2].empty() && pJson.isMember(pMasqueradingVector[2]))
    {
        _dirtyFlag[2] = true;
        _title=std::make_shared<std::string>(pJson[pMasqueradingVector[2]].asString());
    }
    if(!pMasqueradingVector[3].empty() && pJson.isMember(pMasqueradingVector[3]))
    {
        _dirtyFlag[3] = true;
        _authorId=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[3]].asInt64());
    }
    if(!pMasqueradingVector[4].empty() && pJson.isMember(pMasqueradingVector[4]))
    {
        _dirtyFlag[4] = true;
        _projectId=std::make_shared<int32_t>((int32_t)pJson[pMasqueradingVector[4]].asInt64());
    }
    if(!pMasqueradingVector[5].empty() && pJson.isMember(pMasqueradingVector[5]))
    {
        _dirtyFlag[5] = true;
        _location=std::make_shared<std::string>(pJson[pMasqueradingVector[5]].asString());
    }
    if(!pMasqueradingVector[6].empty() && pJson.isMember(pMasqueradingVector[6]))
    {
        _dirtyFlag[6] = true;
        auto timeStr = pJson[pMasqueradingVector[6]].asString();
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
        _startTime=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
    }
    if(!pMasqueradingVector[7].empty() && pJson.isMember(pMasqueradingVector[7]))
    {
        _dirtyFlag[7] = true;
        _duration=std::make_shared<double>(pJson[pMasqueradingVector[7]].asDouble());
    }
}
                                                                    
void MeetingJournals::updateByJson(const Json::Value &pJson) noexcept(false)
{
    if(pJson.isMember("id"))
    {
        _id=std::make_shared<int32_t>((int32_t)pJson["id"].asInt64());
    }
    if(pJson.isMember("journal_id"))
    {
        _dirtyFlag[1] = true;
        _journalId=std::make_shared<int32_t>((int32_t)pJson["journal_id"].asInt64());
    }
    if(pJson.isMember("title"))
    {
        _dirtyFlag[2] = true;
        _title=std::make_shared<std::string>(pJson["title"].asString());
    }
    if(pJson.isMember("author_id"))
    {
        _dirtyFlag[3] = true;
        _authorId=std::make_shared<int32_t>((int32_t)pJson["author_id"].asInt64());
    }
    if(pJson.isMember("project_id"))
    {
        _dirtyFlag[4] = true;
        _projectId=std::make_shared<int32_t>((int32_t)pJson["project_id"].asInt64());
    }
    if(pJson.isMember("location"))
    {
        _dirtyFlag[5] = true;
        _location=std::make_shared<std::string>(pJson["location"].asString());
    }
    if(pJson.isMember("start_time"))
    {
        _dirtyFlag[6] = true;
        auto timeStr = pJson["start_time"].asString();
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
        _startTime=std::make_shared<::trantor::Date>(t*1000000+decimalNum);
    }
    if(pJson.isMember("duration"))
    {
        _dirtyFlag[7] = true;
        _duration=std::make_shared<double>(pJson["duration"].asDouble());
    }
}

const int32_t &MeetingJournals::getValueOfId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_id)
        return *_id;
    return defaultValue;
}
const std::shared_ptr<int32_t> &MeetingJournals::getId() const noexcept
{
    return _id;
}
const typename MeetingJournals::PrimaryKeyType & MeetingJournals::getPrimaryKey() const
{
    assert(_id);
    return *_id;
}

const int32_t &MeetingJournals::getValueOfJournalId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_journalId)
        return *_journalId;
    return defaultValue;
}
const std::shared_ptr<int32_t> &MeetingJournals::getJournalId() const noexcept
{
    return _journalId;
}
void MeetingJournals::setJournalId(const int32_t &pJournalId) noexcept
{
    _journalId = std::make_shared<int32_t>(pJournalId);
    _dirtyFlag[1] = true;
}


const std::string &MeetingJournals::getValueOfTitle() const noexcept
{
    const static std::string defaultValue = std::string();
    if(_title)
        return *_title;
    return defaultValue;
}
const std::shared_ptr<std::string> &MeetingJournals::getTitle() const noexcept
{
    return _title;
}
void MeetingJournals::setTitle(const std::string &pTitle) noexcept
{
    _title = std::make_shared<std::string>(pTitle);
    _dirtyFlag[2] = true;
}
void MeetingJournals::setTitle(std::string &&pTitle) noexcept
{
    _title = std::make_shared<std::string>(std::move(pTitle));
    _dirtyFlag[2] = true;
}


const int32_t &MeetingJournals::getValueOfAuthorId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_authorId)
        return *_authorId;
    return defaultValue;
}
const std::shared_ptr<int32_t> &MeetingJournals::getAuthorId() const noexcept
{
    return _authorId;
}
void MeetingJournals::setAuthorId(const int32_t &pAuthorId) noexcept
{
    _authorId = std::make_shared<int32_t>(pAuthorId);
    _dirtyFlag[3] = true;
}


const int32_t &MeetingJournals::getValueOfProjectId() const noexcept
{
    const static int32_t defaultValue = int32_t();
    if(_projectId)
        return *_projectId;
    return defaultValue;
}
const std::shared_ptr<int32_t> &MeetingJournals::getProjectId() const noexcept
{
    return _projectId;
}
void MeetingJournals::setProjectId(const int32_t &pProjectId) noexcept
{
    _projectId = std::make_shared<int32_t>(pProjectId);
    _dirtyFlag[4] = true;
}


const std::string &MeetingJournals::getValueOfLocation() const noexcept
{
    const static std::string defaultValue = std::string();
    if(_location)
        return *_location;
    return defaultValue;
}
const std::shared_ptr<std::string> &MeetingJournals::getLocation() const noexcept
{
    return _location;
}
void MeetingJournals::setLocation(const std::string &pLocation) noexcept
{
    _location = std::make_shared<std::string>(pLocation);
    _dirtyFlag[5] = true;
}
void MeetingJournals::setLocation(std::string &&pLocation) noexcept
{
    _location = std::make_shared<std::string>(std::move(pLocation));
    _dirtyFlag[5] = true;
}


const ::trantor::Date &MeetingJournals::getValueOfStartTime() const noexcept
{
    const static ::trantor::Date defaultValue = ::trantor::Date();
    if(_startTime)
        return *_startTime;
    return defaultValue;
}
const std::shared_ptr<::trantor::Date> &MeetingJournals::getStartTime() const noexcept
{
    return _startTime;
}
void MeetingJournals::setStartTime(const ::trantor::Date &pStartTime) noexcept
{
    _startTime = std::make_shared<::trantor::Date>(pStartTime);
    _dirtyFlag[6] = true;
}


const double &MeetingJournals::getValueOfDuration() const noexcept
{
    const static double defaultValue = double();
    if(_duration)
        return *_duration;
    return defaultValue;
}
const std::shared_ptr<double> &MeetingJournals::getDuration() const noexcept
{
    return _duration;
}
void MeetingJournals::setDuration(const double &pDuration) noexcept
{
    _duration = std::make_shared<double>(pDuration);
    _dirtyFlag[7] = true;
}


void MeetingJournals::updateId(const uint64_t id)
{
}

const std::vector<std::string> &MeetingJournals::insertColumns() noexcept
{
    static const std::vector<std::string> _inCols={
        "journal_id",
        "title",
        "author_id",
        "project_id",
        "location",
        "start_time",
        "duration"
    };
    return _inCols;
}

void MeetingJournals::outputArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(getJournalId())
    {
        binder << getValueOfJournalId();
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
    if(getAuthorId())
    {
        binder << getValueOfAuthorId();
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
    if(getLocation())
    {
        binder << getValueOfLocation();
    }
    else
    {
        binder << nullptr;
    }
    if(getStartTime())
    {
        binder << getValueOfStartTime();
    }
    else
    {
        binder << nullptr;
    }
    if(getDuration())
    {
        binder << getValueOfDuration();
    }
    else
    {
        binder << nullptr;
    }
}

const std::vector<std::string> MeetingJournals::updateColumns() const
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

void MeetingJournals::updateArgs(drogon::orm::internal::SqlBinder &binder) const
{
    if(_dirtyFlag[1])
    {
        if(getJournalId())
        {
            binder << getValueOfJournalId();
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
        if(getAuthorId())
        {
            binder << getValueOfAuthorId();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[4])
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
    if(_dirtyFlag[5])
    {
        if(getLocation())
        {
            binder << getValueOfLocation();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[6])
    {
        if(getStartTime())
        {
            binder << getValueOfStartTime();
        }
        else
        {
            binder << nullptr;
        }
    }
    if(_dirtyFlag[7])
    {
        if(getDuration())
        {
            binder << getValueOfDuration();
        }
        else
        {
            binder << nullptr;
        }
    }
}
Json::Value MeetingJournals::toJson() const
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
    if(getJournalId())
    {
        ret["journal_id"]=getValueOfJournalId();
    }
    else
    {
        ret["journal_id"]=Json::Value();
    }
    if(getTitle())
    {
        ret["title"]=getValueOfTitle();
    }
    else
    {
        ret["title"]=Json::Value();
    }
    if(getAuthorId())
    {
        ret["author_id"]=getValueOfAuthorId();
    }
    else
    {
        ret["author_id"]=Json::Value();
    }
    if(getProjectId())
    {
        ret["project_id"]=getValueOfProjectId();
    }
    else
    {
        ret["project_id"]=Json::Value();
    }
    if(getLocation())
    {
        ret["location"]=getValueOfLocation();
    }
    else
    {
        ret["location"]=Json::Value();
    }
    if(getStartTime())
    {
        ret["start_time"]=getStartTime()->toDbStringLocal();
    }
    else
    {
        ret["start_time"]=Json::Value();
    }
    if(getDuration())
    {
        ret["duration"]=getValueOfDuration();
    }
    else
    {
        ret["duration"]=Json::Value();
    }
    return ret;
}

Json::Value MeetingJournals::toMasqueradedJson(
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
            if(getJournalId())
            {
                ret[pMasqueradingVector[1]]=getValueOfJournalId();
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
            if(getAuthorId())
            {
                ret[pMasqueradingVector[3]]=getValueOfAuthorId();
            }
            else
            {
                ret[pMasqueradingVector[3]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[4].empty())
        {
            if(getProjectId())
            {
                ret[pMasqueradingVector[4]]=getValueOfProjectId();
            }
            else
            {
                ret[pMasqueradingVector[4]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[5].empty())
        {
            if(getLocation())
            {
                ret[pMasqueradingVector[5]]=getValueOfLocation();
            }
            else
            {
                ret[pMasqueradingVector[5]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[6].empty())
        {
            if(getStartTime())
            {
                ret[pMasqueradingVector[6]]=getStartTime()->toDbStringLocal();
            }
            else
            {
                ret[pMasqueradingVector[6]]=Json::Value();
            }
        }
        if(!pMasqueradingVector[7].empty())
        {
            if(getDuration())
            {
                ret[pMasqueradingVector[7]]=getValueOfDuration();
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
    if(getJournalId())
    {
        ret["journal_id"]=getValueOfJournalId();
    }
    else
    {
        ret["journal_id"]=Json::Value();
    }
    if(getTitle())
    {
        ret["title"]=getValueOfTitle();
    }
    else
    {
        ret["title"]=Json::Value();
    }
    if(getAuthorId())
    {
        ret["author_id"]=getValueOfAuthorId();
    }
    else
    {
        ret["author_id"]=Json::Value();
    }
    if(getProjectId())
    {
        ret["project_id"]=getValueOfProjectId();
    }
    else
    {
        ret["project_id"]=Json::Value();
    }
    if(getLocation())
    {
        ret["location"]=getValueOfLocation();
    }
    else
    {
        ret["location"]=Json::Value();
    }
    if(getStartTime())
    {
        ret["start_time"]=getStartTime()->toDbStringLocal();
    }
    else
    {
        ret["start_time"]=Json::Value();
    }
    if(getDuration())
    {
        ret["duration"]=getValueOfDuration();
    }
    else
    {
        ret["duration"]=Json::Value();
    }
    return ret;
}

bool MeetingJournals::validateJsonForCreation(const Json::Value &pJson, std::string &err)
{
    if(pJson.isMember("id"))
    {
        if(!validJsonOfField(0, "id", pJson["id"], err, true))
            return false;
    }
    if(pJson.isMember("journal_id"))
    {
        if(!validJsonOfField(1, "journal_id", pJson["journal_id"], err, true))
            return false;
    }
    else
    {
        err="The journal_id column cannot be null";
        return false;
    }
    if(pJson.isMember("title"))
    {
        if(!validJsonOfField(2, "title", pJson["title"], err, true))
            return false;
    }
    if(pJson.isMember("author_id"))
    {
        if(!validJsonOfField(3, "author_id", pJson["author_id"], err, true))
            return false;
    }
    if(pJson.isMember("project_id"))
    {
        if(!validJsonOfField(4, "project_id", pJson["project_id"], err, true))
            return false;
    }
    if(pJson.isMember("location"))
    {
        if(!validJsonOfField(5, "location", pJson["location"], err, true))
            return false;
    }
    if(pJson.isMember("start_time"))
    {
        if(!validJsonOfField(6, "start_time", pJson["start_time"], err, true))
            return false;
    }
    if(pJson.isMember("duration"))
    {
        if(!validJsonOfField(7, "duration", pJson["duration"], err, true))
            return false;
    }
    return true;
}
bool MeetingJournals::validateMasqueradedJsonForCreation(const Json::Value &pJson,
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
bool MeetingJournals::validateJsonForUpdate(const Json::Value &pJson, std::string &err)
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
    if(pJson.isMember("journal_id"))
    {
        if(!validJsonOfField(1, "journal_id", pJson["journal_id"], err, false))
            return false;
    }
    if(pJson.isMember("title"))
    {
        if(!validJsonOfField(2, "title", pJson["title"], err, false))
            return false;
    }
    if(pJson.isMember("author_id"))
    {
        if(!validJsonOfField(3, "author_id", pJson["author_id"], err, false))
            return false;
    }
    if(pJson.isMember("project_id"))
    {
        if(!validJsonOfField(4, "project_id", pJson["project_id"], err, false))
            return false;
    }
    if(pJson.isMember("location"))
    {
        if(!validJsonOfField(5, "location", pJson["location"], err, false))
            return false;
    }
    if(pJson.isMember("start_time"))
    {
        if(!validJsonOfField(6, "start_time", pJson["start_time"], err, false))
            return false;
    }
    if(pJson.isMember("duration"))
    {
        if(!validJsonOfField(7, "duration", pJson["duration"], err, false))
            return false;
    }
    return true;
}
bool MeetingJournals::validateMasqueradedJsonForUpdate(const Json::Value &pJson,
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
bool MeetingJournals::validJsonOfField(size_t index,
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
            if(!pJson.isString() && !pJson.isNull())
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
            break;
        case 6:
            if(!pJson.isString() && !pJson.isNull())
            {
                err="Type error in the "+fieldName+"field";
                return false;                
            }
            break;
        case 7:
            if(!pJson.isNumeric())
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
