#include "juseractor.h"
#include "spdlogfix.h"

#include "../wscontroller/context/jusercontext.h"
#include "../wscontroller/wsfns.h"
#include "mainactortype.h"

#include "core/service/jadmin/account/account.h"
#include "core/service/jadmin/account/accountheading.h"
#include "core/service/jadmin/account/accounttype.h"
#include "core/service/jadmin/account/journaltype.h"
#include "core/service/jadmin/account/priority.h"
#include "core/service/jadmin/account/txn.h"

#include "core/service/jadmin/material/accessory.h"
#include "core/service/jadmin/material/metal.h"
#include "core/service/jadmin/material/purity.h"
#include "core/service/jadmin/material/tone.h"

#include "core/service/jadmin/material/clarity.h"
#include "core/service/jadmin/material/cscolor.h"
#include "core/service/jadmin/material/cssize.h"
#include "core/service/jadmin/material/cstype.h"
#include "core/service/jadmin/material/dcolor.h"
#include "core/service/jadmin/material/dsize.h"
#include "core/service/jadmin/material/shape.h"
#include "core/service/jadmin/material/size.h"  // CRUD not required

#include "core/service/jadmin/mfg/casting.h"
#include "core/service/jadmin/mfg/department.h"
#include "core/service/jadmin/mfg/departmenttype.h"
#include "core/service/jadmin/mfg/metalissue.h"
#include "core/service/jadmin/mfg/mfgtxn.h"
#include "core/service/jadmin/mfg/mtransfer.h"
#include "core/service/jadmin/mfg/refining.h"
#include "core/service/jadmin/mfg/waxsetting.h"

#include "core/service/jadmin/product/certifiedby.h"
#include "core/service/jadmin/product/pcategory.h"
#include "core/service/jadmin/product/policy.h"
#include "core/service/jadmin/product/poptions.h"  // CRUD not required
#include "core/service/jadmin/product/product.h"
#include "core/service/jadmin/product/pshippingclass.h"
#include "core/service/jadmin/product/settingtype.h"

#include "core/service/jadmin/entity/addresstype.h"
#include "core/service/jadmin/entity/contacttype.h"
#include "core/service/jadmin/entity/entity.h"
#include "core/service/jadmin/entity/entitytype.h"

#include "core/service/jadmin/menu/node.h"
#include "core/service/jadmin/menu/role.h"
#include "core/service/jadmin/menu/task.h"

#include "core/service/jadmin/post/post.h"
#include "core/service/jadmin/post/tag.h"

#include "core/service/jadmin/setting/currency.h"
#include "core/service/jadmin/setting/image.h"
#include "core/service/jadmin/setting/imagecollection.h"
#include "core/service/jadmin/setting/log.h"
#include "core/service/jadmin/setting/paymentmethod.h"
#include "core/service/jadmin/setting/setting.h"
#include "core/service/jadmin/setting/support.h"

#include "core/service/jadmin/class/auth.h"
#include "core/service/jadmin/class/user.h"

JUserActor::JUserActor(caf::actor_config &cfg) : caf::event_based_actor(cfg) {}

caf::behavior JUserActor::make_behavior() {
  return {
      [this](const drogon::WebSocketConnectionPtr &wsConnPtr,
             std::string message,
             const drogon::WebSocketMessageType &type) -> caf::result<void> {
        blocking_run(wsConnPtr, std::move(message), type);
        return {};
      },
      [this](exit_atom) -> caf::result<void> {
        quit();
        return {};
      }};
}
#define REGISTER(s, T)                                   \
  else if (in[0][0].get<std::string>() == (s)) {         \
    auto contx = wsConnPtr->getContext<JAdminContext>(); \
    T p{contx};                                          \
    auto r = p.handleEvent(in[0], 1, in[1]);             \
    if (!r.is_null()) return r;                          \
  }

