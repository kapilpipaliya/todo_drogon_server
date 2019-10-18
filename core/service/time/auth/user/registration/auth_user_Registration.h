#pragma once
#include "core/service/time/timeservicebase.h"
#include "./proto/auth_user_RegistrationRequest.pb.h"
#include "./proto/auth_user_RegistrationResponse.pb.h"
namespace timeservice
{
namespace auth
{
namespace user
{
class Registration: public TimeServiceBase
{
  public:
    Registration(int event1_, int event2_, const drogon::WebSocketConnectionPtr &wsConnPtr_,
        std::shared_ptr<websocket::todo::TodoContext> context_,
        std::string &&message_);
  void run();
  private:
  // extend_class
  timeservice::RegistrationRequest *msg;
  std::string createuser();
  // extend_class_end
};
}
}
}
