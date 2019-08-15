#ifndef SETTING_H
#define SETTING_H

#include "../baseservice.h"

class Setting : public BaseService
{
public:
    Setting(const WebSocketConnectionPtr& wsConnPtr);

private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
    Json::Value del(Json::Value event, Json::Value args);
};
#endif // SETTING_H