nlohmann::json JUserActor::handleTextMessage(
    const drogon::WebSocketConnectionPtr &wsConnPtr, nlohmann::json in) {
  if (!in.is_array()) {
    return nlohmann::json::array();
  }

  if constexpr (false) {
  }
  REGISTER("auth", jadmin::Auth)
  REGISTER("user", jadmin::User)
  REGISTER("account_type", jadmin::AccountType)
  REGISTER("account", jadmin::Account)
  REGISTER("account_heading", jadmin::AccountHeading)
  REGISTER("journal_type", jadmin::JournalType)
  REGISTER("txn", jadmin::Txn)
  REGISTER("priority", jadmin::Priority)

  REGISTER("node", jadmin::Node)
  REGISTER("role", jadmin::Role)
  REGISTER("task", jadmin::Task)

  REGISTER("department_type", jadmin::DepartmentType)
  REGISTER("department", jadmin::Department)
  REGISTER("casting", jadmin::Casting)
  REGISTER("wax_setting", jadmin::WaxSetting)
  REGISTER("metal_issue", jadmin::MetalIssue)
  REGISTER("MFG_txn", jadmin::MfgTxn)
  REGISTER("refining", jadmin::Refining)
  REGISTER("m_transfer", jadmin::MTransfer)

  REGISTER("metal", jadmin::Metal)
  REGISTER("purity", jadmin::Purity)
  REGISTER("tone", jadmin::Tone)
  REGISTER("accessory", jadmin::Accessory)

  REGISTER("clarity", jadmin::Clarity)
  REGISTER("shape", jadmin::Shape)
  REGISTER("d_color", jadmin::DColor)
  REGISTER("cs_color", jadmin::CSColor)
  REGISTER("cs_type", jadmin::CSType)
  REGISTER("size", jadmin::Size)  // CRUD not required
  REGISTER("d_size", jadmin::DSize)
  REGISTER("cs_size", jadmin::CSSize)

  REGISTER("address_type", jadmin::AddressType)
  REGISTER("contact_type", jadmin::ContactType)
  REGISTER("entity_type", jadmin::EntityType)
  REGISTER("entity", jadmin::Entity)

  REGISTER("setting", jadmin::Setting)
  REGISTER("currency", jadmin::Currency)
  REGISTER("log", jadmin::Log)
  REGISTER("support", jadmin::Support)
  REGISTER("image_collection", jadmin::ImageCollection)
  REGISTER("image", jadmin::Image)
  REGISTER("payment_method", jadmin::PaymentMethod)

  REGISTER("option", jadmin::POption)  // CRUD Not required
  REGISTER("product", jadmin::Product)
  REGISTER("post", jadmin::Post1)
  REGISTER("category", jadmin::PCategory)
  REGISTER("tag", jadmin::Tag)
  REGISTER("shipping_class", jadmin::PShippingClass)
  REGISTER("setting_type", jadmin::SettingType)
  REGISTER("certified_by", jadmin::CertifiedBy)
  REGISTER("policy", jadmin::Policy)
  else {
    return nlohmann::json::array();
  }
  return nlohmann::json::array();
}

nlohmann::json JUserActor::handleBinaryMessage(
    const drogon::WebSocketConnectionPtr &wsConnPtr,
    std::string & /*message*/) {
  nlohmann::json event;
  try {
    long c = wsConnPtr->getContext<JUserContext>()->sessionId();
    auto sqlSession =
        "SELECT event FROM user1.temp_image where session_id = $1";
    auto clientPtr = drogon::app().getDbClient("sce");
    auto r = clientPtr->execSqlSync(sqlSession, c);
    if (!r.empty()) {
      try {
        event = nlohmann::json::parse(r[0]["event"].c_str());
        // p.handleBinaryEvent creates new transaction.
        if (event[0] == "image") {
          // auto contx = wsConnPtr->getContext<JUserContext>();
          // Auth p{contx};
          // auto res = p.handleBinaryEvent(event, 2, message);
          // if(!res.is_null()){
          //   return res;
          //}
        }
      } catch (nlohmann::json::parse_error &e) {
        SPDLOG_TRACE("message: {}", e.what());
        SPDLOG_TRACE("exception id: {}", e.id);
        SPDLOG_TRACE("byte position of error:", e.byte);
        nlohmann::json j =
            std::string("cant parse json reason: ") + e.what() + event.dump();
        WsFns::sendJson(wsConnPtr, j);
      }
    }
  } catch (const std::exception &e) {
    SPDLOG_TRACE(e.what());
    nlohmann::json jresult;
    jresult[0] = event;
    jresult[1] = e.what();
    return jresult;
  }
  nlohmann::json ret;
  return ret;
}
