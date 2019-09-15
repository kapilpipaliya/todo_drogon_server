#ifndef ENTITYTYPE_H
#define ENTITYTYPE_H
#include "../../../../wscontroller/context/jadmincontext.h"
#include "core/sql/query.h"

namespace jadmin {
namespace service {
class EntityType {
 public:
  EntityType(std::shared_ptr<websocket::jadmin::JAdminContext>);
  nlohmann::json handleEvent(nlohmann::json event, unsigned long next,
                             nlohmann::json args);

 private:
  void setupTable();
  nlohmann::json ins(nlohmann::json event, nlohmann::json args);
  nlohmann::json upd(nlohmann::json event, nlohmann::json args);
  std::shared_ptr<websocket::jadmin::JAdminContext> context;
  sql::Query query;
};
}  // namespace service
}  // namespace jadmin
#endif  // ENTITYTYPE_H
