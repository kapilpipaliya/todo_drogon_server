#include "./model.h"

#include <fmt/format.h>

#include <algorithm>
#include <iostream>
#include <json.hpp>
#include <map>
#include <range/v3/all.hpp>
#include <vector>

#include "pystring/pystring.h"
namespace dgraph {
namespace orm {
Model::Model(Schema schema, std::map<std::string, Schema> &models,
             std::shared_ptr<grpcclient::DgraphClient> dgraphClient)
    : schema(schema), models(models), dgraphClient(dgraphClient) {
  // no need i will use _method function manually
  //_generate_methods();
}

void Model::relation(std::string uid, RelationParam params,
                     api::Response *response) {
  if (params.field.empty()) {
    return;
  }

  // Todo Fix this line:
  //_check_attributes(schema.original, params.field, true, true);
  // _check_attributes(schema.original, attributes, true);

  nlohmann::json _include = nlohmann::json::object();

  for (auto &i : params.field) {
    _include[i] = nlohmann::json::object({"as", i});
  }

  method(MethodsType::uid, uid, nlohmann::json::object({"include", _include}),
         {}, response);

  nlohmann::json _user = nlohmann::json::parse(response->json());
  nlohmann::json _data = nlohmann::json::object();
  if (params.field.size() == 1 && _user[0][params.field[0]] &&
      _user[0][params.field[0]].size() > 0) {
    std::vector<std::string> _attributes;
    if (!params.attributes.empty() &&
        params.attributes.contains(params.field[0])) {
      //_attributes.push_back({params.attributes.at(params.field[0])});
    } else {
      _attributes.push_back("uid");
    }
    for (auto &_relation : _user[0][params.field[0]]) {
      merge(_relation, _attributes);
    }

  } else {
    for (auto &_field : params.field) {
      std::vector<std::string> _attributes;
      if (!params.attributes.empty() && params.attributes.contains(_field)) {
        //_attributes.push_back(params.attributes[_field]);
      } else {
        _attributes.push_back("uid");
      }
      if (!_user[0][_field]) {
        _data[_field] = nullptr;
      } else {
        for (auto &_relation : _user[0][_field]) {
          _data[_field] = merge(_relation, _attributes);
        }
      }
    }
  }
}

bool Model::checkPassword(std::string uid, std::string field,
                          std::string password) {
  try {
    if (!_check_if_password_type(field)) {
      throw std::runtime_error(std::string("Field ") + field +
                               " is not of type PASSWORD.");
    }

    auto s = R"({{
            {0} (func: uid({1})) {{
            isValid: checkpwd({0}.{2}, "{3}")
            }}
        }})";
    auto query = fmt::format(s, schema.name, uid, field, password);
    auto response = new api::Response;
    _execute(query, response);

    // json is used to check value only
    nlohmann::json check = nlohmann::json::parse(response->json());
    delete response;
    if (check.size() == 0) {
      return false;
    }

    return check[schema.name][0]["isValid"].get<bool>();

  } catch (std::exception &error) {
    throw std::runtime_error(error.what());
  }
}

void Model::query(std::string query, api::Response *response) {
  auto _txn = dgraphClient->newTxn({});
  try {
    _txn->query(query, response);
  } catch (std::exception &error) {
    auto txn_response = new api::TxnContext;
    _txn->discard(txn_response);
    delete txn_response;
    throw std::runtime_error(error.what());
  }
}

void Model::queryWithVars(QueryParams params, api::Response *response) {
  auto _txn = dgraphClient->newTxn({});
  try {
    _txn->queryWithVars(params.query, params.variables, response);
    return;
  } catch (std::exception &error) {
    auto txn_response = new api::TxnContext;
    _txn->discard(txn_response);
    delete txn_response;
    throw std::runtime_error(error.what());
  }
}

std::string Model::create(Attributes &attributes, api::Response *response) {
  _check_attributes(schema.original, attributes, true);
  _parse_mutation(attributes, schema.name);
  return _create(attributes, response);
}

