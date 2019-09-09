#ifndef SHOUTBOX_H
#define SHOUTBOX_H

#include "../../../../wscontroller/context/madmincontext.h"
#include "../../baseserviceabs.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
class ShoutBox : public BaseServiceAbs {
 public:
  ShoutBox(MAdminContextPtr);
  void setupTable() override;

 private:
  MAdminContextPtr context;
};
}  // namespace madmin
#endif  // SHOUTBOX_H
