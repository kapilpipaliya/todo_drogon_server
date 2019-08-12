#include "demo_v1_User.h"
#include <json/json.h>
#include <pqxx/pqxx>
#include "core/connection/pdb.h"
#include <boost/filesystem.hpp>
using namespace demo::v1;
void User::download(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    auto id = req->getParameter("path", "AdminMenu5.png");
    auto new_path = "/home/kapili3/fileuploads/" + id;
    auto resp = HttpResponse::newFileResponse(new_path);
    callback(resp);
}
void User::download_id(const HttpRequestPtr &req, std::function<void(const HttpResponsePtr &)> &&callback) {
    auto id = req->getParameter("path", "AdminMenu5.png");
    namespace fs = boost::filesystem;
    auto home = fs::path(getenv("HOME"));
    auto c = req->getCookie("admin");
    pqxx::work txn{DD};
    try {
        auto sql = "SELECT name FROM product.post_attachment where id = $1";
        pqxx::result x = txn.exec_params(sql, id);
        if (!x.empty()) {
            //  auto new_path = std::string("/home/kapili3/fileuploads/") + x[0][0].c_str();
            auto resp = HttpResponse::newFileResponse(home.string() + "/fileuploads/" + x[0][0].c_str());
            //resp->setExpiredTime(0);
            resp->addHeader("Cache-Control", "max-age=2592000, public");
            callback(resp);
        } else {
            Json::Value ret;
            ret[0] = "404";
            Json::Value data;
            data[0] = 404;
            data[1] = 0;
            ret[1] = data;
            auto resp = HttpResponse::newHttpJsonResponse(data);
            resp->addCookie("power", "DDD");
            callback(resp);
        }
    } catch (const std::exception &e) {
        txn.abort();
        std::cerr << e.what() << std::endl;
        //simpleJsonSaveResult(event, false, e.what());
    }
}
void User::thumb_id(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    auto id = req->getParameter("path", "AdminMenu5.png");
    namespace fs = boost::filesystem;
    auto home = fs::path(getenv("HOME"));
    auto c = req->getCookie("admin");
    pqxx::work txn{DD};
    try {
        auto sql = "SELECT name FROM setting.image where id = $1";
        pqxx::result x = txn.exec_params(sql, id);
        if (!x.empty()) {
            //  auto new_path = std::string("/home/kapili3/fileuploads/") + x[0][0].c_str();
            auto resp = HttpResponse::newFileResponse(home.string() + "/fileuploads/" + x[0][0].c_str());
            //resp->setExpiredTime(0);
            resp->addHeader("Cache-Control", "max-age=2592000, public");
            callback(resp);
        } else {
            Json::Value ret;
            ret[0] = "404";
            Json::Value data;
            data[0] = 404;
            data[1] = 0;
            ret[1] = data;
            auto resp = HttpResponse::newHttpJsonResponse(data);
            resp->addCookie("power", "DDD");
            callback(resp);
        }
    } catch (const std::exception &e) {
        txn.abort();
        std::cerr << e.what() << std::endl;
        //simpleJsonSaveResult(event, false, e.what());
    }
}
