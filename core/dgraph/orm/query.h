#ifndef DGRAPHORMQUERY_H
#define DGRAPHORMQUERY_H
#include <any>

#include <string>
#include <vector>
#include "./type.h"
namespace dgraph {
namespace orm {
class Query {
 private:
  // std::vector<std::string> _conditions{"$or", "$and"};
  // std::string name;
  // std::shared_ptr<Params> params;
  // MethodsType type;
  // std::string field;
  // std::string value;
  // function logger;
  std::string where;

  static std::string _where(MethodsType type, std::string field,
                            const std::string &func_value,
                            const std::string &name);
  // std::string _filter(std::string key, nlohmann::json value, std::string
  // name);
  std::string _filter1(FilterBase &base, const std::string &name);
  std::string _filter(const std::string &key, const std::string &value,
                      const std::string &name);
  std::string _parse_filter(Filter filter, const std::string &name);
  std::string _attributes(Attributes attributes, const std::string &name);
  std::string _include(std::vector<IncludeBase> &include,
                       const std::string &name);
  std::string _extras(std::shared_ptr<Params> params);
  std::string _parse_order(
      std::vector<std::pair<std::string, std::string> > &order,
      const std::string &name);
  std::string _build(const std::shared_ptr<Params> &params,
                     const std::string &name);

  static std::string methodTypeToString(MethodsType type);

 public:
  Query(MethodsType type, const std::string &field,
        const std::string &func_value, std::shared_ptr<Params> params,
        const std::string &name);
  Query(MethodsType type, std::vector<std::string> field,
        const std::string &func_value, std::shared_ptr<Params> params,
        const std::string &name);
  std::string query;
};
}  // namespace orm
}  // namespace dgraph
#endif  // DGRAPHORMQUERY_H
