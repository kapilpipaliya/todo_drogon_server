#pragma once
#include "caf/all.hpp"
namespace openproj {
namespace worker {
namespace OAuth {
  class CleanupJob: public caf::event_based_actor {//: public ::RakeJob {
  public:
     CleanupJob(caf::actor_config& cfg): caf::event_based_actor(cfg) {
//      super "doorkeeper:db:cleanup"
    }
  };
}
}
}
