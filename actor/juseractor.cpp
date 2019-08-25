#include "juseractor.h"
#include "spdlog/spdlog.h"

#include "mainactortype.h"
#include "../wscontroller/context/jusercontext.h"

#include "core/service/auth/auth.h"

#include "core/service/account/account.h"
#include "core/service/account/accountheading.h"
#include "core/service/account/accounttype.h"
#include "core/service/account/journaltype.h"
#include "core/service/account/priority.h"
#include "core/service/account/txn.h"

#include "core/service/material/metal.h"
#include "core/service/material/purity.h"
#include "core/service/material/tone.h"
#include "core/service/material/accessory.h"

#include "core/service/material/clarity.h"
#include "core/service/material/shape.h"
#include "core/service/material/dcolor.h"
#include "core/service/material/cscolor.h"
#include "core/service/material/cstype.h"
#include "core/service/material/size.h" // CRUD not required
#include "core/service/material/dsize.h"
#include "core/service/material/cssize.h"

#include "core/service/mfg/casting.h"
#include "core/service/mfg/department.h"
#include "core/service/mfg/departmenttype.h"
#include "core/service/mfg/metalissue.h"
#include "core/service/mfg/mfgtxn.h"
#include "core/service/mfg/mtransfer.h"
#include "core/service/mfg/refining.h"
#include "core/service/mfg/waxsetting.h"

#include "core/service/product/poptions.h" // CRUD not required
#include "core/service/product/certifiedby.h"
#include "core/service/product/pcategory.h"
#include "core/service/product/policy.h"
#include "core/service/product/product.h"
#include "core/service/product/pshippingclass.h"
#include "core/service/product/settingtype.h"

#include "core/service/entity/addresstype.h"
#include "core/service/entity/contacttype.h"
#include "core/service/entity/entitytype.h"
#include "core/service/entity/entity.h"

#include "core/service/menu/node.h"
#include "core/service/menu/role.h"
#include "core/service/menu/task.h"

#include "core/service/post/post.h"
#include "core/service/post/tag.h"

#include "core/service/setting/currency.h"
#include "core/service/setting/imagecollection.h"
#include "core/service/setting/image.h"
#include "core/service/setting/log.h"
#include "core/service/setting/paymentmethod.h"
#include "core/service/setting/setting.h"
#include "core/service/setting/support.h"

#define REGISTER(s, T)\
    else if (in[0][1].get<std::string>()==s){\
    T p{};\
    auto r = p.handleEvent(in[0], 2, in[1]);\
    if(!r.is_null())\
    return r;\
    }

JUserActor::JUserActor(caf::actor_config &cfg) : caf::event_based_actor(cfg)
{

}

caf::behavior JUserActor::make_behavior()
{
    return  {
        [this](const WebSocketConnectionPtr &wsConnPtr, std::string message, const WebSocketMessageType &type)-> caf::result<void>{
            blocking_run(wsConnPtr, std::move(message), type);
            return {};
        },
        [this](exit_atom)-> caf::result<void>{
            quit();
            return {};
        }
    };
}

void JUserActor::blocking_run(const WebSocketConnectionPtr &wsConnPtr, std::string &&message, const WebSocketMessageType &type)
{
    switch (type) {
    case WebSocketMessageType::Text: {
        try
        {
            auto valin = json::parse(message);
            if (valin.is_array()){
                json out(json::array());
                for (auto i : valin) {
                    // printJson(valin);
                    auto result  = handleTextMessage(wsConnPtr, std::move(message), i);
                    for (auto &i : result) {
                        if(!i.is_null()){
                            out.push_back(i);
                        }
                    }
                }
                if(!out.empty()){
                    wsConnPtr->send(out.dump());
                } else {
                    nlohmann::json j =  "Message cant served: maybe not valid events in batch: " + message;
                    wsConnPtr->send(j.dump());
                }
            } else {
                nlohmann::json j =  "Invalid Message only array handled: " + message;
                wsConnPtr->send(j.dump());
            }
        }
        catch (json::parse_error& e)
        {
            spdlog::error("message: {}", e.what());
            spdlog::error("exception id: {}", e.id);
            spdlog::error("byte position of error:", e.byte);
            nlohmann::json j =  std::string("cant parse json reason: ") + e.what() ;
            wsConnPtr->send(j.dump());
        }
        break;
    }
    case WebSocketMessageType::Binary: {
        auto result  = handleBinaryMessage(wsConnPtr, message);
        if(!result.is_null()){
            wsConnPtr->send(result.dump());
        }
        break;
    }
    default:
        break;
    }
}

nlohmann::json JUserActor::handleTextMessage(const WebSocketConnectionPtr &wsConnPtr, std::string &&message, nlohmann::json in)
{
    if (!in.is_array()) {
        return json::array();
    }

    if (in[0][0].get<std::string>() == "legacy"){
        if constexpr (false){
        }
        else if (in[0][1].get<std::string>()=="auth"){
            Auth p{wsConnPtr};
            auto r = p.handleEvent(in[0], 2, in[1]);
            if(!r.is_null())
            return r;
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
            return json::array();
        }
    }
    return json::array();
}

nlohmann::json JUserActor::handleBinaryMessage(const WebSocketConnectionPtr &wsConnPtr, std::string &message)
{
    json event;
    try {
        long c = wsConnPtr->getContext<JUserContext>()->admin;
        auto sqlSession = "SELECT event FROM user1.temp_image where session_id = $1";
        auto clientPtr = drogon::app().getDbClient("sce");
        auto r = clientPtr->execSqlSync(sqlSession, c);
        if(r.size()!=0){
            try
            {
                event = json::parse(r[0]["event"].c_str());
                // p.handleBinaryEvent creates new transaction.
                if (event[0]=="legacy"){
                    if (event[1] == "image") {
                        Auth p{wsConnPtr};
                        auto res = p.handleBinaryEvent(event, 2, message);
                        if(!res.is_null()){
                            return res;
                        }
                    }
                }
            }
            catch (json::parse_error& e)
            {
                spdlog::error("message: {}", e.what());
                spdlog::error("exception id: {}", e.id);
                spdlog::error("byte position of error:", e.byte);
                nlohmann::json j =  std::string("cant parse json reason: ") + e.what() + event.dump();
                wsConnPtr->send(j.dump());
            }
        }
    } catch (const std::exception &e) {
        spdlog::error(e.what());
        json jresult;
        jresult[0] = event;
        jresult[1] = e.what();
        return jresult;
    }
    return Json::nullValue;
}