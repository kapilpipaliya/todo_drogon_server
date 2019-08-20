#ifndef TASK_H
#define TASK_H
#include "../baseservice.h"
class Task : public BaseService
{
public:
    Task(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value ins(Json::Value event, Json::Value args);
    Json::Value upd(Json::Value event, Json::Value args);
};
#endif // TASK_H