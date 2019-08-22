#ifndef PRIORITY_H
#define PRIORITY_H
#include "../baseservice.h"
class Priority : public BaseService
{
public:
    Priority(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
#endif // PRIORITY_H