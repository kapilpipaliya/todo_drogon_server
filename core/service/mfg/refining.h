#ifndef REFINING_H
#define REFINING_H
#include "../baseservice.h"
class Refining : public BaseService
{
public:
    Refining(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value ins(Json::Value event, Json::Value args);
    Json::Value upd(Json::Value event, Json::Value args);
};
#endif // REFINING_H