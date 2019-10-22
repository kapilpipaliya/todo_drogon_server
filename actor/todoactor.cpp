
#include "./todoactor.h"

#include "./timeservicehandle.h"
#include "context/todocontext.h"
#include "mainactortype.h"
#include "wsfns.h"
//#include "service/time/auth/user/login/Login.h"
#include "./timeroutes.h"
#include "service/time/account/login/account_Login.h"
#include "service/time/account/logout/account_Logout.h"
#include "service/time/account/registration/account_Registration.h"
#include "service/time/admin/user/user/list/admin_user_user_List.h"
#include "service/time/menu/Menu.h"
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
