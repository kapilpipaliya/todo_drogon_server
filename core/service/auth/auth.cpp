#include "auth.h"

#include "../../strfns.h"
#include "../../jsonfns.h"
#include "../../../EchoWebSocket.h"
#include <boost/filesystem.hpp>
#include "../../sql/query.h"
using namespace std::literals;
Auth::Auth(const WebSocketConnectionPtr& wsConnPtr_): wsConnPtr(wsConnPtr_)
{

}


json Auth::handleEvent(json event, int next, json args)
{
    auto event_cmp = event[next].get<std::string>();
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
    } else if (event_cmp  == "thumb_data") {
        return thumb_data(event, args);
    } else {
        return Json::nullValue;
    }
}

json Auth::handleBinaryEvent(json event, int next, std::string &message)
{
    if(event[next].get<std::string>()  == "save_attachment_data"){
        return save_setting_attachment(event, message);
    } else {
        return Json::nullValue;
    }
}

json Auth::adminLogin( json event, json args)
{
    auto sql = "select e.id from entity.entity e left join entity.entity_user as u on u.entity_id = e.id where e.email = $1 and u.password = $2";
    try {
        auto transPtr = clientPtr->newTransaction();
        auto r = transPtr->execSqlSync(sql, args["email"].get<std::string>(), args["pass"].get<std::string>());

        if (r.size() == 1) {

            json j;
            j["value"] = r[0]["id"].as<int>();
            auto sqlSession = "INSERT INTO user1.session (key, value) VALUES ($1, $2) returning id";
            // To serialize the json into a Json document, you should use a Json writer, or json::dump().
            //LOG_INFO << j.dump();
            auto rs = transPtr->execSqlSync(sqlSession, "admin", j.dump());
            json login_result = simpleJsonSaveResult(event, true, "Done");

            // ask to save cookie
            json cookie_result;
            json cookie_event;
            cookie_event[0] = "legacy";
            cookie_event[1] = "auth";
            cookie_event[2] = "set_cookie";
            cookie_event[3] = 0; // must be zero
            cookie_result[0] = cookie_event;
            json cookie_value;
            //auto s = get_serial_no();
            cookie_value["admin"] = rs[0]["id"].as<int>();
            cookie_result[1] = cookie_value;

            setAdminContext(wsConnPtr, rs[0]["id"].as<int>());

            json final;
            final[0] = login_result;
            final[1] = cookie_result;
            return final;
        } else {
            json ret; ret[0] = simpleJsonSaveResult(event, false, "Error"); return ret;
        }

    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        json ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
    }
}
json Auth::adminLogout( json event, json )
{
    deleteAdminSession(wsConnPtr);
    json ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
}
json Auth::isAdminAuth( json event, json )
{
    json ret;
    json value;
    value[0] = event;

    long c = getAdminContext(wsConnPtr);
    bool result = false;
    if (c != 0) { result = true; } else { result = false; }
    value[1] = result;
    ret[0]=value;
    return ret;
}


