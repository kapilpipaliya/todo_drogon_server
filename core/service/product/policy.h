#ifndef POLICY_H
#define POLICY_H
#include "../baseservice.h"
class Policy : public BaseService
{
public:
    Policy(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
};

#endif // POLICY_H
