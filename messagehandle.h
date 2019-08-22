#ifndef MESSAGEHANDLE_H
#define MESSAGEHANDLE_H

#include  "json.hpp"
using nlohmann:: json;

#include <drogon/WebSocketController.h>
using namespace drogon;

#include "caf/all.hpp"

class NoCAF {
public:
    NoCAF(const WebSocketConnectionPtr &wsConnPtr, std::string &&message,
                  const WebSocketMessageType &type );
    //~NoCAF() override;
    json handleTextMessage(json in);
    json handleBinaryMessage(const WebSocketConnectionPtr &, std::string &message);
    void blocking_run();
private:
    const WebSocketConnectionPtr wsConnPtr;
    json in;
    std::string message;
    const WebSocketMessageType type;
};


class MessageHandle : public caf::event_based_actor
{
public:
    MessageHandle(caf:: actor_config& cfg, const WebSocketConnectionPtr &wsConnPtr, std::string &&message,
                  const WebSocketMessageType &type );
    ~MessageHandle() override;
    json handleTextMessage(json in);
    json handleBinaryMessage(const WebSocketConnectionPtr &, std::string &message);
private:
    void blocking_run();

    const WebSocketConnectionPtr wsConnPtr;
    json in;
    caf:: behavior    running_job; // initial behavior
    std::string message;
    const WebSocketMessageType type;
protected:
   caf::behavior make_behavior() override;
};
#endif // MESSAGEHANDLE_H
