#include "wsfunctions.h"
#include "core/tables/macro.h"
#include "core/tables/jsonfns.h"
#include "core/connection/pdb.h"
#include <algorithm>
#include <cctype>
#include <locale>
using namespace std::literals;

Json::Value admin_login(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
    auto sql = "select e.id from entity.entity e left join entity.entity_user as u on u.entity_id = e.id where e.email = $1 and u.password = $2";
    pqxx::work txn{DD};
    try {
        auto r = txn.exec_params(sql, in["email"].asString(), in["pass"].asString());

        if (r.size() == 1) {

            Json::Value j;
            j["value"] = r[0][0].as<int>();
            auto sqlSession = "INSERT INTO user1.session (key, value) VALUES ($1, $2) returning id";
            // To serialize the Json::Value into a Json document, you should use a Json writer, or Json::Value::toStyledString().
            LOG_INFO << j.toStyledString();
            auto rs = txn.exec_params(sqlSession, "admin", j.toStyledString());
            wsConnPtr->send(simpleJsonSaveResult(event_name, wsConnPtr, true, "Done").toStyledString());

            // ask to save cookie
            Json::Value value;
            value[0] = "set_cookie";
            Json::Value cookie_value;
            //auto s = get_serial_no();
            cookie_value["admin"] = rs[0][0].as<int>();
            value[1] = cookie_value;

            setAdminContext(wsConnPtr, rs[0][0].as<int>());
            wsConnPtr->send(value.toStyledString());
            txn.commit();
            return Json::Value(Json::nullValue);
        } else {
            txn.commit();
            return simpleJsonSaveResult(event_name, wsConnPtr, false, "Error");
        }

    } catch (const std::exception &e) {
        txn.abort();
        std::cerr << e.what() << std::endl;
        return simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }
}

Json::Value admin_logout(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
    deleteAdminSession(wsConnPtr);
    return simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
}

Json::Value is_admin_auth(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
    Json::Value value;
    value[0] = event_name;
    auto c = getAdminContext(wsConnPtr);
    if (c != 0) { value[1] = true; } else { value[1] = false; }
    //wsConnPtr->send(value.toStyledString());
    return value;
}
Json::Value user_register(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in)
{
    std::string strSql = "INSERT INTO entity.entity ( entity_type_id, no, legal_name, slug, email) values($1, $2, $3, $4, $5) returning id";
    pqxx::work txn{DD};
    try {


        std::string data = in["legal_name"].asString();
        std::transform(data.begin(), data.end(), data.begin(),
                       [](unsigned char c){ return std::tolower(c); });
        std::transform(data.begin(), data.end(), data.begin(),
                       [](unsigned char c){ return std::tolower(c); });
        std::transform(data.begin(), data.end(), data.begin(), [](char ch) {
            return ch == ' ' ? '_' : ch;
        });

        auto x = txn.exec_params(strSql, 6, "", in["legal_name"].asString(), data, in["email"].asString() );
        auto entity_id = x[0][0].as<int>();
        std::string strSqlUser = "INSERT INTO entity.entity_user (entity_id, username, password, password_hash) VALUES ($1, $2, $3, $4)";
        txn.exec_params(strSqlUser, entity_id, in["email"].asString(), in["pass"].asString(), in["pass"].asString());

        txn.commit();
        //simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
        return user_login(event_name, wsConnPtr, in);
    } catch (const std::exception &e) {
        txn.abort();
        std::cerr << e.what() << std::endl;
        return simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }
}

Json::Value user_login(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
    auto sql = "select e.id from entity.entity e left join entity.entity_user as u on u.entity_id = e.id where e.email = $1 and u.password = $2";
    pqxx::work txn{DD};
    try {
        auto r = txn.exec_params(sql, in["email"].asString(), in["pass"].asString());

        if (r.size() == 1) {

            Json::Value j;
            j["value"] = r[0][0].as<int>();
            auto sqlSession = "INSERT INTO user1.session (key, value) VALUES ($1, $2) returning id";
            // To serialize the Json::Value into a Json document, you should use a Json writer, or Json::Value::toStyledString().
            LOG_INFO << j.toStyledString();
            auto rs = txn.exec_params(sqlSession, "user", j.toStyledString());
            wsConnPtr->send(simpleJsonSaveResult(event_name, wsConnPtr, true, "Done").toStyledString());

            // ask to save cookie
            Json::Value value;
            value[0] = "set_cookie";
            Json::Value cookie_value;
            //auto s = get_serial_no();
            cookie_value["user"] = rs[0][0].as<int>();
            value[1] = cookie_value;
            wsConnPtr->send(value.toStyledString());

            setUserContext(wsConnPtr, rs[0][0].as<int>());
            txn.commit();
            return Json::Value(Json::nullValue);

        } else {
            txn.commit();
            return simpleJsonSaveResult(event_name, wsConnPtr, false, "Error");
        }

    } catch (const std::exception &e) {
        txn.abort();
        std::cerr << e.what() << std::endl;
        return simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }
}
Json::Value user_id(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
    auto c = getUserContext(wsConnPtr);
    if (c != 0) {
        auto sqlSession = "SELECT key, value FROM user1.session where id = $1";
        pqxx::work txn{DD};
        try {
            auto r = txn.exec_params(sqlSession, c);
            txn.commit();
            // send id
            //simpleJsonSaveResult(event_name, wsConnPtr, true, r[0][1].c_str());
            Json::Value jresult;
            jresult[0]=event_name;

            Json::Value root;
            std::stringstream txt;
            txt << r[0][1].c_str();
            Json::CharReaderBuilder rbuilder;
            rbuilder["collectComments"] = false;
            std::string errs;
            bool ok = Json::parseFromStream(rbuilder, txt, &root, &errs);

            jresult[1]=root["value"].asInt();
            //wsConnPtr->send(jresult.toStyledString());
            return jresult;
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            //simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
            Json::Value jresult;
            jresult[0]=event_name;
            jresult[1]=0;
            //wsConnPtr->send(jresult.toStyledString());
            return jresult;
        }
    }
}

