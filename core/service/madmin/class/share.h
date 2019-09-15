#ifndef SHARE_H
#define SHARE_H

#include "../../../../wscontroller/context/madmincontext.h"

#include "core/sql/query.h"

namespace madmin {
class Share {
 public:
  Share(std::shared_ptr<websocket::music::MAdminContext>);
  nlohmann::json handleEvent(nlohmann::json event, unsigned long next,
                             nlohmann::json args);
  void setupTable();

 private:
  std::shared_ptr<websocket::music::MAdminContext> context;
  sql::Query query;
};
}  // namespace madmin
#endif  // SHARE_H
