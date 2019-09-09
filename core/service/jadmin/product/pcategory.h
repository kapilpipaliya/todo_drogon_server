#ifndef PCATEGORY_H
#define PCATEGORY_H
#include "../../../../wscontroller/context/jadmincontext.h"
#include "../../baseserviceabs.h"
using JAdminContextPtr = std::shared_ptr<JAdminContext>;
namespace jadmin {
class PCategory : public BaseServiceAbs {
 public:
  PCategory(JAdminContextPtr);

 private:
  void setupTable() override;
  nlohmann::json ins(nlohmann::json event, nlohmann::json args) override;
  nlohmann::json upd(nlohmann::json event, nlohmann::json args) override;
  JAdminContextPtr context;
};
}  // namespace jadmin
#endif  // PCATEGORY_H
