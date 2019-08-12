#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include "core/Table.h"
#include <json/json.h>
#include "../../macro.h"

#include <drogon/WebSocketController.h>
using namespace drogon;

class Department
{
public:
    Department(const WebSocketConnectionPtr& wsConnPtr);

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
#endif // DEPARTMENT_H
