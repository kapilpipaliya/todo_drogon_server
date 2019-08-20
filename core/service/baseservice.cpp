#include "baseservice.h"
#include "../jsonfns.h"


BaseService::BaseService(const WebSocketConnectionPtr& wsConnPtr_): wsConnPtr(wsConnPtr_)
{

}

BaseService::~BaseService()
{

}

Json::Value BaseService::handleEvent(Json::Value event, int next, Json::Value args)
{
    auto event_cmp = event[next].asString();
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

Json::Value BaseService::headerData(Json::Value event, Json::Value args)
{
    setupTable();
    Json::Value jresult;
    jresult[0]=event;
    jresult[1]=t.getJsonHeaderData();
    Json::Value ret;
    ret[0] = jresult;  return ret;
}

Json::Value BaseService::allData(Json::Value event, Json::Value args)
{
    setupTable();
    Json::Value jresult;
    jresult[0]=event;
    jresult[1]=t.getAllData(args);
    Json::Value ret;
    ret[0] = jresult; return ret;
}

Json::Value BaseService::del(Json::Value event, Json::Value args)
{
    pqxx::work txn{DD};
    try {
        setupTable();
        t.updateFilterBase(args[0]);
        txn.exec_params(t.m_query.buildDeleteQuery());
        // affected rows should be returned too.
        //txn.exec_params("DELETE FROM " + t.m_table.toDisplayString() + " WHERE id = $1", args[0].asInt());
        txn.commit();
        Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
    } catch (const std::exception &e) {
        txn.abort();
        std::cerr << e.what() << std::endl;
        Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
    }
}

