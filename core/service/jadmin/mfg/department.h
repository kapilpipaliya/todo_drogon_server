#ifndef DEPARTMENT_H
#define DEPARTMENT_H
#include "../../baseserviceabs.h"
#include "../../../../wscontroller/context/jadmincontext.h"
using JAdminContextPtr = std::shared_ptr<JAdminContext>;
namespace jadmin {
class Department : public BaseServiceAbs
{
public:
    Department(JAdminContextPtr );
private:
    void setupTable() override;
    json ins(json event, json args) override;
    json upd(json event, json args) override;
    JAdminContextPtr context;
};
}
#endif // DEPARTMENT_H