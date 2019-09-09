#ifndef IMAGE_H
#define IMAGE_H
#include "../../../../wscontroller/context/jadmincontext.h"
#include "../../baseserviceabs.h"
using JAdminContextPtr = std::shared_ptr<JAdminContext>;
namespace jadmin {
class Image : public BaseServiceAbs {
 public:
  Image(JAdminContextPtr);
  json handleEvent(json event, int next, const json& args);

 private:
  void setupTable() override;
  json ins(json event, json args) override;
  json upd(json event, json args) override;
  JAdminContextPtr context;
};
}  // namespace jadmin
#endif  // IMAGE_H
