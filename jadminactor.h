#ifndef JADMINACTOR_H
#define JADMINACTOR_H

#include  "json.hpp"
using nlohmann:: json;

#include <drogon/WebSocketController.h>
using namespace drogon;

#include "caf/all.hpp"

class JAdminActor : public caf::event_based_actor
{
public:
    JAdminActor(caf:: actor_config& cfg );
    json handleTextMessage(const WebSocketConnectionPtr &wsConnPtr, std::string &&message, json in);
    json handleBinaryMessage(const WebSocketConnectionPtr &, std::string &message);
private:
    void blocking_run(const WebSocketConnectionPtr &wsConnPtr, std::string &&message, const WebSocketMessageType &type);
    caf:: behavior    running_job; // initial behavior
protected:
   caf::behavior make_behavior() override;
};

#endif // JADMINACTOR_H
