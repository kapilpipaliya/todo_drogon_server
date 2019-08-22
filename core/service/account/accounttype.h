#ifndef ACCOUNTTYPE_H
#define ACCOUNTTYPE_H
#include "../baseservice.h"
class AccountType : public BaseService
{
public:
    AccountType(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
#endif // ACCOUNTTYPE_H
