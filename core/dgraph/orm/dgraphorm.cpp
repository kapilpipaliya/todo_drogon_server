#include "dgraphorm.h"

#include <pystring/pystring.h>

#include "../dgraphclientmanger.h"
#include "../dgraphgrpc/dgraphclient.h"
#include "./model.h"
#include "./schema.h"

//#include "../dgraphhttp/dgraphclient.h"
//#include "../dgraphhttp/dgraphclientstub.h"
#include "../dgraphgrpc/dgraphclient.h"

namespace dgraph {
namespace orm {
DGraphOrm::DGraphOrm(const std::string &client_name) {
  dgraphClient = dgraph::DGraphClientManger::getDGraphGrpcClient(client_name);
}

std::shared_ptr<Model> DGraphOrm::model(Schema schema) {
  _set_model_once(schema);

  auto ptr = std::make_shared<Model>(schema, models, dgraphClient);
  return ptr;
}

std::shared_ptr<Model> DGraphOrm::newmodel(std::string name) {
  auto find = models.find(name);
  assert(find != models.end());

  auto ptr =
      std::make_shared<Model>(models.find(name)->second, models, dgraphClient);
  return ptr;
}

void DGraphOrm::_set_model_once(const Schema &schema) {
  if (!schema.name.empty() && models.find(schema.name) == models.end()) {
    models.insert({schema.name, schema});
    _generate_type(schema.name, schema.type);
    _generate_schema(schema.schema);
  }
}

void DGraphOrm::_generate_type(const std::string &name,
                               const std::vector<std::string> &type) {
  api::Operation op;
  std::string t = "\ntype " + name + "{\n";
  t += pystring::join("\n", type);
  t += "\n}\n";
  op.set_schema(t);
  auto response = new api::Payload;
  dgraphClient->alter(op, response);
}

void DGraphOrm::_generate_schema(const std::vector<std::string> &schema) {
  api::Operation op;
  op.set_schema("\n" + pystring::join("\n", schema) + "\n");
  //  LOG_DEBUG << "--------------------CREATING SCHEMA--------------------";
  //  LOG_DEBUG << "\n" << op.schema << "\n";
  //  LOG_DEBUG << "-------------------------------------------------------";
  auto response = new api::Payload;
  dgraphClient->alter(op, response);
}
}  // namespace orm
}  // namespace dgraph
   /*type Person {
       person.name1: string
       person.age: int
       person.friend: [Person]
   }*/
