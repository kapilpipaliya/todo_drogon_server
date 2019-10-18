#ifndef DGRAPHTYPE_H
#define DGRAPHTYPE_H
#include <json.hpp>
#include <map>
#include <string>
#include <tuple>
#include <vector>
//#include <magic_enum.hpp>
namespace dgraph {
namespace orm {

enum error_type { success, unique_error, password_error };

// methods.ts
enum class MethodsType : int {
  eq = 1,
  uid,
  allofterms,
  anyofterms,
  regexp,
  anyoftext,
  alloftext,
  has,
  near,
  within,
  contains,
  intersects,
  uid_in,  // uid_in cannot be used at root, it accepts one UID constant as its
           // argument (not a variable).
  ne,
  le,
  lt,
  ge,
  gt,
  match,  // Fuzzy matching
          // min,max,sum,avg
          // floor ceil ln exp sqrt
          // since
          // pow(a, b)
          // logbase(a,b)
          // cond(a, b, c)
          // @groupby
          // expand(_all_)
          // @cascade
          // @normalize
          // @ignorereflex
          // @facets
          // shortest
          // @recurse
  type

};
// types.ts
enum class TypesType : int {
  INT = 1,
  FLOAT,
  STRING,
  BOOL,
  DATETIME,
  GEO,
  PASSWORD,
  UID
};
// tokenmap.ts
enum class tokenmapString : int { exact, hash, term, fulltext, trigram };
enum class tokenmapDateTime : int { year, month, day, hour };
// typemap.ts
enum class typemapSTRING : int {
  list,
  count,
  lang,
  index,
  upsert,
  token,
  unique
};
enum class typemapINT : int { list, count, index, upsert, unique };
enum class typemapFLOAT : int { list, count, index, upsert, unique };
enum class typemapBOOL : int { list, count, index, upsert };
enum class typemapDATETIME : int { list, count, index, upsert, token };
enum class typemapGEO : int { list, count, index, upsert };
enum class typemapPASSWORD : int {};
enum class typemapUID : int { count, reverse, model, replace };

// utility.ts
nlohmann::json pluck(nlohmann::json& arr, std::string key);
nlohmann::json merge(nlohmann::json& data, std::vector<std::string> keys);

// class Include;
class NullVal {};
class Attributes;
class AttributeBase {
 public:
  TypesType type;
  int intvalue = 0;
  double doublevalue = 0;
  bool boolvalue = false;
  bool isNull = false;
  // there is dateTime in dgraph
  std::string stringvalue;
  std::shared_ptr<Attributes> nested_attr;
  std::string to_string();
};

class Attributes {
 public:
  std::vector<std::pair<std::string, AttributeBase>> attrs;
  bool no_attributes = false;
  Attributes& s(std::string name, std::string value);
  Attributes& i(std::string name, int value);
  Attributes& d(std::string name, double value);
  Attributes& b(std::string name, bool value);
  //  Attributes& n(std::string name, NullVal value);
  Attributes& u(std::string name, std::string value);
  Attributes& u(std::string name, std::vector<std::string> value);
  Attributes& no(bool value);
  std::vector<std::string> to_filter_value();
  std::string to_json();
  std::string to_nquads(std::string type);
  std::string to_update_nquards(const std::string& uid);
};
enum filtertype { fltand = 1, fltor, fltnot };
class Filter;
class FilterBase {
 public:
  filtertype flttype = fltand;
  std::vector<std::pair<MethodsType, Attributes>> filter;
  std::shared_ptr<Filter> filters;
  class builder {
   public:
    builder& add(std::pair<MethodsType, Attributes> value);
    builder& type(filtertype value);
    FilterBase build() const;

   private:
    filtertype flttype_;
    std::vector<std::pair<MethodsType, Attributes>> filter_;
    std::shared_ptr<Filter> filters_;
  };
};

class Filter {
 public:
  std::vector<std::pair<filtertype, FilterBase>> filters;
  class builder {
   public:
    builder& add(filtertype typevalue, FilterBase value);
    builder& add(FilterBase value);

    Filter build() const;
    // std::shared_ptr<Filter> build_shared() const;

   private:
    std::vector<std::pair<filtertype, FilterBase>> filters_;
  };
};
struct Base {
  // Include include;
  Filter filter;
  Attributes attributes;
  std::vector<std::pair<std::string, std::string>> order;  // Array<any>
  long first = 0;
  long offset = 0;
  std::string after;
};
// not using now
struct ConnectionConfig {
  std::string host;
  long port = 0;
  bool debug = false;
  // ChannelCredentials credentails;
};

struct Token {
  bool term = false;
  bool trigram = false;
  bool fulltext = false;
  bool exact = false;
  bool hash = false;
  class builder {
   public:
    builder& term(bool value);
    builder& trigram(bool value);
    builder& fulltext(bool value);
    builder& exact(bool value);
    builder& hash(bool value);

