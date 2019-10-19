#pragma once
#include "./proto/MenuRequest.pb.h"
#include "./proto/MenuResponse.pb.h"
#include "core/service/time/timeservicebase.h"
// inc
#include "./menubase.h"
// inc_end
namespace timeservice {
class Menu : public TimeServiceBase
    /*inh*/
    ,
             public MenuBase
/*inh_end*/
{
 public:
  Menu(int event1_, int event2_,
       const drogon::WebSocketConnectionPtr &wsConnPtr_,
       std::shared_ptr<websocket::todo::TodoContext> context_,
       std::string &&message_);
  void run();

 private:
  // extend_class
  timeservice::MenuRequest *msg;
  std::string getMenu(std::string menu_name);
  // extend_class_end
};
}  // namespace timeservice
