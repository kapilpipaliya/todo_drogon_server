#include "mainactor.h"

#include <chrono>

#include "caf.h"
#include "jadminactor.h"
#include "json.hpp"
#include "madminactor.h"
#include "myactor.h"
#include "todoactor.h"
#include "wscontroller/wsfns.h"

// using std::chrono::seconds;
namespace superactor {
namespace system {
MainActor::MainActor(caf::actor_config &cfg) : caf::event_based_actor(cfg) {
  set_error_handler([=]([[maybe_unused]] caf::error &err) {
    LOG_DEBUG << "Main Actor Error :";
    LOG_DEBUG << superactor::system::globalCAF.getReasonString(err);
  });
  set_down_handler([=](caf::down_msg &msg) {
    LOG_DEBUG << "Main Actor Error Down Error :";
    LOG_DEBUG << superactor::system::globalCAF.getReasonString(msg.reason);
  });
  // If this exception error occur: server freeze.
  set_exception_handler([=](caf::scheduled_actor *,
                            std::exception_ptr &eptr) -> caf::error {
    try {
      if (eptr) {
        std::rethrow_exception(eptr);
      }
    } catch (const std::exception &e) {
      LOG_DEBUG << "Main Actor Exception Error : {}", e.what();
    }
    return caf::make_error(caf::pec::success);  // This will not resume actor.
  });
  set_default_handler([=](scheduled_actor *ptr,
                          caf::message_view &x) -> caf::result<caf::message> {
    LOG_DEBUG << "unexpected message, I will Quit";
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
          LOG_DEBUG << e.what();
        }
        return {};
      },
      [this](superactor::system::exit_atom,
             const drogon::WebSocketConnectionPtr &wsConnPtr) {
        auto it = actorMap.find(wsConnPtr);
        if (it == actorMap.end()) {
          // not possible..
        } else {
          caf::actor userActor = it->second;
          request(userActor, caf::infinite,
                  superactor::system::exit_atom::value);
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
    case MainActorType::Jewel: {
      auto it = actorMap.find(wsConnPtr);
      if (it == actorMap.end()) {
        caf::actor userActor = spawn<jewelactor::JAdminActor>();
        monitor(userActor);  // this will send message when it down
        request(userActor, caf::infinite, wsConnPtr, std::move(message), type);
        actorMap.insert({wsConnPtr, userActor});
      } else {
        caf::actor userActor = it->second;
        request(userActor, caf::infinite, wsConnPtr, std::move(message), type);
      }

      break;
    }
    case MainActorType::Music: {
      auto it = actorMap.find(wsConnPtr);
      if (it == actorMap.end()) {
        caf::actor userActor = spawn<musicactor::MAdminActor>();
        monitor(userActor);  // this will send message when it down
        request(userActor, caf::infinite, wsConnPtr, std::move(message), type);
        actorMap.insert({wsConnPtr, userActor});
      } else {
        caf::actor userActor = it->second;
        request(userActor, caf::infinite, wsConnPtr, std::move(message), type);
      }

      break;
    }
    case MainActorType::Todo: {
      auto it = actorMap.find(wsConnPtr);
      if (it == actorMap.end()) {
        caf::actor todoActor = spawn<todoactor::TodoActor>();
        monitor(todoActor);  // this will send message when it down
        request(todoActor, caf::infinite, wsConnPtr, std::move(message), type);
        actorMap.insert({wsConnPtr, todoActor});
      } else {
        caf::actor todoActor = it->second;
        request(todoActor, caf::infinite, wsConnPtr, std::move(message), type);
      }

      break;
    }
    case MainActorType::My: {
      auto it = actorMap.find(wsConnPtr);
      if (it == actorMap.end()) {
        caf::actor myActor = spawn<myactor::MyActor>();
        monitor(myActor);  // this will send message when it down
        request(myActor, caf::infinite, wsConnPtr, std::move(message), type);
        actorMap.insert({wsConnPtr, myActor});
      } else {
        caf::actor todoActor = it->second;
        request(todoActor, caf::infinite, wsConnPtr, std::move(message), type);
      }

      break;
    }
  }
}
}  // namespace system
}  // namespace superactor
