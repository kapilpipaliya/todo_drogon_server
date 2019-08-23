#ifndef BASESERVICE_H
#define BASESERVICE_H

#include "core/sql/Table.h"
#include <drogon/WebSocketController.h>
#include "../../EchoWebSocket.h"
#include <fmt/format.h>
#include "../jsonfns.h"
using namespace fmt::v5;

using namespace drogon;

#define ids2(s, array)\
std::string array = "{";\
for (auto i : (s)) { array += std::to_string(i["id"].as<int>()) + ","; }\
if((s).size() > 0) array.pop_back();\
array += "}";


class BaseService
{
public:
    BaseService();
    virtual ~BaseService();
    virtual json handleEvent(json event, int next, json args);

protected:
    virtual void setupTable() = 0;
    json headerData(json event, json args);
    json allData(json event, json args);
    virtual  json ins(json event, json args) = 0;
    virtual  json upd(json event, json args) = 0;
    virtual json del(json event, json args);

    template<class... Args>
    json insBase(json event, json args, std::string column, std::string values,  Args... args_bind)
    {
        std::string strSql = "INSERT INTO " + t.m_table.toString() + " (" + column + ") values(" + values + ")";

        try {
            clientPtr->execSqlSync( strSql, args_bind...);
            json ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
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
            clientPtr->execSqlSync(strSql, args_bind... );
            json ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            json ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
        }
    }
    Table t;

};

#endif // BASESERVICE_H
