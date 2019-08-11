#include "EchoWebSocket.h"
#include <map>
#include <regex>
#include <string>

#include "wsfunctions.h"

#include "core/tables/macro.h"

#include "core/tables/service/account/account.h"
#include "core/tables/service/account/accountheading.h"
#include "core/tables/service/account/accounttype.h"
#include "core/tables/service/account/journaltype.h"
#include "core/tables/service/account/priority.h"
#include "core/tables/service/account/txn.h"

#include "core/tables/service/material/metal.h"
#include "core/tables/service/material/purity.h"
#include "core/tables/service/material/tone.h"
#include "core/tables/service/material/accessory.h"

#include "core/tables/service/material/clarity.h"
#include "core/tables/service/material/shape.h"
#include "core/tables/service/material/dcolor.h"
#include "core/tables/service/material/cscolor.h"
#include "core/tables/service/material/cstype.h"
#include "core/tables/service/material/size.h" // CRUD not required
#include "core/tables/service/material/dsize.h"
#include "core/tables/service/material/cssize.h"

#include "core/tables/service/mfg/casting.h"
#include "core/tables/service/mfg/department.h"
#include "core/tables/service/mfg/departmenttype.h"
#include "core/tables/service/mfg/metalissue.h"
#include "core/tables/service/mfg/mfgtxn.h"
#include "core/tables/service/mfg/mtransfer.h"
#include "core/tables/service/mfg/refining.h"
#include "core/tables/service/mfg/waxsetting.h"

#include "core/tables/service/product/poptions.h" // CRUD not required
#include "core/tables/service/product/certifiedby.h"
#include "core/tables/service/product/pcategory.h"
#include "core/tables/service/product/policy.h"
#include "core/tables/service/product/product.h"
#include "core/tables/service/product/pshippingclass.h"
#include "core/tables/service/product/settingtype.h"

#include "core/tables/service/entity/addresstype.h"
#include "core/tables/service/entity/contacttype.h"
#include "core/tables/service/entity/entitytype.h"
#include "core/tables/service/entity/entity.h"

#include "core/tables/service/menu/node.h"
#include "core/tables/service/menu/role.h"
#include "core/tables/service/menu/task.h"

#include "core/tables/service/post/post.h"
#include "core/tables/service/post/tag.h"

#include "core/tables/service/setting/currency.h"
#include "core/tables/service/setting/imagecollection.h"
#include "core/tables/service/setting/image.h"
#include "core/tables/service/setting/log.h"
#include "core/tables/service/setting/paymentmethod.h"
#include "core/tables/service/setting/setting.h"
#include "core/tables/service/setting/support.h"




#include "core/tables/savedel/accountsave.h"
#include "core/tables/savedel/entitysave.h"
#include "core/tables/savedel/materialsave.h"
#include "core/tables/savedel/menusave.h"
#include "core/tables/savedel/mfgsave.h"
#include "core/tables/savedel/postsave.h"
#include "core/tables/savedel/productsave.h"
#include "core/tables/savedel/settingsave.h"



using namespace std::literals;

std::map<std::string, std::function<Json::Value(const std::string &event1, const std::string &event2, const std::string &no, const WebSocketConnectionPtr &wsConnPtr,
                                         Json::Value in)> > fns;
std::map<std::string, std::function<Json::Value(const std::string &event1, const std::string &event2, const std::string &no, const WebSocketConnectionPtr &wsConnPtr,
                                         std::string &message)> > fns_bin;
#define a(s) "account_" s
#define m(s) "material_" s
#define e(s) "entity_" s
#define p(s) "product_" s
#define px(t) "save_" t "_data"

