#ifndef DGraphClientStub_H
#define DGraphClientStub_H

#include <drogon/drogon.h>
#include <map>
#include <string>
#include <vector>
#include "json.hpp"

namespace dgraph {

enum error {
  ERR_NO_CLIENTS,
  ERR_FINISHED,
  ERR_ABORTED,
  ERR_BEST_EFFORT_REQUIRED_READ_ONLY,
  ERR_READ_ONLY,
  ERR_REFRESH_JWT_EMPTY
};
std::string renderDgraphError(error e);

enum DropOpMap { NONE, ALL, DATA, ATTR, TYPE };
struct Operation {
  std::string schema;
  std::string dropAttr;
  bool dropAll;
  DropOpMap dropOp;
  std::string dropValue;
};
struct Payload {
  std::string data;
};
enum ValCase {
  VAL_NOT_SET = 0,
  DEFAULT_VAL = 1,
  BYTES_VAL = 2,
  INT_VAL = 3,
  BOOL_VAL = 4,
  STR_VAL = 5,
  DOUBLE_VAL = 6,
  GEO_VAL = 7,
  DATE_VAL = 8,
  DATETIME_VAL = 9,
  PASSWORD_VAL = 10,
  UID_VAL = 11,
};
struct Value {
  std::string defaultVal;
  std::string bytesVal;
  int intVal = 0;
  bool boolVal = false;
  std::string strVal;
  double doubleVal = false;
  std::string geoVal;
  std::string dateVal;
  std::string datetimeVal;
  std::string passwordVal;
  long uidVal;
};
enum ValTypeMap { STRING, INT, FLOAT, BOOL, DATETIME };
struct Facet {
  std::string key;
  std::string value;
  ValTypeMap valType;
  std::vector<std::string> tokensList;
  std::string alias;
};
struct LoginRequest {
  std::string userid;
  std::string password;
  std::string refreshToken;
};
struct Jwt {
  std::string accessJwt;
  std::string refreshJwt;
};

struct NQuad {
  std::string subject;
  std::string predicate;
  std::string objectId;
  Value objectValue;
  std::string label;
  std::string lang;
  std::vector<Facet> facetsList;
};

struct Mutation {
  std::string setJson;
  std::string deleteJson;
  std::string setNquads;
  std::string delNquads;
  //  Array<NQuad> setList;
  //  Array<NQuad> delList;
  std::string cond;
  bool commitNow = false;
  long startTs = 0;
  // Raw mutation text to send;
  std::string mutation;
  // Set to true if `mutation` field (above) contains a JSON mutation.
  bool isJsonString = false;
};
struct Request {
  long startTs = 0;
  std::string query;
  std::map<std::string, std::string> varsMap;
  bool readOnly = false;
  bool bestEffort = false;
  std::vector<Mutation> mutationsList;
  bool commitNow = false;
  int timeout = 20;
  bool debug = false;
};
struct TxnContext {
  long startTs = 0;
  long commitTs = 0;     //?
  bool aborted = false;  //?
  std::vector<std::string> keysList;
  std::vector<std::string> predsList;
};
struct Latency {
  int parsing_ns = 0;
  int processing_ns = 0;
  int encoding_ns = 0;
  int assignTimestamp_ns = 0;
};
struct Extensions {
  Latency server_latency;
  TxnContext txn;
};

struct Response {
  std::string json;
  TxnContext txn;
  //  Latency latency;
  std::vector<std::pair<std::string, std::string>> uidsMap;
  //  Extensions extensions;
};
struct Version {
  std::string tag;
};
struct UiKeywords {};
struct LoginResponse {
  std::string accessJWT;
  std::string refreshJWT;
};
struct AssignedData {
  std::map<std::string, std::string> uids;
};

struct Assigned {
  AssignedData data;
  Extensions extensions;
};
void to_json(nlohmann::json& j, const TxnContext& p);

void from_json(const nlohmann::json& j, TxnContext& p);
/**
 * Stub is a stub/client connecting to a single dgraph server instance.
 */
class DGraphClientStub {
  std::string addr;
  bool legacyApi = false;
  std::string accessToken;  // Jwt
  std::string refreshToken;

 public:
  DGraphClientStub(const std::string& addr = "localhost:9080",
                   bool legacyApi = false);
  int detectApiVersion();

  std::string login(std::string userid, std::string password,
                    std::string refreshToken) {}

  void alter(Operation op, std::function<void(Payload)> callBack);

  std::string retryLogin() {}

  // I find This is the only function that is used
  void query(Request req, std::function<void(Response)> callBack);

  void mutate(Mutation mu, std::function<void(Response)> callBack);

  void commit(TxnContext& ctx, std::function<void(TxnContext)> callBack);
  void abort(TxnContext ctx, std::function<void(TxnContext)> callBack);

  void close() {}
};

}  // namespace dgraph
#endif  // DGraphClientStub_H
