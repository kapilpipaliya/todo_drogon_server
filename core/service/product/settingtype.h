#ifndef SETTINGTYPE_H
#define SETTINGTYPE_H
#include "../baseservice.h"
class SettingType : public BaseService
{
public:
    SettingType(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
};
#endif // SETTINGTYPE_H
