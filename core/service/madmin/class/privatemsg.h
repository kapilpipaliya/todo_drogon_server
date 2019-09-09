#ifndef PRIVATEMSG_H
#define PRIVATEMSG_H

#include "../../../../wscontroller/context/madmincontext.h"
#include "../../baseserviceabs.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
class PrivateMsg : public BaseServiceAbs {
 public:
  PrivateMsg(MAdminContextPtr);
  void setupTable() override;

 private:
  MAdminContextPtr context;
};
}  // namespace madmin
#endif  // PRIVATEMSG_H