    Token build() const;

   private:
    bool term_ = false;
    bool trigram_ = false;
    bool fulltext_ = false;
    bool exact_ = false;
    bool hash_ = false;
  };
};
struct TokenDateTime {
  bool year = false;
  bool month = false;
  bool day = false;
  bool hour = false;
  class builder {
   public:
    builder& year(bool value);
    builder& month(bool value);
    builder& day(bool value);
    builder& hour(bool value);

    TokenDateTime build() const;

   private:
    bool year_ = false;
    bool month_ = false;
    bool day_ = false;
    bool hour_ = false;
  };
};

struct QueryParams {
  std::string query;
  std::map<std::string, std::string> variables;
};

struct FieldProps {
  std::string name;
  TypesType type;
  bool index = false;
  Token token;  // or std::string
  bool unique = false;
  bool list = false;
  bool count = false;
  bool lang = false;
  std::string model;
  bool reverse = false;
  bool replace = false;
  TokenDateTime tokenDateTime;

  std::vector<tokenmapString> stringops;
  std::vector<typemapINT> intops;
  std::vector<typemapFLOAT> floatops;
  std::vector<typemapBOOL> boolops;
  std::vector<typemapDATETIME> datetimeops;
  std::vector<typemapGEO> geoops;
  std::vector<typemapPASSWORD> passwordops;
  std::vector<typemapUID> uidops;
  class builder {
   public:
    builder& name(std::string value);
    builder& type(TypesType value);
    builder& index(bool value);
    builder& token(Token value);
    builder& unique(bool value);
    builder& list(bool value);
    builder& count(bool value);
    builder& lang(bool value);
    builder& model(std::string value);
    builder& reverse(bool value);
    builder& replace(bool value);
    builder& tokenDateTime(TokenDateTime value);

    FieldProps build() const;

   private:
    std::string name_;
    TypesType type_;
    bool index_ = false;
    Token token_;  // or std::string
    bool unique_ = false;
    bool list_ = false;
    bool count_ = false;
    bool lang_ = false;
    std::string model_;
    bool reverse_ = false;
    bool replace_ = false;
    TokenDateTime tokenDateTime_;
  };
};  // namespace dgraph

struct RelationParam {
  std::vector<std::string> field;  // or std::string
  std::map<std::string, std::vector<std::string>> attributes;
};
/*
class Include : public Base {
  // fix this
  std::map<std::string, std::string> key;
  std::string as;
};
*/
class Params;
class IncludeBase {
 public:
  std::string name;
  std::string as;
  bool count = false;
  std::shared_ptr<Params> params;
  std::vector<std::pair<std::string, std::string>> order;
  std::vector<std::string> attributes;
  Filter filter;
  std::string model;
  class builder {
   public:
    builder& name(std::string value);
    builder& as(std::string value);
    builder& count(bool value);
    builder& params(std::shared_ptr<Params> value);
    builder& order(std::vector<std::pair<std::string, std::string>> value);
    builder& attributes(std::vector<std::string> value);
    builder& filter(Filter value);
    builder& model(std::string value);

    IncludeBase build();

   private:
    std::string name_;
    std::string as_;
    bool count_ = false;
    std::shared_ptr<Params> params_ = nullptr;
    std::vector<std::pair<std::string, std::string>> order_;
    std::vector<std::string> attributes_;
    Filter filter_;
    std::string model_;
  };
};

class Params : public Base {
 public:
  std::vector<IncludeBase> include;
  class builder {
   public:
    builder& inc(IncludeBase value);
    builder& fil(Filter value);
    builder& attributes(Attributes value);
    builder& ord(std::vector<std::pair<std::string, std::string>> value);
    builder& first(long value);
    builder& offset(long value);
    builder& after(std::string value);

    Params build() const;
    std::shared_ptr<Params> build_shared() const;

   private:
    std::vector<IncludeBase> include_;
    std::vector<std::pair<std::string, std::string>> order_;
    long first_ = 0;
    long offset_ = 0;
    std::string after_;
    Filter filter_;
    Attributes attributes_;
  };
};

}  // namespace orm
}  // namespace dgraph
#endif  // DGRAPHTYPE_H
