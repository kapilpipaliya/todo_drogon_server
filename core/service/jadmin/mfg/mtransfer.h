#ifndef MTRANSFER_H
#define MTRANSFER_H
#include "../../../../wscontroller/context/jadmincontext.h"
#include "../../baseserviceabs.h"
using JAdminContextPtr = std::shared_ptr<JAdminContext>;
namespace jadmin {
class MTransfer : public BaseServiceAbs {
 public:
  MTransfer(JAdminContextPtr);

 private:
  void setupTable() override;
  nlohmann::json ins(nlohmann::json event, nlohmann::json args) override;
  nlohmann::json upd(nlohmann::json event, nlohmann::json args) override;
  JAdminContextPtr context;
};
}  // namespace jadmin
#endif  // MTRANSFER_H
