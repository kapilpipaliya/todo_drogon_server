#include "./query.h"

#include <fmt/format.h>
#include <pystring/pystring.h>

#include <iostream>
#include <regex>
namespace dgraph {
namespace orm {
Query::Query(MethodsType type, const std::string &field,
             const std::string &func_value, std::shared_ptr<Params> params,
             const std::string &schema_name, const std::string &query_name,
             const std::vector<std::string> &var_blocks)
    :  // name(name),
       // params(params),
       // type(type),
       // field(field),
       // value(value),
      var_blocks(var_blocks),
      where(_where(type, field, func_value, schema_name)),
      query(_build(params, schema_name, query_name)) {}

// If multiple constructor needed use builder pattern.
Query::Query(MethodsType type, std::vector<std::string> field,
             const std::string &func_value, std::shared_ptr<Params> params,
             const std::string &schema_name, const std::string &query_name,
             const std::vector<std::string> &var_blocks)
    :  // name(name),
       // params(params),
       // type(type),
       // field(pystring::join(", ", field)),
       // value(value),
      var_blocks(var_blocks),
      where(_where(type, pystring::join(", ", field), func_value, schema_name)),
      query(_build(params, schema_name, query_name)) {
  // only method type = uid needs multiple fields.
}

std::string Query::methodTypeToString(MethodsType type) {
  switch (type) {
    case MethodsType::eq:
      return "eq";
    case MethodsType::uid:
      return "uid";
    case MethodsType::allofterms:
      return "allofterms";
    case MethodsType::anyofterms:
      return "anyofterms";
    case MethodsType::regexp:
      return "regexp";
    case MethodsType::anyoftext:
      return "anyoftext";
    case MethodsType::alloftext:
      return "alloftext";
    case MethodsType::has:
      return "has";
    case MethodsType::near:
      return "near";
    case MethodsType::contains:
      return "contains";
    case MethodsType::uid_in:
      return "uid_in";
    case MethodsType::ne:
      return "ne";
    case MethodsType::le:
      return "le";
    case MethodsType::lt:
      return "lt";
    case MethodsType::ge:
      return "ge";
    case MethodsType::gt:
      return "gt";
    case MethodsType::type:
      return "type";
    case MethodsType::min:
      return "min";
    case MethodsType::max:
      return "max";
    case MethodsType::sum:
      return "sum";
    case MethodsType::avg:
      return "avg";
    default:
      return "define_enum";
  }
}
std::string Query::_where(MethodsType type, std::string field,
                          const std::string &func_value,
                          const std::string &name) {
  std::string where_;
  switch (type) {
    case MethodsType::eq:
    case MethodsType::allofterms:
    case MethodsType::alloftext:
    case MethodsType::anyofterms:
    case MethodsType::anyoftext: {
      std::string s = "(func: {0}({1}.{2}, \"{3}\"){{ORDER}}{{LIMIT}})";
      where_ =
          fmt::format(s, methodTypeToString(type), name, field, func_value);
      break;
    }
    case MethodsType::regexp: {
      auto s = "(func: {0}({1}.{2}, {3}){{ORDER}}{{LIMIT}})";
      where_ =
          fmt::format(s, methodTypeToString(type), name, field, func_value);
      break;
    }
    case MethodsType::uid:
    case MethodsType::type: {
      auto s = "(func: {0}({1}){{ORDER}}{{LIMIT}})";
      where_ = fmt::format(s, methodTypeToString(type), field);
      break;
    }
    case MethodsType::has: {
      auto s = "(func: {}({}.{}){{ORDER}}{{LIMIT}})";
      where_ = fmt::format(s, methodTypeToString(type), name, field);
      break;
    }
    // Todo Fix this
    case MethodsType::near: {
      //  auto s = "(func: {}({}.{}, [{}, {}], {}){{ORDER}}{{LIMIT}})";
      //  where_ = fmt::format(s, methodTypeToString(type), name, field,
      //  value.longitude,value.latitude, value.distance);
      break;
    }
      // Todo Fix this
    case MethodsType::contains: {
      //  auto s = "(func: {}({}.{}, [{}, {}]){{ORDER}}{{LIMIT}})";
      //  where_ =
      //     fmt::format(s, methodTypeToString(type), name, field,
      //     value.longitude, value.latitude);
      break;
    }
  }
  return where_;
}

std::string Query::_filter1(FilterBase &base, const std::string &name) {
  std::vector<std::string> res;
  for (auto &rule : base.filter) {
    auto method = std::get<0>(rule);
    auto field = std::get<1>(rule);

    if (field.attrs.size() < 1) {
      throw std::runtime_error("filter add at least one attribute");
    }
    auto key = field.attrs.at(0).first;
    auto value = pystring::join(", ", field.to_filter_value());

    if (method == MethodsType::has) {
      res.push_back(fmt::format("has({}.{})", name, key));
    } else if (method == MethodsType::uid) {
      res.push_back("uid(" + value + ")");
    } else if (!field.val_at_fun.empty()) {
      res.push_back("val(" + field.val_at_fun + ")");
    } else {
      res.push_back(fmt::format(
          "{0}({1}.{2}, {3})", methodTypeToString(method), name, key,
          value));  // std::regex_replace(field, std::regex("$"), "")
    }
  }
  std::string s;
  switch (base.flttype) {
    case filtertype::fltor:
      s = pystring::join(" OR ", res);
      break;
    case filtertype::fltnot:
      s = pystring::join(" NOT ", res);
      break;
    case filtertype::fltand:
    default:
      s = pystring::join(" AND ", res);
      break;
  }

  return s;
}

std::string Query::_filter(const std::string &key, const std::string &value,
                           const std::string &name) {
  if (pystring::lower(key) == "$has") {
    return fmt::format(
        "{}({}.{})", std::regex_replace(key, std::regex("$"), ""), name, value);
  }

  return fmt::format("eq({0}.{1}, \"{2}\")", name, key, value);
}
/*
std::string Query::_filter(std::string key, nlohmann::json value,
                           std::string name) {
  if (value.is_object() && !value.is_array()) {
    std::vector<std::string> _keys;
    for (auto &el : value.items()) {
      _keys.push_back(el.key());
    }
    auto _key = _keys[0];

    if (!_key.empty()) {
      auto _value = value[_key];

      if (_value.is_array()) {
        std::vector<std::string> _sub;
        for (auto &_val : _value) {
          _sub.push_back(fmt::format("uid_in({0}.{1}, {2})", name, key, _val));
        }

        return pystring::join(" OR ", _sub);
      }

      if (_value.is_string() && _key != "$regexp") {
        _value = "\"" + _value.get<std::string>() + "\"";
      }

      if (_key == "$ne") {
        return fmt::format("NOT eq({0}.{1}, {2})", name, key, _value);
      }

      return fmt::format("{0}({1}.${2}, ${3})",
                         std::regex_replace(_key, std::regex("$"), ""), name,
                         key, value);
    }
  }
  return "";
}
*/
std::string Query::_parse_filter(Filter filter, const std::string &name) {
  //  if (filter.filters.size()) {
  //    return "";
  //  }

  std::string fil_;
  bool is_first = true;
  for (auto &_f : filter.filters) {
    auto _filters = _filter1(_f.second, name);

    std::string s;
    switch (_f.first) {
      case filtertype::fltor:
        s = " OR ";
        break;
      case filtertype::fltnot:
        s = " NOT ";
        break;
      case filtertype::fltand:
      default:
        s = " AND ";
        break;
    }

    //    if (_filters.size() > 1) {
    if (is_first) {
      is_first = false;
      s = "";
    }
    s += "(" + _filters + ")";
    //    }
    fil_ += s;
  }

  /*
    if (!filter.isOr || !filter.isAnd) {
      _filters.push_back(_filter(filter.key, filter.simple_filter, name));
    } else {
      std::vector<std::string> _sub;
      for (auto &_k : filter.nested_filter) {
        if (_k.nested_filter.size() > 0) {
          for (auto &_val : _k.nested_filter) {
            _sub.push_back(_filter(_k.key, _k.simple_filter, name));
          }
        } else {
          _sub.push_back(_filter(_k.key, _k.simple_filter, name));
        }
      }
      if (_sub.size() > 0) {
        auto join =
            pystring::upper(std::regex_replace(filter.key, std::regex("$"),
    "")); _filters.push_back("(" + pystring::join(join, _sub) + ")");
      }
    }*/

  if (!fil_.empty()) {
    // auto join = pystring::join(" AND ", _filters);
    return " @filter(" + fil_ + ")";
  }

  return "";
}

std::string Query::_attributes(Attributes attributes, const std::string &name) {
  std::vector<std::string> _attrs;
  for (auto &attr : attributes.attrs) {
    if (attr.first == "uid") {
      _attrs.push_back("uid");
    } else {
      _attrs.push_back(
          fmt::format("{0}: {1}.{2}", attr.first, name, attr.first));
    }
  }

  return pystring::join("\n", _attrs);
}

std::string Query::_include(std::vector<IncludeBase> &include,
                            const std::string &name) {
  std::string _inc = "";

  if (!include.size()) {
    return "";
  }
  for (auto &relation : include) {
    if (relation.count) {
      if (!relation.var.empty()) {
        return relation.var + " as count(" + name + "." + relation.name + ")";
      } else {
        std::string s;
        if (!relation.as.empty()) {
          s += relation.as + ": ";
        }
        if (relation.name == "uid") {
          s += "count(" + relation.name + ")";
        } else {
          s += "count(" + name + "." + relation.name + ")";
        }
        _inc += s;
      }
      continue;
    }

    if (!relation.var.empty()) {
      _inc += fmt::format("{0} AS {1}.{2}", relation.var, name, relation.name);
    } else {
      _inc += fmt::format("{0}: {1}.{2}",
                          relation.as.empty() ? relation.as : relation.name,
                          name, relation.name);
    }

    auto _limit = _extras(relation.params);
    auto _order = _parse_order(relation.order, name);

    _inc += _parse_filter(relation.filter, relation.model);

    if (!_limit.empty()) {
      _inc += " (" + _limit + ") ";
    }

    if (!_order.empty()) {
      _inc += " (" + _order + ")";
    }
    if (!relation.var.empty()) {
      auto nest = _include(relation.params->include, relation.model);
      if (!nest.empty()) {
        _inc += fmt::format(R"({{
        {}
      }})",
                            nest);
      }
    } else {
      _inc +=
          fmt::format(R"({{
        {}
        {}
      }})",
                      _attributes(relation.params->attributes, relation.model),
                      _include(relation.params->include, relation.model));
    }
  }

  return _inc;
}

