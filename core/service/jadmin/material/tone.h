#ifndef TONE_H
#define TONE_H
#include "../../../../wscontroller/context/jadmincontext.h"
#include "../../baseserviceabs.h"
using JAdminContextPtr = std::shared_ptr<JAdminContext>;
namespace jadmin {
class Tone : public BaseServiceAbs {
 public:
  Tone(JAdminContextPtr);

 private:
  void setupTable() override;
  json ins(json event, json args) override;
  json upd(json event, json args) override;
  JAdminContextPtr context;
};
}  // namespace jadmin
#endif  // TONE_H
