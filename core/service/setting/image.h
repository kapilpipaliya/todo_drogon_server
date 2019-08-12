#ifndef IMAGE_H
#define IMAGE_H


#include "core/Table.h"
#include <json/json.h>
#include "../../macro.h"

#include <drogon/WebSocketController.h>
using namespace drogon;

class Image
{
public:
    Image(const WebSocketConnectionPtr& wsConnPtr);

    HANDLEEVENTD()
    Json::Value handleBinaryEvent(Json::Value event, std::string &message);

private:
    void setupTable();
    HEADERDATAD()
    ALLDATAD()
    SAVED()
    DELETED()
    Json::Value thumb_data( Json::Value event, Json::Value args);
    //Binary functin:
    Json::Value save_setting_attachment(Json::Value event, std::string &message);

    Table t;
    const WebSocketConnectionPtr& wsConnPtr;
};





#endif // IMAGE_H
