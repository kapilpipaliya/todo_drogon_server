#ifndef TASK_H
#define TASK_H
#include "../baseservice.h"
class Task : public BaseService
{
public:
    Task(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
};
#endif // TASK_H