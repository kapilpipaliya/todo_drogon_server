#ifndef DGRAPHORM_H
#define DGRAPHORM_H
#include <map>
#include <memory>
#include <string>

#include "./schema.h"
#include "./type.h"
namespace dgraph {
namespace grpcclient {
class DgraphClient;
}
namespace orm {
// class Schema;
class Model;
// Todo make a function to get new model object: get_model("name")
class DGraphOrm {
 public:
  DGraphOrm(const std::string &client_name);

  std::shared_ptr<dgraph::grpcclient::DgraphClient> dgraphClient;
  std::shared_ptr<Model> model(Schema schema);
  std::shared_ptr<Model> newmodel(std::string name);

 private:
  // function _logger;
  // created models
  std::map<std::string, Schema> models;

  void _set_model_once(const Schema &schema);
  void _generate_type(const std::string &name,
                      const std::vector<std::string> &type);
  void _generate_schema(const std::vector<std::string> &schema);
  // note: removed log, query, mutation functions.
};
}  // namespace orm
}  // namespace dgraph
#endif  // DGRAPHORM_H
