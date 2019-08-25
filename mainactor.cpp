#include "mainactor.h"

#include <chrono>

#include "json.hpp"
#include "core/jsonfns.h"

#include "spdlog/spdlog.h"

#include "juseractor.h"
#include "jadminactor.h"
#include "museractor.h"
#include "madminactor.h"

#include "caf.h"

using std::chrono::seconds;

MainActor::MainActor(caf::actor_config &cfg) : caf::event_based_actor(cfg)
{
    set_error_handler([=]([[maybe_unused]]caf::error& err) {
        spdlog::info("Main Actor Error :");
    });
    set_down_handler([=](caf::down_msg& msg) {
        spdlog::info( "Main Actor Error Down Error :");
        spdlog::info(globalCAF.sys.render(msg.reason));
    });
    // If this exception error occur: server freeze.
    set_exception_handler([=](caf::scheduled_actor*, std::exception_ptr& eptr)-> caf::error {
        try {
            if (eptr) {
                std::rethrow_exception(eptr);
            }
        } catch(const std::exception& e) {
            spdlog::info( "\nMain Actor Exception Error : %s\n", e.what());
        }
        return caf::make_error(caf::pec::success); // This will not resume actor.
    });
    set_default_handler([=](scheduled_actor* ptr, caf::message_view& x) -> caf::result<caf::message> {
        spdlog::info( "\nunexpected message, I will Qui\n");
        CAF_LOG_WARNING("unexpected message, I will Quit" << CAF_ARG(x.content()));
        aout(ptr) << "*** unexpected message [id: " << ptr->id()
                  << ", name: " << ptr->name() << "]: "
                  << x.content().stringify()
                  << std::endl;
        return caf::sec::unexpected_message;
      });
}

MainActor::~MainActor()
{
}

caf::behavior MainActor::make_behavior()
{
      return {
        [this](run_atom, MainActorType actortype, const WebSocketConnectionPtr &wsConnPtr, std::string message, const WebSocketMessageType &type) -> caf::result<void>  {
              try{
                  passToUser(actortype, wsConnPtr, std::move(message), type);
          } catch (const std::exception &e) {
              std::cerr << e.what() << std::endl;
          }
         return {};
        },
          [this](exit_atom, const WebSocketConnectionPtr &wsConnPtr){
              auto it = actorMap.find(wsConnPtr) ;
              if (it == actorMap.end()) {
                  // not possible..
              } else {
                   caf::actor userActor = it->second;
                  request(userActor, caf::infinite, exit_atom::value);
                  demonitor(it->second);
                  actorMap.erase(it);
              }
          }
      };
}

void MainActor::passToUser(MainActorType actortype, const WebSocketConnectionPtr &wsConnPtr, std::string &&message, const WebSocketMessageType &type)
{
    // If key not found in map iterator to end is returned
    auto it = actorMap.find(wsConnPtr) ;
    if (it == actorMap.end()) {
        caf::actor userActor = spawn<JAdminActor>();
        monitor(userActor); // this will send message when it down
        request(userActor, caf::infinite, wsConnPtr, std::move(message), type);
        actorMap.insert({wsConnPtr, userActor});
    } else {
         caf::actor userActor = it->second;
        request(userActor, caf::infinite, wsConnPtr, std::move(message), type);
    }
}
