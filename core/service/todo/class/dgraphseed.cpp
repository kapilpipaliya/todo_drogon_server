#include "dgraphseed.h"

//#include "core/dgraph/http/HttpClientManger.h"
#include "core/dgraph/dgraphclientmanger.h"
#include "core/dgraph/dgraphhttp/dgraphclient.h"
#include "core/dgraph/dgraphhttp/dgraphclientstub.h"
#include "core/dgraph/dgraphhttp/dgraphtxn.h"
namespace todo {
namespace service {
DGraphSeed::DGraphSeed() {}

void DGraphSeed::setupTable() {}

void DGraphSeed::handleEvent(const drogon::WebSocketConnectionPtr &wsConnPtr,
                             nlohmann::json event, unsigned long next,
                             nlohmann::json args) {
  auto event_cmp = event[next].get<int>();
  if (event_cmp == 1) {
    dgraph::http::Operation op;
    op.schema = "{\"drop_all\": true}";

    auto dgraphClient = dgraph::DGraphClientManger::getDGraphClient("1");

    auto callBack = [event, wsConnPtr](dgraph::http::Payload result) {
      nlohmann::json j = nlohmann::json::array(
          {nlohmann::json::array({event, nlohmann::json::parse(result.data)})});
      websocket::WsFns::sendJson(wsConnPtr, j);
    };
    dgraphClient->alter(op, callBack);
  } else if (event_cmp == 11) {
    dgraph::http::Operation op;
    op.schema = R"(
# Define Types

type Person {
    name: string
    age: int
    friend: [Person]
}

type Animal {
    name: string
}

# Define Directives and index

name: string @index(term) @lang .
age: int @index(int) .
friend: [uid] @count .
)";

    auto dgraphClient = dgraph::DGraphClientManger::getDGraphClient("1");

    auto callBack = [event, wsConnPtr](dgraph::http::Payload result) {
      nlohmann::json j = nlohmann::json::array(
          {nlohmann::json::array({event, nlohmann::json::parse(result.data)})});
      websocket::WsFns::sendJson(wsConnPtr, j);
    };
    dgraphClient->alter(op, callBack);
  } else if (event_cmp == 2) {
    auto dgraphClient = dgraph::DGraphClientManger::getDGraphClient("1");
    dgraphClient->newTxn({});
    auto query = R"(
{
  everyone(func: anyofterms(name, "Michael Amit")) {
    name
    friend {
      name@ru:ko:en
      friend { expand(_all_) { expand(_all_) } }
    }
  }
}
)";
    auto callBack = [event, wsConnPtr](dgraph::http::Response result) {
      nlohmann::json j = nlohmann::json::array(
          {nlohmann::json::array({event, nlohmann::json::parse(result.json)})});
      websocket::WsFns::sendJson(wsConnPtr, j);
    };
    dgraphClient->newTxn({})->queryWithVars(query, {{"$a", "Alice"}}, callBack);

  } else if (event_cmp == 3) {
    auto dgraphClient = dgraph::DGraphClientManger::getDGraphClient("1");
    auto txn = dgraphClient->newTxn({});
    auto query = R"(
    _:michael <name> "Michael" .
    _:michael <dgraph.type> "Person" .
    _:michael <age> "39" .
    _:michael <friend> _:amit .
    _:michael <friend> _:sarah .
    _:michael <friend> _:sang .
    _:michael <friend> _:catalina .
    _:michael <friend> _:artyom .
    _:michael <owns_pet> _:rammy .

    _:amit <name> "अमित"@hi .
    _:amit <name> "অমিত"@bn .
    _:amit <name> "Amit"@en .
    _:amit <dgraph.type> "Person" .
    _:amit <age> "35" .
    _:amit <friend> _:michael .
    _:amit <friend> _:sang .
    _:amit <friend> _:artyom .

    _:luke <name> "Luke"@en .
    _:luke <dgraph.type> "Person" .
    _:luke <name> "Łukasz"@pl .
    _:luke <age> "77" .

    _:artyom <name> "Артём"@ru .
    _:artyom <name> "Artyom"@en .
    _:artyom <dgraph.type> "Person" .
    _:artyom <age> "35" .

    _:sarah <name> "Sarah" .
    _:sarah <dgraph.type> "Person" .
    _:sarah <age> "55" .

    _:sang <name> "상현"@ko .
    _:sang <name> "Sang Hyun"@en .
    _:sang <dgraph.type> "Person" .
    _:sang <age> "24" .
    _:sang <friend> _:amit .
    _:sang <friend> _:catalina .
    _:sang <friend> _:hyung .
    _:sang <owns_pet> _:goldie .

    _:hyung <name> "형신"@ko .
    _:hyung <name> "Hyung Sin"@en .
    _:hyung <dgraph.type> "Person" .
    _:hyung <friend> _:sang .

    _:catalina <name> "Catalina" .
    _:catalina <dgraph.type> "Person" .
    _:catalina <age> "19" .
    _:catalina <friend> _:sang .
    _:catalina <owns_pet> _:perro .

    _:rammy <name> "Rammy the sheep" .
    _:rammy <dgraph.type> "Animal" .

    _:goldie <name> "Goldie" .
    _:goldie <dgraph.type> "Animal" .

    _:perro <name> "Perro" .
    _:perro <dgraph.type> "Animal" .
)";
    try {
      dgraph::http::Mutation mu;
      // mu.setJson = query;
      mu.commitNow = true;
      mu.setNquads = query;
      auto callBack = [txn, event, wsConnPtr](dgraph::http::Response result) {
        nlohmann::json j = nlohmann::json::array({nlohmann::json::array(
            {event, nlohmann::json::parse(result.json)})});
//                                                                                txn->commit();
        websocket::WsFns::sendJson(wsConnPtr, j);
      };
      txn->mutate(mu, callBack);
    } catch (std::exception &e) {
      LOG_DEBUG << "There is error happened when talking to the server"
                << e.what();
      throw e;
    }
  } else {
  }
}
}  // namespace service
}  // namespace todo
