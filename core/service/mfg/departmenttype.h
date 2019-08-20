#ifndef DEPARTMENTTYPE_H
#define DEPARTMENTTYPE_H
#include "../baseservice.h"
class DepartmentType : public BaseService
{
public:
    DepartmentType(const WebSocketConnectionPtr& wsConnPtr);
private:
    void setupTable();
    Json::Value ins(Json::Value event, Json::Value args);
    Json::Value upd(Json::Value event, Json::Value args);
};
#endif // DEPARTMENTTYPE_H
