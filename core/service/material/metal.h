#ifndef METAL_H
#define METAL_H
#include "../baseservice.h"
class Metal : public BaseService
{
public:
    Metal(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value ins(Json::Value event, Json::Value args);
    Json::Value upd(Json::Value event, Json::Value args);
};
#endif // METAL_H