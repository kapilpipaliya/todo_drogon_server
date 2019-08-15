#ifndef TXN_H
#define TXN_H
#include "../baseservice.h"
class Txn : public BaseService
{
public:
    Txn(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
    Json::Value del(Json::Value event, Json::Value args);
};
#endif // TXN_H
