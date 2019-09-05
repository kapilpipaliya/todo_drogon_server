#include "auth.h"
#include "../../../strfns.h"
#include <boost/filesystem.hpp>
#include "spdlogfix.h"
#include "../../../sql/query.h"
#include "../../../../wscontroller/wsfns.h"
#include "session.h"
using namespace  jadmin;
using nlohmann:: json;
Auth::Auth(const JAdminContextPtr &context_): BaseService(context_)
{

}

void Auth::setupTable()
{

}

json Auth::handleEvent(json event, unsigned long next, json args)
{
    auto event_cmp = event[next].get<std::string>();
    if(event_cmp  == "admin_login"){
        json res = {{}, {}};
        if(args.is_object() && args["user"].is_string() && args["pass"].is_string()){
            auto [session_id, user_id] = adminLogin(args["user"].get<std::string>(), args["pass"].get<std::string>());
            res[0][1] = session_id;
            if(session_id) {
                context->current_session_id = session_id;
                context->user_id = user_id;
                context->setUser();
                res[0] = simpleJsonSaveResult(event, true, "Done");
                res[1] = {{"auth", "set_cookie", 0}, session_id};
                return  res;
            }
        }
        return  {simpleJsonSaveResult(event, false, "Error")};
    } else if (event_cmp  == "admin_logout") {
        auto r = logout();
        if(r){
            return {simpleJsonSaveResult(event, true, "Done")};
        }
        return {simpleJsonSaveResult(event, false, "UnAuthorised")};
    } else if (event_cmp  == "is_admin_auth") {
        return isAdminAuth(event, args);
//    } else if (event_cmp  == "user_login") {
//        return userLogin(event, args);
    } else if (event_cmp  == "user_logout") {
        auto r = logout();
        if(r){
            return {simpleJsonSaveResult(event, true, "Done")};
        }
        return {simpleJsonSaveResult(event, false, "UnAuthorised")};
//    } else if (event_cmp  == "is_user_auth") {
//        return isUserAuth(event, args);
//    } else if (event_cmp  == "user_register") {
//        return userRegister(event, args);
//    } else if (event_cmp  == "user_id") {
//        return userId(event, args);
//    } else if (event_cmp  == "checkout") {
//        return checkout(event, args);
    } else if (event_cmp  == "image_meta_data") {
        return saveImageMeta(event, args);
//    } else if (event_cmp  == "thumb_data") {
//        return thumb_data(event, args);
    } else {
        return nullptr;
    }
}
// Save Image meta on server temporary
json Auth::saveFileMeta(json event, json args)
{
    long c = context->current_session_id;

    //auto strSql = "INSERT INTO music.temp_file_meta ( session_id, event, name, size, type ) VALUES( $1, $2, $3, $4, $5 )";
    auto strSql = format("INSERT INTO music.temp_file_meta ( session_id, event, name, size, type ) VALUES( {0}, '{1}','{2}', {3}, '{4}' )", c, args[0].dump(), args[1].get<std::string>(), args[2].get<long>(), args[3].get<std::string>());
    try {
        auto clientPtr = drogon::app().getDbClient("sce");
        auto transPtr = clientPtr->newTransaction();
        auto r = transPtr->execSqlSync(strSql);
        //auto r = transPtr->execSqlSync(strSql, c, args[0].dump(), args[1].get<std::string>(), args[2].get<long>(), args[3].get<std::string>());
        json ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
    } catch (const std::exception &e) {
       SPDLOG_TRACE(e.what());
        json ret; ret[0] = simpleJsonSaveResult(event, false, "Error"); return ret;
    }
}

std::tuple<long, long> Auth::login(std::string username, std::string password, [[maybe_unused]]bool allow_ui)
{
    long session_id = 0;
    long user_id = 0;
    if (!password.empty() && !username.empty()) {
        try {
            auto sql = "SELECT id, password FROM music.user WHERE username = $1 and password = $2";
            auto clientPtr = drogon::app().getDbClient("sce");
            auto transPtr = clientPtr->newTransaction();
            auto r = transPtr->execSqlSync(sql, username, password);

            if (r.size() == 1) {
                user_id = r[0]["id"].as<long>();
                auto sqlSession = "INSERT INTO music.session (user_id, expire, value) VALUES ($1, $2, $3) returning id";
                auto rs = transPtr->execSqlSync(sqlSession, user_id, 0L, "");
                session_id = rs[0]["id"].as<int>();
            }
        } catch (const std::exception &e) {
           SPDLOG_TRACE(e.what());
        }
    }
    return {session_id, user_id};
}




