#ifndef CASTING_H
#define CASTING_H
#include "../baseservice.h"
class Casting : public BaseService
{
public:
    Casting(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value ins(Json::Value event, Json::Value args);
    Json::Value upd(Json::Value event, Json::Value args);
};
#endif // CASTING_H