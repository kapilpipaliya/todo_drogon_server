#ifndef DGRAPHGRPCTYPE_H
#define DGRAPHGRPCTYPE_H

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>
#include "../dgraph-js/generated/api.grpc.pb.h"

#include "../dgraph-js/generated/api.pb.h"

// delete this file.
namespace dgraph {
namespace grpcclient {

class Payload : public api::Payload {
 public:
  // nlohmann::json getData();
  std::string getData_asB64();
  std::string getData_asU8();
  void setData(std::string value);
};

class Response : public api::Response {
 public:
  // nlohmann::json getJson();
  std::string getJson_asB64();
  std::string getJson_asU8();
  void setJson(std::string value);
};

class Mutation : public api::Mutation {
 public:
  // nlohmann::json getSetJson();
  std::string getSetJson_asB64();
  std::string getSetJson_asU8();
  void setSetJson(std::string value);

  // nlohmann::json getDeleteJson();
  std::string getDeleteJson_asB64();
  std::string getDeleteJson_asU8();
  void setDeleteJson(std::string value);

  // nlohmann::json getSetNquads();
  std::string getSetNquads_asB64();
  std::string getSetNquads_asU8();
  void setSetNquads(std::string value);

  // nlohmann::json getDelNquads();
  std::string getDelNquads_asB64();
  std::string getDelNquads_asU8();
  void setDelNquads(std::string value);
};

Payload createPayload(api::Payload oldPayload);
Response createResponse(api::Response oldResponse);

// utils.ts
void errorCode();
bool isAbortedError(grpc::StatusCode status_code);
bool isConflictError(grpc::StatusCode status_code);
bool isUnauthenticatedError();
void promisify1();
void promisify3();
std::string stringifyMessage(const google::protobuf::Message &msg);
bool isBase64(const std::string &str);
std::string strToB64(const std::string &str);
std::string strToU8(const std::string &str);
std::string b64ToStr(const std::string &str);
std::string u8ToStr(const std::string &str);

// errors.ts
enum error {
  ERR_NO_CLIENTS,
  ERR_FINISHED,
  ERR_ABORTED,
  ERR_BEST_EFFORT_REQUIRED_READ_ONLY,
  ERR_READ_ONLY,
  ERR_REFRESH_JWT_EMPTY
};
std::string errorToString(error err);

}  // namespace grpcclient
}  // namespace dgraph
#endif  // DGRAPHGRPCTYPE_H
