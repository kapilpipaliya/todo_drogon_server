#include "demo_v1_User.h"
#include "spdlogfix.h"
#include <boost/filesystem.hpp>
#include  "json.hpp"

using namespace demo::v1;

void User::download_id(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback, long id, int version) {
    //    auto id = req->getParameter("path", "default.png"); //?path=
    namespace fs = boost::filesystem;
    auto home = fs::path(getenv("HOME"));
    auto c = req->getCookie("admin");
    auto clientPtr = drogon::app().getDbClient("sce");
    try {
        auto sql = "SELECT name FROM product.post_attachment where id = $1";
        auto x = clientPtr->execSqlSync(sql, id);
        if (!x.empty()) {
            //  auto new_path = std::string("/home/kapili3/fileuploads/") + x[0][0].c_str();
            auto resp = HttpResponse::newFileResponse(home.string() + "/fileuploads/" + x[0]["name"].c_str());
            //resp->setExpiredTime(0);
            resp->addHeader("Cache-Control", "max-age=2592000, public");
            callback(resp);
        } else {
            nlohmann:: json j2 = {{"404", {404, 0 } }};
            auto resp = HttpResponse::newHttpResponse();
            resp->setBody(j2.dump());
            callback(resp);
        }
    } catch (const std::exception &e) {
        
        SPDLOG_TRACE(e.what());
        auto resp = HttpResponse::newHttpResponse();
        resp->setBody(e.what());
        callback(resp);
    }
}
void User::thumb_id(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback, long id, int version)
{
    namespace fs = boost::filesystem;
    auto home = fs::path(getenv("HOME"));
    auto c = req->getCookie("admin");
    auto clientPtr = drogon::app().getDbClient("sce");
    try {
        auto sql = "SELECT name FROM setting.image where id = $1";
        auto x = clientPtr->execSqlSync(sql, id);
        if (!x.empty()) {
            //  auto new_path = std::string("/home/kapili3/fileuploads/") + x[0][0].c_str();
            auto resp = HttpResponse::newFileResponse(home.string() + "/fileuploads/" + x[0]["name"].c_str());
            //resp->setExpiredTime(0);
            resp->addHeader("Cache-Control", "max-age=2592000, public");
            callback(resp);
        } else {
            nlohmann:: json j2 = {{"404", {404, 0 } }};
            auto resp = HttpResponse::newHttpResponse();
            resp->setBody(j2.dump());
            callback(resp);
        }
    } catch (const std::exception &e) {
        
        SPDLOG_TRACE(e.what());
        auto resp = HttpResponse::newHttpResponse();
        resp->setBody(e.what());
        callback(resp);
    }
}

void User::music_id(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback, std::string file)
{
    if( req->getHeader("bearer1") == "Sun, 06 Nov 1990 08:49:03 GMT" &&
            req->getHeader("bearer2") == "Sun, 06 Nov 1991 08:49:31 GMT" &&
            req->getHeader("bearer3") == "Sun, 06 Nov 1992 08:49:39 GMT" &&
            req->getHeader("bearer4") == "Sun, 06 Nov 1993 08:49:371 GMT" &&
            req->getHeader("bearer5") == "Sun, 06 Nov 1994 08:49:33 GMT" &&
            req->getHeader("bearer6") == "Sun, 06 Nov 1995 08:49:35 GMT" &&
            req->getHeader("bearer8") == "Sun, 06 Nov 1996 08:49:36 GMT" &&
            req->getHeader("bearer9") == "Sun, 06 Nov 1998 08:49:98 GMT"
            ){
        namespace fs = boost::filesystem;
        auto home = fs::path(getenv("HOME"));
        auto c = req->getCookie("admin");
        auto clientPtr = drogon::app().getDbClient("sce");
        try {
            //auto sql = "SELECT name FROM music.song where id = $1";
            //auto x = clientPtr->execSqlSync(sql, file);
            //if (!x.empty()) {
            //  auto new_path = std::string("/home/kapili3/fileuploads/") + x[0][0].c_str();
            auto resp = HttpResponse::newFileResponse(home.string() + "/fileuploads/" + file);
            //resp->setExpiredTime(0);
            resp->addHeader("Cache-Control", "max-age=2592000, public");
            callback(resp);
            //} else {
            // nlohmann:: json j2 = {{"404", {404, 0 } }};
            //auto resp = HttpResponse::newHttpResponse();
            //resp->setBody(j2.dump());
            //callback(resp);
            //}
        } catch (const std::exception &e) {

            SPDLOG_TRACE(e.what());
            auto resp = HttpResponse::newHttpResponse();
            resp->setBody(e.what());
            callback(resp);
        }
    } else {
        auto resp = HttpResponse::newHttpResponse();
        resp->setBody("0");
        callback(resp);
        return;
    }
}
