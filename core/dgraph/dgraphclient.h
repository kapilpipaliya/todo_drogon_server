#ifndef DGRAPHCLIENT_H
#define DGRAPHCLIENT_H
#include <functional>
#include <memory>
#include <string>
#include <vector>
#include "dgraphclientstub.h"
namespace dgraph {
class DGraphTxn;
struct TxnOptions;

/**
 * Client is a transaction aware client to a set of Dgraph server instances.
 */
class DgraphClient {
  std::vector<DGraphClientStub> clients;

 public:
  bool debugMode = false;
  /**
   * Creates a new Client for interacting with the Dgraph store.
   *
   * The client can be backed by multiple connections (to the same server, or
   * multiple servers in a cluster).
   */
  explicit DgraphClient(std::vector<DGraphClientStub> clients);

  /**
   * By setting various fields of api.Operation, alter can be used to do the
   * following:
   *
   * 1. Modify the schema.
   *
   * 2. Drop a predicate.
   *
   * 3. Drop the database.
   */
  void alter(Operation op, std::function<void(Payload)>);

  /**
   * newTxn creates a new transaction.
   */
  std::shared_ptr<DGraphTxn> newTxn(TxnOptions txnOpts);

  /**
   * setDebugMode switches on/off the debug mode which prints helpful debug
   * messages while performing alters, queries and mutations.
   */
  void setDebugMode(bool mode = true);

  /**
   * debug prints a message on the console if debug mode is switched on.
   */
  void debug(std::string msg);

  DGraphClientStub anyClient();
};

// isJwtExpired returns true if the error indicates that the jwt has expired.
bool isJwtExpired(std::string err);

/**
 * deleteEdges sets the edges corresponding to predicates on the node with the
 * given uid for deletion.
 *
 * This helper function doesn't run the mutation on the server. It must be done
 * by the user after the function returns.
 */
void deleteEdges(Mutation mu, std::string uid,
                 std::vector<std::string> predicates);
;
}  // namespace dgraph
#endif  // DGRAPHCLIENT_H
