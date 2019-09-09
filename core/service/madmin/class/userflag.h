#ifndef USERFLAG_H
#define USERFLAG_H

#include "../../../../wscontroller/context/madmincontext.h"
#include "../../baseserviceabs.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
class UserFlag : public BaseServiceAbs {
 public:
  UserFlag(MAdminContextPtr);
  void setupTable() override;

 private:
  MAdminContextPtr context;
};
}  // namespace madmin
#endif  // USERFLAG_H
