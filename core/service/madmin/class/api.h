#ifndef API_H
#define API_H

#include "../../../../wscontroller/context/madmincontext.h"

#include "core/sql/query.h"

namespace music {
namespace service {
class Api {
 public:
  Api(std::shared_ptr<websocket::music::MAdminContext>);
  nlohmann::json handleEvent(nlohmann::json event, unsigned long next,
                             nlohmann::json args);
  void setupTable();

 private:
  std::shared_ptr<websocket::music::MAdminContext> context;
  sql::Query query;
};
}  // namespace service
}  // namespace music
#endif  // API_H
