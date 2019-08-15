#ifndef PRIORITY_H
#define PRIORITY_H
#include "../baseservice.h"
class Priority : public BaseService
{
public:
    Priority(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
};
#endif // PRIORITY_H