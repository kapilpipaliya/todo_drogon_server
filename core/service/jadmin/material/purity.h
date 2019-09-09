#ifndef PURITY_H
#define PURITY_H
#include "../../../../wscontroller/context/jadmincontext.h"
#include "../../baseserviceabs.h"
using JAdminContextPtr = std::shared_ptr<JAdminContext>;
namespace jadmin {
class Purity : public BaseServiceAbs {
 public:
  Purity(JAdminContextPtr);

 private:
  void setupTable() override;
  json ins(json event, json args) override;
  json upd(json event, json args) override;
  json del(json event, json args) override;
  JAdminContextPtr context;
};
}  // namespace jadmin
#endif  // PURITY_H
