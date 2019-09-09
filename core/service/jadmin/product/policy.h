#ifndef POLICY_H
#define POLICY_H
#include "../../../../wscontroller/context/jadmincontext.h"
#include "../../baseserviceabs.h"
using JAdminContextPtr = std::shared_ptr<JAdminContext>;
namespace jadmin {
class Policy : public BaseServiceAbs {
 public:
  Policy(JAdminContextPtr);

 private:
  void setupTable() override;
  json ins(json event, json args) override;
  json upd(json event, json args) override;
  JAdminContextPtr context;
};
}  // namespace jadmin
#endif  // POLICY_H
