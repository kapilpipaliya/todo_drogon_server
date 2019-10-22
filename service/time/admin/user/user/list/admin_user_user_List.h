#pragma once
#include "service/time/timeservicebase.h"
#include "./proto/admin_user_user_ListRequest.pb.h"
#include "./proto/admin_user_user_ListResponse.pb.h"
// inc
// inc_end
namespace timeservice
{
namespace admin
{
namespace user
{
namespace user
{
class List: public TimeServiceBase
/*inh*/
/*inh_end*/
{
  public:
    List(int event1_, int event2_, const drogon::WebSocketConnectionPtr &wsConnPtr_,
        std::shared_ptr<websocket::todo::TodoContext> context_,
        std::string &&message_);
  void run();
  private:
  // extend_class
  // extend_class_end
};
}
}
}
}
