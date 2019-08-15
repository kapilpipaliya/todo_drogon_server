#ifndef ENTITYTYPE_H
#define ENTITYTYPE_H
#include "../baseservice.h"
class EntityType : public BaseService
{
public:
    EntityType(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
};
#endif // ENTITYTYPE_H