#include "mainactor.h"
#include "core/jsonfns.h"
#include <chrono>
using std::chrono::seconds;

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

#include "json.hpp"

#define REGISTER(s, T)\
    else if (in[0][1].get<std::string>()==s){\
    T p{};\
    auto r = p.handleEvent(in[0], 2, in[1]);\
    if(!r.is_null())\
    return r;\
    }

//https://github.com/gabime/spdlog
//Very fast, header-only/compiled, C++ logging library.
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"



MainActor::MainActor(caf::actor_config &cfg) : caf::event_based_actor(cfg)
{
    set_error_handler([=]([[maybe_unused]]caf::error& err) {
        fprintf(stdout, "\nMain Actor Error :\n");
        fflush(stdout);
    });

    //Actors can store a set of callbacks—usually implemented as lambda expressions—using either
    //behavior or message_handler. The former stores an optional timeout, while the latter is composable.

    /// Describes the behavior of an actor, i.e., provides a message
    /// handler and an optional timeout.
    running_job.assign(
                [=, this](run_atom, const WebSocketConnectionPtr &wsConnPtr, std::string message,
                const WebSocketMessageType &type) {
        blocking_run(wsConnPtr, std::move(message), type);
    }
    );
    fprintf(stdout, "Constructor:\n");
    fflush(stdout);
}

MainActor::~MainActor()
{
    fprintf(stdout, "\nDestructor:\n");
    fflush(stdout);
}
void MainActor::blocking_run(const WebSocketConnectionPtr &wsConnPtr, std::string &&message,
                             const WebSocketMessageType &type)
{
    switch (type) {
    case WebSocketMessageType::Text: {
        try
        {
            auto valin = json::parse(message);
            if (valin.is_array()){
                //                    fprintf(stdout, "\nJson In: ---- %s\n", valin.dump().c_str());
                //                    fflush(stdout);

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
                // fprintf(stdout, "%s", out.dump().c_str());
                // fflush(stdout);
                if(!out.empty()){
                    wsConnPtr->send(out.dump()); // This Sometimes skipped.
                } else {
                    nlohmann::json j =  "Message cant served: maybe not valid events in batch: " + message;
                    wsConnPtr->send(j.dump());
                }
                // fprintf(stdout, "\nJson out:\n");
                // fflush(stdout);
            } else {
                nlohmann::json j =  "Invalid Message only array handled: " + message;
                wsConnPtr->send(j.dump());
            }
        }
        catch (json::parse_error& e)
        {
            std::cout << "message: " << e.what() << '\n'
                      << "exception id: " << e.id << '\n'
                      << "byte position of error: " << e.byte << std::endl;
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
fprintf(stdout, "\nI Done:");
fflush(stdout);
}

caf::behavior MainActor::make_behavior()
{
    // start runnig
    //send(this, run_atom::value); cant send..
    // run the job when message arrive for it.
      return {
        [this](run_atom, const WebSocketConnectionPtr &wsConnPtr, std::string message, const WebSocketMessageType &type) -> caf::result<void>  {
         blocking_run(wsConnPtr, std::move(message), type);
         return {};
        }
    };
}

json MainActor::handleTextMessage(const WebSocketConnectionPtr &wsConnPtr, std::string &&message, json in)
{
    //    fprintf(stdout, "handle message:   -- %s", in.dump().c_str());
    //    fflush(stdout);
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
json MainActor::handleBinaryMessage(const WebSocketConnectionPtr &wsConnPtr, std::string &message)
{
    json event;
    try {
        auto c = getAdminContext(wsConnPtr);
        auto sqlSession = "SELECT event FROM user1.temp_image where session_id = $1";
        auto r = clientPtr->execSqlSync(sqlSession, c);

        if(r.size()!=0){

            // convert this to json
            //  json event_json;
            try
            {
                event = json::parse(r[0]["event"].c_str());
                //p.handleBinaryEvent creates new transaction.
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
                std::cout << "message: " << e.what() << '\n'
                          << "exception id: " << e.id << '\n'
                          << "byte position of error: " << e.byte << std::endl;
                nlohmann::json j =  std::string("cant parse json reason: ") + e.what() ;
                wsConnPtr->send(j.dump());
            }
        return Json::nullValue;
    }
    } catch (const std::exception &e) {
        
        std::cerr << e.what() << std::endl;
        json jresult;
        jresult[0] = event;
        jresult[1] = e.what();
        return jresult;
    }
}

NoCAF::NoCAF(const WebSocketConnectionPtr &wsConnPtr, std::string &&message, const WebSocketMessageType &type) :
    wsConnPtr(wsConnPtr), message(std::move(message)), type(type)
{

}

json NoCAF::handleTextMessage(json in)
{
    //    fprintf(stdout, "handle message:   -- %s", in.dump().c_str());
    //    fflush(stdout);
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

json NoCAF::handleBinaryMessage(const WebSocketConnectionPtr &, std::string &message)
{
    json event;
    try {
        auto c = getAdminContext(wsConnPtr);
        auto sqlSession = "SELECT event FROM user1.temp_image where session_id = $1";
        auto r = clientPtr->execSqlSync(sqlSession, c);

        if(r.size()!=0){

            // convert this to json
            //  json event_json;
            try
            {
                event = json::parse(r[0]["event"].c_str());
                 //p.handleBinaryEvent creates new transaction.

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
                    std::cout << "message: " << e.what() << '\n'
                              << "exception id: " << e.id << '\n'
                              << "byte position of error: " << e.byte << std::endl;
                    nlohmann::json j =  std::string("cant parse json reason: ") + e.what() ;
                    wsConnPtr->send(j.dump());
                }
        return Json::nullValue;
    }
    } catch (const std::exception &e) {

        std::cerr << e.what() << std::endl;
        json jresult;
        jresult[0] = event;
        jresult[1] = e.what();
        return jresult;
    }
}

void NoCAF::blocking_run()
{
    switch (type) {
    case WebSocketMessageType::Text: {
        try
        {
            auto valin = json::parse(message);
            if (valin.is_array()){
                //                    fprintf(stdout, "\nJson In: ---- %s\n", valin.dump().c_str());
                //                    fflush(stdout);

                json out(json::array());
                for (auto i : valin) {
                    // printJson(valin);
                    auto result  = handleTextMessage(i);
                    for (auto &i : result) {
                        if(!i.is_null()){
                            out.push_back(i);
                        }
                    }
                }
                // fprintf(stdout, "%s", out.dump().c_str());
                // fflush(stdout);
                if(!out.empty()){
                    wsConnPtr->send(out.dump()); // This Sometimes skipped.
                } else {
                    nlohmann::json j =  "Message cant served: maybe not valid events in batch: " + message;
                    wsConnPtr->send(j.dump());
                }
                // fprintf(stdout, "\nJson out:\n");
                // fflush(stdout);
            } else {
                nlohmann::json j =  "Invalid Message only array handled: " + message;
                wsConnPtr->send(j.dump());
            }
        }
        catch (json::parse_error& e)
        {
            std::cout << "message: " << e.what() << '\n'
                      << "exception id: " << e.id << '\n'
                      << "byte position of error: " << e.byte << std::endl;
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
