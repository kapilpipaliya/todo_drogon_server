#pragma once
#include "core/service/time/timeservicebase.h"
#include "./proto/auth_user_LogoutRequest.pb.h"
#include "./proto/auth_user_LogoutResponse.pb.h"
namespace timeservice
{
namespace auth
{
namespace user
{
class Logout: public TimeServiceBase
{
  public:
    Logout(int event1_, int event2_, const drogon::WebSocketConnectionPtr &wsConnPtr_,
        std::shared_ptr<websocket::todo::TodoContext> context_,
        std::string &&message_);
  void run();
  private:
      std::string message;
  // extend_class
  // extend_class_end
};
}
}
}
