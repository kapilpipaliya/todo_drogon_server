#ifndef CONTACTTYPE_H
#define CONTACTTYPE_H
#include "../../../../wscontroller/context/jadmincontext.h"
#include "core/sql/query.h"

namespace jadmin {
class ContactType {
 public:
  ContactType(std::shared_ptr<websocket::JAdminContext>);
  nlohmann::json handleEvent(nlohmann::json event, unsigned long next,
                             nlohmann::json args);

 private:
  void setupTable();
  nlohmann::json ins(nlohmann::json event, nlohmann::json args);
  nlohmann::json upd(nlohmann::json event, nlohmann::json args);
  std::shared_ptr<websocket::JAdminContext> context;
  sql::Query query;
};
}  // namespace jadmin
#endif  // CONTACTTYPE_H