void Model::update(const std::string &uid, Attributes &attributes,
                   api::Response *response) {
  if (uid.empty()) {
    return;
  }

  _check_attributes(schema.original, attributes, true);
  _parse_mutation(attributes, schema.name);

  std::string _del;

  for (auto &a : attributes.attrs) {
    auto find = ranges::find(schema.original, a.first, &FieldProps::name);
    if (find == schema.original.end()) {
      continue;
    }
    // This solve the problem:
    // cannot add value with uid 4e57 to predicate post.author because one of
    // the existing values does not match this uid, either delete the existing
    // values first or modify the schema to 'post.author: [uid]'
    if (find->replace) {
      // we not delete all edges like <uid> * * .
      _del += "<" + uid + "> <" + schema.name + "." + find->name + "> * .\n";
    }
  }

  if (!_del.empty()) {
    _delete(_del, response);
  }
  return _update(uid, attributes, response);

  /* Letter FIx this. Basic is currently working now.
   * the below finds all uids then update each.
   * @param param {any}
   * @param condition {string | any}
      if (uid.is_object()) {
        std::vector<std::string> _uid_keys;
        for (auto &el : uid.items()) {
          _keys.push_back(el.key());
        }

        std::string _key = _uid_keys[0];

        nlohmann::json a;
        a["filter"] = uid;
        method(MethodsType::has, _key, a, {}, response);

        nlohmann::json data = nlohmann::json::parse(response->json());
        if (data.size() > 0) {
          std::vector<std::string> _uids = pluck(data, "uid");
          for (auto &_uid : _uids) {
            _update(mutation, _uid, response);
          }
        }
      }
      */
}
/*
void Model::delete_(nlohmann::json params, api::Response *response) {
  if (params.is_object() && !params.is_array()) {
    // Fix this line:
    //_check_attributes(schema.original, params, true);
  }

  if (params.is_array()) {
    nlohmann::json _uids = nlohmann::json::array();

    for (auto &_uid : params) {
      nlohmann::json j;
      j["uid"] = _uid;
      _uids.push_back(j);
    }

    _delete(_uids, response);
    return;
  }

  if (params.is_object()) {
    std::vector<std::string> _fields;
    for (auto &el : params.items()) {
      _fields.push_back(el.key());
    }

    nlohmann::json j;
    j["attributes"] = nlohmann::json::array({"uid"});
    j["filter"] = params;
    method(MethodsType::has, _fields[0], j, {}, response);

    nlohmann::json _data = nlohmann::json::parse(response->json());
    if (_data.size() == 0) {
      return;
    }
    nlohmann::json nll;
    // Todo fix this;
    // delete_(pluck(_data, "uid"), nll, response);
    return;
  }
}
*/

void Model::delete_(std::string uid, api::Response *response) {
  auto q = get_del_nquads(uid);
  _delete(q, response);
  return;
}

void Model::delete_(std::vector<std::string> &uid, api::Response *response) {
  std::string q;
  for (auto &u : uid) {
    q += get_del_nquads(u);
  }
  _delete(q, response);
}
/* why this is meaning less part in delete function on orm?
void Model::delete_(std::vector<std::string> &uid, api::Response *response) {
  // let _params : {[index:string] : any} = {};
  nlohmann::json _params = nlohmann::json::object();
  std::vector<std::string> _keys;
  for (auto &el : params.items()) {
    _keys.push_back(el.key());
  }

  for (auto &_key : _keys) {
    if (_is_relation(_key)) {
      if (params[_key].is_array()) {
        nlohmann::json _a = nlohmann::json::array();
        for (auto &_uid : params[_key]) {
          nlohmann::json j = nlohmann::json::object();
          j["uid"] = _uid;
          _a.push_back(j);
        }

        _params[schema.name + "." + _key] = _a;
      } else {
        auto it = ranges::find(schema.original, _key, &FieldProps::name);
        if (it->replace) {
          _params[schema.name + "." + _key] = nullptr;
        } else {
          nlohmann::json j;
          j["uid"] = params[_key];
          _params[schema.name + "." + _key] = j;
        }
      }
    } else {
      _params[schema.name + "." + _key] = nullptr;
    }
  }

  // if(Array.isArray(uid)) {
  //   const _p: any = [];
  //   uid.forEach(_uid => {
  //     _params.uid = _uid;
  //     _p.push(_params);
  //   });

  //   return _delete(_p);
  // }

  // _params.uid = uid;
  // return _delete(_params);
}
*/
bool Model::_check_if_password_type(std::string field) {
  /*auto find = std::find_if(schema.original.begin(), schema.original.end(),
                           [&field](FieldProps &it) { it.name == field; });*/
  auto find = ranges::find(schema.original, field, &FieldProps::name);
  if (find == schema.original.end()) {
    return false;
  }
  auto _field = find;
  if (_field->name == "password") {
    return true;
  }
  // if(typeof _field == "object" && _field.type == "password") {
  //    return true;
  //}
  return false;
}

void Model::_execute(std::string query, api::Response *response) {
  auto _txn = dgraphClient->newTxn({});
  try {
    std::cout << query << std::endl;
    _txn->query(query, response);

    // return resolve(res.getJson()[schema.name]);
  } catch (std::exception &error) {
    auto txn_response = new api::TxnContext;
    _txn->discard(txn_response);
    delete txn_response;
    throw std::runtime_error(error.what());
  }
}

