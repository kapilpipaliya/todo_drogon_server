#ifndef CURRENCY_H
#define CURRENCY_H


#include "core/Table.h"
#include <json/json.h>
#include "../../macro.h"

#include <drogon/WebSocketController.h>
using namespace drogon;

class Currency
{
public:
    Currency(const WebSocketConnectionPtr& wsConnPtr);

    HANDLEEVENTD()

private:
    void setupTable();
    HEADERDATAD()
    ALLDATAD()
    SAVED()
    DELETED()

    Table t;
    const WebSocketConnectionPtr& wsConnPtr;
};
#endif // CURRENCY_H
