#include "demo_v1_User.h"


#include "core/tables/functions.h"
#include <json/json.h>
#include <pqxx/pqxx>

using namespace demo::v1;


//add definition of your processing function here
void User::login(const HttpRequestPtr &req,
                 std::function<void (const HttpResponsePtr &)> &&callback,
                 std::string &&userId,
                 const std::string &password)
{
    LOG_DEBUG<<"User "<<userId<<" login";
    //Authentication algorithm, read database, verify identity, etc...
    //...
    Json::Value ret;
    ret["result"]="ok";
    ret["token"]=drogon::utils::getUuid();
    auto resp=HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
}

void User::newForm(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    //    std::unordered_map<std::string, std::string> params = req->parameters();
    //    auto material_id1 = params["material_id"];
    //    auto slug1 = params["slug"];
    //    auto name1 = params["name"];

    //    fprintf(stderr, "%d %s %s\n", material_id, slug.c_str(), name.c_str());
    //    fflush(stdout);

    auto h = req->headers();
    auto j = req->getJsonObject().get();
    //    auto k = j->toStyledString();
    //    fprintf(stderr, "%s", k.c_str());

    auto material_id1 = j->get("material_id", 0).asInt();
    auto slug1 = j->get("slug", "").asString();
    auto name1 = j->get("name", "").asString();

    fflush(stdout);


    Table a;
    query_accessory(a);

    Json::Value ret;
    /*
    bool ok = a.insertRow(material_id1, slug1, name1);
    if (!ok) {
        ret["result"]=2;
        ret["error"]=a.insertError;
    } else {
        ret["result"]=1;
    }
    */
    auto resp=HttpResponse::newHttpJsonResponse(ret);
    //    resp->addHeader("Access-Control-Allow-Origin", "*");
    //    resp->addHeader("Access-Control-Allow-Origin", "*");
    //    resp->addHeader("Access-Control-Allow-Methods", "['PUT', 'POST']");
    callback(resp);
}

void User::getInfo(const HttpRequestPtr &req,
                   std::function<void (const HttpResponsePtr &)> &&callback,
                   std::string userId,
                   const std::string &token) const
{
    LOG_DEBUG<<"User "<<userId<<" get his information";

    //Verify the validity of the token, etc.
    //Read the database or cache to get user information
    Json::Value ret;
    ret["result"]="ok";
    ret["user_name"]="Jack";
    ret["user_id"]=userId;
    ret["gender"]=1;
    auto resp=HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
}

void User::allAccessory(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Table a;
    query_accessory(a);
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    callback(resp);
}

void User::allAccount(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Table a;
    query_account(a);
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    callback(resp);
}

void User::allAccountHeading(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Table a;
    query_account_heading(a);
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    callback(resp);
}

void User::allColor(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Table a;
    query_tone(a);
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    callback(resp);

}

void User::allEntity(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Table a;
    query_entity(a);
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    callback(resp);
}

void User::allGemClarity(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Table a;
    query_clarity(a);
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    callback(resp);
}

void User::allGemShape(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Table a;
    query_shape(a);
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    callback(resp);
}

void User::allGlobalSetting(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Table a;
    query_global_setting(a);
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    callback(resp);
}

void User::allLog(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Table a;
    query_log(a);
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    callback(resp);
}

void User::allMaterial(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Table a;
    query_metal(a);
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    callback(resp);
}
/*
void User::allMaterialType(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Table a;
    materialTypeSetupQuery(a);
    a.saveCache = false;
    a.select();

auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
resp->addHeader("Access-Control-Allow-Origin", "*");
callback(resp);
}*/

    void User::allMetalPurity(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Table a;
    query_purity(a);
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    callback(resp);
}

void User::allOrder(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Table a;
    query_order(a);
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    callback(resp);
}

void User::allPartGroup(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Table a;
    query_part_group(a);
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    callback(resp);
}

void User::allPartType(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Table a;
    query_part_type(a);
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    callback(resp);
}

void User::allProduct(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Table a;
    query_product(a);
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    resp->addCookie("n", "o");
    callback(resp);
}


void User::allSale(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Table a;
    query_sale(a);
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    callback(resp);
}

void User::allTransaction(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Table a;
    query_transaction(a);
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    callback(resp);
}

void User::download(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    auto id = req->getParameter("path", "AdminMenu5.png");
//    fprintf(stdout, "%s\n", id.c_str());
//    fflush(stdout);
    auto new_path = "/home/kapili3/fileuploads/" + id;

    auto resp = HttpResponse::newFileResponse(new_path, "", CT_IMAGE_PNG);
    callback(resp);
}

void User::download_id(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback)
{
    auto id = req->getParameter("path", "AdminMenu5.png");
//    fprintf(stdout, "%s\n", id.c_str());
//    fflush(stdout);

auto c = req->getCookie("admin");
    pqxx::work txn{DD};
    try {
        auto sql = "SELECT name FROM product.post_attachment where id = $1";
        pqxx::result x = txn.exec_params(sql, id);
        if(x.size() != 0) {
            //         auto new_path = std::string("/home/kapili3/fileuploads/") + x[0][0].c_str();
            auto resp = HttpResponse::newFileResponse(x[0][0].c_str(), "", CT_IMAGE_PNG);
            callback(resp);
        } else {
            Json::Value ret;
            ret[0] = "404";
            Json::Value data;
            data[0] = 404;
            data[1] = 0;
            ret[1] = data;
            auto resp=HttpResponse::newHttpJsonResponse(data);
            resp->addCookie("power", "DDD");
            callback(resp);
        }
    } catch (const std::exception &e) {
        txn.abort();
        std::cerr << e.what() << std::endl;
        //simpleJsonResult(event_name, wsConnPtr, false, e.what());

    }


}
