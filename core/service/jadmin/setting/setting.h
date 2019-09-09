#ifndef SETTING_H
#define SETTING_H

#include "../../../../wscontroller/context/jadmincontext.h"
#include "../../baseserviceabs.h"
using JAdminContextPtr = std::shared_ptr<JAdminContext>;
namespace jadmin {
class Setting : public BaseServiceAbs {
 public:
  Setting(JAdminContextPtr);

  nlohmann::json handleEvent(nlohmann::json event, int next,
                             const nlohmann::json& args);

 private:
  void setupTable() override;
  nlohmann::json save(const nlohmann::json& event, nlohmann::json args);
  nlohmann::json del(nlohmann::json event, nlohmann::json args) override;
  JAdminContextPtr context;
};
}  // namespace jadmin
#endif  // SETTING_H
