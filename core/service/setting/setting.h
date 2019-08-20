#ifndef SETTING_H
#define SETTING_H

#include "../baseservice.h"

class Setting : public BaseService
{
public:
    Setting(const WebSocketConnectionPtr& wsConnPtr);

   Json::Value handleEvent(Json::Value event, int next, Json::Value args);

private:
    void setupTable();
    Json::Value ins(Json::Value event, Json::Value args){};
    Json::Value upd(Json::Value event, Json::Value args){};
    Json::Value save(Json::Value event, Json::Value args);
    Json::Value del( Json::Value event, Json::Value args);
};
#endif // SETTING_H
