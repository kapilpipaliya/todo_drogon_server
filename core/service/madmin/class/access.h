#pragma once

#include "../../../../wscontroller/context/madmincontext.h"

#include "core/sql/query.h"
namespace madmin {
class Access {
 public:
  Access(std::shared_ptr<MAdminContext>);
  nlohmann::json handleEvent(nlohmann::json event, unsigned long next,
                             nlohmann::json args);
  void setupTable();

 private:
  std::shared_ptr<MAdminContext> context;
  sqlb::Query query;
};
}  // namespace madmin
