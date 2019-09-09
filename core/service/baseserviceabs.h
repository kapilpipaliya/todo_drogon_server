#ifndef BASESERVICEABS_H
#define BASESERVICEABS_H
#include "spdlogfix.h"

#include <drogon/WebSocketController.h>

#include <fmt/format.h>

#include <utility>
#include "../../wscontroller/context/madmincontext.h"
#include "../jsonfns.h"
#include "core/sql/query.h"

using namespace drogon;

class BaseServiceAbs {
 public:
  virtual ~BaseServiceAbs() = default;
  virtual json handleEvent(json event, unsigned long next, json args);

 protected:
  virtual void setupTable() = 0;
  json headerData(json event, const json& args);
  json allData(json event, json args);
  virtual json ins(json event, json args);
  virtual json upd(json event, json args);
  virtual json del(json event, json args);
  virtual json count(json event, json args);
  sqlb::Query& getQuery() { return query; }

  template <class... Args>
  json insBase(const json& event, const json& /*args*/,
               const std::string& column, const std::string& values,
               Args... args_bind) {
    std::string strSql = "INSERT INTO " + query.table().toString() + " (" +
                         column + ") values(" + values + ")";

    try {
      auto clientPtr = drogon::app().getDbClient("sce");
      clientPtr->execSqlSync(strSql, args_bind...);
      json ret;
      ret[0] = simpleJsonSaveResult(event, true, "Done");
      return ret;
    } catch (const std::exception& e) {
      SPDLOG_TRACE(e.what());
      json ret;
      ret[0] = simpleJsonSaveResult(event, false, e.what());
      return ret;
    }
  }

  template <class... Args>
  json updBase(const json& event, json args, std::string column,
               std::string values, Args... args_bind) {
    setupTable();
    query.updateFilterBase(args[1]);
    std::string strSql =
        query.buildUpdateQuery(std::move(column), std::move(values), "");
    try {
      auto clientPtr = drogon::app().getDbClient("sce");
      clientPtr->execSqlSync(strSql, args_bind...);
      json ret;
      ret[0] = simpleJsonSaveResult(event, true, "Done");
      return ret;
    } catch (const std::exception& e) {
      SPDLOG_TRACE(e.what());
      json ret;
      ret[0] = simpleJsonSaveResult(event, false, e.what());
      return ret;
    }
  }

 private:
  sqlb::Query query;
};

#endif  // BASESERVICEABS_H
