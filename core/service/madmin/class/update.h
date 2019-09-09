#ifndef UPDATE_H
#define UPDATE_H

#include "../../../../wscontroller/context/madmincontext.h"
#include "../../baseserviceabs.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
class Update : public BaseServiceAbs {
 public:
  Update(MAdminContextPtr);
  void setupTable() override;

 private:
  MAdminContextPtr context;
};
}  // namespace madmin
#endif  // UPDATE_H
