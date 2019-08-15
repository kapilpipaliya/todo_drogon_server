#ifndef ACCOUNT_H
#define ACCOUNT_H
#include "../baseservice.h"
class Account : public BaseService
{
public:
    Account(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
};
#endif // ACCOUNT_H
