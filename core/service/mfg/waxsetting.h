#ifndef WAXSETTING_H
#define WAXSETTING_H
#include "../baseservice.h"
class WaxSetting : public BaseService
{
public:
    WaxSetting(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
};
#endif // WAXSETTING_H