#include "todoactor.h"
#include "../wscontroller/wsfns.h"
#include "mainactortype.h"
#include "spdlogfix.h"

#include "../wscontroller/context/todocontext.h"

#include "core/service/todo/class/auth.h"
#include "core/service/todo/class/ui.h"
#include "core/service/todo/class/user.h"

TodoActor::TodoActor(caf::actor_config &cfg) : caf::event_based_actor(cfg) {}

caf::behavior TodoActor::make_behavior() {
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

#define REGISTER(T, s)                                       \
  else if (in[0][0].get<std::string>() == (s)) {             \
    auto contx = wsConnPtr->getContext<todo::TodoContext>(); \
    T p{contx};                                              \
    auto r = p.handleEvent(in[0], 1, in[1]);                 \
    if (!r.is_null()) return r;                              \
  }

nlohmann::json TodoActor::handleTextMessage(
    const drogon::WebSocketConnectionPtr &wsConnPtr, nlohmann::json in) {
  try {
    if (!in.is_array()) {
      return nlohmann::json::array();
    }

    if constexpr (false) {
    }
    REGISTER(todo::Auth, "auth")
    REGISTER(todo::User, "user")
    REGISTER(todo::User, "users")
    REGISTER(todo::UI, "ui")
    //    REGISTER(madmin::CatalogLocal, "catalog_local")
    //    REGISTER(madmin::Song, "song")
    else {
      return nlohmann::json::array();
    }
    return nlohmann::json::array();
  } catch (const std::exception &e) {
    SPDLOG_TRACE(e.what());
    throw;
  }
}

nlohmann::json TodoActor::handleBinaryMessage(
    const drogon::WebSocketConnectionPtr &wsConnPtr, std::string &message) {
  nlohmann::json event;
  try {
    auto contx = wsConnPtr->getContext<todo::TodoContext>();
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
          //          madmin::Song p{contx};
          // auto r = p.handleBinaryEvent(event, 1, message);
          // if (!r.is_null()) return r;
          // temp:
          nlohmann::json j;
          return j;
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
