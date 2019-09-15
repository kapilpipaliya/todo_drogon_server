#pragma once

#include "../../../../wscontroller/context/madmincontext.h"

#include "core/sql/query.h"
namespace music {
namespace service {
class Access {
 public:
  Access(std::shared_ptr<websocket::music::MAdminContext>);
  nlohmann::json handleEvent(nlohmann::json event, unsigned long next,
                             nlohmann::json args);
  void setupTable();

 private:
  std::shared_ptr<websocket::music::MAdminContext> context;
  sql::Query query;
};
}  // namespace service
}  // namespace music
