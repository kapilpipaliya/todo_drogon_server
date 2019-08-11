#ifndef SIZE_H
#define SIZE_H

#include "core/tables/Table.h"
#include <json/json.h>
#include "../../macro.h"

#include <drogon/WebSocketController.h>
using namespace drogon;

class Size
{
public:
    Size(const WebSocketConnectionPtr& wsConnPtr);

    HANDLEEVENTD()

private:
    void setupTable();
    HEADERDATAD()
    ALLDATAD()

    Table t;
    const WebSocketConnectionPtr& wsConnPtr;
};
#endif // SIZE_H