void defineFns() {
    //fns.insert(std::pair<std::string, std::function<Json::Value()>>("accessory", accessory));
    //Inserts a new element in the map if its key is unique.

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

Json::Value findAndRun(const WebSocketConnectionPtr &wsConnPtr, Json::Value valin){
//    std::regex r("_data\\d*$");
//    std::regex_replace(valin[0].asString(), r, "_data")
auto event1 = valin[0].asString();
auto event2 = valin[1].asString();
auto no = valin[2].asString();
auto f = fns.find(event1 + (event2.empty() ? "" : "_") + event2);
    if (f != fns.end()) {
        //std::printf("%s", valin[0].asString().c_str());
        //fflush(stdout);
        return f->second(event1, event2, no, wsConnPtr, valin[3]);
    } else {
//        Json::Value jresult;
//        jresult[0] = valin[0].asString();
//        jresult[1] = Json::arrayValue;
//        jresult[2] = Json::arrayValue;
//        jresult[3] = Json::arrayValue;
//        return jresult;
        return Json::arrayValue;
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

            auto event1 = valin[0].asString();
            auto event2 = valin[1].asString();
            auto no = valin[2].asString();

            if(false){
            }
            REGISTER("account_type", AccountType)
            REGISTER("account", Account)
            REGISTER("account_heading", AccountHeading)
            REGISTER("journal_type", JournalType)
            REGISTER("txn", Txn)
            REGISTER("priority", Priority)

            REGISTER("node", Node)
            REGISTER("role", Role)
            REGISTER("task", Task)

            REGISTER("department_type", DepartmentType)
            REGISTER("department", Department)
            REGISTER("casting", Casting)
            REGISTER("wax_setting", WaxSetting)
            REGISTER("metal_issue", MetalIssue)
            REGISTER("MFG_txn", MfgTxn)
            REGISTER("refining", Refining)
            REGISTER("m_transfer", MTransfer)

            REGISTER("metal", Metal)
            REGISTER("purity", Purity)
            REGISTER("tone", Tone)
            REGISTER("accessory", Accessory)

            REGISTER("clarity", Clarity)
            REGISTER("shape", Shape)
            REGISTER("d_color", DColor)
            REGISTER("cs_color", CSColor)
            REGISTER("cs_type", CSType)
            REGISTER("size", Size) // CRUD not required
            REGISTER("d_size", DSize)
            REGISTER("cs_size", CSSize)

            REGISTER("address_type", AddressType)
            REGISTER("contact_type", ContactType)
            REGISTER("entity_type", EntityType)
            REGISTER("entity", Entity)

            REGISTER("setting", Setting)
            REGISTER("currency", Currency)
            REGISTER("log", Log)
            REGISTER("support", Support)
            REGISTER("image_collection", ImageCollection)
            REGISTER("image", Image)
            REGISTER("payment_method", PaymentMethod)

            REGISTER("option", POption) //CRUD Not required
            REGISTER("product", Product)
            REGISTER("post", Post1)
            REGISTER("category", PCategory)
            REGISTER("tag", Tag)
            REGISTER("shipping_class", PShippingClass)
            REGISTER("setting_type", SettingType)
            REGISTER("certified_by", CertifiedBy)
            REGISTER("policy", Policy)

            else {
                auto r = findAndRun(wsConnPtr, valin);
                if(!r.isNull()){
                    wsConnPtr->send(r.toStyledString());
                }
            }


            /*
            if (valin[0].asString().compare(std::string("batch")) == 0){
                Json::Value out(Json::arrayValue);
                for (auto i : valin) {
                    out.append(findAndRun(wsConnPtr, i));
                }
                wsConnPtr->send(out.toStyledString());
            } else {
                auto r = findAndRun(wsConnPtr, valin);
                if(!r.isNull()){
                    wsConnPtr->send(r.toStyledString());
                }
            }
            */


            break;
        }
        case WebSocketMessageType::Binary: {
            std::regex r("_data\\d*$");
            auto event_name_meta = getEventName(wsConnPtr);
            auto f = fns_bin.find(std::regex_replace(event_name_meta, r, "_data"));
            if (f != fns_bin.end()) {
                auto j = f->second(event_name_meta,"", "", wsConnPtr, message);
                wsConnPtr->send(j.toStyledString());
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
    // LOG_DEBUG << req->getCookie("admin");
    for (auto i : req->cookies()) {
        printf("%s,%s", i.first.c_str(), i.second.c_str());
        fflush(stdout);
    }
    // create connection to the database and keep it open. Will Increase Performance.
}

void EchoWebSocket::handleConnectionClosed(const WebSocketConnectionPtr &wsConnPtr) {
}
// How to use any: https://github.com/an-tao/drogon/issues/126

