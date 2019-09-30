#ifndef _MyActor_H
#define _MyActor_H


#include "caf/all.hpp"

#include "useractorbase.h"
namespace superactor {
namespace myactor {
class MyActor : public caf::event_based_actor,
                    public system::UserActorBase {
 public:
  MyActor(caf::actor_config& cfg);

 protected:
  caf::behavior make_behavior() override;

 private:
  nlohmann::json handleTextMessage(
      const drogon::WebSocketConnectionPtr& wsConnPtr,
      const nlohmann::json& in) override;
  nlohmann::json handleBinaryMessage(
      const drogon::WebSocketConnectionPtr& wsConnPtr,
      std::string& message) override;

  template <typename T>
  nlohmann::json handleService(
      //std::shared_ptr<websocket::music::MAdminContext> contx,
      nlohmann::json in) {
    try {
      // T p{contx};
      T p;
      auto r = p.handleEvent(in[0], 1, in[1]);
      if (!r.is_null()) return r;
      return nlohmann::json::array();
    } catch (const std::exception& e) {
      LOG_DEBUG << e.what();
      return nlohmann::json::array({{e.what()}});
    }
  }
};
}  // namespace myactor
}  // namespace superactor
#endif
