#include "./auth_user_Login.h"
timeservice::auth::user::Login::Login(
    int event1_, int event2_, const drogon::WebSocketConnectionPtr &wsConnPtr_,
    std::shared_ptr<websocket::todo::TodoContext> context_,
    std::string &&message_)
: TimeServiceBase(event1_, event2_, wsConnPtr_, context_,
                      std::move(message_)) {}
void timeservice::auth::user::Login::run()
{
  // run
  // run_end
}
  // extend_class
  // extend_class_end
