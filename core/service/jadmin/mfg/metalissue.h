#ifndef METALISSUE_H
#define METALISSUE_H
#include "../../../../wscontroller/context/jadmincontext.h"
#include "../../baseserviceabs.h"
using JAdminContextPtr = std::shared_ptr<JAdminContext>;
namespace jadmin {
class MetalIssue : public BaseServiceAbs {
 public:
  MetalIssue(JAdminContextPtr);

 private:
  void setupTable() override;
  json ins(json event, json args) override;
  json upd(json event, json args) override;
  JAdminContextPtr context;
};
}  // namespace jadmin
#endif  // METALISSUE_H
