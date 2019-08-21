#ifndef BASESERVICE_H
#define BASESERVICE_H

#include "core/sql/Table.h"
#include <drogon/WebSocketController.h>
#include "../../EchoWebSocket.h"
#include <fmt/format.h>
#include "../jsonfns.h"
using namespace fmt::v5;

using namespace drogon;

inline std::string ins_(std::string t, std::string c, std::string v) { return "INSERT INTO " + t +" (" + c + ") VALUES (" + v + ")"; }
inline std::string upd_(std::string t, std::string c, std::string v, std::string w) { return "UPDATE " + t + " SET (" + c + ") = ROW (" + v + ")" + w; }
inline std::string sel_(std::string t, std::string c, std::string w) { return "SELECT " + c + " FROM " + t + " " + w; }
inline std::string dele_(std::string t, std::string w) { return "DELETE FROM " + t + " " + w; }

#define ids2(s, array)\
std::string array = "{";\
for (auto i : (s)) { array += std::to_string(i["id"].as<int>()) + ","; }\
if((s).size() > 0) array.pop_back();\
array += "}";


class BaseService
{
public:
    BaseService(const WebSocketConnectionPtr& wsConnPtr);
    virtual ~BaseService();
    virtual Json::Value handleEvent(Json::Value event, int next, Json::Value args);

protected:
    virtual void setupTable() = 0;
    Json::Value headerData(Json::Value event, Json::Value args);
    Json::Value allData(Json::Value event, Json::Value args);
    virtual  Json::Value ins(Json::Value event, Json::Value args) = 0;
    virtual  Json::Value upd(Json::Value event, Json::Value args) = 0;
    virtual Json::Value del(Json::Value event, Json::Value args);

    template<class... Args>
    Json::Value insBase(Json::Value event, Json::Value args, std::string column, std::string values,  Args... args_bind)
    {
        std::string strSql = "INSERT INTO " + t.m_table.toString() + " (" + column + ") values(" + values + ")";

        try {
            clientPtr->execSqlSync( strSql, args_bind...);
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
        }
    }

    template<class... Args>
    Json::Value updBase(Json::Value event, Json::Value args, std::string column, std::string values,  Args... args_bind)
    {
        setupTable();
        t.updateFilterBase(args[1]);
        std::string strSql = t.m_query.buildUpdateQuery( column, values, "");
        try {
            clientPtr->execSqlSync(strSql, args_bind... );
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
        }
    }
    Table t;
    const WebSocketConnectionPtr& wsConnPtr;
};

#endif // BASESERVICE_H
