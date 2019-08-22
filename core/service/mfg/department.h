#ifndef DEPARTMENT_H
#define DEPARTMENT_H
#include "../baseservice.h"
class Department : public BaseService
{
public:
    Department(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
#endif // DEPARTMENT_H