#ifndef UPDATE_H
#define UPDATE_H

#include "../../../../wscontroller/context/madmincontext.h"

#include "core/sql/query.h"

namespace madmin {
class Update {
 public:
  Update(std::shared_ptr<MAdminContext>);
  nlohmann::json handleEvent(nlohmann::json event, unsigned long next,
                             nlohmann::json args);
  void setupTable();

 private:
  std::shared_ptr<MAdminContext> context;
  sqlb::Query query;
};
}  // namespace madmin
#endif  // UPDATE_H
