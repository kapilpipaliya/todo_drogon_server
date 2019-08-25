#ifndef MESSAGEHANDLE_H
#define MESSAGEHANDLE_H

#include  "json.hpp"
using nlohmann:: json;

#include <drogon/WebSocketController.h>
using namespace drogon;

#include "caf/all.hpp"
#include "./mainactortype.h"

class MainActor : public caf::event_based_actor
{
public:
    MainActor(caf:: actor_config& cfg );
    ~MainActor() override;
protected:
   caf::behavior make_behavior() override;
private:
   void passToUser(MainActorType actortype, const WebSocketConnectionPtr &wsConnPtr, std::string &&message, const WebSocketMessageType &type);
   std::unordered_map<WebSocketConnectionPtr, caf::actor> actorMap;
};
#endif // MESSAGEHANDLE_H