void Model::method(MethodsType type, const std::string &field,
                   const std::string &value,
                   const std::shared_ptr<Params> params,
                   api::Response *response) {
  /*if (type == MethodsType::uid || type == MethodsType::has) {
    // params = value;
    // value = field;
  }*/
  auto _params = _validate(schema.original, params);
  Query query(type, field, value, _params, schema.name);  //, _logger
  _execute(query.query, response);
}

bool Model::_is_relation(std::string _key) {
  // auto find = std::find_if(schema.original.begin(), schema.original.end(),
  //                         [&field](FieldProps &it) { it.name == field; });
  auto findit = ranges::find(schema.original, _key, &FieldProps::name);
  if (findit == schema.original.end()) {
    return false;
  }
  auto _field = findit;
  if (_field->type == TypesType::UID) {  //&& _field != "string"
    return true;
  }
  return false;
}

void Model::_parse_mutation(Attributes &attributes, std::string name) {
  for (auto &_att : attributes.attrs) {
    auto &key = _att.first;
    auto &val = _att.second;

    key = name + "." + key;

    if (_is_relation(key)) {
      // it basically convert array to array of {uid: oxabc}
      // TOdo fix this::
    } else {
      // moved to top.
      // key = name + "." + key;
    }
  }
}

std::string Model::_create(Attributes &attributes, api::Response *response) {
  auto _txn = dgraphClient->newTxn({});

  try {
    api::Mutation mu;
    // mu.set_set_json(attributes.to_json());
    mu.set_set_nquads(attributes.to_q());

    auto _unique_check = _check_unique_values(attributes, _txn, response);

    if (_unique_check) {
      auto txn_response = new api::TxnContext;
      _txn->discard(txn_response);
      delete txn_response;
      throw std::runtime_error(std::string("[Unique Constraint] : ") +
                               (_unique_check ? "true" : "false"));
    }

    mu.set_commit_now(true);
    // mu.setIgnoreIndexConflict(true);

    _txn->mutate(mu, response);

    auto _uid = response->uids().begin()->second;
    method(MethodsType::uid, _uid, "", Params::builder{}.build_shared(),
           response);

    return response->json();

  } catch (std::exception &error) {
    auto txn_response = new api::TxnContext;
    // This gives error when txn is aborted and trying to run this when json
    // exception ocuur.
    _txn->discard(txn_response);
    delete txn_response;
    throw std::runtime_error(error.what());
  }
}

void Model::_update(const std::string &uid, Attributes &attributes,
                    api::Response *response) {
  auto _txn = dgraphClient->newTxn({});
  try {
    api::Mutation mu;
    // mutation["uid"] = uid;
    mu.set_commit_now(true);
    // mu.setIgnoreIndexConflict(true);
    // mu.set_set_json(mutation.dump());
    mu.set_set_nquads(attributes.to_update_nquards(uid));
    std::cout << attributes.to_update_nquards(uid) << std::endl;

    _txn->mutate(mu, response);
  } catch (std::exception &error) {
    auto txn_response = new api::TxnContext;
    _txn->discard(txn_response);
    delete txn_response;
    throw std::runtime_error(error.what());
  }
}

std::string Model::get_del_nquads(const std::string &uid) {
  std::string q = "<" + uid + ">" + " * * .\n";  // This delete all nodes.

  for (auto &i : schema.original) {
    q += "<" + uid + "> <" + schema.name + "." + i.name + "> * .\n";
  }
  return q;
}

void Model::_delete(const std::string &mutation, api::Response *response) {
  auto _txn = dgraphClient->newTxn({});

  try {
    api::Mutation mu;
    mu.set_commit_now(true);
    // mu.setIgnoreIndexConflict(true);
    // mu.set_delete_json(mutation);
    mu.set_del_nquads(mutation);

    _txn->mutate(mu, response);
  } catch (std::exception &error) {
    auto txn_response = new api::TxnContext;
    _txn->discard(txn_response);
    delete txn_response;
    throw std::runtime_error(error.what());
  }
}

std::vector<FieldProps> Model::_get_unique_fields() {
  // auto _unique  = nlohmann::json::array();
  std::vector<FieldProps> _unique;

  for (auto &_param : schema.original) {
    if (_param.unique) {
      _unique.push_back(_param);
    }
  }
  return _unique;
}

