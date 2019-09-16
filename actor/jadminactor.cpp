
#include "jadminactor.h"

#include "jadminservices.h"
namespace superactor {
namespace jewelactor {
JAdminActor::JAdminActor(caf::actor_config &cfg)
    : caf::event_based_actor(cfg) {}

caf::behavior JAdminActor::make_behavior() {
  return {
      [this](const drogon::WebSocketConnectionPtr &wsConnPtr,
             std::string message,
             const drogon::WebSocketMessageType &type) -> caf::result<void> {
        blocking_run(wsConnPtr, std::move(message), type);
        return {};
      },
      [this](superactor::system::exit_atom) -> caf::result<void> {
        quit();
        return {};
      }};
}

nlohmann::json JAdminActor::handleTextMessage(
    const drogon::WebSocketConnectionPtr &wsConnPtr, const nlohmann::json &in) {
  try {
    if (!in.is_array()) {
      return nlohmann::json::array();
    }

    if constexpr (false) {
    }
    REGISTER("auth", jewel::service::Auth)
    REGISTER("user", jewel::service::User)
    REGISTER("account_type", jewel::service::AccountType)
    REGISTER("account", jewel::service::Account)
    REGISTER("account_heading", jewel::service::AccountHeading)
    REGISTER("journal_type", jewel::service::JournalType)
    REGISTER("txn", jewel::service::Txn)
    REGISTER("priority", jewel::service::Priority)

    REGISTER("node", jewel::service::Node)
    REGISTER("role", jewel::service::Role)
    REGISTER("task", jewel::service::Task)

    REGISTER("department_type", jewel::service::DepartmentType)
    REGISTER("department", jewel::service::Department)
    REGISTER("casting", jewel::service::Casting)
    REGISTER("wax_setting", jewel::service::WaxSetting)
    REGISTER("metal_issue", jewel::service::MetalIssue)
    REGISTER("MFG_txn", jewel::service::MfgTxn)
    REGISTER("refining", jewel::service::Refining)
    REGISTER("m_transfer", jewel::service::MTransfer)

    REGISTER("metal", jewel::service::Metal)
    REGISTER("purity", jewel::service::Purity)
    REGISTER("tone", jewel::service::Tone)
    REGISTER("accessory", jewel::service::Accessory)

    REGISTER("clarity", jewel::service::Clarity)
    REGISTER("shape", jewel::service::Shape)
    REGISTER("d_color", jewel::service::DColor)
    REGISTER("cs_color", jewel::service::CSColor)
    REGISTER("cs_type", jewel::service::CSType)
    REGISTER("size", jewel::service::Size)  // CRUD not required
    REGISTER("d_size", jewel::service::DSize)
    REGISTER("cs_size", jewel::service::CSSize)

    REGISTER("address_type", jewel::service::AddressType)
    REGISTER("contact_type", jewel::service::ContactType)
    REGISTER("entity_type", jewel::service::EntityType)
    REGISTER("entity", jewel::service::Entity)

    REGISTER("setting", jewel::service::Setting)
    REGISTER("currency", jewel::service::Currency)
    REGISTER("log", jewel::service::Log)
    REGISTER("support", jewel::service::Support)
    REGISTER("image_collection", jewel::service::ImageCollection)
    REGISTER("image", jewel::service::Image)
    REGISTER("payment_method", jewel::service::PaymentMethod)

    REGISTER("option", jewel::service::POption)  // CRUD Not required
    REGISTER("product", jewel::service::Product)
    REGISTER("post", jewel::service::Post1)
    REGISTER("category", jewel::service::PCategory)
    REGISTER("tag", jewel::service::Tag)
    REGISTER("shipping_class", jewel::service::PShippingClass)
    REGISTER("setting_type", jewel::service::SettingType)
    REGISTER("certified_by", jewel::service::CertifiedBy)
    REGISTER("policy", jewel::service::Policy)
    else {
      return nlohmann::json::array();
    }
    return nlohmann::json::array();
  } catch (const std::exception &e) {
    LOG_DEBUG << e.what();
    return nlohmann::json::array({{e.what()}});
    // throw; // This actor must not die.
  }
}

nlohmann::json JAdminActor::handleBinaryMessage(
    const drogon::WebSocketConnectionPtr &wsConnPtr, std::string &message) {
  nlohmann::json event;
  try {
    long c =
        wsConnPtr->getContext<websocket::jewel::JAdminContext>()->sessionId();
    auto sqlSession =
        "SELECT event FROM public.temp_image where session_id = $1";
    auto clientPtr = drogon::app().getDbClient("sce");
    auto r = clientPtr->execSqlSync(sqlSession, c);
    if (!r.empty()) {
      try {
        event = nlohmann::json::parse(r[0]["event"].c_str());
        // p.handleBinaryEvent creates new transaction.
        if (event[0] == "image") {
          auto contx = wsConnPtr->getContext<websocket::jewel::JAdminContext>();
          jewel::service::Auth p{contx};
          auto res = p.handleBinaryEvent(event, 1, message);
          if (!res.is_null()) {
            return res;
          }
        }
      } catch (nlohmann::json::parse_error &e) {
        LOG_DEBUG << "message: {}", e.what();
        LOG_DEBUG << "exception id: {}", e.id;
        LOG_DEBUG << "byte position of error:", e.byte;
        nlohmann::json j =
            std::string("cant parse json reason: ") + e.what() + event.dump();
        websocket::WsFns::sendJson(wsConnPtr, j);
      }
    }
  } catch (const std::exception &e) {
    LOG_DEBUG << e.what();
    nlohmann::json jresult;
    jresult[0] = event;
    jresult[1] = e.what();
    return jresult;
  }
  nlohmann::json ret;
  return ret;
}

}  // namespace jewelactor
}  // namespace superactor
