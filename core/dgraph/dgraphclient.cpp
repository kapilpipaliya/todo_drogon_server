#include "dgraphclient.h"
#include <memory>
#include "dgraphtxn.h"
#include "drogon/drogon.h"
namespace dgraph {

DgraphClient::DgraphClient(std::vector<DGraphClientStub> clients) {
  if (clients.size() == 0) {
    throw ERR_NO_CLIENTS;
  }

  this->clients = clients;
}

void DgraphClient::alter(Operation op, std::function<void(Payload)> callBack) {
  LOG_DEBUG << "Alter request:";
  LOG_DEBUG << op.schema;

  auto c = this->anyClient();
  try {
    c.alter(op, callBack);
  } catch (std::exception &e) {
    //          if (isJwtExpired(e) == true) {
    //            c.retryLogin();
    //            payload = c.alter(op);
    //          } else {
    //            throw e;
    //          }
  }
  // not work.
  // this->debug("Alter response:" + payload.data);
}

std::shared_ptr<DGraphTxn> DgraphClient::newTxn(TxnOptions txnOpts) {
  std::shared_ptr<DGraphTxn> txn = std::make_shared<DGraphTxn>(this, txnOpts);
  return txn;
}

void DgraphClient::setDebugMode(bool mode) { this->debugMode = mode; }

void DgraphClient::debug(std::string msg) {
  if (this->debugMode) {
    LOG_DEBUG << msg;
  }
}

DGraphClientStub DgraphClient::anyClient() {
  //      return this.clients[Math.floor(Math.random() *
  //      this.clients.length)];
  return clients.at(0);
}

bool isJwtExpired(std::string err) {
  //    if (!err) {
  //      return false;
  //    }
  //    return isUnauthenticatedError(err);
}

void deleteEdges(Mutation mu, std::string uid,
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

}  // namespace dgraph
