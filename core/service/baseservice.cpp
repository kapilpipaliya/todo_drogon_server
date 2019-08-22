#include "baseservice.h"
#include "../jsonfns.h"


BaseService::BaseService(const WebSocketConnectionPtr& wsConnPtr_): wsConnPtr(wsConnPtr_)
{  }
BaseService::~BaseService() {  }
json BaseService::handleEvent(json event, int next, json args)
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
json BaseService::headerData(json event, json args)
{
    setupTable();
    json jresult;
    jresult[0]=event;
    jresult[1]=t.getJsonHeaderData();
    json ret;
    ret[0] = jresult;  return ret;
}
json BaseService::allData(json event, json args)
{
    setupTable();
    json jresult;
    jresult[0]=event;
    jresult[1]=t.getAllData(args);
    json ret;
    ret[0] = jresult; return ret;
}

json BaseService::del(json event, json args)
{
    try {
        auto transPtr = clientPtr->newTransaction();
        setupTable();
        t.updateFilterBase(args[0]);
        transPtr->execSqlSync(t.m_query.buildDeleteQuery());
        // affected rows should be returned too.
        //transPtr->execSqlSync("DELETE FROM " + t.m_table.toDisplayString() + " WHERE id = $1", args[0]);
        json ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        json ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
    }
}

