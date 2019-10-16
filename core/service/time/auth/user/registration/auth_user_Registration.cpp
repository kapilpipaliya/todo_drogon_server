#include "./auth_user_Registration.h"
timeservice::auth::user::Registration::Registration(
    int event1_, int event2_, const drogon::WebSocketConnectionPtr &wsConnPtr_,
    std::shared_ptr<websocket::todo::TodoContext> context_,
    std::string &&message_)
    : TimeServiceBase(event1_, event2_, wsConnPtr_, context_,
                      std::move(message_)) {}
void timeservice::auth::user::Registration::run() {
  // run
  auto me = new timeservice::RegistrationRequest();
  me->ParseFromString(message);
  std::cout << "hi" << me->name() << std::endl;
  std::cout << me->username() << std::endl;
  std::cout << me->password() << std::endl;
  std::cout.flush();
  // run_end
}
// extend_class
// extend_class_end
