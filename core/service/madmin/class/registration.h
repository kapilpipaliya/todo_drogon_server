#ifndef REGISTRATION_H
#define REGISTRATION_H

#include "../../../../wscontroller/context/madmincontext.h"
#include "../../baseserviceabs.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
class Registration : public BaseServiceAbs {
 public:
  Registration(MAdminContextPtr);
  void setupTable() override;

 private:
  MAdminContextPtr context;
};
}  // namespace madmin
#endif  // REGISTRATION_H
