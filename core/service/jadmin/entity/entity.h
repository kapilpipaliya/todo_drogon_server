#ifndef ENTITY_H
#define ENTITY_H
#include "../../../../wscontroller/context/jadmincontext.h"
#include "../../baseserviceabs.h"
using JAdminContextPtr = std::shared_ptr<JAdminContext>;
namespace jadmin {
class Entity : public BaseServiceAbs {
 public:
  Entity(JAdminContextPtr);

 private:
  void setupTable() override;
  json ins(json event, json args) override;
  json upd(json event, json args) override;
  json del(json event, json args) override;
  JAdminContextPtr context;
};
}  // namespace jadmin
#endif  // ENTITY_H
