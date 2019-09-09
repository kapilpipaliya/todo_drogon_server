#ifndef MADMINACTOR_H
#define MADMINACTOR_H

#include "caf/all.hpp"
#include "useractorbase.h"

class MAdminActor : public caf::event_based_actor, public UserActorBase {
 public:
  MAdminActor(caf::actor_config &cfg);

 protected:
  caf::behavior make_behavior() override;

 private:
  json handleTextMessage(const WebSocketConnectionPtr &wsConnPtr,
                         json in) override;
  json handleBinaryMessage(const WebSocketConnectionPtr &wsConnPtr,
                           std::string &message) override;
};
#endif  // MADMINACTOR_H
