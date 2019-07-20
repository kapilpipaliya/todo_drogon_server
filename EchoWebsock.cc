#include "EchoWebsock.h"
#include <map>
#include <regex>

#include "core/tables/functions.h"
#include "core/tables/savefunctions.h"

std::map<std::string, std::function<void(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in)> > fns;
std::map<std::string, std::function<void(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, std::string &message )> > fns_bin;
#define m(s) "material_" s
#define e(s) "entity_" s
#define p(s) "product_" s
#define px(t) "save_" t "_data"
void EchoWebsock::defineFns()
{
    //fns.insert(std::pair<std::string, std::function<Json::Value()>>("accessory", accessory));
    //Inserts a new element in the map if its key is unique.

    // Public
    // Branch
    // Menu
    // Mfg
    // Payroll
    // Material (synced)
    CRUD(m("metal"), metal);
    CRUD(m("purity"), purity);
    CRUD(m("tone"), tone);
    CRUD(m("accessory"), accessory);

    CRUD(m("clarity"), clarity);
    CRUD(m("shape"), shape);
    CRUD(m("d_color"), d_color);
    CRUD(m("cs_color"), cs_color);
    getAllTheColumns(m("size"), query_size);
    CRUD(m("diamond_size"), diamond_size);
    CRUD(m("color_stone_size"), color_stone_size);

    // Account
    getAllTheColumns("account_heading", query_account_heading);
    getAllTheColumns("account", query_account);
    getAllTheColumns("order", query_order);
    getAllTheColumns("sale", query_sale);
    getAllTheColumns("transaction", query_transaction);
    // Entity
    CRUD(e("address_type"), address_type);
    CRUD(e("contact_type"), contact_type);
    CRUD(e("entity_type"), entity_type);
    CRUD(e("entity"), entity);

    // Setting
    getAllTheColumns("global_setting", query_global_setting);
    CRUD("setting_currency", currency);
    getAllTheColumns("log", query_log);
    // Part
    getAllTheColumns("part_categories", query_part_group);
    getAllTheColumns("part_type", query_part_type);
    // product:
    getAllTheColumns(p("option"), query_product_options);
    CRUD(p("product"), product);
    CRUD(p("post"), post);
    CRUD(p("category"), category);
    CRUD(p("tag"), tag);
    CRUD(p("shipping_class"), shipping_class);
    CRUD(p("setting_type"), setting_type);
    CRUD(p("certified_by"), certified_by);
    fns.emplace("get_product_attachment_data", get_product_attachment);
    fns.emplace("get_product_diamond_price_data", get_diamond_price);
    fns.emplace("get_product_cs_price_data", get_cs_price);
    fns.emplace("get_product_category_tree_data", get_product_category_tree_data);

    fns.emplace("admin_login", admin_login);
    fns.emplace("admin_logout", admin_logout);
    fns.emplace("is_admin_auth", is_admin_auth);

    fns.emplace(px("image_meta"), saveImageMeta); // Save Image meta on server temparary
    //Binary Handle Functions:
    fns_bin.emplace(px("product_attachment"), save_product_attachment);
}

void EchoWebsock::handleNewMessage(const WebSocketConnectionPtr& wsConnPtr, std::string &&message, const WebSocketMessageType &type)
{
    // It is very useful to keep a record of the connected clients, as it provides details with different data or send different messages to each one.

    //fprintf(stdout, "%s\n", message.c_str());
    //fflush(stdout);

    switch (type) {
    case WebSocketMessageType::Text: {
        Json::Reader reader;
        Json::Value valin;
        reader.parse(message,  valin);

        if (valin.type() != Json::ValueType::arrayValue) {
            return wsConnPtr->send("");
        }

        std::regex r("_data\\d*$");
        auto f = fns.find(std::regex_replace(valin[0].asString(), r, "_data"));
        if (f != fns.end()) {
            f->second(valin[0].asString(), wsConnPtr, valin[1]);
        } else {
            Json::Value jresult;
            jresult[0]=valin[0].asString();
            jresult[1]=Json::arrayValue;
            wsConnPtr->send(jresult.toStyledString());
        }

        break;
    }
    case WebSocketMessageType::Binary: {
        std::regex r("_data\\d*$");
        auto event_name_meta = getEventName(wsConnPtr);
        auto f = fns_bin.find(std::regex_replace(event_name_meta, r, "_data"));
        if (f != fns_bin.end()) {
            f->second(event_name_meta, wsConnPtr, message);
        }

        break;
    }
    }
}
void EchoWebsock::handleNewConnection(const HttpRequestPtr &req,const WebSocketConnectionPtr& wsConnPtr)
{

    // save the cookie in contex, because its not available on other handler
    LOG_DEBUG << "new websocket connection!\n";
    //auto &key=req->getHeader("Sec-WebSocket-Key");
    //LOG_DEBUG << key;

    processCookie(req, wsConnPtr);
//    LOG_DEBUG << req->getCookie("admin");
    for (auto i : req->cookies()) {
        printf("%s,%s", i.first.c_str(), i.second.c_str());
        fflush(stdout);

    }


    // create connection to the database and keep it open. Will Increase Performance.
}
void EchoWebsock::handleConnectionClosed(const WebSocketConnectionPtr& wsConnPtr) {
//    deleteSession(wsConnPtr);
}
// How to use any: https://github.com/an-tao/drogon/issues/126
