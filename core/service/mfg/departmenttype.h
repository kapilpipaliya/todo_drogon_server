#ifndef DEPARTMENTTYPE_H
#define DEPARTMENTTYPE_H
#include "../baseservice.h"
class DepartmentType : public BaseService
{
public:
    DepartmentType(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value save(Json::Value event, Json::Value args);
};
#endif // DEPARTMENTTYPE_H
