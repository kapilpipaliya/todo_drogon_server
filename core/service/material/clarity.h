#ifndef CLARITY_H
#define CLARITY_H
#include "../baseservice.h"
class Clarity : public BaseService
{
public:
    Clarity(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
#endif // CLARITY_H