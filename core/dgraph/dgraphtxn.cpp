#include "dgraphtxn.h"
#include "dgraphclient.h"
namespace dgraph {

DGraphTxn::DGraphTxn(DgraphClient *dc, TxnOptions txnOpts) { this->dc = dc; }

void DGraphTxn::query(std::string q, std::function<void(Response)> callBack) {
  this->queryWithVars(q, {}, callBack);
}

void DGraphTxn::queryWithVars(std::string q,
                              std::map<std::string, std::string> vars,
                              std::function<void(Response)> callBack) {
  if (this->finished) {
    dc->debug("Query request (ERR_FINISHED):\nquery = ${q}\nvars = ${vars}");
    throw ERR_FINISHED;
  }

  Request req;
  req.query = q;
  req.startTs = this->ctx.startTs;
  req.readOnly = this->useReadOnly;
  req.bestEffort = this->useBestEffort;
  req.varsMap = vars;
  this->doRequest(req, callBack);
}

void DGraphTxn::mutate(Mutation mu, std::function<void(Response)> callBack) {
  Request req;
  req.startTs = this->ctx.startTs;
  req.mutationsList.push_back(mu);
  req.commitNow = mu.commitNow;

  this->doRequest(req, callBack);
}

void DGraphTxn::doRequest(Request req, std::function<void(Response)> callBack) {
  auto mutationList = req.mutationsList;
  if (this->finished) {
    this->dc->debug(
        "Do request (ERR_FINISHED):\nquery = ${req.getQuery()}\nvars = "
        "${req.getVarsMap()}");
    this->dc->debug(
        "Do request (ERR_FINISHED):\nmutation = "
        "${stringifyMessage(mutationList[0])}");
    throw ERR_FINISHED;
  }

  if (mutationList.size() > 0) {
    if (this->useReadOnly) {
      this->dc->debug(
          "Do request (ERR_READ_ONLY):\nmutation = "
          "${stringifyMessage(mutationList[0])}");
      throw ERR_READ_ONLY;
    }
    this->mutated = true;
  }

  req.startTs = this->ctx.startTs;
  this->dc->debug("Do request :\n " + req.query);  // and/or print mutation

  auto callBack2 = [req, callBack, this](Response resp) {
    callBack(resp);

    if (req.commitNow) {
      this->finished = true;
    }

    this->mergeContext(resp.txn);
    this->dc->debug("Do request :\nresponse" +
                    resp.json);  // print resp properly
  };

  auto c = this->dc->anyClient();
  try {
    c.query(req, callBack2);  // This is the main line

    //        resp = createResponse(reqp);
  } catch (std::exception &e) {
    //    if (isJwtExpired(e)) {
    //      c.retryLogin();
    //      resp = c.query(req);
    //          resp = createResponse(resp);
    //    } else {
    // Since a mutation error occurred, the txn should no longer be sed
    // (some mutations could have applied but not others, but we don't know
    // which ones). Discarding the transaction enforces that the user cannot
    // use the txn further.
    try {
      this->discard();
    } catch (std::exception &e) {
      //          // Ignore error - user should see the original error.
    }

    // Transaction could be aborted(status.ABORTED) if commitNow was true, or
    // server could send a message that this mutation
    // conflicts(status.FAILED_PRECONDITION) with another transaction.
    //      if (isAbortedError(e) || isConflictError(e)) {
    //        throw ERR_ABORTED;
    //      } else {
    //        throw e;
    //      }
  }
}

void DGraphTxn::commit() {
  if (this->finished) {
    throw ERR_FINISHED;
  }

  this->finished = true;
  if (!this->mutated) {
    return;
  }

  auto c = this->dc->anyClient();
  try {
    c.commitOrAbort(this->ctx);
  } catch (std::exception &e) {
    //      if (isJwtExpired(e) == = true) {
    //        await c.retryLogin(metadata, options);
    //        await operation();
    //      } else {
    //        throw isAbortedError(e) ? ERR_ABORTED : e;
    //      }
  }
}

void DGraphTxn::discard() {
  if (this->finished) {
    //      return;
  }

  this->finished = true;
  if (!this->mutated) {
    //      return;
  }

  this->ctx.aborted = true;
  auto c = this->dc->anyClient();
  try {
    c.commitOrAbort(this->ctx);
  } catch (std::exception &e) {
    //      if (isJwtExpired(e) == = true) {
    //        await c.retryLogin(metadata, options);
    //        await operation();
    //      } else {
    //        throw isAbortedError(e) ? ERR_ABORTED : e;
    //      }
  }
}

void DGraphTxn::mergeContext(TxnContext src) {
  //    if (src == = undefined) {
  //      // This condition will be true only if the server doesn't return a
  //      txn
  //      // context after a query or mutation.
  //      return;
  //    }

  if (this->ctx.startTs == 0) {
    this->ctx.startTs = src.startTs;
  } else if (this->ctx.startTs != src.startTs) {
    // This condition should never be true.
    throw "StartTs mismatch";
  }

  for (auto &i : src.keysList) {
    this->ctx.keysList.push_back(i);
  }
}

}  // namespace dgraph
