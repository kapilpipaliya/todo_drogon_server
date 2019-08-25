#ifndef JUSERACTOR_H
#define JUSERACTOR_H

#include  "json.hpp"
#include <drogon/WebSocketController.h>
#include "caf/all.hpp"

using nlohmann:: json;
using namespace drogon;

class JUserActor : public caf::event_based_actor
{
public:
    JUserActor(caf:: actor_config& cfg );
protected:
   caf::behavior make_behavior() override;
private:
    void blocking_run(const WebSocketConnectionPtr &wsConnPtr, std::string &&message, const WebSocketMessageType &type);
    json handleTextMessage(const WebSocketConnectionPtr &wsConnPtr, std::string &&message, json in);
    json handleBinaryMessage(const WebSocketConnectionPtr &wsConnPtr, std::string &message);
};
#endif // JUSERACTOR_H
