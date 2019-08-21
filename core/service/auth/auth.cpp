#include "auth.h"

#include "../../strfns.h"
#include "../../jsonfns.h"
#include "../../../EchoWebSocket.h"

using namespace std::literals;
Auth::Auth(const WebSocketConnectionPtr& wsConnPtr_): wsConnPtr(wsConnPtr_)
{

}


Json::Value Auth::handleEvent(Json::Value event, int next, Json::Value args)
{
    auto event_cmp = event[next].asString();
    if(event_cmp  == "admin_login"){
        return adminLogin(event, args);
    } else if (event_cmp  == "admin_logout") {
        return adminLogout(event, args);
    } else if (event_cmp  == "is_admin_auth") {
        return isAdminAuth(event, args);
    } else if (event_cmp  == "user_login") {
        return userLogin(event, args);
    } else if (event_cmp  == "user_logout") {
        return userLogout(event, args);
    } else if (event_cmp  == "is_user_auth") {
        return isUserAuth(event, args);
    } else if (event_cmp  == "user_register") {
        return userRegister(event, args);
    } else if (event_cmp  == "user_id") {
        return userId(event, args);
    } else if (event_cmp  == "checkout") {
        return checkout(event, args);
    } else if (event_cmp  == "save_image_meta_data") {
        return saveImageMeta(event, args);
    } else {
        return Json::nullValue;
    }
}

Json::Value Auth::adminLogin( Json::Value event, Json::Value args)
{
    auto sql = "select e.id from entity.entity e left join entity.entity_user as u on u.entity_id = e.id where e.email = $1 and u.password = $2";
    try {
        auto transPtr = clientPtr->newTransaction();
        auto r = transPtr->execSqlSync(sql, args["email"].asString(), args["pass"].asString());

        if (r.size() == 1) {

            Json::Value j;
            j["value"] = r[0]["id"].as<int>();
            auto sqlSession = "INSERT INTO user1.session (key, value) VALUES ($1, $2) returning id";
            // To serialize the Json::Value into a Json document, you should use a Json writer, or Json::Value::toStyledString().
            LOG_INFO << j.toStyledString();
            auto rs = transPtr->execSqlSync(sqlSession, "admin", j.toStyledString());
            Json::Value login_result = simpleJsonSaveResult(event, true, "Done");

            // ask to save cookie
            Json::Value cookie_result;
            Json::Value cookie_event;
            cookie_event[0] = "legacy";
            cookie_event[1] = "auth";
            cookie_event[2] = "set_cookie";
            cookie_event[3] = 0; // must be zero
            cookie_result[0] = cookie_event;
            Json::Value cookie_value;
            //auto s = get_serial_no();
            cookie_value["admin"] = rs[0]["id"].as<int>();
            cookie_result[1] = cookie_value;

            setAdminContext(wsConnPtr, rs[0]["id"].as<int>());

            Json::Value final;
            final[0] = login_result;
            final[1] = cookie_result;
            return final;
        } else {
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, "Error"); return ret;
        }

    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
    }
}
Json::Value Auth::adminLogout( Json::Value event, Json::Value )
{
    deleteAdminSession(wsConnPtr);
    Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
}
Json::Value Auth::isAdminAuth( Json::Value event, Json::Value )
{
    Json::Value ret;
    Json::Value value;
    value[0] = event;

    auto c = getAdminContext(wsConnPtr);
    bool result = false;
    if (c != 0) { result = true; } else { result = false; }
    value[1] = result;
    ret[0]=value;
    return ret;
}


