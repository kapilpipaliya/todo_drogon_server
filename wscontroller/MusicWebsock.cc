#include "MusicWebsock.h"
void MusicWebsock::handleNewMessage(const WebSocketConnectionPtr& wsConnPtr, std::string &&message, const WebSocketMessageType &type)
{
    //write your application logic here
}
void MusicWebsock::handleNewConnection(const HttpRequestPtr &req,const WebSocketConnectionPtr& wsConnPtr)
{
    //write your application logic here
}
void MusicWebsock::handleConnectionClosed(const WebSocketConnectionPtr& wsConnPtr)
{
    //write your application logic here
}