json Auth::userRegister( json event, json args)
{

    std::string strSql = "INSERT INTO entity.entity ( entity_type_id, no, legal_name, slug, email) values($1, $2, $3, $4, $5) returning id";
    try {
        auto transPtr = clientPtr->newTransaction();


        std::string data = args["legal_name"].get<std::string>();
        std::transform(data.begin(), data.end(), data.begin(),
                       [](unsigned char c){ return std::tolower(c); });
        std::transform(data.begin(), data.end(), data.begin(),
                       [](unsigned char c){ return std::tolower(c); });
        std::transform(data.begin(), data.end(), data.begin(), [](char ch) {
            return ch == ' ' ? '_' : ch;
        });

        auto x = transPtr->execSqlSync(strSql, 6, "", args["legal_name"].get<std::string>(), data, args["email"].get<std::string>() );
        auto entity_id = x[0]["id"].as<int>();
        std::string strSqlUser = "INSERT INTO entity.entity_user (entity_id, username, password, password_hash) VALUES ($1, $2, $3, $4)";
        transPtr->execSqlSync(strSqlUser, entity_id, args["email"].get<std::string>(), args["pass"].get<std::string>(), args["pass"].get<std::string>());

        //simpleJsonSaveResult(event, true, "Done");
        return userLogin(event, args);
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        json ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
    }
}
json Auth::userLogin( json event, json args)
{
    auto sql = "select e.id from entity.entity e left join entity.entity_user as u on u.entity_id = e.id where e.email = $1 and u.password = $2";
    try {
        auto transPtr = clientPtr->newTransaction();
        auto r = transPtr->execSqlSync(sql, args["email"].get<std::string>(), args["pass"].get<std::string>());

        if (r.size() == 1) {

            json j;
            j["value"] = r[0]["id"].as<int>();
            auto sqlSession = "INSERT INTO user1.session (key, value) VALUES ($1, $2) returning id";
            // To serialize the json into a Json document, you should use a Json writer, or json::dump().
            LOG_INFO << j.dump();
            auto rs = transPtr->execSqlSync(sqlSession, "user", j.dump());
            json login_result = simpleJsonSaveResult(event, true, "Done");

            // ask to save cookie
            json cookie_result;
            json cookie_event;
            cookie_event[0] = "legacy";
            cookie_event[1] = "auth";
            cookie_event[2] = "set_cookie";
            cookie_event[3] = 0; // must be zero
            cookie_result[0] = cookie_event;
            json cookie_value;
            //auto s = get_serial_no();
            cookie_value["user"] = rs[0]["id"].as<int>();
            cookie_result[1] = cookie_value;

            setUserContext(wsConnPtr, rs[0]["id"].as<int>());
            json final;
            final[0] = login_result;
            final[1] = cookie_result;
            return final;
        } else {
            json ret; ret[0] = simpleJsonSaveResult(event, false, "Error"); return ret;
        }

    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        json ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
    }
}
json Auth::userId( json event, json )
{
    long c = getUserContext(wsConnPtr);
    if (c != 0) {
        auto sqlSession = "SELECT key, value FROM user1.session where id = $1";
        try {
            auto transPtr = clientPtr->newTransaction();
            auto r = transPtr->execSqlSync(sqlSession, c);
            // send id
            //simpleJsonSaveResult(event, true, r[0][1].c_str());
            json jresult;
            jresult[0]=event;

            try
            {
                auto root = json::parse(r[0][1].c_str());
                 jresult[1]=root["value"];
            }
            catch (json::parse_error& e)
            {
                 jresult[1]=0;
                std::cout << "message: " << e.what() << '\n'
                          << "exception id: " << e.id << '\n'
                          << "byte position of error: " << e.byte << std::endl;
                nlohmann::json j =  std::string("cant parse json reason: ") + e.what() ;
            }
            return jresult;
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            json jresult;
            jresult[0]=event;
            jresult[1]=0;
            return jresult;
        }
    }
    json ret; ret[0] = 0; return ret;
}
json Auth::userLogout( json event, json )
{
    deleteuserSession(wsConnPtr);
    json ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
}
json Auth::isUserAuth( json event, json )
{
    json ret;
    json value;
    value[0] = event;
    long c = getUserContext(wsConnPtr);
    if (c != 0) { value[1] = true; } else { value[1] = false; }
    ret[0]=value;
    return ret;
}
json Auth::checkout( json event, json args)
{
    long c = getUserContext(wsConnPtr);
    printJson(args);
    if (c != 0) {
        auto sqlSession = "SELECT key, value FROM user1.session where id = $1";
        try {
            auto transPtr = clientPtr->newTransaction();
            auto r = transPtr->execSqlSync(sqlSession, c);
            // send id
            json jresult;
            jresult[0]=event;

            auto root = json::parse(r[0][1].c_str());
            jresult[1]=root["value"];
            return jresult;
        } catch (const std::exception &e) {
            std::cerr << e.what() << std::endl;
            json jresult;
            jresult[0]=event;
            jresult[1]=0;
            return jresult;
        }
    } else {
        return Json::nullValue;
    }
}
 // Save Image meta on server temporary
