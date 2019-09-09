#ifndef DEPARTMENTTYPE_H
#define DEPARTMENTTYPE_H
#include "../../../../wscontroller/context/jadmincontext.h"
#include "../../baseserviceabs.h"
using JAdminContextPtr = std::shared_ptr<JAdminContext>;
namespace jadmin {
class DepartmentType : public BaseServiceAbs {
 public:
  DepartmentType(JAdminContextPtr);

 private:
  void setupTable() override;
  json ins(json event, json args) override;
  json upd(json event, json args) override;
  JAdminContextPtr context;
};
}  // namespace jadmin
#endif  // DEPARTMENTTYPE_H
