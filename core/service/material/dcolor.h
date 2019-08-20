#ifndef DCOLOR_H
#define DCOLOR_H
#include "../baseservice.h"
class DColor : public BaseService
{
public:
    DColor(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value ins(Json::Value event, Json::Value args);
    Json::Value upd(Json::Value event, Json::Value args);
};
#endif // DCOLOR_H