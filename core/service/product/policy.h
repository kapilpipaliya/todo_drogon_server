#ifndef POLICY_H
#define POLICY_H
#include "../baseservice.h"
class Policy : public BaseService
{
public:
    Policy(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value ins(Json::Value event, Json::Value args);
    Json::Value upd(Json::Value event, Json::Value args);
};

#endif // POLICY_H
