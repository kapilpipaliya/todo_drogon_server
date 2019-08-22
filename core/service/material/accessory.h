#ifndef ACCESSORY_H
#define ACCESSORY_H
#include "../baseservice.h"
class Accessory : public BaseService
{
public:
    Accessory(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
#endif // ACCESSORY_H