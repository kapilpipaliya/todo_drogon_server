#include "./txn.h"

#include <pystring/pystring.h>

#include "./dgraphclient.h"
namespace dgraph {
namespace grpcclient {

Txn::Txn(DgraphClient *dc, TxnOptions txnOpts)
    : useReadOnly(txnOpts.readOnly), useBestEffort(txnOpts.bestEffort) {
  this->dc = dc;

  if (this->useBestEffort && !this->useReadOnly) {
    dc->debug(
        "Client attempted to query using best-effort without setting the "
        "transaction to read-only");
    throw std::runtime_error(errorToString(ERR_BEST_EFFORT_REQUIRED_READ_ONLY));
  }
}

void Txn::query(std::string q, api::Response *response) {
  this->queryWithVars(q, {}, response);
}

void Txn::queryWithVars(const std::string &q,
                        const std::map<std::string, std::string> &vars,
                        api::Response *response) {
  if (this->finished) {
    dc->debug("Query request (ERR_FINISHED):\nquery = " + q +
              "\nvars = " + getPrintableMap(vars));
    throw std::runtime_error(errorToString(ERR_FINISHED));
  }

  api::Request req;
  req.set_query(q);
  req.set_start_ts(ctx.start_ts());
  req.set_read_only(this->useReadOnly);
  req.set_best_effort(this->useBestEffort);
  //  req.timeout = this->dc->getQueryTimeout();
  //  req.debug = options.debug
  auto varsMap = req.mutable_vars();
  varsMap->insert(vars.begin(), vars.end());
  doRequest(req, response);
}

void Txn::mutate(api::Mutation &mu, api::Response *response) {
  api::Request req;
  // doint this on do request function:
  // if (ctx.start_ts() != 0) { req.set_start_ts(ctx.start_ts());}
  req.set_commit_now(mu.commit_now());
  auto mutationList =
      req.mutable_mutations();  // RepeatedPtrField< ::api::Mutation >*
  mutationList->Add(std::move(mu));
  // LOG_DEBUG << mu.commit_now();  // This now changed to false! must fix.
  doRequest(req, response);
}

void Txn::doRequest(api::Request &req, api::Response *response) {
  auto mutationList = req.mutations();

  if (this->finished) {
    this->dc->debug("Do request (ERR_FINISHED):\nquery = " + req.query() +
                    "\nvars = " + getPrintableMap(req.vars()));
    this->dc->debug("Do request (ERR_FINISHED):\nmutation = " +
                    mutationList.at(0).SerializeAsString());
    throw std::runtime_error(errorToString(ERR_FINISHED));
  }

  if (mutationList.size() > 0) {
    if (this->useReadOnly) {
      this->dc->debug("Do request (ERR_READ_ONLY):\nmutation = " +
                      mutationList.at(0).SerializeAsString());
      throw std::runtime_error(errorToString(ERR_READ_ONLY));
    }
    this->mutated = true;
  }

  grpc::ClientContext context;  // get context properly,,
  if (ctx.start_ts() != 0) {
    req.set_start_ts(ctx.start_ts());
  }

  dc->debug("Do request :\n " + req.SerializeAsString());
  auto &c = dc->anyClient();
  auto status = c->Query(&context, req, response);
  // resp = createResponse(reqp); // is this needed?
  if (status.ok()) {
    // Nothing..
  } else {
    std::cout << "rpc failed." << std::endl;
    std::cout << status.error_message() << std::endl;
    if (isJwtExpired(status.error_code())) {
      //      c.retryLogin(); // if err != nil { return nil, err }
      //      resp = c.query(req, response);
      //      resp = createResponse(resp);
    } else {
      // Since a mutation error occurred, the txn should no longer be sed
      // (some mutations could have applied but not others, but we don't know
      // which ones). Discarding the transaction enforces that the user cannot
      // use the txn further.

      auto t = new api::TxnContext();
      this->discard(t);
      delete t;
      // Ignore error - user should see the original error.

      // Transaction could be aborted(status.ABORTED) if commitNow was true, or
      // server could send a message that this mutation
      // conflicts(status.FAILED_PRECONDITION) with another transaction.
      if (status.error_code() == grpc::StatusCode::ABORTED ||
          status.error_code() == grpc::StatusCode::FAILED_PRECONDITION) {
        throw std::runtime_error(errorToString(ERR_ABORTED));
      } else {
        throw std::runtime_error("dgraph::grpcclient::Txn::doRequest: " +
                                 status.error_message());
      }
    }
  }
  if (req.commit_now()) {
    this->finished = true;
  }

  this->mergeContext(response->txn());
  this->dc->debug("Do request :\nresponse" + response->SerializeAsString());
}

void Txn::commit(api::TxnContext *response) {
  if (useReadOnly) {
    throw std::runtime_error(errorToString(ERR_READ_ONLY));
  }
  if (finished) {
    throw std::runtime_error(errorToString(ERR_FINISHED));
  }

  commitOrAbort(response);
  if (response->aborted()) {
    throw std::runtime_error(errorToString(ERR_ABORTED));
  }
}

void Txn::discard(api::TxnContext *response) {
  this->ctx.set_aborted(true);
  commitOrAbort(response);
}

void Txn::commitOrAbort(api::TxnContext *response) {
  if (this->finished) {
    return;
  }

  this->finished = true;
  if (!this->mutated) {
    return;
  }

  // get context properly: this.getContext(this->ctx) refer dbo client
  grpc::ClientContext context;  // get context properly,,
  auto &c = this->dc->anyClient();
  auto status = c->CommitOrAbort(&context, this->ctx, response);
  if (status.ok()) {
    // Nothing..
  } else {
    if (isJwtExpired(status.error_code())) {
      //  await c.retryLogin(metadata, options);
      //  await c.stub_->CommitOrAbort(&context, this->ctx, response);
    } else {
      if (status.error_code() == grpc::StatusCode::ABORTED) {
        throw std::runtime_error(errorToString(ERR_ABORTED));
      } else {
        throw std::runtime_error(status.error_message());
      }
    }
  }
}

void Txn::mergeContext(const api::TxnContext &src) {
  //  if (src == undefined) {
  // This condition will be true only if the server doesn't return a txn context
  // after a query or mutation.
  //      return;
  //  }

  if (this->ctx.start_ts() == 0) {
    this->ctx.set_start_ts(src.start_ts());
  } else if (this->ctx.start_ts() != src.start_ts()) {
    // This condition should never be true.
    throw std::runtime_error("StartTs mismatch");
  }

  for (auto &key : src.keys()) {
    this->ctx.add_keys(key);
  }
  for (auto &pred : src.preds()) {
    this->ctx.add_preds(pred);
  }
}
std::string Txn::getPrintableMap(
    const std::map<std::string, std::string> &vars) {
  return "tofix1";
}

std::string Txn::getPrintableMap(
    const google::protobuf::Map<std::string, std::string> &vars) {
  return "tofix2";
}

}  // namespace grpcclient
}  // namespace dgraph
