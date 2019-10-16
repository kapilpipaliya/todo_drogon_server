#ifndef TIMESERVICEBASE_H
#define TIMESERVICEBASE_H
#include <drogon/WebSocketController.h>
#include <drogon/drogon.h>

#include <memory>

#include "../../../wscontroller/context/todocontext.h"
#include "core/dgraph/dgraphclientmanger.h"
#include "json.hpp"
class TimeServiceBase {
 public:
  TimeServiceBase(int event1, int event2,
                  const drogon::WebSocketConnectionPtr &wsConnPtr,
                  std::shared_ptr<websocket::todo::TodoContext> context_,
                  std::string &&message);

  int event1;
  int event2;
  drogon::WebSocketConnectionPtr wsConnPtr;
  std::shared_ptr<websocket::todo::TodoContext> context;
  std::string message;

  std::shared_ptr<dgraph::orm::DGraphOrm> dgraphorm;
};

#endif  // SERVICEBASE_H
