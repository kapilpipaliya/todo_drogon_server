#ifndef METALISSUE_H
#define METALISSUE_H
#include "../../../../wscontroller/context/jadmincontext.h"
#include "core/sql/query.h"

namespace jadmin {
class MetalIssue {
 public:
  MetalIssue(std::shared_ptr<JAdminContext>);
  nlohmann::json handleEvent(nlohmann::json event, unsigned long next,
                             nlohmann::json args);

 private:
  void setupTable();
  nlohmann::json ins(nlohmann::json event, nlohmann::json args);
  nlohmann::json upd(nlohmann::json event, nlohmann::json args);
  std::shared_ptr<JAdminContext> context;
  sqlb::Query query;
};
}  // namespace jadmin
#endif  // METALISSUE_H
