
#include "juseractor.h"

#include "inc/juserervices.h"
namespace superactor {
namespace juseractor {
JUserActor::JUserActor(caf::actor_config &cfg) : caf::event_based_actor(cfg) {}

caf::behavior JUserActor::make_behavior() {
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

nlohmann::json JUserActor::handleTextMessage(
    const drogon::WebSocketConnectionPtr &wsConnPtr, const nlohmann::json &in) {
  try {
    if (!in.is_array()) {
      return nlohmann::json::array();
    }

    if constexpr (false) {
    }
    REGISTER("auth", jadmin::service::Auth)
    REGISTER("user", jadmin::service::User)
    REGISTER("account_type", jadmin::service::AccountType)
    REGISTER("account", jadmin::service::Account)
    REGISTER("account_heading", jadmin::service::AccountHeading)
    REGISTER("journal_type", jadmin::service::JournalType)
    REGISTER("txn", jadmin::service::Txn)
    REGISTER("priority", jadmin::service::Priority)

    REGISTER("node", jadmin::service::Node)
    REGISTER("role", jadmin::service::Role)
    REGISTER("task", jadmin::service::Task)

    REGISTER("department_type", jadmin::service::DepartmentType)
    REGISTER("department", jadmin::service::Department)
    REGISTER("casting", jadmin::service::Casting)
    REGISTER("wax_setting", jadmin::service::WaxSetting)
    REGISTER("metal_issue", jadmin::service::MetalIssue)
    REGISTER("MFG_txn", jadmin::service::MfgTxn)
    REGISTER("refining", jadmin::service::Refining)
    REGISTER("m_transfer", jadmin::service::MTransfer)

    REGISTER("metal", jadmin::service::Metal)
    REGISTER("purity", jadmin::service::Purity)
    REGISTER("tone", jadmin::service::Tone)
    REGISTER("accessory", jadmin::service::Accessory)

    REGISTER("clarity", jadmin::service::Clarity)
    REGISTER("shape", jadmin::service::Shape)
    REGISTER("d_color", jadmin::service::DColor)
    REGISTER("cs_color", jadmin::service::CSColor)
    REGISTER("cs_type", jadmin::service::CSType)
    REGISTER("size", jadmin::service::Size)  // CRUD not required
    REGISTER("d_size", jadmin::service::DSize)
    REGISTER("cs_size", jadmin::service::CSSize)

    REGISTER("address_type", jadmin::service::AddressType)
    REGISTER("contact_type", jadmin::service::ContactType)
    REGISTER("entity_type", jadmin::service::EntityType)
    REGISTER("entity", jadmin::service::Entity)

    REGISTER("setting", jadmin::service::Setting)
    REGISTER("currency", jadmin::service::Currency)
    REGISTER("log", jadmin::service::Log)
    REGISTER("support", jadmin::service::Support)
    REGISTER("image_collection", jadmin::service::ImageCollection)
    REGISTER("image", jadmin::service::Image)
    REGISTER("payment_method", jadmin::service::PaymentMethod)

    REGISTER("option", jadmin::service::POption)  // CRUD Not required
    REGISTER("product", jadmin::service::Product)
    REGISTER("post", jadmin::service::Post1)
    REGISTER("category", jadmin::service::PCategory)
    REGISTER("tag", jadmin::service::Tag)
    REGISTER("shipping_class", jadmin::service::PShippingClass)
    REGISTER("setting_type", jadmin::service::SettingType)
    REGISTER("certified_by", jadmin::service::CertifiedBy)
    REGISTER("policy", jadmin::service::Policy)
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

nlohmann::json JUserActor::handleBinaryMessage(
    const drogon::WebSocketConnectionPtr &wsConnPtr, std::string &message) {
  nlohmann::json event;
  try {
    long c =
        wsConnPtr->getContext<websocket::juser::JUserContext>()->sessionId();
    auto sqlSession =
        "SELECT event FROM public.temp_image where session_id = $1";
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
        websocket::WsFns::sendJson(wsConnPtr, j);
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

}  // namespace juseractor
}  // namespace superactor
