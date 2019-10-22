#include "dgraphclient.h"

#include <iostream>
#include <memory>

#include "dgraphclientstub.h"
#include "dgraphtxn.h"

namespace dgraph {
namespace http {
DGraphClient::DGraphClient(std::vector<DGraphClientStub> clients) {
  if (clients.size() == 0) {
    throw ERR_NO_CLIENTS;
  }

  this->clients = clients;
}

void DGraphClient::alter(Operation op, std::function<void(Payload)> callBack) {
  std::cout << "Alter request:" << std::endl;
  std::cout << op.schema << std::endl;

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

std::shared_ptr<DGraphTxn> DGraphClient::newTxn(TxnOptions txnOpts) {
  std::shared_ptr<DGraphTxn> txn = std::make_shared<DGraphTxn>(this, txnOpts);
  return txn;
}

void DGraphClient::setDebugMode(bool mode) { this->debugMode = mode; }

void DGraphClient::debug(std::string msg) {
  if (this->debugMode) {
    std::cout << msg << std::endl;
  }
}

DGraphClientStub DGraphClient::anyClient() {
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

/**
 * deleteEdges sets the edges corresponding to predicates on the node with the
 * given uid for deletion.
 *
 * This helper function doesn't run the mutation on the server. It must be done
 * by the user after the function returns.
 */
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
}  // namespace http
}  // namespace dgraph
