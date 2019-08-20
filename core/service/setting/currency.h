#ifndef CURRENCY_H
#define CURRENCY_H
#include "../baseservice.h"
class Currency : public BaseService
{
public:
    Currency(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value ins(Json::Value event, Json::Value args);
    Json::Value upd(Json::Value event, Json::Value args);
};
#endif // CURRENCY_H
