#ifndef LOCALPLAY_H
#define LOCALPLAY_H

#include "../../../../wscontroller/context/madmincontext.h"
#include "../../baseserviceabs.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
class LocalPlay : public BaseServiceAbs {
 public:
  LocalPlay(MAdminContextPtr);
  void setupTable() override;

 private:
  MAdminContextPtr context;
};
}  // namespace madmin
#endif  // LOCALPLAY_H
