#include "JUserWebsock.h"
void JUserWebsock::handleNewMessage(const WebSocketConnectionPtr& wsConnPtr, std::string &&message, const WebSocketMessageType &type)
{
    //write your application logic here
}
void JUserWebsock::handleNewConnection(const HttpRequestPtr &req,const WebSocketConnectionPtr& wsConnPtr)
{
    //write your application logic here
}
void JUserWebsock::handleConnectionClosed(const WebSocketConnectionPtr& wsConnPtr)
{
    //write your application logic here
}
