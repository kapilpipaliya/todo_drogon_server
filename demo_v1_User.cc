#include "demo_v1_User.h"
#include "spdlog/spdlog.h"
#include <boost/filesystem.hpp>
#include  "json.hpp"

using namespace demo::v1;
void User::download(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    auto id = req->getParameter("path", "AdminMenu5.png");
    auto new_path = "/home/kapili3/fileuploads/" + id;
    auto resp = HttpResponse::newFileResponse(new_path);
    callback(resp);
}
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
        
       spdlog::error(e.what());
       auto resp = HttpResponse::newHttpResponse();
       resp->setBody(e.what());
       callback(resp);
    }
}
void User::thumb_id(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback, long id, int version)
{
    // auto id = req->getParameter("path", "default.png"); //?path=
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
        
        spdlog::error(e.what());
        auto resp = HttpResponse::newHttpResponse();
        resp->setBody(e.what());
        callback(resp);
    }
}
