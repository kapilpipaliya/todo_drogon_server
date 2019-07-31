#include "EchoWebSocket.h"
#include <map>
#include <regex>
#include <string>

#include "wsfunctions.h"

#include "core/tables/macro.h"
#include "core/tables/query/accountquery.h"
#include "core/tables/query/entityquery.h"
#include "core/tables/query/materialquery.h"
#include "core/tables/query/menuquery.h"
#include "core/tables/query/mfgquery.h"
#include "core/tables/query/postquery.h"
#include "core/tables/query/productquery.h"
#include "core/tables/query/settingquery.h"

#include "core/tables/savedel/accountsave.h"
#include "core/tables/savedel/entitysave.h"
#include "core/tables/savedel/materialsave.h"
#include "core/tables/savedel/menusave.h"
#include "core/tables/savedel/mfgsave.h"
#include "core/tables/savedel/postsave.h"
#include "core/tables/savedel/productsave.h"
#include "core/tables/savedel/settingsave.h"

using namespace std::literals;

std::map<std::string, std::function<void(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr,
                                         Json::Value in)> > fns;
std::map<std::string, std::function<void(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr,
                                         std::string &message)> > fns_bin;
#define a(s) "account_" s
#define m(s) "material_" s
#define e(s) "entity_" s
#define p(s) "product_" s
#define px(t) "save_" t "_data"

void defineFns() {
    //fns.insert(std::pair<std::string, std::function<Json::Value()>>("accessory", accessory));
    //Inserts a new element in the map if its key is unique.

    // Account
    CRUD(a("account_type"), account_type)
    CRUD(a("account"), account)
    CRUD(a("account_heading"), account_heading)
    CRUD(a("journal_type"), journal_type)
    CRUD(a("txn"), txn)
    CRUD(a("priority"), priority)
    // Branch
    // Menu
    CRUD("menu_menu_node", menu_node)
    CRUD("menu_menu_role", menu_role)
    CRUD("menu_menu_task", menu_task)
    // Mfg
    CRUD("mfg_department_type", department_type)
    CRUD("mfg_department", department)
    CRUD("mfg_casting", casting)
    CRUD("mfg_wax_setting", wax_setting)
    CRUD("mfg_metal_issue", metal_issue)
    CRUD("mfg_mfg_txn", mfg_txn)
    CRUD("mfg_refining", refining)
    CRUD("mfg_m_transfer", m_transfer)
    // Payroll
    // Material (synced)
    CRUD(m("metal"), metal)
    CRUD(m("purity"), purity)
    CRUD(m("tone"), tone)
    CRUD(m("accessory"), accessory)

    CRUD(m("clarity"), clarity)
    CRUD(m("shape"), shape)
    CRUD(m("d_color"), d_color)
    CRUD(m("cs_color"), cs_color)
    CRUD(m("cs_type"), cs_type)
    getAllTheColumns(m("size"), query_size) // CRUD not required
    CRUD(m("diamond_size"), diamond_size)
    CRUD(m("color_stone_size"), color_stone_size)

    // Entity
    CRUD(e("address_type"), address_type)
    CRUD(e("contact_type"), contact_type)
    CRUD(e("entity_type"), entity_type)
    CRUD(e("entity"), entity)

    // Setting
    CRUD("setting_global_setting", global_setting)
    CRUD("setting_currency", currency)
    CRUD("setting_log", log)
    CRUD("setting_support", support)
    CRUD("setting_image_collection", image_collection)
    CRUD("setting_image", image)
    CRUD("setting_payment_method", payment_method)
    // Part
    // product:
    getAllTheColumns(p("option"), query_product_options)
    CRUD(p("product"), product)
    CRUD(p("post"), post)
    CRUD(p("category"), category)
    CRUD(p("tag"), tag)
    CRUD(p("shipping_class"), shipping_class)
    CRUD(p("setting_type"), setting_type)
    CRUD(p("certified_by"), certified_by)
    CRUD(p("policy"), policy)

    fns.emplace("get_product_attachment_data", get_product_attachment_data);
    fns.emplace("get_product_diamond_price_data", get_product_diamond_price_data);
    fns.emplace("get_product_cs_price_data", get_product_cs_price_data);
    fns.emplace("get_product_category_tree_data", get_product_category_tree_data);

    fns.emplace("admin_login", admin_login);
    fns.emplace("admin_logout", admin_logout);
    fns.emplace("is_admin_auth", is_admin_auth);
    fns.emplace("user_login", user_login);
    fns.emplace("user_logout", user_logout);
    fns.emplace("is_user_auth", is_user_auth);
    fns.emplace("user_register", user_register);
    fns.emplace("user_id", user_id);
    fns.emplace("checkout", user_checkout);

    fns.emplace(px("image_meta"), saveImageMeta); // Save Image meta on server temporary
    //Binary Handle Functions:
    fns_bin.emplace(px("setting_attachment"), save_setting_attachment);

    fns.emplace("get_setting_thumb_data", get_setting_thumb_data);
}

