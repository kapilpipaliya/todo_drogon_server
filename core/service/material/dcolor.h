#ifndef DCOLOR_H
#define DCOLOR_H
#include "../baseservice.h"
class DColor : public BaseService
{
public:
    DColor(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
#endif // DCOLOR_H