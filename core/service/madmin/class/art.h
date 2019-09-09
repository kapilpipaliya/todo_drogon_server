#ifndef ART_H
#define ART_H

#include "../../../../wscontroller/context/madmincontext.h"
#include "../../baseserviceabs.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
class Art : public BaseServiceAbs {
 public:
  Art(MAdminContextPtr);
  void setupTable() override;

 private:
  MAdminContextPtr context;
};
}  // namespace madmin
#endif  // ART_H
