#ifndef MESSAGEHANDLE_H
#define MESSAGEHANDLE_H
#include <json/json.h>
#include <drogon/WebSocketController.h>
using namespace drogon;
class MessageHandle
{
public:
    Json::Value handleTextMessage(const WebSocketConnectionPtr &, Json::Value in);
    Json::Value handleBinaryMessage(const WebSocketConnectionPtr &, std::string &message);
private:
};
extern MessageHandle msgHandle; // global variable
#endif // MESSAGEHANDLE_H
