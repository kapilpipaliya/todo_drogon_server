#pragma once
#include "core/service/time/timeservicebase.h"
#include "./proto/MenuRequest.pb.h"
#include "./proto/MenuResponse.pb.h"
namespace timeservice
{
class Menu: public TimeServiceBase
/*inh*/
/*inh_end*/
{
  public:
    Menu(int event1_, int event2_, const drogon::WebSocketConnectionPtr &wsConnPtr_,
        std::shared_ptr<websocket::todo::TodoContext> context_,
        std::string &&message_);
  void run();
  private:
  // extend_class
      void create_menu(std::string type, std::string name, std::string path, std::string icon = "");
  // extend_class_end
};
}
