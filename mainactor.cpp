#include "mainactor.h"
#include "core/jsonfns.h"
#include <chrono>
using std::chrono::seconds;

#include "json.hpp"

//https://github.com/gabime/spdlog
//Very fast, header-only/compiled, C++ logging library.
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"

#include "juseractor.h"
#include "jadminactor.h"
#include "museractor.h"
#include "madminactor.h"

#include "caf.h"

MainActor::MainActor(caf::actor_config &cfg) : caf::event_based_actor(cfg)
{
    set_error_handler([=]([[maybe_unused]]caf::error& err) {
        fprintf(stdout, "\nMain Actor Error :\n");
        fflush(stdout);
    });
    set_down_handler([=](caf::down_msg& msg) {
        fprintf(stdout, "\nMain Actor Error Down Error :\n");
        std::cerr <<globalCAF.sys.render(msg.reason);
        fflush(stdout);
    });
    // If this exception error occur: server freeze.
    set_exception_handler([=](caf::scheduled_actor*, std::exception_ptr& eptr)-> caf::error {
        try {
            if (eptr) {
                std::rethrow_exception(eptr);
            }
        } catch(const std::exception& e) {
            fprintf(stdout, "\nMain Actor Exception Error : %s\n", e.what());
            fflush(stdout);
        }
        return caf::make_error(caf::pec::success);
    });
    set_default_handler([=](scheduled_actor* ptr, caf::message_view& x) -> caf::result<caf::message> {
        fprintf(stdout, "\nunexpected message, I will Qui\n");
        fflush(stdout);
        CAF_LOG_WARNING("unexpected message, I will Quit" << CAF_ARG(x.content()));
        aout(ptr) << "*** unexpected message [id: " << ptr->id()
                  << ", name: " << ptr->name() << "]: "
                  << x.content().stringify()
                  << std::endl;
        return caf::sec::unexpected_message;
      });
    fprintf(stdout, "Constructor:\n");
    fflush(stdout);
}

MainActor::~MainActor()
{
    fprintf(stdout, "\nDestructor:\n");
    fflush(stdout);
}
//Actors can store a set of callbacks—usually implemented as lambda expressions—using either
//behavior or message_handler. The former stores an optional timeout, while the latter is composable.

/// Describes the behavior of an actor, i.e., provides a message
/// handler and an optional timeout.
caf::behavior MainActor::make_behavior()
{
    // start runnig
    //send(this, run_atom::value); cant send..
    // run the job when message arrive for it.
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
              }
              else {
                   caf::actor userActor = it->second;
                  request(userActor, caf::infinite, exit_atom::value);
                  demonitor(it->second);
                  actorMap.erase(it);
                  fprintf(stdout, "\nShutting down actor :\n");
                  fflush(stdout);
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
    }
    else {
         caf::actor userActor = it->second;
        request(userActor, caf::infinite, wsConnPtr, std::move(message), type);
    }
}
