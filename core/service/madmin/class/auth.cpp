#include "auth.h"
#include "session.h"
using namespace  madmin;
Auth::Auth(const MAdminContextPtr &context_): BaseService(context_)
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
        auto [session_id, user_id] = login(args["user"].get<std::string>(), args["pass"].get<std::string>());
        res[0][1] = session_id;
        if(session_id) {
            context->current_session_id = session_id;
            context->user_id = user_id;
            context->setUser();
            res[0] = simpleJsonSaveResult(event, true, "Done");
            res[1] = {{"auth", "set_cookie", 0}, session_id};
            return  res;
        } else {
            return  {simpleJsonSaveResult(event, false, "Error")};
        }
    } else if (event_cmp == "logout") {
        auto r = logout();
        if(r){
            return {simpleJsonSaveResult(event, true, "Done")};
        }
        return {simpleJsonSaveResult(event, false, "UnAuthorised")};
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
