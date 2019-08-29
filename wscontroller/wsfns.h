#ifndef WSFNS_H
#define WSFNS_H
#include  "json.hpp"
#include <drogon/WebSocketController.h>
#include "spdlogfix.h"

using nlohmann:: json;
using namespace drogon;

class WsFns
{
public:
    WsFns();

    static void sendJson(const WebSocketConnectionPtr &wsConnPtr, json &j);
};

#endif // WSFNS_H
