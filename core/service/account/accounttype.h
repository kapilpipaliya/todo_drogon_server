#ifndef ACCOUNTTYPE_H
#define ACCOUNTTYPE_H
#include "../baseservice.h"
class AccountType : public BaseService
{
public:
    AccountType(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value ins(Json::Value event, Json::Value args);
    Json::Value upd(Json::Value event, Json::Value args);
};
#endif // ACCOUNTTYPE_H
