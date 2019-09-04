#ifndef BASESERVICEABS_H
#define BASESERVICEABS_H
#include "spdlogfix.h"

#include <drogon/WebSocketController.h>

#include <fmt/format.h>
#include "../jsonfns.h"
#include "core/sql/Table.h"
#include "../../wscontroller/context/madmincontext.h"

using namespace fmt::v5;
using namespace drogon;

class BaseServiceAbs
{
public:
  virtual ~BaseServiceAbs(){};
  virtual json handleEvent(json event, unsigned long next, json args);

protected:
  virtual void setupTable() = 0;
  json headerData(json event, json args);
  json allData(json event, json args);
  virtual  json ins(json event, json args);
  virtual  json upd(json event, json args);
  virtual json del(json event, json args);
  virtual json count(json event, json args);

  template<class... Args>
  json insBase(json event, json args, std::string column, std::string values,  Args... args_bind)
  {
    std::string strSql = "INSERT INTO " + t.m_table.toString() + " (" + column + ") values(" + values + ")";

    try {
      auto clientPtr = drogon::app().getDbClient("sce");
      clientPtr->execSqlSync( strSql, args_bind...);
      json ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
    } catch (const std::exception &e) {
      SPDLOG_TRACE(e.what());
      json ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
    }
  }

  template<class... Args>
  json updBase(json event, json args, std::string column, std::string values,  Args... args_bind)
  {
    setupTable();
    t.updateFilterBase(args[1]);
    std::string strSql = t.m_query.buildUpdateQuery( column, values, "");
    try {
      auto clientPtr = drogon::app().getDbClient("sce");
      clientPtr->execSqlSync(strSql, args_bind... );
      json ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
    } catch (const std::exception &e) {
      SPDLOG_TRACE(e.what());
      json ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
    }
  }
  Table t;
};

#endif // BASESERVICEABS_H
