#ifndef USERACTORBASE_H
#define USERACTORBASE_H

#include <drogon/WebSocketController.h>
#include "json.hpp"

using namespace drogon;
using nlohmann::json;

class UserActorBase {
 public:
  UserActorBase();

 protected:
  virtual void blocking_run(const WebSocketConnectionPtr &wsConnPtr,
                            std::string &&message,
                            const WebSocketMessageType &type);
  virtual json handleTextMessage(const WebSocketConnectionPtr &wsConnPtr,
                                 json in) = 0;
  virtual json handleBinaryMessage(const WebSocketConnectionPtr &wsConnPtr,
                                   std::string &message) = 0;
};

#endif  // USERACTORBASE_H
