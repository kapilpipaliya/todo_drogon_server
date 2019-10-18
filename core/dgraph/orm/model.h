#ifndef DGRAPHORMMODEL_H
#define DGRAPHORMMODEL_H
// TODO fix delete functions.
// TODO fix update : when passed object.
// Todo fix delete : when passed object
// Todo fix delete : when passed object with some value set to null.
// Todo fix relation function - useless?
// Todo fix uid_in function. look at orm example but its not proper.
/*
on _create it check unique values.
on _update it also should check for unique values.
*/

#include "../dgraph-js/generated/api.grpc.pb.h"
#include "../dgraph-js/generated/api.pb.h"
#include "../dgraphgrpc/dgraphclient.h"
#include "./query.h"
#include "./schema.h"
#include "./type.h"

namespace dgraph {
namespace orm {
// No Json in this class please
class Model {
 public:
  Schema schema;
  std::string error_msg;

  Model(Schema schema, std::map<std::string, Schema> &models,
        std::shared_ptr<dgraph::grpcclient::DgraphClient> dgraphClient);
  void relation(std::string uid, RelationParam params, api::Response *response);
  bool checkPassword(std::string uid, std::string field, std::string password);
  void query(std::string query, api::Response *response);
  void queryWithVars(QueryParams params, api::Response *response);
  error_type create(Attributes &attributes, api::Response *response);
  void update(const std::string &uid, Attributes &attributes,
              api::Response *response);
  // void delete_(nlohmann::json params, api::Response *response);
  void delete_(std::string uid, api::Response *response);
  void delete_(std::vector<std::string> &uid, api::Response *response);

  void method(MethodsType type, const std::string &field,
              const std::string &value, const std::shared_ptr<Params> params,
              api::Response *response);

 private:
  std::map<std::string, Schema> &models;
  std::shared_ptr<dgraph::grpcclient::DgraphClient> dgraphClient;
  // Connection connection;
  // function _logger;

  bool _check_if_password_type(std::string field);
  // void _generate_methods();
  void _execute(std::string query, api::Response *response);
  bool _is_relation(std::string _key);
  void _parse_mutation(Attributes &attributes, std::string name);
  error_type _create(Attributes &attributes, api::Response *response);
  void _update(const std::string &uid, Attributes &attributes,
               api::Response *response);
  std::string get_del_nquads(const std::string &uid);
  void _delete(const std::string &mutation, api::Response *response);
  std::vector<FieldProps> _get_unique_fields();
  bool _check_unique_values(Attributes &attributes,
                            std::shared_ptr<grpcclient::Txn> _txn,
                            api::Response *response);
  static std::vector<std::string> _lang_fields(
      std::vector<FieldProps> original);
  void _check_attributes(std::vector<FieldProps> original,
                         const Attributes &attributes, bool isUpdate = false,
                         bool isRelation = false);
  static Attributes _all_attributes(std::vector<FieldProps> original);
  std::shared_ptr<Params> _validate(std::vector<FieldProps> original,
                                    std::shared_ptr<Params> params = {});
};
}  // namespace orm
}  // namespace dgraph
#endif  // DGRAPHORMMODEL_H
