#include "dgraphtxn.h"
#include "dgraphclient.h"
namespace dgraph {

DGraphTxn::DGraphTxn(DgraphClient *dc, TxnOptions txnOpts) { this->dc = dc; }

void DGraphTxn::query(std::string q, std::function<void(Response)> callBack) {
  this->queryWithVars(q, {}, callBack);
}

void DGraphTxn::queryWithVars(const std::string &q,
                              const std::map<std::string, std::string> &vars,
                              std::function<void(Response)> callBack) {
  if (this->finished) {
    dc->debug("Query request (ERR_FINISHED):\nquery = " + q +
              "\nvars = " + "vars");  // fix vars.
    throw ERR_FINISHED;
  }

  Request req;
  req.query = q;
  req.startTs = this->ctx.startTs;
  //  req.timeout = this->dc->getQueryTimeout();
  //  req.debug = options.debug
  req.readOnly = this->useReadOnly;
  req.bestEffort = this->useBestEffort;
  req.varsMap = vars;

  auto callBack2 = [req, callBack, this](Response resp) {
    callBack(resp);

    this->mergeContext(resp.txn);  // resp.extensions.txn
    this->dc->debug("Query response:");
    this->dc->debug(resp.json);  // print resp properly
  };

  this->dc->debug("Query request:");
  this->dc->debug(req.query);  // print req dump

  auto c = this->dc->anyClient();
  //  this->doRequest(req, callBack2);
  c.query(req, callBack2);
}
void DGraphTxn::mutate(Mutation mu, std::function<void(Response)> callBack) {
  if (this->finished) {
    this->dc->debug("Mutate request (ERR_FINISHED):\nmutation = \n");
    this->dc->debug(mu.setJson);  // print mu dump
    throw ERR_FINISHED;
  }
  this->mutated = true;
  mu.startTs = this->ctx.startTs;
  this->dc->debug("Mutate request:\n" + mu.mutation);  // print mu dump

  try {
    auto callBack2 = [mu, callBack, this](Response resp) {
      if (mu.commitNow) {
        this->finished = true;
      }

      this->mergeContext(resp.txn);  // resp.extensions.txn
      this->dc->debug("Mutate response:\n");
      this->dc->debug(resp.json);  // print resp dump

      callBack(resp);
    };

    auto c = this->dc->anyClient();
    c.mutate(mu, callBack2);
    // or this->doRequest(req, callBack2);
  } catch (std::exception &e) {
    // Since a mutation error occurred, the txn should no longer be used (some
    // mutations could have applied but not others, but we don't know which
    // ones). Discarding the transaction enforces that the user cannot use the
    // txn further.
    try {
      this->discard();
    } catch (std::exception &e) {
      // Ignore error - user should see the original error.
    }

    // Transaction could be aborted(status.ABORTED) if commitNow was true, or
    // server could send a message that this mutation
    // conflicts(status.FAILED_PRECONDITION) with another transaction.
    if (Utils::isAbortedError(e.what()) || Utils::isConflictError(e.what())) {
      throw ERR_ABORTED;
    } else {
      throw e;
    }
  }
}
/*
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
*/
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
    c.commit(this->ctx, [](TxnContext t) {});
  } catch (std::exception &e) {
    //      if (isJwtExpired(e) == = true) {
    //        await c.retryLogin(metadata, options);
    //        await operation();
    //      } else {
    //        throw isAbortedError(e) ? ERR_ABORTED : e;
    //      }
    if (Utils::isAbortedError(e.what())) {
      throw ERR_ABORTED;
    } else {
      throw e;
    }
  }
}

void DGraphTxn::discard() {
  if (this->finished) {
    return;
  }

  this->finished = true;
  if (!this->mutated) {
    return;
  }

  this->ctx.aborted = true;
  auto c = this->dc->anyClient();
  try {
    c.abort(this->ctx, [](TxnContext t) {});
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
  for (auto &i : src.predsList) {
    this->ctx.predsList.push_back(i);
  }
}

bool Utils::isAbortedError(std::string error) {
  /* if (!(error instanceof APIError)) {
       return false;
     }

     if (error.errors.length === 0) {
       return false;
     }
     const firstError: APIResultError = error.errors[0];

     const message = firstError.message.toLowerCase();
     return message.indexOf("abort") >= 0 && message.indexOf("retry") >= 0;
 */
  return false;
}

bool Utils::isConflictError(std::string error) {
  /*if (!(error instanceof APIError)) {
      return false;
    }

    if (error.errors.length === 0) {
      return false;
    }
    const firstError: APIResultError = error.errors[0];

    const message = firstError.message.toLowerCase();
    return message.indexOf("conflict") >= 0;*/
}

}  // namespace dgraph
