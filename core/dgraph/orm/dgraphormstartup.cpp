#include "./dgraphormstartup.h"

#include <string>

#include "../dgraphclientmanger.h"
#include "./model.h"
namespace dgraph {
namespace orm {
DGraphOrmStartup::DGraphOrmStartup() {
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
}  // namespace orm
}  // namespace dgraph
