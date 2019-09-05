#include "auth.h"

#include <utility>
#include "../../dba.h"
#include "session.h"
using namespace  madmin;
Auth::Auth(MAdminContextPtr context_): context(std::move(context_))
{

}

void Auth::setupTable()
{

}

nlohmann::json Auth::handleEvent(nlohmann::json event, unsigned long next, nlohmann::json args)
{
    auto event_cmp = event[next].get<std::string>();
    if(event_cmp == "login"){
        json res = {{}, {}};
        if(args.is_object() && args["user"].is_string() && args["pass"].is_string()){
            auto [session_id, user_id] = login(args["user"].get<std::string>(), args["pass"].get<std::string>());
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
    } if (event_cmp == "logout") {
        auto r = logout();
        if(r){
            return {simpleJsonSaveResult(event, true, "Done")};
        }
        return {simpleJsonSaveResult(event, false, "UnAuthorised")};
    } else if (event_cmp  == "file_meta_data") {
        return saveFileMeta(event, args);
    } else if (event_cmp  == "ins") {
        return ins(event, args);
    } else if (event_cmp  == "upd") {
        return upd(event, args);
    } else if (event_cmp  == "del") {
        return del(event, args);
    } else {
        return nullptr;
    }
}
// Save Image meta on server temporary
nlohmann::json Auth::saveFileMeta(const nlohmann::json& event, nlohmann::json args)
{
    long c = context->current_session_id;

    //auto strSql = "INSERT INTO music.temp_file_meta ( session_id, event, name, size, type ) VALUES( $1, $2, $3, $4, $5 )";
    auto strSql = format("INSERT INTO music.temp_file_meta ( session_id, event, name, size, type ) VALUES( {0}, '{1}','{2}', {3}, '{4}' )", c, args[0].dump(), args[1].get<std::string>(), args[2].get<long>(), args[3].get<std::string>());
    try {
        auto clientPtr = drogon::app().getDbClient("sce");
        auto transPtr = clientPtr->newTransaction();
        auto r = Dba::writeInTrans(transPtr, strSql);
        //auto r = Dba::writeInTrans(transPtr, strSql, c, args[0].dump(), args[1].get<std::string>(), args[2].get<long>(), args[3].get<std::string>());
        json ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
    } catch (const std::exception &e) {
       SPDLOG_TRACE(e.what());
        json ret; ret[0] = simpleJsonSaveResult(event, false, "Error"); return ret;
    }
}

bool Auth::logout(long key,[[maybe_unused]] bool relogin)
{
    // If no key is passed try to find the session id
    key = key ? key : context->current_session_id;

    // Nuke the cookie before all else
    auto r = Session::destroy(key);
    if(r){
        context->current_session_id = 0;
        return true;
    }
    return false;
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

std::tuple<long, long> Auth::login(const std::string& username, const std::string& password, [[maybe_unused]]bool allow_ui)
{
    long session_id = 0;
    long user_id = 0;
    if (!password.empty() && !username.empty()) {
        try {
            auto sql = "SELECT id, password FROM music.user WHERE username = $1 and password = $2";
            auto clientPtr = drogon::app().getDbClient("sce");
            auto transPtr = clientPtr->newTransaction();
            auto r = Dba::writeInTrans(transPtr, sql, username, password);

            if (r.size() == 1) {
                user_id = r[0]["id"].as<long>();
                auto sqlSession = "INSERT INTO music.session (user_id, expire, value) VALUES ($1, $2, $3) returning id";
                auto rs = Dba::writeInTrans(transPtr, sqlSession, user_id, 0L, "");
                session_id = rs[0]["id"].as<long>();
            }
        } catch (const std::exception &e) {
           SPDLOG_TRACE(e.what());
        }
    }
    return {session_id, user_id};
}
