#ifndef SETTING_H
#define SETTING_H

#include "../../../../wscontroller/context/jadmincontext.h"
#include "core/sql/query.h"

namespace jadmin {
namespace service {
class Setting {
 public:
  Setting(std::shared_ptr<websocket::jadmin::JAdminContext>);
  nlohmann::json handleEvent(nlohmann::json event, unsigned long next,
                             nlohmann::json args);

 private:
  void setupTable();
  nlohmann::json save(const nlohmann::json& event, nlohmann::json args);
  nlohmann::json del(nlohmann::json event, nlohmann::json args);
  std::shared_ptr<websocket::jadmin::JAdminContext> context;
  sql::Query query;
};
}  // namespace service
}  // namespace jadmin
#endif  // SETTING_H
