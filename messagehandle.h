#ifndef MESSAGEHANDLE_H
#define MESSAGEHANDLE_H
#include <json/json.h>
#include <drogon/WebSocketController.h>
using namespace drogon;

#include "caf/all.hpp"

class MessageHandle : public caf::event_based_actor
{
public:
    MessageHandle(caf:: actor_config& cfg, const WebSocketConnectionPtr &wsConnPtr, std::string &&message,
                  const WebSocketMessageType &type );
    ~MessageHandle() override;
    Json::Value handleTextMessage(Json::Value in);
    Json::Value handleBinaryMessage(const WebSocketConnectionPtr &, std::string &message);
private:
    void blocking_run();

    const WebSocketConnectionPtr wsConnPtr;
    Json::Value in;
    caf:: behavior    running_job; // initial behavior
    std::string message;
    const WebSocketMessageType type;
protected:
   caf::behavior make_behavior() override;
};
#endif // MESSAGEHANDLE_H
