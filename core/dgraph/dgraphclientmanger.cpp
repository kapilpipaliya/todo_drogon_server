#include "dgraphclientmanger.h"
#include <cassert>
#include "./dgraphclient.h"
#include "./dgraphclientstub.h"
namespace dgraph {
std::map<std::string, std::shared_ptr<DgraphClient>>
    DGraphClientManger::dgraphconns = {};
DGraphClientManger::DGraphClientManger() {}

std::shared_ptr<DgraphClient> DGraphClientManger::getDGraphClient(
    const std::string &name) {
  assert(dgraphconns.find(name) != dgraphconns.end());
  return dgraphconns[name];
}

std::shared_ptr<DgraphClient> DGraphClientManger::createDGraphClient(
    const std::string &name, const dgraph::DGraphClientStub &clientstub) {
  std::vector<DGraphClientStub> clients;
  clients.push_back(clientstub);
  auto ptr = std::make_shared<DgraphClient>(clients);
  dgraphconns[name] = ptr;
  return ptr;
}
}  // namespace dgraph
