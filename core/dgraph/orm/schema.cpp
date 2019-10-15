#include "./schema.h"

#include <magic_enum.hpp>

#include "pystring/pystring.h"
namespace dgraph {
namespace orm {
Schema::Schema(const std::string name, std::vector<FieldProps> original)
    : name(name), original(original) {
  schema = _generate(name, original);
  type = _generate_type(name, original);
}

std::vector<std::string> Schema::_generate_type(
    const std::string &name, const std::vector<FieldProps> &original) {
  std::vector<std::string> _type;
  _type.push_back("dgraph.type:" + name);
  for (auto &i : original) {
    _type.push_back(name + "." + i.name + ": " + typeToString(i.type));
  }
  return _type;
}

std::vector<std::string> Schema::_generate(
    const std::string &name, const std::vector<FieldProps> &original) {
  std::vector<std::string> _schema;
  for (auto &i : original) {
    _schema.push_back(name + "." + _build(i));
  }
  return _schema;
}
std::string Schema::_build(const FieldProps &params) {
  checkOptions(params);
  return prepareSchema(params);
}

void Schema::checkOptions(const FieldProps &options) {
  if (options.type == TypesType::UID && options.model.empty()) {
    throw std::runtime_error("[Type Error]: In " + options.name + " of type " +
                             pystring::upper(typeToString(options.type)) +
                             ", model is required.");
  }

  if (options.count && (options.type != TypesType::UID && !options.list)) {
    throw std::runtime_error("[Type Error]: In " + options.name + " of type " +
                             pystring::upper(typeToString(options.type)) +
                             ", count requires list.");
  }

  if (!options.index && isToken(options.token)) {
    throw std::runtime_error("[Type Error]: In " + options.name + " of type " +
                             pystring::upper(typeToString(options.type)) +
                             ", token requires index.");
  }

  if (!isToken(options.token) && options.index &&
      (options.type == TypesType::DATETIME ||
       options.type == TypesType::STRING)) {
    throw std::runtime_error("[Type Error]: In " + options.name + " of type " +
                             pystring::upper(typeToString(options.type)) +
                             ", index requires token.");
  }

  if (isToken(options.token) && options.type != TypesType::DATETIME) {
    if (options.token.exact && options.token.hash) {
      throw std::runtime_error(
          "[Type Error]: In " + options.name + " of type " +
          pystring::upper(typeToString(options.type)) +
          ", exact and hash index types shouldn\"t be used together.");
    }
  }

  if (options.token.exact && options.token.term) {
    throw std::runtime_error("[Type Error]: In " + options.name + " of type " +
                             pystring::upper(typeToString(options.type)) +
                             ", exact or hash index types shouldn\"t be used "
                             "alongside the term index type.");
  }

  if (options.token.hash && options.token.term) {
    throw std::runtime_error("[Type Error]: In " + options.name + " of type " +
                             pystring::upper(typeToString(options.type)) +
                             ", exact or hash index types shouldn\"t be used "
                             "alongside the term index type.");
  }
}

std::string Schema::typeToString(const TypesType &type) {
  std::string schema;
  switch (type) {
    case TypesType::INT:
      schema = "int";
      break;
    case TypesType::FLOAT:
      schema = "float";
      break;
    case TypesType::STRING:
      schema = "string";
      break;
    case TypesType::BOOL:
      schema = "bool";
      break;
    case TypesType::DATETIME:
      schema = "datetime";
      break;
    case TypesType::GEO:
      schema = "geo";
      break;
    case TypesType::PASSWORD:
      schema = "password";
      break;
    case TypesType::UID:
      schema = "uid";
      break;
  }
  return schema;
}

std::string Schema::prepareSchema(const FieldProps &options) {
  auto schema = typeToString(options.type) + " ";

  if (options.list) {
    schema = "[" + schema + "] ";
  }

  if (options.index) {
    if (options.type != TypesType::STRING &&
        options.type != TypesType::DATETIME) {
      schema += " @index(" + typeToString(options.type) + ") ";
    } else if (options.type == TypesType::DATETIME) {
      schema += " @index(" + tokenToString(options.token) + ") ";
    } else {
      schema += " @index(" + tokenToString(options.token) + ") ";
    }
  }
  if (options.count) {
    schema += "@count ";
  }
  if (options.lang) {
    schema += "@lang ";
  }
  if (options.reverse) {
    schema += "@reverse ";
  }

  return options.name + ": " + schema + ".";
}

bool Schema::isToken(const Token &t) {
  return t.term || t.trigram || t.fulltext || t.exact || t.hash;
}

std::string Schema::tokenToString(const Token &token) {
  std::string s;
  if (token.term) s += "term, ";
  if (token.trigram) s += "trigram, ";
  if (token.fulltext) s += "fulltext, ";
  if (token.exact) s += "exact, ";
  if (token.hash) s += "hash, ";
  if (!s.empty()) {
    s.pop_back();
    s.pop_back();
  }
  return s;
}
}  // namespace orm
}  // namespace dgraph
