#include "./account_Registration.h"
timeservice::account::Registration::Registration(
    int event1_, int event2_, const drogon::WebSocketConnectionPtr &wsConnPtr_,
    std::shared_ptr<websocket::todo::TodoContext> context_,
    std::string &&message_)
    : TimeServiceBase(event1_, event2_, wsConnPtr_, context_,
                      std::move(message_))
/*inh*/
/*inh_end*/
{}
void timeservice::account::Registration::run() {
  // run
  msg = getmsg<timeservice::RegistrationRequest>();

  auto res = new timeservice::RegistrationResponse();
  if (msg->username().length() < 5) {
    res->set_status(timeservice::RegistrationResponse::INVALID_USERNAME);
    res->set_error_msg("User name should be at least 5 characters");
    sendmsg<timeservice::RegistrationResponse>(res);
    return;
  }
  if (msg->password().length() < 6) {
    res->set_status(timeservice::RegistrationResponse::WEAK_PASSWORD);
    res->set_error_msg("Password should be at least 6 characters");
    sendmsg<timeservice::RegistrationResponse>(res);
    return;
  }

  auto dgraphorm = dgraph::DGraphClientManger::getDGraphOrm("1");
  auto user = dgraphorm->newmodel("user");
  auto session = dgraphorm->newmodel("session");

  auto response = new api::Response;
  auto u = user->create(dgraph::orm::Attributes{}
                            .key("_:u1")
                            .s("firstname", msg->username())
                            .s("login", msg->username())
                            .s("password", msg->password()),
                        response);
  switch (u) {
    case dgraph::orm::success: {
      auto j = nlohmann::json::parse(response->json());
      auto uid = j["user"][0]["uid"].get<std::string>();

      {
        auto s = session->create(
            dgraph::orm::Attributes{}.key("_:s1").u("user", uid), response);
        auto j_s = nlohmann::json::parse(response->json());
        auto uid_session = j_s["session"][0]["uid"].get<std::string>();

        res->set_status(timeservice::RegistrationResponse::OK);
        res->set_token(uid_session);
        // set context
        {
          context->session.session_uid = uid_session;
          context->user.uid = uid;
          context->user.name = msg->name();
          // todo: context->user.parent_uid = todo
        }
      }
      break;
    }
    case dgraph::orm::unique_error:
      res->set_status(timeservice::RegistrationResponse::INVALID_USERNAME);
      std::cout << user->error_msg << std::endl;
      res->set_error_msg(
          "User name already exists. please choose different username.");
      break;
    default:
      res->set_status(timeservice::RegistrationResponse::UNKNOWN_ERROR);
      res->set_error_msg(user->error_msg);
  }
  delete response;

  sendmsg<timeservice::RegistrationResponse>(res);
  // run_end
}
// extend_class
// extend_class_end
