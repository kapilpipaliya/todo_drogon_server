#ifndef CSCOLOR_H
#define CSCOLOR_H
#include "../../../../wscontroller/context/jadmincontext.h"
#include "../../baseserviceabs.h"
using JAdminContextPtr = std::shared_ptr<JAdminContext>;
namespace jadmin {
class CSColor : public BaseServiceAbs {
 public:
  CSColor(JAdminContextPtr);

 private:
  void setupTable() override;
  nlohmann::json ins(nlohmann::json event, nlohmann::json args) override;
  nlohmann::json upd(nlohmann::json event, nlohmann::json args) override;
  JAdminContextPtr context;
};
}  // namespace jadmin
#endif  // CSCOLOR_H
