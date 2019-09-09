#include "baseserviceabs.h"

#include <utility>

#include "../sql/query.h"
#include "dba.h"

nlohmann::json BaseServiceAbs::handleEvent(nlohmann::json event,
                                           unsigned long next,
                                           nlohmann::json args) {
  auto event_cmp = event[next].get<std::string>();
  if (event_cmp == "data") {
    return allData(event, args);
  }
  if (event_cmp == "header") {
    return headerData(event, args);
  } else if (event_cmp == "ins") {
    return ins(event, args);
  } else if (event_cmp == "upd") {
    return upd(event, args);
  } else if (event_cmp == "del") {
    return del(event, args);
  } else {
    nlohmann::json ret;
    return ret;
  }
}
nlohmann::json BaseServiceAbs::headerData(
    nlohmann::json event, [[maybe_unused]] const nlohmann::json &args) {
  setupTable();
  nlohmann::json jresult;
  jresult[0] = std::move(event);
  jresult[1] = query.getJsonHeaderData();
  nlohmann::json ret;
  ret[0] = jresult;
  return ret;
}
nlohmann::json BaseServiceAbs::allData(nlohmann::json event,
                                       nlohmann::json args) {
  setupTable();
  nlohmann::json jresult;
  jresult[0] = std::move(event);
  jresult[1] = query.getAllData(args);
  nlohmann::json ret;
  ret[0] = jresult;
  return ret;
}

nlohmann::json BaseServiceAbs::ins(nlohmann::json event, nlohmann::json args) {
  std::string strSql;
  try {
    setupTable();
    strSql = query.buildInsQuery(std::move(args));
    if (strSql.empty()) {
      nlohmann::json ret;
      ret[0] = simpleJsonSaveResult(event, false, "UnValid Arguments");
      return ret;
    }
  } catch (const std::exception &e) {
    SPDLOG_TRACE("error: {0}, sql: {1}", e.what(), strSql);
    throw;
  }
  try {
    auto clientPtr = drogon::app().getDbClient("sce");
    clientPtr->execSqlSync(strSql);
    nlohmann::json ret;
    ret[0] = simpleJsonSaveResult(event, true, "Done");
    return ret;
  } catch (const std::exception &e) {
    SPDLOG_TRACE("error: {0}, sql: {1}", e.what(), strSql);
    nlohmann::json ret;
    ret[0] = simpleJsonSaveResult(event, false, e.what());
    return ret;
  }
}

nlohmann::json BaseServiceAbs::upd(nlohmann::json event, nlohmann::json args) {
  setupTable();
  query.updateFilterBase(args[1]);
  std::string strSql = query.buildUpdateQuery(args);
  if (strSql.empty()) {
    nlohmann::json ret;
    ret[0] = simpleJsonSaveResult(event, false, "UnValid Arguments");
    return ret;
  }
  try {
    auto clientPtr = drogon::app().getDbClient("sce");
    auto res = clientPtr->execSqlSync(strSql);
    if (res.size() > 1) {
      SPDLOG_TRACE("error: Argus Must update one row");
      throw("not valid arguments");
    }
    nlohmann::json ret;
    ret[0] = simpleJsonSaveResult(event, true, "Done");
    return ret;
  } catch (const std::exception &e) {
    SPDLOG_TRACE("error: {0}, sql: {1}", e.what(), strSql);
    nlohmann::json ret;
    ret[0] = simpleJsonSaveResult(event, false, e.what());
    return ret;
  }
}

nlohmann::json BaseServiceAbs::del(nlohmann::json event, nlohmann::json args) {
  try {
    auto clientPtr = drogon::app().getDbClient("sce");
    auto transPtr = clientPtr->newTransaction();
    setupTable();
    query.updateFilterBase(args[0]);
    auto res = Dba::writeInTrans(transPtr, query.buildDeleteQuery());
    if (res.size() > 1) {
      throw("not valid arguments");
    }
    // affected rows should be returned too.
    // Dba::writeInTrans(transPtr, "DELETE FROM " +
    // query.m_table.toDisplayString()
    // + " WHERE id = $1", args[0]);
    nlohmann::json ret;
    ret[0] = simpleJsonSaveResult(event, true, "Done");
    return ret;
  } catch (const std::exception &e) {
    SPDLOG_TRACE(e.what());
    nlohmann::json ret;
    ret[0] = simpleJsonSaveResult(event, false, e.what());
    return ret;
  }
}

nlohmann::json BaseServiceAbs::count(nlohmann::json event,
                                     nlohmann::json args) {
  try {
    auto clientPtr = drogon::app().getDbClient("sce");
    auto transPtr = clientPtr->newTransaction();
    setupTable();
    query.updateFilterBase(args[0]);
    query.updateSortBase(args[1]);
    query.updatePaginationBase(args[2]);
    // SPDLOG_TRACE(query.buildCountQuery());
    auto res = Dba::writeInTrans(transPtr, query.buildCountQuery());
    // affected rows should be returned too.
    // Dba::writeInTrans(transPtr, "DELETE FROM " +
    // query.m_table.toDisplayString()
    // + " WHERE id = $1", args[0]);
    nlohmann::json ret;
    ret[0] = nlohmann::json::array({event, res[0]["count"].as<long>()});
    return ret;
  } catch (const std::exception &e) {
    SPDLOG_TRACE(e.what());
    nlohmann::json ret;
    ret[0] = simpleJsonSaveResult(event, false, e.what());
    return ret;
  }
}
