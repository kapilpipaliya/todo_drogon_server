#ifndef ENTITYTYPE_H
#define ENTITYTYPE_H
#include "../baseservice.h"
class EntityType : public BaseService
{
public:
    EntityType(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
#endif // ENTITYTYPE_H