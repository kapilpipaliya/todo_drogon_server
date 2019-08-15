#ifndef ACCOUNTHEADING_H
#define ACCOUNTHEADING_H
#include "../baseservice.h"
class AccountHeading : public BaseService
{
public:
    AccountHeading(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
};
#endif // ACCOUNTHEADING_H