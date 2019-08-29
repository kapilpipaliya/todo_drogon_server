#include "wsfns.h"

WsFns::WsFns()
{

}

void WsFns::sendJson(const WebSocketConnectionPtr &wsConnPtr, nlohmann::json &j)
{
  try
  {
    wsConnPtr->send(j.dump());
    }
    catch (json::parse_error& e)
    {
       SPDLOG_TRACE("message: {}", e.what());
       SPDLOG_TRACE("exception id: {}", e.id);
       SPDLOG_TRACE("byte position of error:", e.byte);
       json r =  std::string("cant parse internal json reason: ") + e.what();
       wsConnPtr->send(r.dump());
    }
}
