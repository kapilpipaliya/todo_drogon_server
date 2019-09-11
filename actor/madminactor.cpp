#include "madminactor.h"
#include "../wscontroller/wsfns.h"
#include "mainactortype.h"
#include "spdlogfix.h"

#include "../wscontroller/context/madmincontext.h"

#include "inc/madminservices.h"

MAdminActor::MAdminActor(caf::actor_config &cfg)
    : caf::event_based_actor(cfg) {}

caf::behavior MAdminActor::make_behavior() {
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

template <typename T>
nlohmann::json handleService(std::shared_ptr<MAdminContext> contx,
                             nlohmann::json in) {
  try {
    T p{contx};
    auto r = p.handleEvent(in[0], 1, in[1]);
    if (!r.is_null()) return r;
    return nlohmann::json::array();
  } catch (const std::exception &e) {
    SPDLOG_TRACE(e.what());
    return nlohmann::json::array({{e.what()}});
  }
}

nlohmann::json MAdminActor::handleTextMessage(
    const drogon::WebSocketConnectionPtr &wsConnPtr, nlohmann::json in) {
  if (!in.is_array() || !in[0].is_array() || !in[0][0].is_string()) {
    return nlohmann::json::array();
  }
  auto contx = wsConnPtr->getContext<MAdminContext>();
  auto evt = in[0][0].get<std::string>();
  if (evt == "auth") {
    return handleService<madmin::Auth>(contx, in);
  } else if (evt == "user" || evt == "users") {
    return handleService<madmin::User>(contx, in);
  } else if (evt == "ui") {
    return handleService<madmin::UI>(contx, in);
  } else if (evt == "catalog_local") {
    return handleService<madmin::CatalogLocal>(contx, in);
  } else if (evt == "song") {
    return handleService<madmin::Song>(contx, in);
  } else {
    return nlohmann::json::array();
  }
}

nlohmann::json MAdminActor::handleBinaryMessage(
    const drogon::WebSocketConnectionPtr &wsConnPtr, std::string &message) {
  nlohmann::json event;
  try {
    auto contx = wsConnPtr->getContext<MAdminContext>();
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
          madmin::Song p{contx};
          auto r = p.handleBinaryEvent(event, 1, message);
          if (!r.is_null()) return r;
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
