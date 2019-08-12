#ifndef TONE_H
#define TONE_H

#include "core/Table.h"
#include <json/json.h>
#include "../../macro.h"

#include <drogon/WebSocketController.h>
using namespace drogon;

class Tone
{
public:
    Tone(const WebSocketConnectionPtr& wsConnPtr);

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

#endif // TONE_H
