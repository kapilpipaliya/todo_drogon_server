#ifndef ENTITY_H
#define ENTITY_H
#include "../baseservice.h"
class Entity : public BaseService
{
public:
    Entity(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
    json del(json event, json args);
};
#endif // ENTITY_H
