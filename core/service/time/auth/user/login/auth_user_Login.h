#pragma once
#include "core/service/time/timeservicebase.h"
#include "./proto/auth_user_LoginRequest.pb.h"
#include "./proto/auth_user_LoginResponse.pb.h"
namespace timeservice
{
namespace auth
{
namespace user
{
class Login: public TimeServiceBase
{
  public:
    Login(int event1_, int event2_, const drogon::WebSocketConnectionPtr &wsConnPtr_,
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
