#ifndef SUPPORT_H
#define SUPPORT_H

#include "../baseservice.h"

class Support : public BaseService
{
public:
    Support(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value ins(Json::Value event, Json::Value args);
    Json::Value upd(Json::Value event, Json::Value args);
};

#endif // SUPPORT_H
