
#include "todoactor.h"

#include "inc/todoservices.h"

namespace superactor {
namespace todoactor {
TodoActor::TodoActor(caf::actor_config &cfg) : caf::event_based_actor(cfg) {}

caf::behavior TodoActor::make_behavior() {
  return {
      [this](const drogon::WebSocketConnectionPtr &wsConnPtr,
             std::string message,
             const drogon::WebSocketMessageType &type) -> caf::result<void> {
        run(wsConnPtr, std::move(message), type);
        return {};
      },
      [this](superactor::system::exit_atom) -> caf::result<void> {
        quit();
        return {};
      }};
}

void TodoActor::run(const drogon::WebSocketConnectionPtr &wsConnPtr,
                    std::string &&message,
                    const drogon::WebSocketMessageType &type) {
  switch (type) {
    case drogon::WebSocketMessageType::Text: {
      try {
        auto valin = nlohmann::json::parse(message);
        if (valin.is_array()) {
          for (const auto &i : valin) {
            handleTextMessage(wsConnPtr, i);
          }
        } else {
          nlohmann::json j = "Invalid Message only array handled: " + message;
          websocket::WsFns::sendJson(wsConnPtr, j);
        }
      } catch (nlohmann::json::parse_error &e) {
        LOG_DEBUG << "message: " << e.what();
        LOG_DEBUG << "exception id: " << e.id;
        LOG_DEBUG << "byte position of error:" << e.byte;
        nlohmann::json j = std::string("cant parse json reason: ") + e.what();
        websocket::WsFns::sendJson(wsConnPtr, j);
      }
      break;
    }
    case drogon::WebSocketMessageType::Binary: {
      auto result = handleBinaryMessage(wsConnPtr, message);
      if (!result.is_null()) {
        websocket::WsFns::sendJson(wsConnPtr, result);
      }
      break;
    }
    default:
      break;
  }
}

nlohmann::json TodoActor::handleTextMessage(
    const drogon::WebSocketConnectionPtr &wsConnPtr, const nlohmann::json &in) {
  if (!in.is_array() || !in[0].is_array() || !in[0][0].is_number()) {
    return nlohmann::json::array();
  }
  // auto contx = wsConnPtr->getContext<websocket::todo::TodoContext>();
  auto evt = in[0][0].get<int>();
  nlohmann::json r;
  //  if (evt == "auth") {
  //    r = handleService<todo::service::Auth>(contx, in);
  //  } else if (evt == 1) {
  //    r = handleService<todo::service::User>(contx, in);
  //  } else
  //  if (evt == 1) {
  //    r = handleService<todo::service::UI>(contx, in);
  //  } else if (evt == 2) {
  //    r = handleService<todo::service::Seed>(contx, in);
  //  } else
  if (evt == 3) {
    todo::service::DGraphSeed t;
    t.handleEvent(wsConnPtr, in[0], 1, in[1]);
  } else {
    r = nlohmann::json::array();
  }
  fflush(stdout);
  return r;
}

nlohmann::json TodoActor::handleBinaryMessage(
    const drogon::WebSocketConnectionPtr &wsConnPtr, std::string &message) {
  nlohmann::json event;
  try {
    auto contx = wsConnPtr->getContext<websocket::todo::TodoContext>();
    long c = contx->sessionId();
    auto sqlSession =
        "SELECT event FROM music.temp_file_meta where session_id = $1";
    auto clientPtr = drogon::app().getDbClient("sce");
    auto r = clientPtr->execSqlSync(sqlSession, c);
    if (!r.empty()) {
      try {
        event = nlohmann::json::parse(r[0]["event"].c_str());
        // p.handleBinaryEvent creates new transaction.

        if (event[0] == "song") {
          //          todo::Song p{contx};
          // auto r = p.handleBinaryEvent(event, 1, message);
          // if (!r.is_null()) return r;
          // temp:
          nlohmann::json j;
          return j;
        }
      } catch (nlohmann::json::parse_error &e) {
        LOG_DEBUG << "message: " << e.what();
        LOG_DEBUG << "exception id: " << e.id;
        LOG_DEBUG << "byte position of error:" << e.byte;
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

}  // namespace todoactor
}  // namespace superactor
