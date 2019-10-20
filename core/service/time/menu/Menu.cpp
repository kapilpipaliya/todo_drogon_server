#include "./Menu.h"
timeservice::Menu::Menu(int event1_, int event2_,
                        const drogon::WebSocketConnectionPtr &wsConnPtr_,
                        std::shared_ptr<websocket::todo::TodoContext> context_,
                        std::string &&message_)
    : TimeServiceBase(event1_, event2_, wsConnPtr_, context_,
                      std::move(message_))
/*inh*/
/*inh_end*/
{}
void timeservice::Menu::run() {
  // run
  msg = getmsg<timeservice::MenuRequest>();
  auto menu = getMenu(msg->name());
  auto res = new timeservice::MenuResponse();
  res->set_json(menu);
  sendmsg<timeservice::MenuResponse>(res);
  // run_end
}

std::string timeservice::Menu::getMenu(std::string menu_name) {
  auto response = new api::Response;
  auto dgraphorm = dgraph::DGraphClientManger::getDGraphOrm("1");
  auto menu = dgraphorm->newmodel("menu");
  auto status = menu->method(
      dgraph::orm::MethodsType::eq, "menu_name", menu_name,
      dgraph::orm::Params::builder{}
          .fil(dgraph::orm::Filter::builder{}
                   .add({dgraph::orm::FilterBase::builder{}
                             .add({dgraph::orm::MethodsType::eq,
                                   dgraph::orm::Attributes{}.i("level", 0)})
                             .build()})
                   .build())
          .inc(dgraph::orm::IncludeBase::builder{}
                   .name("children")
                   .as("children")
                   .order({{"position", "asc"}})
                   .build())
          .ord({{"position", "asc"}})
          .build_shared(),
      response);
  auto json = response->json();
  delete response;
  return json;
}

// extend_class

// extend_class_end
