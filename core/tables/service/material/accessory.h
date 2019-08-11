#ifndef ACCESSORY_H
#define ACCESSORY_H


#include "core/tables/Table.h"
#include <json/json.h>
#include "../../macro.h"

#include <drogon/WebSocketController.h>
using namespace drogon;

class Accessory
{
public:
    Accessory(const WebSocketConnectionPtr& wsConnPtr);

    HANDLEEVENTD()

private:
    void setupTable();
    HEADERDATAD()
    ALLDATAD()

    Table t;
    const WebSocketConnectionPtr& wsConnPtr;
};

#endif // ACCESSORY_H
