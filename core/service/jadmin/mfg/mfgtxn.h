#ifndef MFGTXN_H
#define MFGTXN_H
#include "../../../../wscontroller/context/jadmincontext.h"
#include "../../baseserviceabs.h"
using JAdminContextPtr = std::shared_ptr<JAdminContext>;
namespace jadmin {
class MfgTxn : public BaseServiceAbs {
 public:
  MfgTxn(JAdminContextPtr);

 private:
  void setupTable() override;
  nlohmann::json ins(nlohmann::json event, nlohmann::json args) override;
  nlohmann::json upd(nlohmann::json event, nlohmann::json args) override;
  JAdminContextPtr context;
};
}  // namespace jadmin
#endif  // MFGTXN_H
