#pragma once
#include "./proto/auth_user_RegistrationRequest.pb.h"
#include "./proto/auth_user_RegistrationResponse.pb.h"
#include "core/service/time/timeservicebase.h"
namespace timeservice {
namespace auth {
namespace user {
class Registration : public TimeServiceBase {
 public:
  Registration(int event1_, int event2_,
               const drogon::WebSocketConnectionPtr &wsConnPtr_,
               std::shared_ptr<websocket::todo::TodoContext> context_,
               std::string &&message_);
  void run();

  // extend_class
  // extend_class_end
};
}  // namespace user
}  // namespace auth
}  // namespace timeservice