Json::Value Auth::userRegister( Json::Value event, Json::Value args)
{

    std::string strSql = "INSERT INTO entity.entity ( entity_type_id, no, legal_name, slug, email) values($1, $2, $3, $4, $5) returning id";
    try {
        auto transPtr = clientPtr->newTransaction();


        std::string data = args["legal_name"].asString();
        std::transform(data.begin(), data.end(), data.begin(),
                       [](unsigned char c){ return std::tolower(c); });
        std::transform(data.begin(), data.end(), data.begin(),
                       [](unsigned char c){ return std::tolower(c); });
        std::transform(data.begin(), data.end(), data.begin(), [](char ch) {
            return ch == ' ' ? '_' : ch;
        });

        auto x = transPtr->execSqlSync(strSql, 6, "", args["legal_name"].asString(), data, args["email"].asString() );
        auto entity_id = x[0]["id"].as<int>();
        std::string strSqlUser = "INSERT INTO entity.entity_user (entity_id, username, password, password_hash) VALUES ($1, $2, $3, $4)";
        transPtr->execSqlSync(strSqlUser, entity_id, args["email"].asString(), args["pass"].asString(), args["pass"].asString());

        //simpleJsonSaveResult(event, true, "Done");
        return userLogin(event, args);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
    }
}
Json::Value Auth::userLogin( Json::Value event, Json::Value args)
{
    auto sql = "select e.id from entity.entity e left join entity.entity_user as u on u.entity_id = e.id where e.email = $1 and u.password = $2";
    try {
        auto transPtr = clientPtr->newTransaction();
        auto r = transPtr->execSqlSync(sql, args["email"].asString(), args["pass"].asString());

        if (r.size() == 1) {

            Json::Value j;
            j["value"] = r[0]["id"].as<int>();
            auto sqlSession = "INSERT INTO user1.session (key, value) VALUES ($1, $2) returning id";
            // To serialize the Json::Value into a Json document, you should use a Json writer, or Json::Value::toStyledString().
            LOG_INFO << j.toStyledString();
            auto rs = transPtr->execSqlSync(sqlSession, "user", j.toStyledString());
            Json::Value login_result = simpleJsonSaveResult(event, true, "Done");

            // ask to save cookie
            Json::Value cookie_result;
            Json::Value cookie_event;
            cookie_event[0] = "legacy";
            cookie_event[1] = "auth";
            cookie_event[2] = "set_cookie";
            cookie_event[3] = 0; // must be zero
            cookie_result[0] = cookie_event;
            Json::Value cookie_value;
            //auto s = get_serial_no();
            cookie_value["user"] = rs[0]["id"].as<int>();
            cookie_result[1] = cookie_value;

            setUserContext(wsConnPtr, rs[0]["id"].as<int>());
            Json::Value final;
            final[0] = login_result;
            final[1] = cookie_result;
            return final;
        } else {
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, "Error"); return ret;
        }

    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
    }
}
Json::Value Auth::userId( Json::Value event, Json::Value )
{
    auto c = getUserContext(wsConnPtr);
    if (c != 0) {
        auto sqlSession = "SELECT key, value FROM user1.session where id = $1";
        try {
            auto transPtr = clientPtr->newTransaction();
            auto r = transPtr->execSqlSync(sqlSession, c);
            // send id
            //simpleJsonSaveResult(event, true, r[0][1].c_str());
            Json::Value jresult;
            jresult[0]=event;

            Json::Value root;
            std::stringstream txt;
            txt << r[0][1].c_str();
            Json::CharReaderBuilder rbuilder;
            rbuilder["collectComments"] = false;
            std::string errs;
            bool ok = Json::parseFromStream(rbuilder, txt, &root, &errs);
            if(ok){
                jresult[1]=root["value"].asInt();
            } else {
                 jresult[1]=0;
            }
            return jresult;
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            Json::Value jresult;
            jresult[0]=event;
            jresult[1]=0;
            return jresult;
        }
    }
    Json::Value ret; ret[0] = 0; return ret;
}
Json::Value Auth::userLogout( Json::Value event, Json::Value )
{
    deleteuserSession(wsConnPtr);
    Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
}
Json::Value Auth::isUserAuth( Json::Value event, Json::Value )
{
    Json::Value ret;
    Json::Value value;
    value[0] = event;
    auto c = getUserContext(wsConnPtr);
    if (c != 0) { value[1] = true; } else { value[1] = false; }
    ret[0]=value;
    return ret;
}
Json::Value Auth::checkout( Json::Value event, Json::Value args)
{
    auto c = getUserContext(wsConnPtr);
    printJson(args);
    if (c != 0) {
        auto sqlSession = "SELECT key, value FROM user1.session where id = $1";
        try {
            auto transPtr = clientPtr->newTransaction();
            auto r = transPtr->execSqlSync(sqlSession, c);
            // send id
            Json::Value jresult;
            jresult[0]=event;

            Json::Value root;
            std::stringstream txt;
            txt << r[0][1].c_str();
            Json::CharReaderBuilder rbuilder;
            rbuilder["collectComments"] = false;
            std::string errs;
            bool ok = Json::parseFromStream(rbuilder, txt, &root, &errs);
            if(ok){
                //auto user_entity_id = root["value"].asInt();
            } else {

            }
            jresult[1]=root["value"].asInt();
            return jresult;
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            Json::Value jresult;
            jresult[0]=event;
            jresult[1]=0;
            return jresult;
        }
    } else {
        return Json::nullValue;
    }
}
 // Save Image meta on server temporary
Json::Value Auth::saveImageMeta( Json::Value event, Json::Value args)
{
    auto c = getAdminContext(wsConnPtr);

    auto strSql = "INSERT INTO user1.temp_image ( session_id, event, name, size, type ) VALUES( $1, $2, $3, $4, $5 )";
    try {
        auto transPtr = clientPtr->newTransaction();
        auto r = transPtr->execSqlSync(strSql, c, args[0].toStyledString(), args[1].asString(), args[2].asInt64(), args[3].asString());
        Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, "Error"); return ret;
    }
}
//--------------------------
int generateContext(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr, std::string account_type) {
    auto c = req->getCookie(account_type);
    if (c.empty()) {
        return 0;
    } else {
        auto sqlSession = "SELECT * FROM user1.session where id = $1";
        try {
            auto transPtr = clientPtr->newTransaction();
            auto r = transPtr->execSqlSync(sqlSession, c);
            if (r.size() != 0) {
                auto i = r[0]["id"].as<int>();
                return i;
            } else {
                return 0;
            }
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            return 0;
        }
    }
}

void deleteAdminSession(const WebSocketConnectionPtr &wsConnPtr) {
    auto c = getAdminContext(wsConnPtr);
    if (c != 0) {
        auto sqlSession = "DELETE FROM user1.session where id = $1";
        try {
            auto transPtr = clientPtr->newTransaction();
            auto r = transPtr->execSqlSync(sqlSession, c);
            setAdminContext(wsConnPtr, 0);
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
    }
}
void deleteuserSession(const WebSocketConnectionPtr &wsConnPtr) {
    auto c = getUserContext(wsConnPtr);
    if (c != 0) {
        auto sqlSession = "DELETE FROM user1.session where id = $1";
        try {
            auto transPtr = clientPtr->newTransaction();
            auto r = transPtr->execSqlSync(sqlSession, c);
            setUserContext(wsConnPtr, 0);
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
        }
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
