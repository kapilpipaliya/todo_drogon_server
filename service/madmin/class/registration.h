#ifndef REGISTRATION_H
#define REGISTRATION_H

#include "../../../../wscontroller/context/madmincontext.h"

#include "sql/query.h"

namespace music {
namespace service {
class Registration {
 public:
  Registration(std::shared_ptr<websocket::music::MAdminContext>);
  nlohmann::json handleEvent(nlohmann::json event, unsigned long next,
                             nlohmann::json args);
  void setupTable();

 private:
  std::shared_ptr<websocket::music::MAdminContext> context;
  sql::Query query;
};
}  // namespace service
}  // namespace music
#endif  // REGISTRATION_H
