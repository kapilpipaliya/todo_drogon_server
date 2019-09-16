#ifndef MyCAF_H
#define MyCAF_H

#include "caf/all.hpp"

#include <drogon/WebSocketController.h>

#include "mainactor.h"

#include "json.hpp"

CAF_ALLOW_UNSAFE_MESSAGE_TYPE(drogon::WebSocketConnectionPtr)
CAF_ALLOW_UNSAFE_MESSAGE_TYPE(nlohmann::json)
namespace superactor {
namespace system {
class MyCAF {
 public:
  MyCAF();
  caf::scoped_actor& communicateWithActors() { return self; }
  caf::actor& mainActor() { return mainactor; }
  inline std::string getReasonString(caf::error& err) { sys.render(err); }

 private:
  caf::actor_system_config cfg;
  caf::actor_system sys;
  caf::scoped_actor self;
  inline void initialiseMainWector();
  //    mainAct_type mainactor;
  caf::actor mainactor;
};

//
// inlines
//
inline MyCAF::MyCAF() : sys(cfg), self(sys) {
  initialiseMainWector();
  // auto mainactor = self->spawn<MainActor>();
}

inline void MyCAF::initialiseMainWector() {
  mainactor = self->spawn<MainActor>();
}

extern MyCAF globalCAF;
}  // namespace system
}  // namespace superactor
#endif  // MyCAF_H
