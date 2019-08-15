#ifndef CURRENCY_H
#define CURRENCY_H
#include "../baseservice.h"
class Currency : public BaseService
{
public:
    Currency(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
};
#endif // CURRENCY_H
