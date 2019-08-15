#ifndef SUPPORT_H
#define SUPPORT_H

#include "../baseservice.h"

class Support : public BaseService
{
public:
    Support(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
};

#endif // SUPPORT_H
