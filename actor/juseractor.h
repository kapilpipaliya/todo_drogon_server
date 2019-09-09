#ifndef JUSERACTOR_H
#define JUSERACTOR_H

#include "caf/all.hpp"
#include "useractorbase.h"

class JUserActor : public caf::event_based_actor, public UserActorBase {
 public:
  JUserActor(caf::actor_config &cfg);

 protected:
  caf::behavior make_behavior() override;

 private:
  json handleTextMessage(const WebSocketConnectionPtr &wsConnPtr,
                         json in) override;
  json handleBinaryMessage(const WebSocketConnectionPtr &wsConnPtr,
                           std::string &message) override;
};
#endif  // JUSERACTOR_H
