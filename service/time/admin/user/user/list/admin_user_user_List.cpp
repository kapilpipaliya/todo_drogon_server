#include "./admin_user_user_List.h"
timeservice::admin::user::user::List::List(
    int event1_, int event2_, const drogon::WebSocketConnectionPtr &wsConnPtr_,
    std::shared_ptr<websocket::todo::TodoContext> context_,
    std::string &&message_)
    : TimeServiceBase(event1_, event2_, wsConnPtr_, context_,
                      std::move(message_))
/*inh*/
/*inh_end*/
{}
void timeservice::admin::user::user::List::run() {
  // run
  /*auto msg = getmsg<timeservice::UserListRequest>();
  auto dgraphorm = dgraph::DGraphClientManger::getDGraphOrm("1");
  auto user = dgraphorm->newmodel("user");
  auto response = new api::Response;
  auto status =
      user->method(dgraph::orm::MethodsType::type, "user", "",
                   dgraph::orm::Params::builder{}.build_shared(), response);
  auto res = new timeservice::UserListResponse();

  res->set_json(response->json());
  sendmsg<timeservice::UserListResponse>(res);*/
  // run_end
}
// extend_class
// extend_class_end
