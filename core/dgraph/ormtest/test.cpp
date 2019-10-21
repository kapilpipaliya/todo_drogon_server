#include "./test.h"

#include "../dgraph-js/generated/api.grpc.pb.h"
#include "../dgraph-js/generated/api.pb.h"
#include "../orm/dgraphorm.h"
#include "../orm/model.h"
#include "../orm/schema.h"
#include "./dgraphclientmanger.h"

using namespace dgraph::orm;
Test::Test() {
  auto dgraphorm = dgraph::DGraphClientManger::getDGraphOrm("1");
  /*
    auto user = dgraphorm->newmodel("user");

    auto user2 = dgraphorm->newmodel("user");
    user->error_msg = "errr1";
    user2->error_msg = "errr2";

    auto session = dgraphorm->newmodel("session");

    auto response = new api::Response;
    session->method(
        dgraph::orm::MethodsType::uid, "0x9c57", "",
        dgraph::orm::Params::builder{}
            .inc(IncludeBase::builder{}.name("user").as("user").build())
            .build_shared(),
        response);

    std::cout << user->error_msg << std::endl;
    std::cout << user2->error_msg << std::endl;
    std::cout << response->json() << std::endl;
  */

  auto user = dgraphorm->newmodel("user");
  auto response = new api::Response;
  //  auto status =
  //      user->method(dgraph::orm::MethodsType::has, "uid", "",
  //                   dgraph::orm::Params::builder{}.build_shared(), response);
  //  std::cout << response->json() << std::endl;
  // get count of a type:
  /*{
    user->method(MethodsType::type, "menu", "",
                 Params::builder{}
                     .attributes(Attributes{}.no(true))
                     .inc(IncludeBase::builder{}
                              .name("uid")
                              //.as("user_count")
                              .count(true)
                              //.attributes({"email"})
                              .build())
                     .build_shared(),
                 response);
    std::cout << response->json() << std::endl;
  }*/
  /*// test nested menu saving:
  {
    using a = dgraph::orm::Attributes;
    auto dgraphorm = dgraph::DGraphClientManger::getDGraphOrm("1");
    auto menu = dgraphorm->newmodel("menu");
    auto response = new api::Response;
    {
      // a.u("children", "_:m2");
      auto m = a{}.key("_:m")
                   .s("menu_name", "K")
                   .s("name", "KName")
                   .s("path", "KPath")
                   .n("children", "menu", "_:m2",
                      a{}.s("menu_name", "K1")
                          .s("name", "KName1")
                          .s("path", "KPath1"));
      auto status = menu->create(m, response);

      switch (status) {
        case dgraph::orm::success: {
          auto j = nlohmann::json::parse(response->json());
          auto uid = j["menu"][0]["uid"].get<std::string>();
          break;
        }
        case dgraph::orm::unique_error:
          break;
        default:
          break;
      }
    }
    delete response;
  }*/
  // get admin_menu in correct order:
  /*
{
      menu (func: type(menu)) @filter(eq(menu.level, 0))  {
        k: count(uid)
        menu_name: menu.name
                children: menu.children {
          menu.name
        }

}
}*/
  // Fetch menu
  {
    auto dgraphorm = dgraph::DGraphClientManger::getDGraphOrm("1");
    auto menu = dgraphorm->newmodel("menu");
    //    auto status =
    //        menu->method(dgraph::orm::MethodsType::eq, "menu_name",
    //        "admin_menu",
    //                     dgraph::orm::Params::builder{}
    //                         .fil(Filter::builder{}
    //                                  .add({FilterBase::builder{}
    //                                            .add({MethodsType::eq,
    //                                                  Attributes{}.i("level",
    //                                                  0)})
    //                                            .build()})
    //                                  .build())
    //                         .inc(IncludeBase::builder{}
    //                                  .name("children")
    //                                  .as("children")
    //                                  .order({{"position", "asc"}})
    //                                  .build())
    //                         .ord({{"position", "asc"}})
    //                         .build_shared(),
    //                     response);
    //    std::cout << response->json() << std::endl;
  }
  {
    // test var block
    auto dgraphorm = dgraph::DGraphClientManger::getDGraphOrm("1");
    auto menu = dgraphorm->newmodel("menu");
    menu->add_var_block(
        dgraph::orm::MethodsType::eq, "menu_name", "admin_menu",
        dgraph::orm::Params::builder{}
            .attributes(Attributes{}.no(true))
            .fil(Filter::builder{}
                     .add({FilterBase::builder{}
                               .add({MethodsType::eq,
                                     Attributes{}.i("level", 0)})
                               .build()})
                     .build())
            .inc(IncludeBase::builder{}
                     .name("children")
                     .as("children")
                     .var("A")
                     .order({{"position", "asc"}})
                     .params(Params::builder{}
                                 .inc(IncludeBase::builder{}
                                          .name("children")
                                          .as("children")
                                          .count(true)
                                          .var("B")
                                          .build())
                                 .build_shared())
                     .build())
            .ord({{"position", "asc"}})
            .build_shared());

    auto status = menu->method(
        dgraph::orm::MethodsType::eq, "menu_name", "admin_menu",
        dgraph::orm::Params::builder{}
            .fil(Filter::builder{}
                     .add({FilterBase::builder{}
                               .add({MethodsType::uid,
                                     Attributes{}.u1("", {"A", "B"})})
                               .build()})
                     .build())
            .inc(IncludeBase::builder{}
                     .name("children")
                     .as("children")
                     .order({{"position", "asc"}})
                     .build())
            .ord({{"position", "asc"}})
            .build_shared(),
        response);
    std::cout << response->json() << std::endl;
  }
}
/*
 {
      menu (func: eq(menu.menu_name, "admin_menu"))  @filter(NOT uid("0xeb8b"))
 { uid # menu.menu_name name: menu.name # path: menu.path # caption:
 menu.caption # icon: menu.icon # param: menu.param # help: menu.help
        menu.children {
          uid
          menu.name
          # menu.path
        }
        k: count(uid)
      }
    }*/
/*
      menu (func: eq(menu.menu_name, "admin_menu"))  @filter(NOT
   eq(count(menu.children), 0))   { uid menu.menu_name name: menu.name path:
   menu.path caption: menu.caption icon: menu.icon param: menu.param help:
   menu.help menu.children { uid menu.name menu.path
        }
        k: count(uid)
      }
    }*/
