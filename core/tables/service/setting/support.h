#ifndef SUPPORT_H
#define SUPPORT_H

#include "core/tables/Table.h"
#include <json/json.h>
#include "../../macro.h"

#include <drogon/WebSocketController.h>
using namespace drogon;

class Support
{
public:
    Support(const WebSocketConnectionPtr& wsConnPtr);

    HANDLEEVENTD()

private:
    void setupTable();
    HEADERDATAD()
    ALLDATAD()

    Table t;
    const WebSocketConnectionPtr& wsConnPtr;
};

#endif // SUPPORT_H
