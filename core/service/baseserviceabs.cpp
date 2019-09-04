#include "baseserviceabs.h"

#include "../sql/query.h"


json BaseServiceAbs::handleEvent(json event, unsigned long next, json args)
{
    auto event_cmp = event[next].get<std::string>();
    if(event_cmp == "data"){
        return allData(event, args);
    } else if (event_cmp == "header") {
        return headerData(event, args);
    } else if (event_cmp  == "ins") {
        return ins(event, args);
    } else if (event_cmp  == "upd") {
        return upd(event, args);
    } else if (event_cmp  == "del") {
        return del(event, args);
    } else {
        return Json::nullValue;
    }
}
json BaseServiceAbs::headerData(json event,[[maybe_unused]] json args)
{
    setupTable();
    json jresult;
    jresult[0]=event;
    jresult[1]=t.getJsonHeaderData();
    json ret;
    ret[0] = jresult;  return ret;
}
json BaseServiceAbs::allData(json event, json args)
{
    setupTable();
    json jresult;
    jresult[0]=event;
    jresult[1]=t.getAllData(args);
    json ret;
    ret[0] = jresult; return ret;
}

nlohmann::json BaseServiceAbs::ins(nlohmann::json event, nlohmann::json args)
{
    std::string strSql;
    try {
        setupTable();
        strSql = t.m_query.buildInsQuery(args);
        if(strSql.empty()){
             json ret; ret[0] = simpleJsonSaveResult(event, false, "UnValid Arguments"); return ret;
        }
    } catch (const std::exception &e) {
        SPDLOG_TRACE("error: {0}, sql: {1}", e.what(), strSql);
        throw;
    }
    try {
        auto clientPtr = drogon::app().getDbClient("sce");
        clientPtr->execSqlSync(strSql);
        json ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
    } catch (const std::exception &e) {
       SPDLOG_TRACE("error: {0}, sql: {1}", e.what(), strSql);
        json ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
    }
}

nlohmann::json BaseServiceAbs::upd(nlohmann::json event, nlohmann::json args)
{
    setupTable();
    t.updateFilterBase(args[1]);
    std::string strSql = t.m_query.buildUpdateQuery(args);
    if(strSql.empty()){
         json ret; ret[0] = simpleJsonSaveResult(event, false, "UnValid Arguments"); return ret;
    }
    try {
        auto clientPtr = drogon::app().getDbClient("sce");
        auto res = clientPtr->execSqlSync(strSql);
        if (res.size() > 1){
            SPDLOG_TRACE("error: Argus Must update one row");
            throw("not valid arguments");
        }
        json ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
    } catch (const std::exception &e) {
       SPDLOG_TRACE("error: {0}, sql: {1}", e.what(), strSql);
        json ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
    }
}

json BaseServiceAbs::del(json event, json args)
{
    try {
        auto clientPtr = drogon::app().getDbClient("sce");
        auto transPtr = clientPtr->newTransaction();
        setupTable();
        t.updateFilterBase(args[0]);
        auto res = transPtr->execSqlSync(t.m_query.buildDeleteQuery());
        if (res.size() > 1){
            throw("not valid arguments");
        }
        // affected rows should be returned too.
        //transPtr->execSqlSync("DELETE FROM " + t.m_table.toDisplayString() + " WHERE id = $1", args[0]);
        json ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
    } catch (const std::exception &e) {
       SPDLOG_TRACE(e.what());
        json ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
    }
}

nlohmann::json BaseServiceAbs::count(nlohmann::json event, nlohmann::json args)
{
    try {
        auto clientPtr = drogon::app().getDbClient("sce");
        auto transPtr = clientPtr->newTransaction();
        setupTable();
        t.updateFilterBase(args[0]);
        t.updateSortBase(args[1]);
        t.updatePaginationBase(args[2]);
        //SPDLOG_TRACE(t.m_query.buildCountQuery());
        auto res = transPtr->execSqlSync(t.m_query.buildCountQuery());
        // affected rows should be returned too.
        //transPtr->execSqlSync("DELETE FROM " + t.m_table.toDisplayString() + " WHERE id = $1", args[0]);
        json ret; ret[0] = json::array({event, res[0]["count"].as<long>()}); return  ret;
    } catch (const std::exception &e) {
       SPDLOG_TRACE(e.what());
        json ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
    }
}

