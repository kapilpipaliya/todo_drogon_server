#include "mainactor.h"

#include <chrono>

#include "json.hpp"
#include "wscontroller/wsfns.h"

#include "spdlogfix.h"

#include "jadminactor.h"
#include "juseractor.h"
#include "madminactor.h"
#include "todoactor.h"

#include "caf.h"

// using std::chrono::seconds;
namespace superactor {
MainActor::MainActor(caf::actor_config &cfg) : caf::event_based_actor(cfg) {
  set_error_handler([=]([[maybe_unused]] caf::error &err) {
    SPDLOG_TRACE("Main Actor Error :");
    SPDLOG_TRACE(superactor::globalCAF.getReasonString(err));
  });
  set_down_handler([=](caf::down_msg &msg) {
    SPDLOG_TRACE("Main Actor Error Down Error :");
    SPDLOG_TRACE(superactor::globalCAF.getReasonString(msg.reason));
  });
  // If this exception error occur: server freeze.
  set_exception_handler([=](caf::scheduled_actor *,
                            std::exception_ptr &eptr) -> caf::error {
    try {
      if (eptr) {
        std::rethrow_exception(eptr);
      }
    } catch (const std::exception &e) {
      SPDLOG_TRACE("Main Actor Exception Error : {}", e.what());
    }
    return caf::make_error(caf::pec::success);  // This will not resume actor.
  });
  set_default_handler([=](scheduled_actor *ptr,
                          caf::message_view &x) -> caf::result<caf::message> {
    SPDLOG_TRACE("unexpected message, I will Quit");
    CAF_LOG_WARNING("unexpected message, I will Quit" << CAF_ARG(x.content()));
    aout(ptr) << "*** unexpected message [id: " << ptr->id()
              << ", name: " << ptr->name() << "]: " << x.content().stringify()
              << std::endl;
    return caf::sec::unexpected_message;
  });
}

MainActor::~MainActor() = default;

caf::behavior MainActor::make_behavior() {
  return {
      [this](run_atom, MainActorType actortype,
             const drogon::WebSocketConnectionPtr &wsConnPtr,
             std::string message,
             const drogon::WebSocketMessageType &type) -> caf::result<void> {
        try {
          passToUser(actortype, wsConnPtr, std::move(message), type);
        } catch (const std::exception &e) {
          SPDLOG_TRACE(e.what());
        }
        return {};
      },
      [this](exit_atom, const drogon::WebSocketConnectionPtr &wsConnPtr) {
        auto it = actorMap.find(wsConnPtr);
        if (it == actorMap.end()) {
          // not possible..
        } else {
          caf::actor userActor = it->second;
          request(userActor, caf::infinite, exit_atom::value);
          demonitor(it->second);
          actorMap.erase(it);
        }
      }};
}

void MainActor::passToUser(MainActorType actortype,
                           const drogon::WebSocketConnectionPtr &wsConnPtr,
                           std::string &&message,
                           const drogon::WebSocketMessageType &type) {
  switch (actortype) {
    case MainActorType::JAdmin: {
      auto it = actorMap.find(wsConnPtr);
      if (it == actorMap.end()) {
        caf::actor userActor = spawn<JAdminActor>();
        monitor(userActor);  // this will send message when it down
        request(userActor, caf::infinite, wsConnPtr, std::move(message), type);
        actorMap.insert({wsConnPtr, userActor});
      } else {
        caf::actor userActor = it->second;
        request(userActor, caf::infinite, wsConnPtr, std::move(message), type);
      }

      break;
    }
    case MainActorType::JUser: {
      auto it = actorMap.find(wsConnPtr);
      if (it == actorMap.end()) {
        caf::actor userActor = spawn<JUserActor>();
        monitor(userActor);  // this will send message when it down
        request(userActor, caf::infinite, wsConnPtr, std::move(message), type);
        actorMap.insert({wsConnPtr, userActor});
      } else {
        caf::actor userActor = it->second;
        request(userActor, caf::infinite, wsConnPtr, std::move(message), type);
      }

      break;
    }
    case MainActorType::MAdmin: {
      auto it = actorMap.find(wsConnPtr);
      if (it == actorMap.end()) {
        caf::actor userActor = spawn<MAdminActor>();
        monitor(userActor);  // this will send message when it down
        request(userActor, caf::infinite, wsConnPtr, std::move(message), type);
        actorMap.insert({wsConnPtr, userActor});
      } else {
        caf::actor userActor = it->second;
        request(userActor, caf::infinite, wsConnPtr, std::move(message), type);
      }

      break;
    }
    case MainActorType::TODO: {
      auto it = actorMap.find(wsConnPtr);
      if (it == actorMap.end()) {
        caf::actor todoActor = spawn<TodoActor>();
        monitor(todoActor);  // this will send message when it down
        request(todoActor, caf::infinite, wsConnPtr, std::move(message), type);
        actorMap.insert({wsConnPtr, todoActor});
      } else {
        caf::actor todoActor = it->second;
        request(todoActor, caf::infinite, wsConnPtr, std::move(message), type);
      }

      break;
    }
    default:
      break;
  }
}
}  // namespace superactor
