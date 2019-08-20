#ifndef CSCOLOR_H
#define CSCOLOR_H
#include "../baseservice.h"
class CSColor : public BaseService
{
public:
    CSColor(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value ins(Json::Value event, Json::Value args);
    Json::Value upd(Json::Value event, Json::Value args);
};
#endif // CSCOLOR_H