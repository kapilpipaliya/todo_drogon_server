#include "demo_v1_User.h"


#include "core/tables/Accessory.h"
#include "core/tables/Account.h"
#include "core/tables/AccountHeading.h"
#include "core/tables/Color.h"
#include "core/tables/Entity.h"
#include "core/tables/GemClarity.h"
#include "core/tables/GemShape.h"
#include "core/tables/GemSize.h"
#include "core/tables/GemType.h"
#include "core/tables/GlobalSetting.h"
#include "core/tables/Log.h"
#include "core/tables/Material.h"
#include "core/tables/MaterialType.h"
#include "core/tables/MetalPurity.h"
#include "core/tables/Order.h"
#include "core/tables/PartGroup.h"
#include "core/tables/PartType.h"
#include "core/tables/Product.h"
#include "core/tables/RateOn.h"
#include "core/tables/Sale.h"
#include "core/tables/Transaction.h"


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


    Accessory a;
    bool ok = a.insertRow(material_id1, slug1, name1);

    Json::Value ret;
    if (!ok) {
        ret["result"]=2;
        ret["error"]=a.insertError;
    } else {
        ret["result"]=1;
    }
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
    Accessory a;
    a.init();
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    callback(resp);
}

void User::allAccount(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Account a;
    a.init();
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    callback(resp);
}

void User::allAccountHeading(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    AccountHeading a;
    a.init();
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    callback(resp);
}

void User::allColor(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Color a;
    a.init();
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    callback(resp);

}

void User::allEntity(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Entity a;
    a.init();
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    callback(resp);
}

void User::allGemClarity(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    GemClarity a;
    a.init();
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    callback(resp);
}

void User::allGemShape(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    GemShape a;
    a.init();
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    callback(resp);
}

void User::allGemSize(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    GemSize a;
    a.init();
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    callback(resp);
}

void User::allGemType(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    GemType a;
    a.init();
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    callback(resp);
}

void User::allGlobalSetting(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    GlobalSetting a;
    a.init();
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    callback(resp);
}

void User::allLog(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Log a;
    a.init();
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    callback(resp);
}

void User::allMaterial(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Material a;
    a.init();
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    callback(resp);
}

void User::allMaterialType(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    MaterialType a;
    a.init();
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    callback(resp);
}

void User::allMetalPurity(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    MetalPurity a;
    a.init();
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    callback(resp);
}

void User::allOrder(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Order a;
    a.init();
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    callback(resp);
}

void User::allPartGroup(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    PartGroup a;
    a.init();
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    callback(resp);
}

void User::allPartType(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    PartType a;
    a.init();
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    callback(resp);
}

void User::allProduct(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Product a;
    a.init();
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    callback(resp);
}

void User::allRateOn(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    RateOn a;
    a.init();
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    callback(resp);
}

void User::allSale(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Sale a;
    a.init();
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    callback(resp);
}

void User::allTransaction(const HttpRequestPtr &req, std::function<void (const HttpResponsePtr &)> &&callback) const
{
    Transaction a;
    a.init();
    a.saveCache = false;
    a.select();

    auto resp=HttpResponse::newHttpJsonResponse(a.getJsonData());
    resp->addHeader("Access-Control-Allow-Origin", "*");
    callback(resp);
}
