#ifndef LOCALPLAYBASE_H
#define LOCALPLAYBASE_H

#include "../../../../wscontroller/context/madmincontext.h"
#include "../../baseserviceabs.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
class LocalPlayBase : public BaseServiceAbs {
 public:
  LocalPlayBase(MAdminContextPtr);
  void setupTable() override;

 private:
  MAdminContextPtr context;
};
}  // namespace madmin
#endif  // LOCALPLAYBASE_H
