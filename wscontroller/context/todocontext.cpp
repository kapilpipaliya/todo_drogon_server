#include "todocontext.h"

#include "dgraph/dgraphclientmanger.h"
#include "dgraph/orm/dgraphorm.h"
#include "dgraph/orm/model.h"

namespace websocket {
namespace todo {

TodoContext::TodoContext(const drogon::HttpRequestPtr &req,
                         const drogon::WebSocketConnectionPtr &wsConnPtr_)
    : wsConnPtr(wsConnPtr_) {
  cookie = req->getCookie("time");
  std::cout << cookie << std::endl;
  std::cout.flush();
  updateContext();
}

void TodoContext::updateContext() {
  // get session from the session schema.
  auto dgraphorm = dgraph::DGraphClientManger::getDGraphOrm("1");
  auto user_ = dgraphorm->newmodel("user");
  auto session_ = dgraphorm->newmodel("session");

  auto response = new api::Response;

  session_->method(dgraph::orm::MethodsType::uid, "0x9c57", "",
                   dgraph::orm::Params::builder{}
                       .inc(dgraph::orm::IncludeBase::builder{}
                                .name("user")
                                .as("user")
                                .build())
                       .build_shared(),
                   response);
  //{"session":[{"uid":"0x9c57","user":{"uid":"0x9c56","name":"kapil","email":"kapil"}}]}
  auto j = nlohmann::json::parse(response->json());
  auto u = j["session"][0]["user"];
  if (u.is_object()) {
    session.session_uid = j["session"][0]["uid"];

    user.uid = u["uid"].get<std::string>();
    user.name = u["name"];
    // user.email = u["email"];
  }
}

}  // namespace todo
}  // namespace websocket
