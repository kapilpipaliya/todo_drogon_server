#ifndef POLICY_H
#define POLICY_H
#include "../baseservice.h"
class Policy : public BaseService
{
public:
    Policy(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};

#endif // POLICY_H
