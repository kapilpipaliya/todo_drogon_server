#ifndef PURITY_H
#define PURITY_H
#include "../baseservice.h"
class Purity : public BaseService
{
public:
    Purity(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value ins(Json::Value event, Json::Value args);
    Json::Value upd(Json::Value event, Json::Value args);
    Json::Value del(Json::Value event, Json::Value args);
};
#endif // PURITY_H