void findAndRun(const WebSocketConnectionPtr &wsConnPtr, Json::Value valin){
    std::regex r("_data\\d*$");
    auto f = fns.find(std::regex_replace(valin[0].asString(), r, "_data"));
    if (f != fns.end()) {
        f->second(valin[0].asString(), wsConnPtr, valin[1]);
    } else {
        Json::Value jresult;
        jresult[0] = valin[0].asString();
        jresult[1] = Json::arrayValue;
        wsConnPtr->send(jresult.toStyledString());
    }
}

void EchoWebSocket::handleNewMessage(const WebSocketConnectionPtr &wsConnPtr, std::string &&message,
                                   const WebSocketMessageType &type) {
    // It is very useful to keep a record of the connected clients, as it provides details with different data or send different messages to each one.

    // fprintf(stdout, "%s\n", message.c_str());
    // fflush(stdout);

    switch (type) {
        case WebSocketMessageType::Text: {
            Json::Reader reader;
            Json::Value valin;
            reader.parse(message, valin);

            if (valin.type() != Json::ValueType::arrayValue) {
                return wsConnPtr->send("");
            }
            if (valin[0].asString().compare(std::string("batch")) == 0){
                for (auto i : valin) {
                    findAndRun(wsConnPtr, i);
                }
            } else {
                findAndRun(wsConnPtr, valin);
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

void EchoWebSocket::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr) {

    // save the cookie in contex, because its not available on other handler
    LOG_DEBUG << "new websocket connection!\n";
    //auto &key=req->getHeader("Sec-WebSocket-Key");
    //LOG_DEBUG << key;

    std::shared_ptr<std::map<std::string, std::vector<int> >> k(new std::map<std::string, std::vector<int> >);

    //k["foo"].insert(...)
    k->insert(std::pair<std::string, std::vector<int> >("admin"s, {0}));
    k->insert(std::pair<std::string, std::vector<int> >("user"s, {0}));
//    k->at("admin"s).push_back(0);
//    k["user"s].push_back(5);
    wsConnPtr->setContext(k);
    auto adminContext = generateContext(req, wsConnPtr, "admin");
    setAdminContext(wsConnPtr, adminContext);
    auto userContext = generateContext(req, wsConnPtr, "user");
    setUserContext(wsConnPtr, userContext);
    //    LOG_DEBUG << req->getCookie("admin");
    for (auto i : req->cookies()) {
        printf("%s,%s", i.first.c_str(), i.second.c_str());
        fflush(stdout);
    }
    // create connection to the database and keep it open. Will Increase Performance.
}

void EchoWebSocket::handleConnectionClosed(const WebSocketConnectionPtr &wsConnPtr) {
}
// How to use any: https://github.com/an-tao/drogon/issues/126