std::string Query::_extras(std::shared_ptr<Params> params) {
  std::vector<std::string> _extra;
  if (!params) {
    return "";
  }

  if (params->first != 0) {
    _extra.push_back("first: " + std::to_string(params->first));
  }

  if (params->offset != 0) {
    _extra.push_back("offset: " + std::to_string(params->offset));
  }

  if (!params->after.empty()) {
    _extra.push_back("after: " + params->after);
  }

  if (_extra.size() > 0) {
    return pystring::join(", ", _extra);
  }

  return "";
}

std::string Query::_parse_order(
    std::vector<std::pair<std::string, std::string>> &order,
    const std::string &name) {
  std::vector<std::string> _order;

  for (auto &_o : order) {
    _order.push_back(fmt::format("order{0}: {1}.{2}",
                                 pystring::lower(std::get<1>(_o)), name,
                                 std::get<0>(_o)));
  }

  if (_order.size() > 0) {
    return pystring::join(", ", _order);
  }

  return "";
}

std::string Query::_build(const std::shared_ptr<Params> &params,
                          const std::string &schema_name,
                          const std::string &query_name) {
  auto _order = _parse_order(params->order, schema_name);
  auto _limit = _extras(params);

  if (!_order.empty()) {
    _order = ", " + _order;
  }

  if (!_limit.empty()) {
    _limit = ", " + _limit;
  }

  auto s = pystring::replace(where, "{ORDER}", _order);
  s = pystring::replace(s, "{LIMIT}", _limit);
  auto f = _parse_filter(params->filter, schema_name);
  auto a = _attributes(params->attributes, schema_name);
  auto i = _include(params->include, schema_name);
  std::string query_name_{query_name};
  if (query_name.empty()) {
    query_name_ = schema_name;
  }
  if (query_name == "var") {
    auto query_ = R"(
      {0} {1} {2} {{
        {3}
        {4}
      }}
  )";
    auto query = fmt::format(query_, query_name_, s, f, a, i);
    return query;
  } else {
    auto query_ = R"({{
      {0}
      {1} {2} {3} {{
        {4}
        {5}
      }}
    }})";
    auto query = fmt::format(query_, pystring::join("", var_blocks),
                             query_name_, s, f, a, i);
    // logger(query);
    return query;
  }
}

}  // namespace orm
}  // namespace dgraph
