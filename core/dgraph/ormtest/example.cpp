#include "./example.h"

#include "../dgraph-js/generated/api.grpc.pb.h"
#include "../dgraph-js/generated/api.pb.h"
#include "../orm/dgraphorm.h"
#include "../orm/model.h"
#include "../orm/schema.h"
#include "./dgraphclientmanger.h"
using namespace dgraph::orm;

Example::Example() {
  auto dgraphorm = dgraph::DGraphClientManger::getDGraphOrm("1");

  auto user = dgraphorm->model(Schema{
      "user",
      {FieldProps::builder{}
           .name("name")
           .type(TypesType::STRING)
           .index(true)
           .lang(true)
           .token(
               Token::builder{}.term(true).trigram(true).fulltext(true).build())
           .build(),
       FieldProps::builder{}
           .name("email")
           .type(TypesType::STRING)
           .index(true)
           .unique(true)
           .token(Token::builder{}.exact(true).build())
           .build(),
       FieldProps::builder{}.name("password").type(TypesType::PASSWORD).build(),
       FieldProps::builder{}.name("bio").type(TypesType::STRING).build(),
       FieldProps::builder{}
           .name("age")
           .type(TypesType::INT)
           .index(true)
           .build(),
       FieldProps::builder{}
           .name("friend")
           .type(TypesType::UID)
           .model("user")
           .count(true)
           .reverse(true)
           .build(),
       FieldProps::builder{}
           .name("avatar")
           .type(TypesType::UID)
           .model("media")
           .reverse(true)  //.replace(true) not works
           .build()}});
  auto post = dgraphorm->model(Schema{
      "post",
      {FieldProps::builder{}.name("title").type(TypesType::STRING).build(),
       FieldProps::builder{}
           .name("content")
           .type(TypesType::STRING)

           .build(),
       FieldProps::builder{}
           .name("author")
           .type(TypesType::UID)
           .model("user")
           .replace(true)
           .build(),
       FieldProps::builder{}
           .name("banner")
           .type(TypesType::UID)
           .model("media")
           //.replace(true)
           .build()}});
  auto media = dgraphorm->model(Schema{
      "media",
      {FieldProps::builder{}.name("type").type(TypesType::STRING).build(),
       FieldProps::builder{}.name("src").type(TypesType::STRING).build()}});
}

