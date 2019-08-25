#include "MUserWebsock.h"
void MUserWebsock::handleNewMessage(const WebSocketConnectionPtr& wsConnPtr, std::string &&message, const WebSocketMessageType &type)
{
    //write your application logic here
}
void MUserWebsock::handleNewConnection(const HttpRequestPtr &req,const WebSocketConnectionPtr& wsConnPtr)
{
    //write your application logic here
}
void MUserWebsock::handleConnectionClosed(const WebSocketConnectionPtr& wsConnPtr)
{
    //write your application logic here
}
