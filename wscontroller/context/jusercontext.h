#pragma once

#include <drogon/WebSocketController.h>
namespace websocket {
namespace juser {
class JUserContext {
 public:
  JUserContext(const drogon::HttpRequestPtr &req,
               const drogon::WebSocketConnectionPtr &wsConnPtr_);
  std::tuple<long, long> generateContext(const drogon::HttpRequestPtr &req,
                                         const std::string &account_type);
  void setUser();
  long sessionId() { return current_session_id; }
  void setSessionId(long id) { current_session_id = id; }
  void setUserId(long id) { user_id = id; }
  long getUserId() { return user_id; }

 private:
  long current_session_id = 0;
  long user_id = 0;
  const drogon::WebSocketConnectionPtr &wsConnPtr;
};
}  // namespace juser
}  // namespace websocket