Json::Value user_logout(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
    deleteuserSession(wsConnPtr);
    return simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
}

Json::Value is_user_auth(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
    Json::Value value;
    value[0] = event_name;
    auto c = getUserContext(wsConnPtr);
    if (c != 0) { value[1] = true; } else { value[1] = false; }
    //wsConnPtr->send(value.toStyledString());
    return value;
}
Json::Value user_checkout(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
    auto c = getUserContext(wsConnPtr);
    printJson(in);
    if (c != 0) {
        auto sqlSession = "SELECT key, value FROM user1.session where id = $1";
        pqxx::work txn{DD};
        try {
            auto r = txn.exec_params(sqlSession, c);
            txn.commit();
            // send id
            Json::Value jresult;
            jresult[0]=event_name;

            Json::Value root;
            std::stringstream txt;
            txt << r[0][1].c_str();
            Json::CharReaderBuilder rbuilder;
            rbuilder["collectComments"] = false;
            std::string errs;
            bool ok = Json::parseFromStream(rbuilder, txt, &root, &errs);
            auto user_entity_id = root["value"].asInt();


            jresult[1]=root["value"].asInt();
            //wsConnPtr->send(jresult.toStyledString());
            return jresult;
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            //simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
            Json::Value jresult;
            jresult[0]=event_name;
            jresult[1]=0;
            //wsConnPtr->send(jresult.toStyledString());
            return jresult;
        }
    }
}
//--------------------------
int generateContext(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr, std::string account_type) {
    auto c = req->getCookie(account_type);
    if (c.empty()) {
        // ask to login
        Json::Value lresult;
        lresult[0] = "require_login";
        wsConnPtr->send(lresult.toStyledString());
        return 0;
    } else {
        auto sqlSession = "SELECT * FROM user1.session where id = $1";
        pqxx::work txn{DD};
        try {
            auto r = txn.exec_params(sqlSession, c);
            if (r.size() != 0) {
                auto i = r[0][0].as<int>();
                return i;
            } else {
                return 0;
            }
            txn.commit();
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            return 0;
        }
    }
}

void deleteAdminSession(const WebSocketConnectionPtr &wsConnPtr) {
    auto c = getAdminContext(wsConnPtr);
    if (c != 0) {
        auto sqlSession = "DELETE FROM user1.session where id = $1";
        pqxx::work txn{DD};
        try {
            auto r = txn.exec_params(sqlSession, c);
            txn.commit();
            setAdminContext(wsConnPtr, 0);
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
        }
    }
}
void deleteuserSession(const WebSocketConnectionPtr &wsConnPtr) {
    auto c = getUserContext(wsConnPtr);
    if (c != 0) {
        auto sqlSession = "DELETE FROM user1.session where id = $1";
        pqxx::work txn{DD};
        try {
            auto r = txn.exec_params(sqlSession, c);
            txn.commit();
            setUserContext(wsConnPtr, 0);
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
        }
    }
}

std::string getEventName(const WebSocketConnectionPtr &wsConnPtr) {
    auto c = getAdminContext(wsConnPtr);
    auto sqlSession = "SELECT event_name FROM user1.temp_image where session_id = $1";
    pqxx::work txn{DD};
    try {
        auto r = txn.exec_params(sqlSession, c);
        txn.commit();
        return r[0][0].c_str();
    } catch (const std::exception &e) {
        txn.abort();
        std::cerr << e.what() << std::endl;
        return "";
    }
}

void setAdminContext(const WebSocketConnectionPtr &wsConnPtr, int in)
{
    auto c = wsConnPtr->getContext<std::map<std::string, std::vector<int> >>();
    c->at("admin"s)[0] = in;
}
int getAdminContext(const WebSocketConnectionPtr &wsConnPtr){
    auto c = wsConnPtr->getContext<std::map<std::string, std::vector<int> >>();
    return c->at("admin"s)[0];
}
void setUserContext(const WebSocketConnectionPtr &wsConnPtr, int in)
{
    auto c = wsConnPtr->getContext<std::map<std::string, std::vector<int> >>();
    c->at("user"s)[0] = in;
}
int getUserContext(const WebSocketConnectionPtr &wsConnPtr){
    auto c = wsConnPtr->getContext<std::map<std::string, std::vector<int> >>();
    return c->at("user"s)[0];
}

