#ifndef BASESERVICE_H
#define BASESERVICE_H

#include "core/sql/Table.h"
#include <drogon/WebSocketController.h>
#include <pqxx/pqxx>
#include "core/connection/pdb.h"
#include "../../EchoWebSocket.h"
using namespace drogon;

inline std::string ins_(std::string t, std::string c, std::string v) { return "INSERT INTO " + t +" (" + c + ") VALUES (" + v + ")"; }
inline std::string upd_(std::string t, std::string c, std::string v, std::string w) { return "UPDATE " + t + " SET (" + c + ") = ROW (" + v + ")" + w; }
inline std::string sel_(std::string t, std::string c, std::string w) { return "SELECT " + c + " FROM " + t + " " + w; }
inline std::string dele_(std::string t, std::string w) { return "DELETE FROM " + t + " " + w; }

#define ids2(s, array)\
std::string array = "{";\
for (auto i : (s)) { array += std::to_string(i[0].as<int>()) + ","; }\
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

    Table t;
    const WebSocketConnectionPtr& wsConnPtr;
};

#define save_table(T, t, c, i, u, w, ...) \
Json::Value T::ins( Json::Value event, Json::Value args)\
{\
    if(args["id"].asInt()) {\
        std::string strSql = "update " t " set (" c ") = ROW(" u ") " w;\
\
        try {\
            clientPtr->execSqlSync(strSql, args["id"].asInt64(), ##__VA_ARGS__ );\
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;\
        } catch (const std::exception &e) {\
            std::cerr << e.what() << std::endl;\
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;\
        }\
    }\
}\
Json::Value T::upd( Json::Value event, Json::Value args)\
 {\
        std::string strSql = "INSERT INTO " t " (" c ") values(" i ")";\
\
        try {\
            clientPtr->execSqlSync( strSql, ##__VA_ARGS__ );\
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;\
        } catch (const std::exception &e) {\
            std::cerr << e.what() << std::endl;\
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;\
        }\
}

#endif // BASESERVICE_H
