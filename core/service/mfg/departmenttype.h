#ifndef DEPARTMENTTYPE_H
#define DEPARTMENTTYPE_H
#include "../baseservice.h"
class DepartmentType : public BaseService
{
public:
    DepartmentType();
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
#endif // DEPARTMENTTYPE_H
