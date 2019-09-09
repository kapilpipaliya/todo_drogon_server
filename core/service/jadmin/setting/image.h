#ifndef IMAGE_H
#define IMAGE_H
#include "../../../../wscontroller/context/jadmincontext.h"
#include "../../baseserviceabs.h"
using JAdminContextPtr = std::shared_ptr<JAdminContext>;
namespace jadmin {
class Image : public BaseServiceAbs {
 public:
  Image(JAdminContextPtr);
  nlohmann::json handleEvent(nlohmann::json event, int next, const nlohmann::json& args);

 private:
  void setupTable() override;
  nlohmann::json ins(nlohmann::json event, nlohmann::json args) override;
  nlohmann::json upd(nlohmann::json event, nlohmann::json args) override;
  JAdminContextPtr context;
};
}  // namespace jadmin
#endif  // IMAGE_H
