#ifndef BASESERVICEABS_H
#define BASESERVICEABS_H
#include "spdlogfix.h"

#include <drogon/WebSocketController.h>

#include <fmt/format.h>

#include <utility>
#include "../../wscontroller/context/madmincontext.h"
#include "../jsonfns.h"
#include "core/sql/query.h"

class BaseServiceAbs {
 public:
  BaseServiceAbs() = default;
  virtual ~BaseServiceAbs() = default;
  virtual nlohmann::json handleEvent(nlohmann::json event, unsigned long next,
                                     nlohmann::json args);

 protected:
  virtual void setupTable() = 0;
  nlohmann::json headerData(nlohmann::json event, const nlohmann::json& args);
  nlohmann::json allData(nlohmann::json event, nlohmann::json args);
  virtual nlohmann::json ins(nlohmann::json event, nlohmann::json args);
  virtual nlohmann::json upd(nlohmann::json event, nlohmann::json args);
  virtual nlohmann::json del(nlohmann::json event, nlohmann::json args);
  virtual nlohmann::json count(nlohmann::json event, nlohmann::json args);
  sqlb::Query& getQuery() { return query; }
  // const sqlb::Query& getQuery() { return query; }
  // void setQuery(const sqlb::Query& query_) { query = query_; }

  template <class... Args>
  nlohmann::json insBase(const nlohmann::json& event,
                         const nlohmann::json& /*args*/,
                         const std::string& column, const std::string& values,
                         Args... args_bind) {
    std::string strSql = "INSERT INTO " + query.table().toString() + " (" +
                         column + ") values(" + values + ")";

    try {
      auto clientPtr = drogon::app().getDbClient("sce");
      clientPtr->execSqlSync(strSql, args_bind...);
      nlohmann::json ret;
      ret[0] = simpleJsonSaveResult(event, true, "Done");
      return ret;
    } catch (const std::exception& e) {
      SPDLOG_TRACE(e.what());
      nlohmann::json ret;
      ret[0] = simpleJsonSaveResult(event, false, e.what());
      return ret;
    }
  }

  template <class... Args>
  nlohmann::json updBase(const nlohmann::json& event, nlohmann::json args,
                         const std::string& column, const std::string& values,
                         Args... args_bind) {
    setupTable();
    query.updateFilterBase(args[1]);
    std::string strSql = query.buildUpdateQuery(column, values, "");
    try {
      auto clientPtr = drogon::app().getDbClient("sce");
      clientPtr->execSqlSync(strSql, args_bind...);
      nlohmann::json ret;
      ret[0] = simpleJsonSaveResult(event, true, "Done");
      return ret;
    } catch (const std::exception& e) {
      SPDLOG_TRACE(e.what());
      nlohmann::json ret;
      ret[0] = simpleJsonSaveResult(event, false, e.what());
      return ret;
    }
  }

 private:
  sqlb::Query query;
};

#endif  // BASESERVICEABS_H
