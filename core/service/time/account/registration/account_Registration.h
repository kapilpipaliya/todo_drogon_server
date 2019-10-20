#pragma once
#include "core/service/time/timeservicebase.h"
#include "./proto/account_RegistrationRequest.pb.h"
#include "./proto/account_RegistrationResponse.pb.h"
// inc
// inc_end
namespace timeservice
{
namespace account
{
class Registration: public TimeServiceBase
/*inh*/
/*inh_end*/
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