void Example::test() {
  auto dgraphorm = dgraph::DGraphClientManger::getDGraphOrm("1");
  auto user = dgraphorm->newmodel("user");
  auto post = dgraphorm->newmodel("post");
  auto media = dgraphorm->newmodel("media");

  /**
   * User.near(field: String, value = {
   *  latitude: float,
   *  longitude: float
   *  distance: number
   * }, options);
   *
   * User.contains(field: String, value = {
   *  latitude: float,
   *  longitude: float
   * }, options);
   */

  auto response = new api::Response;
  user->method(MethodsType::has, "email", "", Params::builder{}.build_shared(),
               response);
  std::cout << response->json() << std::endl;
  user->method(MethodsType::eq, "email", "kapil.pipaliya@yahoo.com",
               Params::builder{}.build_shared(), response);
  std::cout << response->json() << std::endl;
  user->method(MethodsType::uid, "0xabc", "", Params::builder{}.build_shared(),
               response);
  std::cout << response->json() << std::endl;
  // must indexed with term:
  user->method(MethodsType::allofterms, "name", "all of terms",
               Params::builder{}.build_shared(), response);
  std::cout << response->json() << std::endl;
  // must indexed with term:
  user->method(MethodsType::anyofterms, "name", "anyofterms",
               Params::builder{}.build_shared(), response);
  std::cout << response->json() << std::endl;
  // must indexed with fulltext:
  user->method(MethodsType::anyoftext, "name", "anyoftext",
               Params::builder{}.build_shared(), response);
  std::cout << response->json() << std::endl;
  // must indexed with fulltext:
  user->method(MethodsType::alloftext, "name", "alloftext",
               Params::builder{}.build_shared(), response);
  std::cout << response->json() << std::endl;
  user->method(MethodsType::regexp, "name", "/regexp/",
               Params::builder{}.build_shared(), response);
  std::cout << response->json() << std::endl;

  Attributes a1_;
  a1_.s("name", "Someone")
      .s("email", "someone@gmail.com")
      .s("bio", "Performance and load tester")
      .s("password", "p@ssw@rd");
  auto u1_ = user->create(a1_, response);
  nlohmann::json u1j_ = nlohmann::json::parse(response->json());
  auto u1 = u1j_["user"][0]["uid"].get<std::string>();

  Attributes a2__;
  a2__.s("name", "Someone1")
      .s("email", "someone@gmail.com1")
      .s("bio", "Performance and load tester1")
      .s("password", "p@ssw@rd1");
  auto a2___ = user->create(a2__, response);
  nlohmann::json a2____ = nlohmann::json::parse(response->json());
  auto u2 = a2____["user"][0]["uid"].get<std::string>();

  // user->delete_(u1, response);

  Attributes a2_;
  a2_.s("name@fr", "Parinita Sharma");
  a2_.s("name", "Parinita Sharma");
  user->update(u1, a2_, response);

  // const pari = await User.uid("0x1", {
  //   first: 1
  // });
  // console.log(pari);

  user->method(MethodsType::uid, u1, "", Params::builder{}.build_shared(),
               response);
  std::cout << response->json() << std::endl;

  Attributes a3_;
  a3_.s("name", "Parinita Sharma")
      .s("bio", "Co Founder and COO, Impulsive Web Pvt. Ltd.");
  user->update(u1, a3_, response);

  // user->delete_(u1, response);

  user->method(MethodsType::has, "name", "", Params::builder{}.build_shared(),
               response);
  std::cout << response->json() << std::endl;

  auto _check = user->checkPassword(u1, "password", "p@ssw@rd");
  std::cout << _check << std::endl;

  Attributes a4_;
  a4_.u("friend", {u2});
  user->update(u1, a4_, response);

  // await User.delete({
  //   friend: ["0x271c", "0x2711"]
  // }, "0x1");

  user->method(
      MethodsType::has, "name", "",
      Params::builder{}
          .inc(IncludeBase::builder{}.name("friend").as("friends").build())
          .build_shared(),
      response);
  std::cout << response->json() << std::endl;

  // await User.delete({
  //   name: null
  // }, ["0x271c", "0x2711"]);

  Attributes a5_;
  a5_.i("age", 32);

  user->method(
      MethodsType::has, "email", "",
      Params::builder{}
          .ord({{"email", "desc"}, {"name", "asc"}})
          .first(5)
          .fil(Filter::builder{}
                   .add(FilterBase::builder{}
                            .add({MethodsType::eq, Attributes{}.i("age", 32)})
                            .add({MethodsType::le, Attributes{}.i("age", 30)})
                            .build())
                   .add(filtertype::fltor,
                        FilterBase::builder{}
                            .type(filtertype::fltor)
                            .add({MethodsType::eq, Attributes{}.i("age", 50)})
                            .build())
                   .build())
          .build_shared(),
      response);
  std::cout << response->json() << std::endl;

  post->method(MethodsType::has, "title", "", Params::builder{}.build_shared(),
               response);
  std::cout << response->json() << std::endl;

  Attributes m1_;
  m1_.s("type", "image")
      .s("src",
         "https://miro.medium.com/max/3150/1*RJuEp_08DylEspADBgsHoQ.jpeg");
  auto m1__ = media->create(m1_, response);
  nlohmann::json m1___ = nlohmann::json::parse(response->json());
  auto m1 = m1___["media"][0]["uid"].get<std::string>();

  media->method(MethodsType::has, "src", "", Params::builder{}.build_shared(),
                response);
  std::cout << response->json() << std::endl;

  // const user = await User.relation("0x2711", {
  //   field: "friend",
  //   attributes: {
  //     friend: ["uid", "name"]
  //   }
  // });

  // console.log(user);
  //  RelationParam r{{"friend"}, {"uid", {"name"}}};
  //  user->relation(u1, r, response);

  Attributes p3_;
  p3_.s("title", "A new sample post")
      .s("content", "<p>Sample content</p>")
      .u("author", u1);
  auto p3__ = post->create(p3_, response);
  nlohmann::json p3___ = nlohmann::json::parse(response->json());
  auto p1 = p3___["post"][0]["uid"].get<std::string>();

  Attributes p2_;
  p2_.u("author", u2);
  post->update(p1, p2_, response);
  // await Post.delete({
  //   author: "0x1"
  // }, "0xc351");

  // await User.delete({
  //   name: null
  // }, "0xea63");

  // const user = await User.has("friend", {
  //   include: {
  //     friend: {
  //       as: "friends",
  //       include: {
  //         friend: {
  //           as: "friends",
  //           include: {
  //             friend: {
  //               as: "friends",
  //             }
  //           }
  //         }
  //       }
  //     }
  //   }
  // });

  // console.log(user);

  Attributes m2_;
  m2_.s("type", "image").s("src", "myname.jpg");
  auto m2__ = media->create(m2_, response);
  nlohmann::json m2___ = nlohmann::json::parse(response->json());
  auto m2 = m2___["media"][0]["uid"].get<std::string>();

  Attributes u6_;
  u6_.u("avatar", m2);
  user->update(u1, u6_, response);

  post->method(MethodsType::has, "", "", Params::builder{}.build_shared(),
               response);
  std::cout << response->json() << std::endl;

  Attributes p5_;
  p5_.u("banner", m2);
  post->update(p1, p5_, response);

  post->method(
      MethodsType::uid, p1, "",
      Params::builder{}
          .inc(IncludeBase::builder{}
                   .name("author")
                   .as("author")
                   .params(Params::builder{}
                               .inc(IncludeBase::builder{}
                                        .name("friend")
                                        .as("friend")
                                        .build())
                               .inc(IncludeBase::builder{}
                                        .name("avatar")
                                        .as("avatar")
                                        .build())
                               .build_shared())
                   .build())
          .inc(IncludeBase::builder{}.name("banner").as("banner").build())
          .build_shared(),
      response);
  std::cout << response->json() << std::endl;
}
