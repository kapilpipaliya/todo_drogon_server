#ifndef ACCESSORY_H
#define ACCESSORY_H
#include "../../../../wscontroller/context/jadmincontext.h"
#include "core/sql/query.h"

namespace jadmin {
class Accessory {
 public:
  Accessory(std::shared_ptr<JAdminContext>);
  nlohmann::json handleEvent(nlohmann::json event, unsigned long next,
                             nlohmann::json args);

 private:
  void setupTable();
  nlohmann::json ins(nlohmann::json event, nlohmann::json args);
  nlohmann::json upd(nlohmann::json event, nlohmann::json args);
  std::shared_ptr<JAdminContext> context;
  sqlb::Query query;
};
}  // namespace jadmin
#endif  // ACCESSORY_H
