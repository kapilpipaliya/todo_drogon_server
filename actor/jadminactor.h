#ifndef _JADMINACTOR_H
#define _JADMINACTOR_H

#include "caf/all.hpp"

#include "useractorbase.h"
namespace superactor {
namespace jadminactor {
class JAdminActor : public caf::event_based_actor, public UserActorBase {
 public:
  JAdminActor(caf::actor_config& cfg);

 protected:
  caf::behavior make_behavior() override;

 private:
  nlohmann::json handleTextMessage(
      const drogon::WebSocketConnectionPtr& wsConnPtr,
      const nlohmann::json& in) override;
  nlohmann::json handleBinaryMessage(
      const drogon::WebSocketConnectionPtr& wsConnPtr,
      std::string& message) override;
};
}  // namespace jadminactor
}  // namespace superactor
#endif
