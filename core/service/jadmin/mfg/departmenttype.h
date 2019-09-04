#ifndef DEPARTMENTTYPE_H
#define DEPARTMENTTYPE_H
#include "../baseservice.h"
namespace jadmin {
class DepartmentType : public BaseService
{
public:
    DepartmentType(const JAdminContextPtr &);
private:
    void setupTable();
    json ins(json event, json args);
    json upd(json event, json args);
};
}
#endif // DEPARTMENTTYPE_H
