#pragma once

#include "../../../../wscontroller/context/madmincontext.h"

#include "core/sql/query.h"
namespace madmin {
class Access {
 public:
  Access(std::shared_ptr<websocket::MAdminContext>);
  nlohmann::json handleEvent(nlohmann::json event, unsigned long next,
                             nlohmann::json args);
  void setupTable();

 private:
  std::shared_ptr<websocket::MAdminContext> context;
  sql::Query query;
};
}  // namespace madmin
