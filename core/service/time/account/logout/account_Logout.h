#pragma once
#include "core/service/time/timeservicebase.h"
#include "./proto/account_LogoutRequest.pb.h"
#include "./proto/account_LogoutResponse.pb.h"
// inc
// inc_end
namespace timeservice
{
namespace account
{
class Logout: public TimeServiceBase
/*inh*/
/*inh_end*/
{
  public:
    Logout(int event1_, int event2_, const drogon::WebSocketConnectionPtr &wsConnPtr_,
        std::shared_ptr<websocket::todo::TodoContext> context_,
        std::string &&message_);
  void run();
  private:
  // extend_class
  // extend_class_end
};
}
}
