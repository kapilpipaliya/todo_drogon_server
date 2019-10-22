#include "./timeservicebase.h"

TimeServiceBase::TimeServiceBase(
    int event1, int event2, const drogon::WebSocketConnectionPtr &wsConnPtr,
    std::shared_ptr<websocket::todo::TodoContext> context_,
    std::string &&message)
    : event1(event1),
      event2(event2),
      wsConnPtr(wsConnPtr),
      context(context_),
      message(std::move(message)) {
  dgraphorm = dgraph::DGraphClientManger::getDGraphOrm("1");
}
