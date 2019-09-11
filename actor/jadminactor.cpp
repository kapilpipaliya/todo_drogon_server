
#include "jadminactor.h"

#include "jadminservices.h"
#include "jadminservices.h"
JAdminActor::JAdminActor(caf::actor_config & cfg)
    : caf::event_based_actor(cfg) {
}

caf::behavior JAdminActor::make_behavior() {
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

nlohmann::json JAdminActor::handleTextMessage(const drogon::WebSocketConnectionPtr & wsConnPtr, const nlohmann::json & in) {
  try {
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
  } catch (const std::exception &e) {
    SPDLOG_TRACE(e.what());
    return nlohmann::json::array({{e.what()}});
    // throw; // This actor must not die.
  }
}

nlohmann::json JAdminActor::handleBinaryMessage(const drogon::WebSocketConnectionPtr & wsConnPtr, std::string & message) {
  nlohmann::json event;
  try {
    long c = wsConnPtr->getContext<JAdminContext>()->sessionId();
    auto sqlSession =
        "SELECT event FROM user1.temp_image where session_id = $1";
    auto clientPtr = drogon::app().getDbClient("sce");
    auto r = clientPtr->execSqlSync(sqlSession, c);
    if (!r.empty()) {
      try {
        event = nlohmann::json::parse(r[0]["event"].c_str());
        // p.handleBinaryEvent creates new transaction.
        if (event[0] == "image") {
          auto contx = wsConnPtr->getContext<JAdminContext>();
          jadmin::Auth p{contx};
          auto res = p.handleBinaryEvent(event, 1, message);
          if (!res.is_null()) {
            return res;
          }
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

