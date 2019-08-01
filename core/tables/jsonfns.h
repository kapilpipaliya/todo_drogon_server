#ifndef JSONFNS_H
#define JSONFNS_H

#include <json/json.h>
#include <drogon/WebSocketController.h>
using namespace drogon;

void printJson(Json::Value & in);
Json::Value simpleJsonSaveResult(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, bool ok, const std::string & error);



#endif // JSONFNS_H
