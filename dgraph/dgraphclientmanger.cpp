#include "dgraphclientmanger.h"
#include <cassert>
#include "./dgraphhttp/dgraphclient.h"
#include "./dgraphhttp/dgraphclientstub.h"
#include "./orm/dgraphorm.h"

#include "./dgraphgrpc/dgraphclient.h"
namespace dgraph {

std::map<std::string, std::shared_ptr<http::DGraphClient>>
    DGraphClientManger::dgraph_http_clients = {};
std::map<std::string, std::shared_ptr<grpcclient::DgraphClient>>
    DGraphClientManger::dgraph_grpc_clients = {};
std::map<std::string, std::shared_ptr<orm::DGraphOrm>>
    DGraphClientManger::dgraphorms = {};
DGraphClientManger::DGraphClientManger() {}

std::shared_ptr<http::DGraphClient> DGraphClientManger::getDGraphClient(
    const std::string &name) {
  assert(dgraph_http_clients.find(name) != dgraph_http_clients.end());
  return dgraph_http_clients[name];
}

std::shared_ptr<http::DGraphClient> DGraphClientManger::createDGraphClient(
    const std::string &name, const dgraph::http::DGraphClientStub &clientstub) {
  std::vector<http::DGraphClientStub> clients;
  clients.push_back(clientstub);
  auto ptr = std::make_shared<http::DGraphClient>(clients);
  dgraph_http_clients[name] = ptr;
  return ptr;
}

std::shared_ptr<grpcclient::DgraphClient>
DGraphClientManger::getDGraphGrpcClient(const std::string &name) {
  assert(dgraph_grpc_clients.find(name) != dgraph_grpc_clients.end());
  return dgraph_grpc_clients[name];
}

std::shared_ptr<grpcclient::DgraphClient>
DGraphClientManger::createDGraphGrpcClient(const std::string &name,
                                           const std::string &host) {
  auto stub = api::Dgraph::NewStub(
      grpc::CreateChannel(host, grpc::InsecureChannelCredentials()));
  std::vector<std::unique_ptr<api::Dgraph::Stub>> clients;
  clients.push_back(std::move(stub));

  auto ptr = std::make_shared<dgraph::grpcclient::DgraphClient>(clients);
  dgraph_grpc_clients[name] = ptr;
  return ptr;
}

std::shared_ptr<orm::DGraphOrm> DGraphClientManger::getDGraphOrm(
    const std::string &name) {
  assert(dgraphorms.find(name) != dgraphorms.end());
  return dgraphorms[name];
}

std::shared_ptr<orm::DGraphOrm> DGraphClientManger::createDGraphOrm(
    const std::string &name, const std::string &client_name) {
  auto ptr = std::make_shared<orm::DGraphOrm>(client_name);
  dgraphorms[name] = ptr;
  return ptr;
}
}  // namespace dgraph
