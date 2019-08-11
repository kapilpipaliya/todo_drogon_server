#ifndef CLARITY_H
#define CLARITY_H

#include "core/tables/Table.h"
#include <json/json.h>
#include "../../macro.h"

#include <drogon/WebSocketController.h>
using namespace drogon;

class Clarity
{
public:
    Clarity(const WebSocketConnectionPtr& wsConnPtr);

    HANDLEEVENTD()

private:
    void setupTable();
    HEADERDATAD()
    ALLDATAD()

    Table t;
    const WebSocketConnectionPtr& wsConnPtr;
};

#endif // CLARITY_H
