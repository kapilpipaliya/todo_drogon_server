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
}
