#ifndef BASESERVICE_H
#define BASESERVICE_H

#include "core/Table.h"
#include <drogon/WebSocketController.h>
using namespace drogon;

inline std::string ins(std::string t, std::string c, std::string v) { return "INSERT INTO " + t +" (" + c + ") VALUES (" + v + ")"; }
inline std::string upd(std::string t, std::string c, std::string v, std::string w) { return "UPDATE " + t + " SET (" + c + ") = ROW (" + v + ")" + w; }
inline std::string sel(std::string t, std::string c, std::string w) { return "SELECT " + c + " FROM " + t + " " + w; }
inline std::string dele(std::string t, std::string w) { return "DELETE FROM " + t + " " + w; }

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
    virtual Json::Value handleEvent(Json::Value event, Json::Value args);

protected:
    virtual void setupTable() = 0;
    Json::Value headerData(Json::Value event, Json::Value args);
    Json::Value allData(Json::Value event, Json::Value args);
   virtual  Json::Value save(Json::Value event, Json::Value args) = 0;
   virtual Json::Value del(Json::Value event, Json::Value args);

    Table t;
    const WebSocketConnectionPtr& wsConnPtr;
};

#define save_table(T, t, c, i, u, w, ...) \
Json::Value T::save( Json::Value event, Json::Value args)\
{\
    if(args["id"].asInt()) {\
        std::string strSql = "update " t " set (" c ") = ROW(" u ") " w;\
\
        pqxx::work txn{DD};\
        try {\
            txn.exec_params(strSql, args["id"].asInt(), ##__VA_ARGS__ );\
            txn.commit();\
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;\
        } catch (const std::exception &e) {\
            txn.abort();\
            std::cerr << e.what() << std::endl;\
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;\
        }\
    } else {\
        std::string strSql = "INSERT INTO " t " (" c ") values(" i ")";\
\
        pqxx::work txn{DD};\
        try {\
            txn.exec_params( strSql, ##__VA_ARGS__ );\
            txn.commit();\
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;\
        } catch (const std::exception &e) {\
            txn.abort();\
            std::cerr << e.what() << std::endl;\
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;\
        }\
    }\
}

#endif // BASESERVICE_H
