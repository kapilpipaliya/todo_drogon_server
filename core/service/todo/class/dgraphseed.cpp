#include "dgraphseed.h"

//#include "core/dgraph/http/HttpClientManger.h"
#include "core/dgraph/dgraphclient.h"
#include "core/dgraph/dgraphclientmanger.h"
#include "core/dgraph/dgraphclientstub.h"
#include "core/dgraph/dgraphtxn.h"
namespace todo {
namespace service {
DGraphSeed::DGraphSeed() {}

void DGraphSeed::setupTable() {}

void DGraphSeed::handleEvent(const drogon::WebSocketConnectionPtr &wsConnPtr,
                             nlohmann::json event, unsigned long next,
                             nlohmann::json args) {
  auto event_cmp = event[next].get<int>();
  if (event_cmp == 1) {
    dgraph::Operation op;
    op.schema = "{\"drop_all\": true}";

    auto dgraphClient = dgraph::DGraphClientManger::getDGraphClient("1");

    auto callBack = [event, wsConnPtr](dgraph::Payload result) {
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
    auto callBack = [event, wsConnPtr](dgraph::Payload result) {
      nlohmann::json j =
          nlohmann::json::array({nlohmann::json::array({event, ppl})});
      websocket::WsFns::sendJson(wsConnPtr, j);
    };
    dgraphClient->newTxn({})->queryWithVars(query, {{"$a", "Alice"}}, callBack);

  } else if (event_cmp == 3) {
    auto dgraphClient = dgraph::DGraphClientManger::getDGraphClient("1");
    auto txn = dgraphClient->newTxn({});
    auto query = R"(
{
  set {
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
  }
}

)";
    try {
      dgraph::Mutation mu;
      mu.setJson = query;
      auto res = txn->mutate(mu);
      LOG_DEBUG << "Hiiiiiiii" << res.json;
      auto ppl = nlohmann::json::parse(res.json);
      // Print results.
      LOG_DEBUG << "Number of people named \"Alice\": " << ppl.size();
      nlohmann::json j =
          nlohmann::json::array({nlohmann::json::array({event, ppl})});
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
