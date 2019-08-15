#include "messagehandle.h"
#include "core/macro.h"
#include "core/jsonfns.h"

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

MessageHandle msgHandle; // Global Variable initialise

//https://github.com/gabime/spdlog
//Very fast, header-only/compiled, C++ logging library.
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

Json::Value MessageHandle::handleTextMessage(const WebSocketConnectionPtr &wsConnPtr, Json::Value in)
{
    if (in.type() != Json::ValueType::arrayValue) {
        return Json::arrayValue;
    }
    if constexpr (false){
    }
    REGISTER("auth", Auth)

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
        return Json::arrayValue;
    }
    return Json::arrayValue;
}
Json::Value MessageHandle::handleBinaryMessage(const WebSocketConnectionPtr &wsConnPtr, std::string &message)
{
   Json::Value event;
    pqxx::work txn{DD};
    try {
        auto c = getAdminContext(wsConnPtr);
        auto sqlSession = "SELECT event FROM user1.temp_image where session_id = $1";
        auto r = txn.exec_params(sqlSession, c);

        if(r.size()!=0){

            // convert this to json
           //  Json::Value event_json;
            std::stringstream txt;
            txt << r[0][0].c_str();
            Json::CharReaderBuilder rbuilder;
            rbuilder["collectComments"] = false;
            std::string errs;
            bool ok = Json::parseFromStream(rbuilder, txt, &event, &errs);
            txn.commit(); //p.handleBinaryEvent creates new transaction.
            if(ok){
                if constexpr (false){
                }
                else if (event[0].asString() == "image") {
                    Image p{wsConnPtr};
                    auto res = p.handleBinaryEvent(event, message);
                    if(!res.isNull()){
                        return res;
                    }
                }
            }
        }
        return Json::nullValue;
    } catch (const std::exception &e) {
        txn.abort();
        std::cerr << e.what() << std::endl;
        Json::Value jresult;
        jresult[0] = event;
        jresult[1] = e.what();
        return jresult;
    }
}