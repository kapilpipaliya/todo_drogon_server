#ifndef MESSAGEHANDLE_H
#define MESSAGEHANDLE_H

#include "json.hpp"

#include <drogon/WebSocketController.h>

#include "./mainactortype.h"
#include "caf/all.hpp"

class MainActor : public caf::event_based_actor {
 public:
  MainActor(caf::actor_config &cfg);
  ~MainActor() override;

 protected:
  caf::behavior make_behavior() override;

 private:
  void passToUser(MainActorType actortype,
                  const drogon::WebSocketConnectionPtr &wsConnPtr,
                  std::string &&message,
                  const drogon::WebSocketMessageType &type);
  std::unordered_map<drogon::WebSocketConnectionPtr, caf::actor> actorMap;
};
#endif  // MESSAGEHANDLE_H
