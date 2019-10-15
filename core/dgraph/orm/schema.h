#ifndef SCHEMA_H
#define SCHEMA_H

#include <map>
#include <vector>
#include "./type.h"
namespace dgraph {
namespace orm {
class Schema {
 public:
  Schema(const std::string name, std::vector<FieldProps> original);

  std::string name;
  std::vector<FieldProps> original;
  std::vector<std::string> type;
  std::vector<std::string> schema;

 private:
  static std::vector<std::string> _generate_type(
      const std::string &name, const std::vector<FieldProps> &original);
  static std::vector<std::string> _generate(
      const std::string &name, const std::vector<FieldProps> &original);

  static std::string _build(const FieldProps &params);

  // moved this function from helper/utilities.js
  static void checkOptions(const FieldProps &options);
  static std::string prepareSchema(const FieldProps &options);

  static std::string typeToString(const TypesType &type);
  static bool isToken(const Token &t);
  static std::string tokenToString(const Token &token);
};
}  // namespace orm
}  // namespace dgraph
#endif  // SCHEMA_H
