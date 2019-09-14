#ifndef LABEL_H
#define LABEL_H

#include "../../../../wscontroller/context/madmincontext.h"

#include "core/sql/query.h"

namespace madmin {
class Label {
 public:
  Label(std::shared_ptr<websocket::MAdminContext>);
  nlohmann::json handleEvent(nlohmann::json event, unsigned long next,
                             nlohmann::json args);
  void setupTable();

 private:
  std::shared_ptr<websocket::MAdminContext> context;
  sql::Query query;
};
}  // namespace madmin
#endif  // LABEL_H
