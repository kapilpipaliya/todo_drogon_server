#ifndef ADDRESSTYPE_H
#define ADDRESSTYPE_H

#include "core/Table.h"
#include <json/json.h>
#include "../../macro.h"

#include <drogon/WebSocketController.h>
using namespace drogon;

class AddressType
{
public:
    AddressType(const WebSocketConnectionPtr& wsConnPtr);

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
#endif // ADDRESSTYPE_H