bool Model::_check_unique_values(Attributes &attributes,
                                 std::shared_ptr<dgraph::grpcclient::Txn> _txn,
                                 api::Response *response) {
  auto _unique = _get_unique_fields();

  if (_unique.size() == 0) {
    return false;
  }
  for (auto &_param : _unique) {
    auto name = schema.name + "." + _param.name;
    auto findit =
        std::find_if(attributes.attrs.begin(), attributes.attrs.end(),
                     [name](std::pair<std::string, AttributeBase> &atr) {
                       return atr.first == name;
                     });
    auto _mvalue = findit->second.to_string();

    auto query = fmt::format(R"({{
           data (func: eq({0}.{1}, {2})) {{
            {1}: {0}.{1}
           }}
          }})",
                             schema.name, _param.name, _mvalue);
    _txn->query(query, response);

    // nlohmann json is only used to check data size.
    auto data = nlohmann::json::parse(response->json());
    if (data["data"].size() > 0) {
      std::cout << response->json() << std::endl;
      std::cout << "Duplicate value for " + _param.name << " value :" << _mvalue
                << std::endl;
      return true;
    }
  }

  return false;
}  // namespace dgraph

std::vector<std::string> Model::_lang_fields(std::vector<FieldProps> original) {
  std::vector<std::string> _fields;

  for (auto &_p : original) {
    if (_p.type == TypesType::STRING && _p.lang) {
      _fields.push_back(_p.name);
    }
  }

  return _fields;
}

void Model::_check_attributes(std::vector<FieldProps> original,
                              const Attributes &attributes, bool isUpdate,
                              bool isRelation) {
  // std::vector<std::string> attributes_ = attributes;
  bool haveData = false;

  if (attributes.attrs.size() == 0) {
    return;
  }

  std::vector<std::string> _lang_fields_ = _lang_fields(original);
  for (auto &attribute : attributes.attrs) {
    auto name = attribute.first;
    auto value = attribute.second;

    std::string find_name;
    auto findit = ranges::find(original, name, &FieldProps::name);
    if (findit == original.end()) {
      find_name = "";
    } else {
      find_name = findit->name;
    }

    auto langFound = [&name, &_lang_fields_]() {
      std::vector<std::string> spilts;
      pystring::split(name, spilts, "@");
      if (spilts.size() > 0) {
        auto with_out_lang = spilts.at(0);
        auto _index = ranges::find(_lang_fields_, with_out_lang);
        if (_index != ranges::end(_lang_fields_)) {
          return true;
        }
      }
      return false;
    };

    if (pystring::find(name, "@") == -1 && find_name.empty()) {
      throw std::runtime_error(schema.name + " has no attribute " +
                               attribute.first);
    } else if (pystring::find(name, "@") != -1 && !langFound()) {
      throw std::runtime_error(
          "${this.schema.name} has no lang property in ${attribute}");
    }
    // TODO FIX OTHER THREE CHECKS
  }
}

Attributes Model::_all_attributes(std::vector<FieldProps> original) {
  Attributes _attrs;
  for (auto &_p : original) {
    if (_p.type == TypesType::UID || _p.type == TypesType::PASSWORD) {
      continue;
    }
    AttributeBase b;
    b.type = _p.type;

    _attrs.attrs.push_back({_p.name, b});
  }

  return _attrs;
}

std::shared_ptr<Params> Model::_validate(std::vector<FieldProps> original,
                                         std::shared_ptr<Params> params) {
  //  if (!params) {
  //    Params p{};
  //    params = std::make_shared<Params>(p);
  //  }

  if (params->attributes.attrs.size() == 0) {
    params->attributes = _all_attributes(original);
  }
  //  auto _index = ranges::find(params->attributes, "uid");
  auto _index = std::find_if(params->attributes.attrs.begin(),
                             params->attributes.attrs.end(),
                             [](std::pair<std::string, AttributeBase> &att) {
                               return att.first == "uid";
                             });

  if (_index != params->attributes.attrs.end()) {
    params->attributes.attrs.erase(_index);
  }

  _check_attributes(original, params->attributes);

  AttributeBase b;
  b.type = TypesType::UID;
  params->attributes.attrs.insert(params->attributes.attrs.begin(), {"uid", b});

  if (params->include.size()) {
    for (auto &relation : params->include) {
      // Todo!! Fix this
      // if (typeof original[relation] == "undefined") {
      // throw new Error("${schema.name} has no relation $ { relation }");
      //}

      std::string model;
      auto findit = ranges::find(original, relation.name, &FieldProps::name);
      if (findit == original.end()) {
        throw std::runtime_error(schema.name + " has no relation " +
                                 relation.name);
      }
      model = findit->model;

      relation.model = model;

      // relation.params must not be null
      _validate(models.at(model).original, relation.params);
    }
  }

  return params;
}

}  // namespace orm
}  // namespace dgraph
