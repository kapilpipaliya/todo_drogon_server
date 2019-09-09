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
  nlohmann::json handleTextMessage(const drogon::WebSocketConnectionPtr &wsConnPtr,
                         nlohmann::json in) override;
  nlohmann::json handleBinaryMessage(const drogon::WebSocketConnectionPtr &wsConnPtr,
                           std::string &message) override;
  // std::map<std::string, WebSocketConnectionPtr> _clientsMap;
  // //UserID--->connection std::mutex _mapMtx;
};
#endif  // JADMINACTOR_H
