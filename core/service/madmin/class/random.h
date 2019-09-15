#ifndef RANDOM_H
#define RANDOM_H

#include "../../../../wscontroller/context/madmincontext.h"

#include "core/sql/query.h"

namespace madmin {
class Random {
 public:
  Random(std::shared_ptr<websocket::music::MAdminContext>);
  nlohmann::json handleEvent(nlohmann::json event, unsigned long next,
                             nlohmann::json args);
  void setupTable();

 private:
  std::shared_ptr<websocket::music::MAdminContext> context;
  sql::Query query;
};
}  // namespace madmin
#endif  // RANDOM_H