void Auth::deleteAdminSession() {
    if (context->current_session_id != 0) {
        auto sqlSession = "DELETE FROM user1.session where id = $1";
        try {
            auto clientPtr = drogon::app().getDbClient("sce");
            auto transPtr = clientPtr->newTransaction();
            auto r = transPtr->execSqlSync(sqlSession, context->current_session_id);
            context->current_session_id = 0;
        } catch (const std::exception &e) {
            SPDLOG_TRACE(e.what());
        }
    }
}

bool Auth::logout(long key, bool relogin)
{
    // If no key is passed try to find the session id
    key = key ? key : context->current_session_id;

    // Nuke the cookie before all else
    auto r = Session::destroy(key);
    if(r){
        context->current_session_id = 0;
        return true;
    }
    //if ((!relogin) && AmpConfig::get('logout_redirect')) {
        //target = AmpConfig::get('logout_redirect');
    //} else {
        //target = AmpConfig::get('web_path') . '/login.php';
    //}

    // Do a quick check to see if this is an AJAXed logout request
    // if so use the iframe to redirect
    //if (defined('AJAX_INCLUDE')) {
        //ob_end_clean();
        //ob_start();

        //xoutput_headers();

        //results            = array();
        //results['rfc3514'] = '<script type="text/javascript">reloadRedirect("' . target . '")</script>';
        //echo xoutput_from_array(results);
    //} else {
        /* Redirect them to the login page */
        //header('Location: ' . target);
    //}
}
/*
void Auth::deleteuserSession() {
    if (user != 0) {
        auto sqlSession = "DELETE FROM user1.session where id = $1";
        try {
            auto clientPtr = drogon::app().getDbClient("sce");
            auto transPtr = clientPtr->newTransaction();
            auto r = transPtr->execSqlSync(sqlSession, user);
            user = 0 ;
        } catch (const std::exception &e) {
            SPDLOG_TRACE(e.what());
        }
    }
}
*/


json Auth::handleBinaryEvent(json event, int next, std::string &message)
{
    if(event[next].get<std::string>()  == "save_attachment_data"){
        return save_setting_attachment(event, message);
    } else {
        return Json::nullValue;
    }
}

std::tuple<long, long> Auth::adminLogin(std::string username, std::string password, bool allow_ui)
{
    long session_id = 0;
    long user_id = 0;
    if (!password.empty() && !username.empty()) {
        try {
            auto sql = "select e.id from entity.entity e left join entity.entity_user as u on u.entity_id = e.id where e.email = $1 and u.password = $2";
            auto clientPtr = drogon::app().getDbClient("sce");
            auto transPtr = clientPtr->newTransaction();
            auto r = transPtr->execSqlSync(sql, username, password);

            if (r.size() == 1) {
                user_id = r[0]["id"].as<long>();
                //auto sqlSession = "INSERT INTO music.session (user_id, expire, value) VALUES ($1, $2, $3) returning id";
                auto sqlSession = "INSERT INTO user1.session (key, value) VALUES ($1, $2) returning id";
                //auto rs = transPtr->execSqlSync(sqlSession, user_id, 0L, "");
                json j;
                j["value"] = r[0]["id"].as<long>();
                auto rs = transPtr->execSqlSync(sqlSession, "admin", j.dump());
                session_id = rs[0]["id"].as<int>();
            }
        } catch (const std::exception &e) {
           SPDLOG_TRACE(e.what());
        }
    }
    return {session_id, user_id};
}

json Auth::isAdminAuth( json event, json )
{
    json ret = {{event}};
    bool result = false;
    if (context->current_session_id != 0) { result = true; } else { result = false; }
    ret[0][1] = result;
    return ret;
}

