#ifndef USERFLAG_H
#define USERFLAG_H

#include "../../../../wscontroller/context/madmincontext.h"

#include "sql/query.h"

namespace music {
namespace service {
class UserFlag {
 public:
  UserFlag(std::shared_ptr<websocket::music::MAdminContext>);
  nlohmann::json handleEvent(nlohmann::json event, unsigned long next,
                             nlohmann::json args);
  void setupTable();

 private:
  std::shared_ptr<websocket::music::MAdminContext> context;
  sql::Query query;
};
}  // namespace service
}  // namespace music
#endif  // USERFLAG_H
