#ifndef ROLE_H
#define ROLE_H
#include "../baseservice.h"
class Role : public BaseService
{
public:
    Role(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
};
#endif // ROLE_H