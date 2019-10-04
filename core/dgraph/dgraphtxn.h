#ifndef DGRAPHCLIENT_TXN_H
#define DGRAPHCLIENT_TXN_H

//#import "./dgraphclient.h" //gives error
namespace dgraph {
struct Response;
class TxnContext;
class DgraphClient;
struct TxnOptions {
  bool readOnly = false;
  bool bestEffort = false;
};
/**
 * Txn is a single atomic transaction.
 *
 * A transaction lifecycle is as follows:
 *
 * 1. Created using Client.newTxn.
 *
 * 2. Various query and mutate calls made.
 *
 * 3. commit or discard used. If any mutations have been made, It's important
 * that at least one of these methods is called to clean up resources. discard
 * is a no-op if commit has already been called, so it's safe to call discard
 * after calling commit.
 */
class DGraphTxn {
  DgraphClient *dc;
  TxnContext ctx;
  bool finished = false;
  bool mutated = false;
  bool useReadOnly = false;
  bool useBestEffort = false;

 public:
  DGraphTxn(DgraphClient *dc, TxnOptions txnOpts);

  /**
   * query sends a query to one of the connected Dgraph instances. If no
   * mutations need to be made in the same transaction, it's convenient to chain
   * the method, e.g. client.newTxn().query("...").
   */
  void query(std::string q, std::function<void(Response)> callBack);

  /**
   * queryWithVars is like query, but allows a variable map to be used. This can
   * provide safety against injection attacks.
   */
  void queryWithVars(const std::string &q,
                     const std::map<std::string, std::string> &vars,
                     std::function<void(Response)> callBack);

  /**
   * mutate allows data stored on Dgraph instances to be modified. The fields in
   * Mutation come in pairs, set and delete. Mutations can either be encoded as
   * JSON or as RDFs.
   *
   * If commitNow is set, then this call will result in the transaction being
   * committed. In this case, an explicit call to commit doesn't need to
   * subsequently be made.
   *
   * If the mutation fails, then the transaction is discarded and all future
   * operations on it will fail.
   */
  void mutate(Mutation mu, std::function<void(Response)> callBack);

  // void doRequest(Request req, std::function<void(Response)> callBack);

  /**
   * commit commits any mutations that have been made in the transaction. Once
   * commit has been called, the lifespan of the transaction is complete.
   *
   * Errors could be thrown for various reasons. Notably, ERR_ABORTED could be
   * thrown if transactions that modify the same data are being run
   * concurrently. It's up to the user to decide if they wish to retry. In this
   * case, the user should create a new transaction.
   */
  void commit();

  /**
   * discard cleans up the resources associated with an uncommitted transaction
   * that contains mutations. It is a no-op on transactions that have already
   * been committed or don't contain mutations. Therefore it is safe (and
   * recommended) to call it in a finally block.
   *
   * In some cases, the transaction can't be discarded, e.g. the grpc connection
   * is unavailable. In these cases, the server will eventually do the
   * transaction clean up.
   */
  void discard();

 private:
  void mergeContext(TxnContext src);
};

class Utils {
 public:
  static bool isAbortedError(std::string error);
  static bool isConflictError(std::string error);
};
}  // namespace dgraph
#endif  // DGRAPHCLIENT_TXN_H
