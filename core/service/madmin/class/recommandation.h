#ifndef RECOMMANDATION_H
#define RECOMMANDATION_H

#include "../../../../wscontroller/context/madmincontext.h"
#include "../../baseserviceabs.h"

using MAdminContextPtr = std::shared_ptr<MAdminContext>;
namespace madmin {
class Recommandation : public BaseServiceAbs {
 public:
  Recommandation(MAdminContextPtr);
  void setupTable() override;

 private:
  MAdminContextPtr context;
};
}  // namespace madmin
#endif  // RECOMMANDATION_H
