#ifndef TIMESERVICEBASE_H
#define TIMESERVICEBASE_H
#include <drogon/WebSocketController.h>
#include <drogon/drogon.h>
#include <memory>
#include "../../../wscontroller/context/todocontext.h"
#include "json.hpp"

#include <memory>
#include "core/dgraph/dgraphclientmanger.h"
class TimeServiceBase {
 public:
  TimeServiceBase();

  std::shared_ptr<dgraph::orm::DGraphOrm> dgraphorm;
};

#endif  // SERVICEBASE_H