json Auth::saveImageMeta( json event, json args)
{
    long c = getAdminContext(wsConnPtr);

    auto strSql = "INSERT INTO user1.temp_image ( session_id, event, name, size, type ) VALUES( $1, $2, $3, $4, $5 )";
    try {
        auto transPtr = clientPtr->newTransaction();
        auto r = transPtr->execSqlSync(strSql, c, args[0].dump(), args[1].get<std::string>(), args[2].get<long>(), args[3].get<std::string>());
        json ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
        json ret; ret[0] = simpleJsonSaveResult(event, false, "Error"); return ret;
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
    long c = getAdminContext(wsConnPtr);
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
    long c = getUserContext(wsConnPtr);
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

void setAdminContext(const WebSocketConnectionPtr &wsConnPtr, long in)
{
    auto c = wsConnPtr->getContext<std::map<std::string, std::vector<int> >>();
    c->at("admin"s)[0] = in;
}
long getAdminContext(const WebSocketConnectionPtr &wsConnPtr){
    auto c = wsConnPtr->getContext<std::map<std::string, std::vector<int> >>();
    return c->at("admin"s)[0];
}
void setUserContext(const WebSocketConnectionPtr &wsConnPtr, long in)
{
    auto c = wsConnPtr->getContext<std::map<std::string, std::vector<int> >>();
    c->at("user"s)[0] = in;
}
long getUserContext(const WebSocketConnectionPtr &wsConnPtr){
    auto c = wsConnPtr->getContext<std::map<std::string, std::vector<int> >>();
    return c->at("user"s)[0];
}


// ------------------
json Auth::thumb_data( json event, json args)
{
    // send meta_data
    json batch;
    json ret;

    json data1;
    data1[0] = "take_image_meta";
    ret[0] = data1;
    ret[1] = event;

    batch[0] = ret;
    wsConnPtr->send(batch.dump());

    namespace fs = boost::filesystem;
    auto home = fs::path(getenv("HOME"));

    auto transPtr = clientPtr->newTransaction();
    try {
        auto sql = "SELECT name FROM setting.image WHERE id = $1";
        auto x = transPtr->execSqlSync(sql, args.get<int>());

        if (x.size() == 1) {
            std::streampos size;
            // http://www.cplusplus.com/doc/tutorial/files/
            // What is the best way to read an entire file into a std::string in C++?
            // https://stackoverflow.com/questions/116038/what-is-the-best-way-to-read-an-entire-file-into-a-stdstring-in-c/116220#116220
            std::ifstream file(home.string() + "/fileuploads/" + x[0]["name"].c_str(), std::ios::in | std::ios::binary | std::ios::ate);
            if (file.is_open()) {
                auto memblock = read_all(file);
                file.close();

                //std::cout << "the entire file content is in memory";
                wsConnPtr->send(memblock, WebSocketMessageType::Binary); // Note when server not able to send this file, front end crash.
                //delete[] memblock;
            }
        } else {
            // Fix simpleJsonSaveResult(event, true, "Done");
        }
        return json(Json::nullValue);
    } catch (const std::exception &e) {

        std::cerr << e.what() << std::endl;
        //simpleJsonSaveResult(event, false, e.what());
        return json(Json::nullValue);
    }
    //get binary data and send.
}

// save image in disk and return temporary id:
json Auth::save_setting_attachment(json event, std::string &message)
{
    auto session_id = getAdminContext(wsConnPtr);
    auto strSql = sel_("user1.temp_image", "event,  name, size, type", "where session_id = $1");
    auto transPtr = clientPtr->newTransaction();
    try {
        auto r = transPtr->execSqlSync(strSql, session_id);
        transPtr->execSqlSync(dele_("user1.temp_image", "where session_id = $1"), session_id);

        // check if file exist else rename a file
        // convert this to json

        auto event_json = json::parse(r[0]["temp_image"].c_str());

        namespace fs = boost::filesystem;
        auto home = fs::path(getenv("HOME"));

        std::string name = r[0][1].c_str();
        auto size = r[0][2].as<int>();
        auto type = r[0][3].c_str();


        fprintf(stdout, "%s %d %s\n", name.c_str(), size, type);
        fflush(stdout);

        // basic file operations

        std::string new_name = name;
        auto path = boost::filesystem::path(home.string() + "/fileuploads/" + new_name);
        int i = 1;
        while (true) {
            if (boost::filesystem::exists(home.string() + "/fileuploads/" + new_name)) {
                // new_name = path.parent_path().string() + "/" + path.stem().string() + std::to_string(i) + path.extension().string();
                new_name = path.stem().string() + std::to_string(i) + path.extension().string();
            } else {
                break;
            }
            i++;
        }
        name = new_name;


        std::ofstream myfile;
        myfile.open(home.string() + "/fileuploads/" + name);
        myfile << message;
        myfile.close();

        // Insert Image
        auto temp_image_table = sqlb::ObjectIdentifier("setting", "temp_image_id", "pa");
        std::string strSql = "INSERT INTO %1.%2 (name, size, type) VALUES ($1, $2, $3) RETURNING id";
        ReplaceAll2(strSql, "%1", temp_image_table.schema());
        ReplaceAll2(strSql, "%2", temp_image_table.name());

        json ret;
        json jresult;
        jresult[0] = event_json;
        auto insert_result = transPtr->execSqlSync(strSql, name, size, type);
        jresult[1] = insert_result[0]["id"].as<int>();
        //jresult[1] = e.what();
        ret[0] = jresult;

        return ret;

    } catch (const std::exception &e) {

        std::cerr << e.what() << std::endl;
        return Json::nullValue;
    }

}
