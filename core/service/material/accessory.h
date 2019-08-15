#ifndef ACCESSORY_H
#define ACCESSORY_H
#include "../baseservice.h"
class Accessory : public BaseService
{
public:
    Accessory(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
};
#endif // ACCESSORY_H