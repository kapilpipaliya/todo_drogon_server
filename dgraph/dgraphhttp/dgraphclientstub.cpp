#include "dgraphclientstub.h"

#include "dgraph/dgraphhttp/httpendpoint/DGraphHttpClient.h"
#include "dgraph/dgraphhttp/httpendpoint/HttpClientManger.h"

namespace dgraph {
namespace http {
DGraphClientStub::DGraphClientStub(const std::string &host, const int port,
                                   bool legacyApi)
    : host(host), port(port), legacyApi(legacyApi) {}

int DGraphClientStub::detectApiVersion() {
  //  auto health = this->health();
  //  this->legacyApi = health.version.startsWith("1.0.");
  //  return health.version;
}

void DGraphClientStub::alter(Operation op,
                             std::function<void(Payload)> callBack) {
  auto httpClient = dgraph::http::HttpClientManager::getClient("1");
  std::string body;
  try {
    if (!op.schema.empty()) {
      body = op.schema;
    } else if (!op.dropAttr.empty()) {
      nlohmann::json j;
      j["drop_attr"] = op.dropAttr;
      body = j.dump();
    } else if (op.dropAll) {
      nlohmann::json j;
      j["drop_all"] = true;
      body = j.dump();
    } else {
      std::cout << "Invalid op argument in alter" << std::endl;
    }
    auto callBackHttp = [callBack](std::string result) { callBack({result}); };
    httpClient->drogonHttpAPI(host, port, "/alter", "post", body, "", {},
                              callBackHttp);

  } catch (std::exception const &e) {
    std::cerr << "Error: " << e.what() << std::endl;
  }
}

void DGraphClientStub::query(Request req,
                             std::function<void(Response)> callBack) {
  auto httpClient = dgraph::http::HttpClientManager::getClient("1");

  std::string content_type;
  if (req.varsMap.size() > 0) {
    content_type = "application/json";

    nlohmann::json j;
    j["query"] = req.query;
    j["variables"] = req.varsMap;
    req.query = j.dump();
  } else {
    content_type = "application/graphql+-";
  }

  std::string target;

  std::map<std::string, std::string> params;
  if (req.startTs != 0) {
    params["startTs"] = std::to_string(req.startTs);
  }
  if (req.timeout > 0) {
    params["timeout"] = std::to_string(req.timeout) + "s";
  }
  if (req.debug) {
    params["debug"] = "true";
  }
  if (params.size() > 0) {
    target += "?";
    for (auto &it : params) {
      target += it.first + "=" + it.second + "&";
    }
    if (!target.empty()) {
      target.pop_back();
    }
  }
  auto callBackHttp = [callBack](std::string result) {
    Response r;
    r.json = result;
    callBack(r);
  };
  httpClient->drogonHttpAPI(host, port, "/query" + target, "post",

                            req.query, content_type, {}, callBackHttp);
}

void DGraphClientStub::mutate(Mutation mu,
                              std::function<void(Response)> callBack) {
  auto httpClient = dgraph::http::HttpClientManager::getClient("1");
  std::string body;
  bool usingJSON = false;
  if (!mu.setJson.empty() || !mu.deleteJson.empty()) {
    usingJSON = true;
    nlohmann::json obj;
    if (!mu.setJson.empty()) {
      obj["set"] = mu.setJson;
    }
    if (!mu.deleteJson.empty()) {
      obj["delete"] = mu.deleteJson;
    }
    body = obj.dump();
  } else if (!mu.setNquads.empty() || !mu.delNquads.empty()) {
    body = "  {";
    if (!mu.setNquads.empty()) {
      body += "set {";
      body += mu.setNquads;
      body += "}";
    }
    if (!mu.delNquads.empty()) {
      body += "delete {";
      body += mu.delNquads;
      body += "}";
    }
    body += "}";
  } else if (!mu.mutation.empty()) {
    body = mu.mutation;
    if (mu.isJsonString) {
      // Caller has specified mutation type
      usingJSON = mu.isJsonString;
    } else {
      // Detect content-type
      try {
        auto r = nlohmann::json::parse(mu.mutation);
        usingJSON = true;
      } catch (std::exception &e) {
        usingJSON = false;
      }
    }
  } else {
    std::cout << "Mutation has no data" << std::endl;
  }
  std::string content_type;
  if (usingJSON) {
    content_type = "application/json";
  } else {
    content_type = "application/rdf";
  }

  std::string target = "/mutate";

  std::string nextDelim = "?";
  if (mu.startTs > 0) {
    target += "?startTs=" + std::to_string(mu.startTs);
    nextDelim = "&";
  }
  if (mu.commitNow) {
    target += nextDelim + "commitNow=true";
  }
  auto callBackHttp = [callBack](std::string result) {
    auto j = nlohmann::json::parse(result);

    Response r;
    TxnContext t;
    // Todo handle error here:
    if (j.contains("errors")) {
      std::cout << j["errors"][0]["message"].get<std::string>() << std::endl;
      std::cout
          << "-----------Todo: Please Handle this situation properly----------"
          << std::endl;
    } else {
      auto p2 = j["extensions"]["txn"].get<dgraph::http::TxnContext>();
      r.txn = p2;
      r.json = result;
      callBack(r);
    }
  };
  httpClient->drogonHttpAPI(host, port, target, "post", body, content_type, {},
                            callBackHttp);
}

void DGraphClientStub::commit(TxnContext &ctx,
                              std::function<void(TxnContext)> callBack) {
  std::string body;
  if (ctx.keysList.size() > 0) {
    nlohmann::json j;
    for (auto &i : ctx.keysList) {
      j.push_back(i);
    }
    body = j.dump();
  }
  auto url = "/commit?startTs=" + std::to_string(ctx.startTs);
  auto callBackHttp = [callBack](std::string result) {
    TxnContext t;
    // todo..
    callBack(t);
  };
  auto httpClient = dgraph::http::HttpClientManager::getClient("1");
  httpClient->drogonHttpAPI(host, port, url, "post", body, "", {},
                            callBackHttp);
}
void DGraphClientStub::abort(TxnContext ctx,
                             std::function<void(TxnContext)> callBack) {
  auto url = "commit?startTs=" + std::to_string(ctx.startTs) + "&abort=true";
  auto callBackHttp = [callBack](std::string result) {
    TxnContext t;
    // todo..
    callBack(t);
  };
  auto httpClient = dgraph::http::HttpClientManager::getClient("1");
  httpClient->drogonHttpAPI(host, port, url, "post", "", "", {}, callBackHttp);
}

std::string renderDgraphError(error e) {
  switch (e) {
    case ERR_NO_CLIENTS:
      return "No clients provided in DgraphClient autoructor";
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

void to_json(nlohmann::json &j, const TxnContext &p) {
  j = nlohmann::json{
      {"start_ts", p.startTs},
      {"keys", p.keysList},
      {"preds", p.predsList},
      {"commit_ts", p.commitTs},
  };
}

void from_json(const nlohmann::json &j, TxnContext &p) {
  j.at("start_ts").get_to(p.startTs);
  // if mutation/commitNow=true it not retrun keys and return commit_ts
  if (j.contains("keys") && j["keys"].is_array()) {
    j.at("keys").get_to(p.keysList);
  }
  if (j.contains("commit_ts") && j["commit_ts"].is_number()) {
    j.at("commit_ts").get_to(p.commitTs);
  }
  j.at("preds").get_to(p.predsList);
}
}  // namespace http
}  // namespace dgraph
