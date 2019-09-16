#ifndef USERACTORBASE_H
#define USERACTORBASE_H

#include <drogon/WebSocketController.h>
#include "json.hpp"
namespace superactor {
namespace system {
class UserActorBase {
 public:
  UserActorBase();
  virtual ~UserActorBase();

 protected:
  virtual void blocking_run(const drogon::WebSocketConnectionPtr &wsConnPtr,
                            std::string &&message,
                            const drogon::WebSocketMessageType &type);
  virtual nlohmann::json handleTextMessage(
      const drogon::WebSocketConnectionPtr &wsConnPtr,
      const nlohmann::json &in) = 0;
  virtual nlohmann::json handleBinaryMessage(
      const drogon::WebSocketConnectionPtr &wsConnPtr,
      std::string &message) = 0;
};
}  // namespace system
}  // namespace superactor
#endif  // USERACTORBASE_H
