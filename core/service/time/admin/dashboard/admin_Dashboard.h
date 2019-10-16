#pragma once
#include "core/service/time/timeservicebase.h"
namespace timeservice
{
namespace admin
{
class Dashboard: public TimeServiceBase
{
  public:
    Dashboard(int event1, int event2, const drogon::WebSocketConnectionPtr &wsConnPtr,
        std::shared_ptr<websocket::todo::TodoContext> context_,
        nlohmann::json args);
  void run();
  private:
  // manual_part
  // manual_part_end
};
}
}
