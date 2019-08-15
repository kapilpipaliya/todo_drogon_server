#ifndef ACCOUNTTYPE_H
#define ACCOUNTTYPE_H
#include "../baseservice.h"
class AccountType : public BaseService
{
public:
    AccountType(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
};
#endif // ACCOUNTTYPE_H
