#ifndef JADMINACTOR_H
#define JADMINACTOR_H

#include "caf/all.hpp"
#include "useractorbase.h"

class JAdminActor : public caf::event_based_actor, public UserActorBase {
 public:
  JAdminActor(caf::actor_config &cfg);

 protected:
  caf::behavior make_behavior() override;

 private:
  json handleTextMessage(const WebSocketConnectionPtr &wsConnPtr,
                         json in) override;
  json handleBinaryMessage(const WebSocketConnectionPtr &wsConnPtr,
                           std::string &message) override;
  // std::map<std::string, WebSocketConnectionPtr> _clientsMap;
  // //UserID--->connection std::mutex _mapMtx;
};
#endif  // JADMINACTOR_H
