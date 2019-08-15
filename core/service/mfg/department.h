#ifndef DEPARTMENT_H
#define DEPARTMENT_H
#include "../baseservice.h"
class Department : public BaseService
{
public:
    Department(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
};
#endif // DEPARTMENT_H