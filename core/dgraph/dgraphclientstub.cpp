#include "dgraphclientstub.h"
#include <boost/beast/core.hpp>
#include "drogon/drogon.h"
namespace dgraph {

DGraphClientStub::DGraphClientStub(std::string addr, bool legacyApi)
    : addr(addr), legacyApi(legacyApi) {}

int DGraphClientStub::detectApiVersion() {
  //  auto health = this->health();
  //  this->legacyApi = health.version.startsWith("1.0.");
  //  return health.version;
}

Payload DGraphClientStub::alter(Operation op,
                                std::function<void(Payload)> callBack) {
  auto httpClient = dgraph::HttpClientManager::getClient("1");
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
      LOG_DEBUG << "Invalid op argument in alter";
      return {};
    }

    auto callBackHttp = [callBack](std::string result) {
      //
      callBack({result});
    };
    httpClient->drogonHttpAPI("localhost", 8080, "/alter",
                              boost::beast::http::verb::post, body, "", {},
                              callBackHttp);

  } catch (std::exception const &e) {
    std::cerr << "Error: " << e.what() << std::endl;
    return {e.what()};
  }
}

Response DGraphClientStub::query(Request req) {
  auto httpClient = dgraph::HttpClientManager::getClient("1");

  std::string content_type;
  //  if(this->legacyApi)
  if (req.varsMap.size() > 0) {
    content_type = "application/json";

    nlohmann::json j;
    j["query"] = req.query;
    j["variables"] = req.varsMap;
    req.query = j.dump();
    LOG_DEBUG << "MUST" << req.query;
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

  auto result = httpClient->callAPICurl("localhost", 8080, "/query" + target,
                                        boost::beast::http::verb::post,
                                        req.query, content_type, {});

  Response r;
  r.json = result;

  return r;
}

Response DGraphClientStub::mutate(Mutation mu) {
  auto httpClient = dgraph::HttpClientManager::getClient("1");
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
    body = R"(
  {
                {0}
                {1}
            }
)";
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
    LOG_DEBUG << "Mutation has no data";
    return {};
  }
  std::string content_type;
  if (usingJSON) {
    content_type = "application/json";
  } else {
    content_type = "application/rdf";
  }

  std::string target;

  std::string nextDelim = "?";
  if (mu.startTs > 0) {
    target += "?startTs=" + std::to_string(mu.startTs);
    nextDelim = "&";
  }
  if (mu.commitNow) {
    target += nextDelim + "commitNow=true";
  }

  auto result = httpClient->callAPI("localhost", 8080, "/mutate" + target,
                                    boost::beast::http::verb::post, body,
                                    content_type, {});

  Response r;
  r.json = result;

  return r;
}

TxnContext DGraphClientStub::commitOrAbort(TxnContext ctx) {}

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

}  // namespace dgraph
