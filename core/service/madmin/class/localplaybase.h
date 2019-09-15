#ifndef LOCALPLAYBASE_H
#define LOCALPLAYBASE_H

#include "../../../../wscontroller/context/madmincontext.h"

#include "core/sql/query.h"

namespace music {
namespace service {
class LocalPlayBase {
 public:
  LocalPlayBase(std::shared_ptr<websocket::music::MAdminContext>);
  nlohmann::json handleEvent(nlohmann::json event, unsigned long next,
                             nlohmann::json args);
  void setupTable();

 private:
  std::shared_ptr<websocket::music::MAdminContext> context;
  sql::Query query;
};
}  // namespace service
}  // namespace music
#endif  // LOCALPLAYBASE_H