/*
json Auth::userRegister( json event, json args)
{

    std::string strSql = "INSERT INTO entity.entity ( entity_type_id, no, legal_name, slug, email) values($1, $2, $3, $4, $5) returning id";
    try {
        auto clientPtr = drogon::app().getDbClient("sce");
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
        SPDLOG_TRACE(e.what());
        json ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
    }
}

json Auth::userLogin( json event, json args)
{
    auto sql = "select e.id from entity.entity e left join entity.entity_user as u on u.entity_id = e.id where e.email = $1 and u.password = $2";
    try {
        auto clientPtr = drogon::app().getDbClient("sce");
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
            cookie_event[0] = "auth";
            cookie_event[1] = "set_cookie";
            cookie_event[2] = 0; // must be zero
            cookie_result[0] = cookie_event;
            json cookie_value;
            //auto s = get_serial_no();
            cookie_value["user"] = rs[0]["id"].as<int>();
            cookie_result[1] = cookie_value;

            user = rs[0]["id"].as<int>();
            json final;
            final[0] = login_result;
            final[1] = cookie_result;
            return final;
        } else {
            json ret; ret[0] = simpleJsonSaveResult(event, false, "Error"); return ret;
        }

    } catch (const std::exception &e) {
        SPDLOG_TRACE(e.what());
        json ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
    }
}

json Auth::userId( json event, json )
{
    long c =  user;
    if (c != 0) {
        auto sqlSession = "SELECT key, value FROM user1.session where id = $1";
        try {
            auto clientPtr = drogon::app().getDbClient("sce");
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
                SPDLOG_TRACE("message: {}", e.what());
                SPDLOG_TRACE("exception id: {}", e.id);
                SPDLOG_TRACE("byte position of error:", e.byte);
                json j =  std::string("cant parse json reason: ") + e.what() ;
            }
            return jresult;
        } catch (const std::exception &e) {
            SPDLOG_TRACE(e.what());
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
    deleteuserSession();
    json ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
}
json Auth::isUserAuth( json event, json )
{
    json ret;
    json value;
    value[0] = event;
    long c = user;
    if (c != 0) { value[1] = true; } else { value[1] = false; }
    ret[0]=value;
    return ret;
}
json Auth::checkout( json event, json args)
{
    long c = user;
    if (c != 0) {
        auto sqlSession = "SELECT key, value FROM user1.session where id = $1";
        try {
            auto clientPtr = drogon::app().getDbClient("sce");
            auto transPtr = clientPtr->newTransaction();
            auto r = transPtr->execSqlSync(sqlSession, c);
            // send id
            json jresult;
            jresult[0]=event;

            auto root = json::parse(r[0][1].c_str());
            jresult[1]=root["value"];
            return jresult;
        } catch (const std::exception &e) {
            SPDLOG_TRACE(e.what());
            json jresult;
            jresult[0]=event;
            jresult[1]=0;
            return jresult;
        }
    } else {
        return Json::nullValue;
    }
}
*/
// Save Image meta on server temporary
json Auth::saveImageMeta( json event, json args)
{
    long c = context->current_session_id;

    auto strSql = "INSERT INTO user1.temp_image ( session_id, event, name, size, type ) VALUES( $1, $2, $3, $4, $5 )";
    try {
        auto clientPtr = drogon::app().getDbClient("sce");
        auto transPtr = clientPtr->newTransaction();
        auto r = transPtr->execSqlSync(strSql, c, args[0].dump(), args[1].get<std::string>(), args[2].get<long>(), args[3].get<std::string>());
        json ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
    } catch (const std::exception &e) {
        SPDLOG_TRACE(e.what());
        json ret; ret[0] = simpleJsonSaveResult(event, false, "Error"); return ret;
    }
}
//--------------------------

// ------------------
/*
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
    WsFns::sendJson(wsConnPtr, batch);

    namespace fs = boost::filesystem;
    auto home = fs::path(getenv("HOME"));

    auto clientPtr = drogon::app().getDbClient("sce");
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

                //SPDLOG_TRACE("the entire file content is in memory");
                wsConnPtr->send(memblock, WebSocketMessageType::Binary); // Note when server not able to send this file, front end crash.
                //delete[] memblock;
            }
        } else {
            // Fix simpleJsonSaveResult(event, true, "Done");
        }
        return json(Json::nullValue);
    } catch (const std::exception &e) {

        SPDLOG_TRACE(e.what());
        //simpleJsonSaveResult(event, false, e.what());
        return json(Json::nullValue);
    }
    //get binary data and send.
}
*/

// save image in disk and return temporary id:
json Auth::save_setting_attachment(json event, std::string &message)
{
    auto session_id = context->current_session_id;
    auto strSql = sel_("user1.temp_image", "event,  name, size, type", "where session_id = $1");
    auto clientPtr = drogon::app().getDbClient("sce");
    auto transPtr = clientPtr->newTransaction();
    try {
        auto r = transPtr->execSqlSync(strSql, session_id);
        transPtr->execSqlSync(dele_("music.temp_file_meta", "where session_id = $1 and event = $2"), session_id, r[0]["event"].as<std::string>());

        // check if file exist else rename a file
        // convert this to json

        auto event_json = json::parse(r[0]["event"].c_str());

        namespace fs = boost::filesystem;
        auto home = fs::path(getenv("HOME"));

        std::string name = r[0][1].c_str();
        auto size = r[0][2].as<int>();
        auto type = r[0][3].c_str();

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
        jresult[1] = insert_result[0]["id"].as<long>();
        //jresult[1] = e.what();
        ret[0] = jresult;

        return ret;

    } catch (const std::exception &e) {

        SPDLOG_TRACE(e.what());
        return Json::nullValue;
    }

}
