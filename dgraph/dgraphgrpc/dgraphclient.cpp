#include "./dgraphclient.h"

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

namespace dgraph {
namespace grpcclient {

DgraphClient::DgraphClient(
    std::vector<std::unique_ptr<api::Dgraph::Stub> > &clients) {
  if (clients.size() == 0) {
    throw std::runtime_error(errorToString(ERR_NO_CLIENTS));
  }
  this->clients = std::move(clients);
}

std::string DgraphClient::login(std::string userid, std::string password,
                                std::string refreshJwt) {
  return "";
}

void DgraphClient::alter(api::Operation &op, api::Payload *response) {
  debug("Alter request:\n" + op.schema());  // stringifyMessage(op)
  auto &dc = this->anyClient();

  grpc::ClientContext context;  // getContext(ctx)
  auto status = dc->Alter(&context, op, response);
  if (status.ok()) {
    // std::cout << "rpc succeeded." << std::endl;
  } else {
    std::cout << "alter rpc failed." << std::endl;
    std::cout << op.SerializeAsString() << std::endl;
    std::cout << status.error_message() << std::endl;
    if (isJwtExpired(status.error_code())) {
      //    dc.retryLogin(); // if err != nil { return err }
      //    stub_->Alter(&context, op, response);
      //  } else {
      //    throw err;
    }
  }

  debug("Alter response:\n" + response->data());  // stringifyMessage(pl)
}

api::Jwt DgraphClient::retryLogin() {
  /*if (refreshJwt.length === 0) {
  throw ERR_REFRESH_JWT_EMPTY;
}
const req = new api::LoginRequest();
req.setRefreshToken(refreshJwt);
const resp = await promisified.login(req);
const jwtResponse = api::Jwt.deserializeBinary(resp.getJson_asU8());
accessJwt = jwtResponse.getAccessJwt();
refreshJwt = jwtResponse.getRefreshJwt();
return jwtResponse;*/
}

std::shared_ptr<Txn> DgraphClient::newTxn(TxnOptions txnOpts) {
  std::shared_ptr<Txn> txn = std::make_shared<Txn>(this, txnOpts);
  return txn;
}

void DgraphClient::setDebugMode(bool mode) { this->debugMode = mode; }

void DgraphClient::debug(std::string msg) {
  if (this->debugMode) {
    std::cout << msg << std::endl;
  }
}

std::unique_ptr<api::Dgraph::Stub> &DgraphClient::anyClient() {
  //      return this.clients[Math.floor(Math.random() *
  //      this.clients.length)];
  return clients.at(0);
}

void DgraphClient::checkVersion(api::Check &check, api::Version *version) {
  auto &dc = this->anyClient();
  grpc::ClientContext context;
  auto status = dc->CheckVersion(&context, check, version);
  if (status.ok()) {
    // std::cout << "rpc succeeded." << std::endl;
  } else {
    std::cout << "rpc failed." << std::endl;
    std::cout << status.error_message() << std::endl;
  }
}

bool isJwtExpired(grpc::StatusCode status_code) {
  //    if (!err) {
  //        return false;
  //    }
  //    return isUnauthenticatedError(err);
  return false;
}

void deleteEdges(api::Mutation mu, std::string uid,
                 std::vector<std::string> predicates) {
  //    for (const predicate of predicates) {
  //      const nquad = new NQuad();
  //      nquad.setSubject(uid);
  //      nquad.setPredicate(predicate);

  //      const ov = new Value();
  //      ov.setDefaultVal("_STAR_ALL");
  //      nquad.setObjectValue(ov);

  //      mu.addDel(nquad);
  //    }
}

std::string errorToString(error err) {
  switch (err) {
    case ERR_NO_CLIENTS:
      return "No clients provided in DgraphClient constructor";
    case ERR_FINISHED:
      return "Transaction has already been committed or discarded";
    case ERR_ABORTED:
      return "Transaction has been aborted. Please retry";
    case ERR_BEST_EFFORT_REQUIRED_READ_ONLY:
      return "Best effort only works for read-only queries";
    case ERR_READ_ONLY:
      return "Readonly transaction cannot run mutations or be committed";
    case ERR_REFRESH_JWT_EMPTY:
      return "refresh jwt should not be empty";
  }
}

}  // namespace grpcclient
}  // namespace dgraph
