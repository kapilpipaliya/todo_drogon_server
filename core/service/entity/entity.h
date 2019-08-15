#ifndef ENTITY_H
#define ENTITY_H
#include "../baseservice.h"
class Entity : public BaseService
{
public:
    Entity(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
    Json::Value del(Json::Value event, Json::Value args);
};
#endif // ENTITY_H
