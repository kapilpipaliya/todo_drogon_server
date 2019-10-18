#ifndef TIMESERVICEBASE_H
#define TIMESERVICEBASE_H
#include <drogon/WebSocketController.h>
#include <drogon/drogon.h>

#include <memory>

#include "../../../wscontroller/context/todocontext.h"
#include "../../dgraph/orm/dgraphorm.h"
#include "../../dgraph/orm/model.h"
//#include "../../dgraph/orm/schema.h"

#include "core/dgraph/dgraphclientmanger.h"
#include "json.hpp"
class TimeServiceBase {
 public:
  TimeServiceBase(int event1, int event2,
                  const drogon::WebSocketConnectionPtr &wsConnPtr,
                  std::shared_ptr<websocket::todo::TodoContext> context_,
                  std::string &&message);

  template <typename T>
  T *getmsg() {
    auto m = new T;
    m->ParseFromString(message);
    return m;
  }
  template <typename T>
  void sendmsg(T *response) {
    auto s = new std::string;
    *s += static_cast<char>(event1);
    *s += static_cast<char>(event2);
    response->AppendToString(s);

    wsConnPtr->send(*s, drogon::WebSocketMessageType::Binary);
    delete s;
  }

  int event1;
  int event2;
  drogon::WebSocketConnectionPtr wsConnPtr;
  std::shared_ptr<websocket::todo::TodoContext> context;
  std::string message;

  std::shared_ptr<dgraph::orm::DGraphOrm> dgraphorm;
};

#endif  // SERVICEBASE_H
