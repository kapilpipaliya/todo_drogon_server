#ifndef MESSAGEHANDLE_H
#define MESSAGEHANDLE_H
#include <json/json.h>
#include <drogon/WebSocketController.h>
using namespace drogon;

#include "caf/all.hpp"

class MessageHandle : public caf::blocking_actor
{
public:
    MessageHandle(caf:: actor_config& cfg, const WebSocketConnectionPtr &wsConnPtr, std::string &&message,
                  const WebSocketMessageType &type );
    ~MessageHandle();
    Json::Value handleTextMessage(Json::Value in);
    Json::Value handleBinaryMessage(const WebSocketConnectionPtr &, std::string &message);
    void blocking_run();
private:
    const WebSocketConnectionPtr wsConnPtr;
    Json::Value in;
    caf:: behavior    run_job; // initial behavior
    std::string message;
    const WebSocketMessageType type;
protected:
 void act() override;
};
#endif // MESSAGEHANDLE_H
