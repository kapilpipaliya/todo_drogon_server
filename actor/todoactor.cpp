
#include "./todoactor.h"

#include "./inc/todoservices.h"
#include "./timeservicehandle.h"
//#include "core/service/time/auth/user/login/Login.h"
#include "./timeroutes.h"
#include "core/service/time/account/login/account_Login.h"
#include "core/service/time/account/logout/account_Logout.h"
#include "core/service/time/account/registration/account_Registration.h"
#include "core/service/time/menu/Menu.h"
#include "core/service/time/admin/user/user/list/admin_user_user_List.h"
// auto_include_above
namespace superactor {
namespace todoactor {
/*
 * Todo Actor run() function added
 * Its not subclassed from baseactor class because batch support is breaked and
 * not needed.
 * */
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
    /*case drogon::WebSocketMessageType::Text: {
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
    }*/
    case drogon::WebSocketMessageType::Text:
    case drogon::WebSocketMessageType::Binary: {
      auto result = handleBinaryMessage(wsConnPtr, std::move(message));
      if (!result.is_null()) {
        websocket::WsFns::sendJson(wsConnPtr, result);
      }
      break;
    }
    default:
      break;
  }
}

void TodoActor::handleTextMessage(
    const drogon::WebSocketConnectionPtr &wsConnPtr, const nlohmann::json &in) {
  if (!in.is_array() || !in[0].is_array() || !in[0][0].is_number()) {
    LOG_DEBUG << "server_only_respond_number_on_event";
  }
  auto contx = wsConnPtr->getContext<websocket::todo::TodoContext>();
  auto evt = in[0][0].get<int>();
  if (evt == account_login) {
    // handleService<timeservice::auth::user::Login>(wsConnPtr, contx, in);
  }
  TimeServiceHandle t;
  t.runService(contx, in);
}

nlohmann::json TodoActor::handleBinaryMessage(
    const drogon::WebSocketConnectionPtr &wsConnPtr, std::string &&message) {
  nlohmann::json event;
  try {
    auto contx = wsConnPtr->getContext<websocket::todo::TodoContext>();
    /*
        std::vector<uint8_t> source(message.begin(), message.end());
        std::cout << int(source.at(0)) << std::endl;
        std::cout << int(source.at(1)) << std::endl;
        source.erase(source.begin());
        source.erase(source.begin());

        unsigned char buffer[message.length()];
        //memcpy(buffer, message.data(), message.length());
        std::copy(message.begin(), message.end(), buffer);
        */
    // remember that int8_t and uint8_t are 'fake' types. just aliases to char
    // and streams try to print chars as they were CHARS :D
    auto event1 = static_cast<int>(message.at(0));
    // please note event2 will not be printed on console.
    auto event2 = static_cast<uint8_t>(message.at(1));
    message.erase(message.begin());
    message.erase(message.begin());
    // clang-format off

    if (event1 == account_registration) {
      handleService<timeservice::account::Registration>(event1, event2, wsConnPtr, contx, std::move(message));
    }
    if (event1 == admin_user_user_list) {
      handleService<timeservice::admin::user::user::List>(event1, event2, wsConnPtr, contx, std::move(message));
    }
    if (event1 == menu) {
      handleService<timeservice::Menu>(event1, event2, wsConnPtr, contx, std::move(message));
    }
    // auto_event_above
    // clang-format on
    auto sqlSession =
        "SELECT event FROM music.temp_file_meta where session_id = $1";
    auto clientPtr = drogon::app().getDbClient("sce");
    // auto r = clientPtr->execSqlSync(sqlSession, c);
    /*if (!r.empty()) {
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
    }*/
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
