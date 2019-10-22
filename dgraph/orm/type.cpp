#include "./type.h"

#include <iostream>

namespace dgraph {
namespace orm {
Token::builder &Token::builder::term(bool value) {
  term_ = value;
  return *this;
}

Token::builder &Token::builder::trigram(bool value) {
  trigram_ = value;
  return *this;
}

Token::builder &Token::builder::fulltext(bool value) {
  fulltext_ = value;
  return *this;
}

Token::builder &Token::builder::exact(bool value) {
  exact_ = value;
  return *this;
}

Token::builder &Token::builder::hash(bool value) {
  hash_ = value;
  return *this;
}

Token Token::builder::build() const {
  return Token{term_, trigram_, fulltext_, exact_, hash_};
}

FieldProps::builder &FieldProps::builder::name(std::string value) {
  name_ = value;
  return *this;
}

FieldProps::builder &FieldProps::builder::type(TypesType value) {
  type_ = value;
  return *this;
}

FieldProps::builder &FieldProps::builder::index(bool value) {
  index_ = value;
  return *this;
}

FieldProps::builder &FieldProps::builder::token(Token value) {
  token_ = value;
  return *this;
}

FieldProps::builder &FieldProps::builder::unique(bool value) {
  unique_ = value;
  return *this;
}

FieldProps::builder &FieldProps::builder::list(bool value) {
  list_ = value;
  return *this;
}

FieldProps::builder &FieldProps::builder::count(bool value) {
  count_ = value;
  return *this;
}

FieldProps::builder &FieldProps::builder::lang(bool value) {
  lang_ = value;
  return *this;
}

FieldProps::builder &FieldProps::builder::model(std::string value) {
  model_ = value;
  return *this;
}

FieldProps::builder &FieldProps::builder::reverse(bool value) {
  reverse_ = value;
  return *this;
}

FieldProps::builder &FieldProps::builder::replace(bool value) {
  replace_ = value;
  return *this;
}

FieldProps::builder &FieldProps::builder::tokenDateTime(TokenDateTime value) {
  tokenDateTime_ = value;
  return *this;
}

FieldProps FieldProps::builder::build() const {
  if (name_.empty()) {
    throw std::runtime_error("name must be proveded to FieldProps");
  }
  if (static_cast<unsigned int>(type_) == 0) {
    throw std::runtime_error("type must be proveded to FieldProps on" + name_);
  }
  return FieldProps{name_,  type_, index_, token_,   unique_,  list_,
                    count_, lang_, model_, reverse_, replace_, tokenDateTime_};
}

nlohmann::json pluck(nlohmann::json &arr, std::string key) {
  nlohmann::json _data = nlohmann::json::array();

  if (!arr.is_array()) {
    return nlohmann::json::array();
  }

  for (auto &obj : arr) {
    if (obj.is_object() && !obj[key].is_null()) {
      _data.push_back(obj[key]);
    }
  }
  return _data;
}
nlohmann::json merge(nlohmann::json &data, std::vector<std::string> keys) {
  if (keys.size() == 1 && !data[keys[0]].is_null()) {
    return data[keys[0]];
  }

  nlohmann::json _data = nlohmann::json::object();

  for (auto &_key : keys) {
    if (!data[_key].is_null()) {
      _data[_key] = data[_key];
    }
  }

  return _data;
}

TokenDateTime::builder &TokenDateTime::builder::year(bool value) {
  year_ = value;
  return *this;
}

TokenDateTime::builder &TokenDateTime::builder::month(bool value) {
  month_ = value;
  return *this;
}

TokenDateTime::builder &TokenDateTime::builder::day(bool value) {
  day_ = value;
  return *this;
}

TokenDateTime::builder &TokenDateTime::builder::hour(bool value) {
  hour_ = value;
  return *this;
}

TokenDateTime TokenDateTime::builder::build() const {
  return TokenDateTime{year_, month_, day_, hour_};
}

IncludeBase::builder &IncludeBase::builder::name(std::string value) {
  name_ = value;
  return *this;
}

IncludeBase::builder &IncludeBase::builder::as(std::string value) {
  as_ = value;
  return *this;
}

IncludeBase::builder &IncludeBase::builder::var(std::string value) {
  var_ = value;
  return *this;
}

IncludeBase::builder &IncludeBase::builder::count(bool value) {
  count_ = value;
  return *this;
}

IncludeBase::builder &IncludeBase::builder::params(
    std::shared_ptr<Params> value) {
  params_ = value;
  return *this;
}

IncludeBase::builder &IncludeBase::builder::order(
    std::vector<std::pair<std::string, std::string>> value) {
  order_ = value;
  return *this;
}

IncludeBase::builder &IncludeBase::builder::attributes(
    std::vector<std::string> value) {
  attributes_ = value;
  return *this;
}

IncludeBase::builder &IncludeBase::builder::filter(Filter value) {
  filter_ = value;
  return *this;
}

IncludeBase::builder &IncludeBase::builder::model(std::string value) {
  model_ = value;
  return *this;
}

IncludeBase IncludeBase::builder::build() {
  if (!params_) {
    params_ = std::make_shared<Params>();
  }
  return IncludeBase{name_,  as_,         var_,    count_, params_,
                     order_, attributes_, filter_, model_};
}

Params::builder &Params::builder::inc(IncludeBase value) {
  include_.push_back(value);
  return *this;
}

Params::builder &Params::builder::fil(Filter value) {
  filter_ = value;
  return *this;
}

Params::builder &Params::builder::attributes(Attributes value) {
  attributes_ = value;
  return *this;
}

Params::builder &Params::builder::ord(
    std::vector<std::pair<std::string, std::string>> value) {
  order_ = value;
  return *this;
}

Params::builder &Params::builder::first(long value) {
  first_ = value;
  return *this;
}

Params::builder &Params::builder::offset(long value) {
  offset_ = value;
  return *this;
}

Params::builder &Params::builder::after(std::string value) {
  after_ = value;
  return *this;
}

Params Params::builder::build() const {
  Params p{};
  p.include = include_;
  p.order = order_;
  p.first = first_;
  p.offset = offset_;
  p.after = after_;
  p.filter = filter_;
  p.attributes = attributes_;
  return p;
}

std::shared_ptr<Params> Params::builder::build_shared() const {
  //  Params p{};
  //  p.include = include_;
  //  p.order = order_;
  //  p.first = first_;
  //  p.offset = offset_;
  //  p.after = after_;
  //  p.filter = filter_;
  //  return std::make_shared<Params>(p);
  return std::make_shared<Params>(build());
}

Attributes &Attributes::key(const std::string &uid_key_) {
  uid_key = uid_key_;
  return *this;
}

Attributes &Attributes::type(const std::string &dgraph_type_) {
  dgraph_type = dgraph_type_;
  return *this;
}

Attributes &Attributes::s(const std::string &name, const std::string &value) {
  AttributeBase b;
  b.type = TypesType::STRING;
  b.stringvalue = value;
  attrs.push_back({name, b});
  return *this;
}

Attributes &Attributes::i(const std::string &name, int value) {
  AttributeBase b;
  b.type = TypesType::INT;
  b.intvalue = value;
  attrs.push_back({name, b});
  return *this;
}

Attributes &Attributes::d(const std::string &name, double value) {
  AttributeBase b;
  b.type = TypesType::FLOAT;
  b.doublevalue = value;
  attrs.push_back({name, b});
  return *this;
}

Attributes &Attributes::b(const std::string &name, bool value) {
  AttributeBase b;
  b.type = TypesType::BOOL;
  b.boolvalue = value;
  attrs.push_back({name, b});
  return *this;
}
// when insert / update we cant delete predicate. useless function:
// Attributes &Attributes::n(const std::string & name, NullVal value) {
//  AttributeBase b;
//  b.type = TypesType::nulltype;
//  b.isNull = true;
//  attrs.push_back({name, b});
//  return *this;
//}

Attributes &Attributes::u(const std::string &name, const std::string &value) {
  AttributeBase b;
  b.type = TypesType::UID;
  b.stringvalue = value;
  attrs.push_back({name, b});
  return *this;
}

Attributes &Attributes::u1(const std::string &name,
                           std::vector<std::string> value) {
  for (auto &v : value) {
    AttributeBase b;
    b.type = TypesType::UID;
    b.stringvalue = v;
    attrs.push_back({name, b});
  }
  return *this;
}

Attributes &Attributes::dt(const std::string &name, bool value) {
  AttributeBase b;
  b.type = TypesType::DATETIME;
  b.dateTimevalue = value;
  attrs.push_back({name, b});
  return *this;
}

Attributes &Attributes::val(const std::string &name,
                            const std::string &val_value) {
  // AttributeBase b;
  // b.type = TypesType::STRING;  //?
  // b.val = val_value;
  // attrs.push_back({name, b});
  val_at_fun = val_value;
  return *this;
}

Attributes &Attributes::n(const std::string &dgraph_type_,
                          const std::string &key_, Attributes value) {
  AttributeBase b;
  b.type = TypesType::INT;
  value.dgraph_type = dgraph_type_;
  value.uid_key = key_;
  b.nested_attr = std::make_shared<Attributes>(value);
  attrs.push_back({"", b});
  return *this;
}

Attributes &Attributes::n(const std::string &link,
                          const std::string &dgraph_type_,
                          const std::string &key_, Attributes value) {
  u(link, key_);

  AttributeBase b;
  b.type = TypesType::INT;
  value.dgraph_type = dgraph_type_;
  value.uid_key = key_;
  b.nested_attr = std::make_shared<Attributes>(value);
  attrs.push_back({"", b});
  return *this;
}

Attributes &Attributes::no(bool value) {
  no_attributes = value;
  return *this;
}

std::vector<std::string> Attributes::to_filter_value() {
  std::vector<std::string> s;
  for (auto &pair : attrs) {
    auto &name = pair.first;
    auto &value = pair.second;
    s.push_back(value.to_string());
  }
  return s;
}

std::string Attributes::to_json() {
  // note schema name should be alread modified before running this function
  std::string s = "{";
  for (auto &pair : attrs) {
    auto &name = pair.first;
    auto &value = pair.second;

    switch (value.type) {
      case TypesType::INT:
        s += "\"" + name + "\": " + std::to_string(value.intvalue);
        break;
      case TypesType::FLOAT:
        s += "\"" + name + "\": " + std::to_string(value.doublevalue);
        break;
      case TypesType::BOOL:
        s += "\"" + name + "\": " + std::to_string(value.boolvalue);
        break;
      case TypesType::STRING:
        s += "\"" + name + "\": " + "\"" + value.stringvalue + "\"";
        break;
      case TypesType::UID:
        s += "\"" + name + "\": " + "\"" + value.stringvalue + "\"";
        break;
    }
    s += ", ";
  }
  s.pop_back();
  s.pop_back();
  s += "}";
  return s;
}

// this should consider nested_attr also (think about it)
std::string Attributes::to_nquads() {
  // note schema name should be alread modified before running this function
  //_:blank-0 <name> "diggy" .
  std::string s = "\n";

  //_:a <dgraph.type> "Pet" .
  if (attrs.size() > 0) {
    if (uid_key.empty()) {
      std::cout << "Uid key must be provided to: " << dgraph_type << std::endl;
    } else {
      s += uid_key + " <dgraph.type> \"" + dgraph_type + "\" .\n";
    }
  }
  // start looping map
  for (auto &pair : attrs) {
    auto &name = pair.first;
    auto &value = pair.second;
    if (value.nested_attr && value.nested_attr->attrs.size() > 0) {
      s += value.nested_attr->to_nquads();
    } else {
      switch (value.type) {
        case TypesType::INT:
          s += uid_key + " <" + name + "> " + "\"" +
               std::to_string(value.intvalue) + "\"" + "^^<xs:int>";
          break;
        case TypesType::FLOAT:
          s += uid_key + " <" + name + "> " + "\"" +
               std::to_string(value.doublevalue) + "\"" + "^^<xs:double>";
          break;
        case TypesType::BOOL:
          s += uid_key + " <" + name + "> " + "\"" +
               std::to_string(value.boolvalue) + "\"" + "^^<xs:boolean>";
          break;
        case TypesType::STRING:
          s += uid_key + " <" + name + "> " + "\"" + value.stringvalue + "\"" +
               "^^<xs:string>";
          break;
        case TypesType::UID:
          s += uid_key + " <" + name + "> " + "<" + value.stringvalue + ">";
          break;
        case TypesType::DATETIME:
          s += uid_key + " <" + name + "> " + "\"" + value.stringvalue + "\"" +
               "^^<xs:dateTime>";
          break;
        case TypesType::PASSWORD:
          s += uid_key + " <" + name + "> " + "\"" + value.stringvalue + "\"" +
               "^^<xs:password>";
          break;
        case TypesType::GEO:
          s += uid_key + " <" + name + "> " + "\"" + value.stringvalue + "\"" +
               "^^<geo:geojson>";
          break;
      }
      s += " .\n";
    }

    // if(value.nested_attr)
  }
  std::cout << s << std::endl;
  return s;
}
/*
{
    set {
        _:b0 <menu.name> "M" .
        _:b0 <dgraph.type> "menu" .
        _:b0 <menu.path> "path" .
        _:b0 <menu.children>  _:y .
        _:b0 <menu.children>  _:z .
        _:y <menu.name> "M1" .
        _:y <dgraph.type> "menu" .
        _:z <menu.name> "M2" .
        _:z <dgraph.type> "menu" .
    }
}
*/
std::string Attributes::to_update_nquards(const std::string &uid) {
  // note schema name should be alread modified before running this function
  //<0x467ba0> <food> "taco" .
  //<0x467ba0> <rating> "tastes good" .
  std::string s = "\n";
  for (auto &pair : attrs) {
    auto &name = pair.first;
    auto &value = pair.second;

    switch (value.type) {
      case TypesType::INT:
        s += "<" + uid + "> <" + name + "> " + "\"" +
             std::to_string(value.intvalue) + "\"" + "^^<xs:int>";
        break;
      case TypesType::FLOAT:
        s += "<" + uid + "> <" + name + "> " + "\"" +
             std::to_string(value.doublevalue) + "\"" + "^^<xs:double>";
        break;
      case TypesType::BOOL:
        s += "<" + uid + "> <" + name + "> " + "\"" +
             std::to_string(value.boolvalue) + "\"" + "^^<xs:boolean>";
        break;
      case TypesType::STRING:
        s += "<" + uid + "> <" + name + "> " + "\"" + value.stringvalue + "\"" +
             "^^<xs:string>";
        break;
      case TypesType::UID:
        s += "<" + uid + "> <" + name + "> " + "<" + value.stringvalue + ">";
        break;
      case TypesType::DATETIME:
        s += "<" + uid + "> <" + name + "> " + "\"" + value.stringvalue + "\"" +
             "^^<xs:dateTime";
        break;
      case TypesType::PASSWORD:
        s += "<" + uid + "> <" + name + "> " + "\"" + value.stringvalue + "\"" +
             "^^<xs:password";
        break;
      case TypesType::GEO:
        s += "<" + uid + "> <" + name + "> " + "\"" + value.stringvalue + "\"" +
             "^^<geo:geojson";
        break;
    }
    s += " .\n";
  }
  return s;
}

std::string AttributeBase::to_string() {
  switch (type) {
    case TypesType::INT:
      return std::to_string(intvalue);
    case TypesType::FLOAT:
      return std::to_string(doublevalue);
    case TypesType::BOOL:
      return std::to_string(boolvalue);
    case TypesType::STRING:
      return "\"" + stringvalue + "\"";
    case TypesType::UID:
      return "\"" + stringvalue + "\"";
      //    case TypesType::nulltype:
      //      return "null";
  }
}

FilterBase::builder &FilterBase::builder::add(
    std::pair<MethodsType, Attributes> value) {
  filter_.push_back(value);
  return *this;
}

FilterBase::builder &FilterBase::builder::type(filtertype value) {
  this->flttype_ = value;
  return *this;
}

FilterBase FilterBase::builder::build() const {
  FilterBase b;
  b.flttype = flttype_;
  b.filters = filters_;
  b.filter = filter_;
  return b;
}

Filter::builder &Filter::builder::add(filtertype typevalue, FilterBase value) {
  filters_.push_back({typevalue, value});
  return *this;
}

Filter::builder &Filter::builder::add(FilterBase value) {
  filters_.push_back({filtertype::fltand, value});
  return *this;
}

Filter Filter::builder::build() const {
  Filter f{};
  f.filters = filters_;
  return f;
}

}  // namespace orm
}  // namespace dgraph
