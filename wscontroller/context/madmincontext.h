#ifndef CONTEXT_H
#define CONTEXT_H

#include <string>

#include <drogon/WebSocketController.h>
using namespace drogon;

struct ContextUser {
  long id{0};
  std::string type{""};
};

class MAdminContext {
 public:
  MAdminContext(const HttpRequestPtr &req,
                const WebSocketConnectionPtr &wsConnPtr_);

  std::tuple<long, long> generateContext(const HttpRequestPtr &req);
  void setUser();
  long sessionId() { return current_session_id; }
  void setSessionId(long id) { current_session_id = id; }
  void setUserId(long id) { user_id = id; }
  ContextUser &getUser() { return user; }
  long getUserId() { return user_id; }

 private:
  long current_session_id = 0;
  long user_id = 0;
  ContextUser user;
  const WebSocketConnectionPtr &wsConnPtr;
};

#endif  // CONTEXT_H
