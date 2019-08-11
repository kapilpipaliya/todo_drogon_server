#ifndef MACRO_H
#define MACRO_H

#include <string>
#include <algorithm>    // std::find_if

#define getAllDataMacro(s, f)\
    fns.emplace("get_"  s  "_data", [](const std::string &event1, const std::string &event2, const std::string &no, const WebSocketConnectionPtr& wsConnPtr, Json::Value in) {\
        Table a;\
        f(a);\
        Json::Value jresult;\
        jresult[0]=event1;\
        jresult[1]=event2;\
        jresult[2]=no;\
        jresult[3]=a.getAllData(in);\
        return jresult;\
    });
#define getAllHDataMacro(s, f)\
    fns.emplace("get_" s "_h_data", [](const std::string &event1, const std::string &event2, const std::string &no, const WebSocketConnectionPtr& wsConnPtr, Json::Value in) {\
        Table a;\
        f(a);\
        Json::Value jresult;\
        jresult[0]=event1;\
        jresult[1]=event2;\
        jresult[2]=no;\
        jresult[3]=a.getJsonHeaderData();\
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
    Json::Value save_##s(const std::string &event1, const std::string &event2, const std::string &no, const WebSocketConnectionPtr& wsConnPtr, Json::Value in);\
    Json::Value delete_##s(const std::string &event1, const std::string &event2, const std::string &no, const WebSocketConnectionPtr& wsConnPtr, Json::Value in);\
//For Cpp:
#define delFn(s, s1)\
Json::Value delete_##s(const std::string &event1, const std::string &event2, const std::string &no, const WebSocketConnectionPtr& wsConnPtr, Json::Value in)\
{\
    pqxx::work txn{DD};\
    try {\
        txn.exec_params("DELETE FROM " s1 " WHERE id = $1", in[0].asInt());\
        txn.commit();\
        return simpleJsonSaveResult(event1, event2, no, wsConnPtr, true, "Done");\
    } catch (const std::exception &e) {\
        txn.abort();\
        std::cerr << e.what() << std::endl;\
        return simpleJsonSaveResult(event1,event2 , no, wsConnPtr, false, e.what());\
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
void save_product_##f(Json::Value &in, pqxx::work &txn, int idv1){\
    std::string strSqlPostCategories = "SELECT " id1 ", " id2 " FROM " t " where " id1 " = $1";\
    std::string strSqlPostCategorySimpleFind = "SELECT * FROM " t " WHERE " id1 " = $1 and " id2 " = $2";\
    std::string strSqlPostCategoryDel = "DELETE FROM " t " WHERE " id1 " = $1 and " id2 " = $2";\
    std::string strSqlPostCategoryInsert = "INSERT INTO " t " (" id1 ", " id2 ") VALUES ($1, $2);";\
    std::vector<int>inNewTones;\
    for (auto i : in[ inKey ]) {\
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

#define save_table(fn, t, c, i, u, w, ...) \
Json::Value save_##fn(const std::string &event1, const std::string &event2, const std::string &no, const WebSocketConnectionPtr &wsConnPtr, Json::Value in)\
{\
    if(in["id"].asInt()) {\
        std::string strSql = "update " t " set (" c ") = ROW(" u ") " w;\
\
        pqxx::work txn{DD};\
        try {\
            txn.exec_params(strSql, in["id"].asInt(), ##__VA_ARGS__ );\
            txn.commit();\
            return simpleJsonSaveResult(event1, event2, no, wsConnPtr, true, "Done");\
        } catch (const std::exception &e) {\
            txn.abort();\
            std::cerr << e.what() << std::endl;\
            return simpleJsonSaveResult(event1, event2, no, wsConnPtr, false, e.what());\
        }\
    } else {\
        std::string strSql = "INSERT INTO " t " (" c ") values(" i ")";\
\
        pqxx::work txn{DD};\
        try {\
            txn.exec_params( strSql, ##__VA_ARGS__ );\
            txn.commit();\
            return simpleJsonSaveResult(event1, event2, no, wsConnPtr, true, "Done");\
        } catch (const std::exception &e) {\
            txn.abort();\
            std::cerr << e.what() << std::endl;\
            return simpleJsonSaveResult(event1, event2, no, wsConnPtr, false, e.what());\
        }\
    }\
}

#define HANDLEEVENTD()\
Json::Value handleEvent(const std::string& event1, const std::string& event2, const std::string& no, Json::Value in);

#define HANDLEEVENT(T)\
Json::Value T::handleEvent(const std::string& event1, const std::string& event2, const std::string& no, Json::Value in)\
{\
    if(event2 == "data"){\
        return allData(event1, event2, no, in);\
    } else if (event2 == "header") {\
        return headerData(event1, event2, no, in);\
    } else {\
        return Json::nullValue;\
    }\
}
#define HEADERDATAD(T)\
Json::Value headerData(const std::string& event1, const std::string& event2, const std::string& no, Json::Value in);
#define ALLDATAD(T)\
Json::Value allData(const std::string& event1, const std::string& event2, const std::string& no, Json::Value in);
#define ALLDATA(T)\
Json::Value T::allData(const std::string& event1, const std::string& event2, const std::string& no, Json::Value in)\
{\
    setupTable();\
    Json::Value jresult;\
    jresult[0]=event1;\
    jresult[1]=event2;\
    jresult[2]=no;\
    jresult[3]=t.getAllData(in);\
    return jresult;\
}
#define HEADERDATA(T)\
Json::Value T::headerData(const std::string& event1, const std::string& event2, const std::string& no, Json::Value in)\
{\
    setupTable();\
    Json::Value jresult;\
    jresult[0]=event1;\
    jresult[1]=event2;\
    jresult[2]=no;\
    jresult[3]=t.getJsonHeaderData();\
    return jresult;\
}

#define REGISTER(s, T)\
 else if (valin[0].asString()==s){\
T p{wsConnPtr};wsConnPtr->send(p.handleEvent(event1, event2, no, valin[3]).toStyledString());\
}

#endif // MACRO_H
