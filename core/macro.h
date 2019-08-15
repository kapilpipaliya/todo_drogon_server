#ifndef MACRO_H
#define MACRO_H

#include <string>
#include <algorithm>    // std::find_if

#define getAllDataMacro(s, f)\
    fns.emplace("get_"  s  "_data", [](Json::Value in, const WebSocketConnectionPtr& wsConnPtr, Json::Value args) {\
        Table a;\
        f(a);\
        Json::Value jresult;\
        jresult[0]=event1;\
        jresult[1]=a.getAllData(in);\
        return jresult;\
    });
#define getAllHDataMacro(s, f)\
    fns.emplace("get_" s "_h_data", [](Json::Value in, const WebSocketConnectionPtr& wsConnPtr, Json::Value args) {\
        Table a;\
        f(a);\
        Json::Value jresult;\
        jresult[0]=event1;\
        jresult[1]=a.getJsonHeaderData();\
        return jresult;\
    });

#define getAllTheColumns(s, f)\
    getAllDataMacro(s, f)\
    getAllHDataMacro(s, f)

#define CRUD(s, s1)\
    getAllTheColumns(s, query_##s1)\
    fns.emplace("save_" s "_data", save_##s1);\
    fns.emplace("del_" s "_data", delete_##s1);

//----Save Del Macro----

#define saveDel(s)\
    [[nodiscard]] Json::Value save_##s(Json::Value in, const WebSocketConnectionPtr& wsConnPtr, Json::Value args);\
    [[nodiscard]] Json::Value delete_##s(Json::Value in, const WebSocketConnectionPtr& wsConnPtr, Json::Value args);\
//For Cpp:
#define delFn1(s, s1)\
Json::Value delete_##s(Json::Value in, const WebSocketConnectionPtr& wsConnPtr, Json::Value args)\
{\
    pqxx::work txn{DD};\
    try {\
        txn.exec_params("DELETE FROM " s1 " WHERE id = $1", args[0].asInt());\
        txn.commit();\
        Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;\
    } catch (const std::exception &e) {\
        txn.abort();\
        std::cerr << e.what() << std::endl;\
        Json::Value ret; ret[0] = simpleJsonSaveResult(event1, false, e.what()); return ret;\
    }\
}

#define ids2(s, array)\
std::string array = "{";\
for (auto i : (s)) { array += std::to_string(i[0].as<int>()) + ","; }\
if((s).size() > 0) array.pop_back();\
array += "}";

#define ins(t, c, v) "INSERT INTO " t " (" c ") VALUES (" v ")"
#define upd(t, c, v, w) "UPDATE " t " SET (" c ") = ROW (" v ")" w
#define sel(t, c, w) "SELECT " c " FROM " t " " w

#define dele(t, w) "DELETE FROM " t " " w

//Cpp:
#define purejoinTableSave(f, t, inKey, id1, id2)\
void save_product_##f(Json::Value &args, pqxx::work &txn, int idv1){\
    std::string strSqlPostCategories = "SELECT " id1 ", " id2 " FROM " t " where " id1 " = $1";\
    std::string strSqlPostCategorySimpleFind = "SELECT * FROM " t " WHERE " id1 " = $1 and " id2 " = $2";\
    std::string strSqlPostCategoryDel = "DELETE FROM " t " WHERE " id1 " = $1 and " id2 " = $2";\
    std::string strSqlPostCategoryInsert = "INSERT INTO " t " (" id1 ", " id2 ") VALUES ($1, $2);";\
    std::vector<int>inNewTones;\
    for (auto i : args[ inKey ]) {\
        if (!i.isNull()) inNewTones.push_back(i.asInt());\
    }\
    \
    pqxx::result all_ct = txn.exec_params(strSqlPostCategories, idv1);\
    /* For each saved tones, If saved tone not exist in new tones, delete it.*/\
    for (auto r : all_ct) {\
        std::vector<int>::iterator it = std::find(inNewTones.begin(), inNewTones.end(), r[1].as<int>());\
        if (it == inNewTones.end()) {/* Element not Found*/\
            txn.exec_params(strSqlPostCategoryDel, r[0].as<int>(), r[1].as<int>());\
        }\
    }\
    /* For each new tones, insert it if it not already exist.*/\
    for (auto x : inNewTones) {\
        pqxx::result y = txn.exec_params(strSqlPostCategorySimpleFind, idv1, x);\
        if(y.size() == 0) {\
            txn.exec_params(strSqlPostCategoryInsert, idv1, x);\
        }\
    }\
}

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

#define HANDLEEVENTD()\
Json::Value handleEvent(Json::Value event, Json::Value args);

#define HANDLEEVENT(T)\
Json::Value T::handleEvent(Json::Value event, Json::Value args)\
{\
    if(event[1].asString()  == "data"){\
        return allData(event, args);\
    } else if (event[1].asString()  == "header") {\
        return headerData(event, args);\
    } else if (event[1].asString()  == "save") {\
        return save(event, args);\
    } else if (event[1].asString()  == "del") {\
        return del(event, args);\
    } else {\
        return Json::nullValue;\
    }\
}
#define HEADERDATAD(T)\
Json::Value headerData(Json::Value event, Json::Value args);
#define ALLDATAD(T)\
Json::Value allData(Json::Value event, Json::Value args);
#define SAVED(T)\
Json::Value save(Json::Value event, Json::Value args);
#define DELETED(T)\
Json::Value del(Json::Value event, Json::Value args);


#define ALLDATA(T)\
Json::Value T::allData(Json::Value event, Json::Value args)\
{\
    setupTable();\
    Json::Value jresult;\
    jresult[0]=event;\
    jresult[1]=t.getAllData(args);\
    Json::Value ret;\
    ret[0] = jresult; return ret;\
}
#define HEADERDATA(T)\
Json::Value T::headerData(Json::Value event, Json::Value args)\
{\
    setupTable();\
    Json::Value jresult;\
    jresult[0]=event;\
    jresult[1]=t.getJsonHeaderData();\
    Json::Value ret;\
    ret[0] = jresult;  return ret;\
}

#define REGISTER(s, T)\
 else if (in[0][0].asString()==s){\
T p{wsConnPtr};\
auto r = p.handleEvent(in[0], in[1]);\
if(!r.isNull())\
    return r;\
}

#define delFn(T)\
Json::Value T::del(Json::Value event, Json::Value args)\
{\
    pqxx::work txn{DD};\
    try {\
        txn.exec_params("DELETE FROM " + t.m_table.toDisplayString() + " WHERE id = $1", args[0].asInt());\
        txn.commit();\
        Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;\
    } catch (const std::exception &e) {\
        txn.abort();\
        std::cerr << e.what() << std::endl;\
        Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;\
    }\
}

#endif // MACRO_H
