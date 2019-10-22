#ifndef DGRAPHGRPCCLIENT_H
#define DGRAPHGRPCCLIENT_H

#include <vector>
#include <memory>

#include <grpc/grpc.h>
#include <grpcpp/channel.h>
#include <grpcpp/client_context.h>
#include <grpcpp/create_channel.h>
#include <grpcpp/security/credentials.h>

#include "../dgraph-js/generated/api.grpc.pb.h"
#include "../dgraph-js/generated/api.pb.h"
#include "./txn.h"

namespace dgraph {
namespace grpcclient {
enum error {
    ERR_NO_CLIENTS,
    ERR_FINISHED,
    ERR_ABORTED,
    ERR_BEST_EFFORT_REQUIRED_READ_ONLY,
    ERR_READ_ONLY,
    ERR_REFRESH_JWT_EMPTY
};
std::string errorToString(error err);
class DgraphClient
{
    std::vector<std::unique_ptr<api::Dgraph::Stub> > clients;
    std::string accessJwt;
    std::string refreshJwt;

public:
    bool debugMode =false;
    /**
     * Creates a new Client for interacting with the Dgraph store.
     *
     * The client can be backed by multiple connections (to the same server, or
     * multiple servers in a cluster).
     */
    DgraphClient(std::vector<std::unique_ptr<api::Dgraph::Stub> > &clients);
    // Todo Implement this:
    std::string login(std::string userid, std::string password,
                      std::string refreshJwt);


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
    void alter(api::Operation &op, api::Payload *response);

    api::Jwt retryLogin();


    /**
   * newTxn creates a new transaction.
   */
    std::shared_ptr<grpcclient::Txn> newTxn(TxnOptions txnOpts);

    /**
   * setDebugMode switches on/off the debug mode which prints helpful debug
   * messages while performing alters, queries and mutations.
   */
    void setDebugMode(bool mode = true);

    /**
   * debug prints a message on the console if debug mode is switched on.
   */
    void debug(std::string msg);

    std::unique_ptr<api::Dgraph::Stub> &anyClient();
      void checkVersion(api::Check &check, api::Version *version);
};

// isJwtExpired returns true if the error indicates that the jwt has expired.
bool isJwtExpired(grpc::StatusCode status_code);

// DeleteEdges sets the edges corresponding to predicates
// on the node with the given uid for deletion.
// This helper function doesn't run the mutation on the server.
// It must be done by the user after the function returns.
// Txn needs to be committed in order to execute the mutation.
void deleteEdges(api::Mutation mu, std::string uid,
                 std::vector<std::string> predicates);
}
}
#endif // DGRAPHGRPCCLIENT_H
