#ifndef REFINING_H
#define REFINING_H
#include "../baseservice.h"
class Refining : public BaseService
{
public:
    Refining(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
#endif // REFINING_H