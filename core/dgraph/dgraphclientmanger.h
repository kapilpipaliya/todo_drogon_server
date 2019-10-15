#ifndef DGRAPHCLIENTMANGER_H
#define DGRAPHCLIENTMANGER_H
#include <map>
#include <memory>

namespace dgraph {
namespace orm {
class DGraphOrm;
}
namespace http {
class DGraphClient;
class DGraphClientStub;
}  // namespace http
namespace grpcclient {
class DgraphClient;
}

class DGraphClientManger {
 public:
  static std::map<std::string, std::shared_ptr<http::DGraphClient>>
      dgraph_http_clients;
  static std::map<std::string, std::shared_ptr<grpcclient::DgraphClient>>
      dgraph_grpc_clients;
  static std::map<std::string, std::shared_ptr<orm::DGraphOrm>> dgraphorms;

  DGraphClientManger();
  static std::shared_ptr<http::DGraphClient> getDGraphClient(
      const std::string &name);
  static std::shared_ptr<http::DGraphClient> createDGraphClient(
      const std::string &name,
      const dgraph::http::DGraphClientStub &clientstub);

  static std::shared_ptr<grpcclient::DgraphClient> getDGraphGrpcClient(
      const std::string &name);
  static std::shared_ptr<grpcclient::DgraphClient> createDGraphGrpcClient(
      const std::string &name, const std::string &host);

  static std::shared_ptr<orm::DGraphOrm> getDGraphOrm(const std::string &name);
  static std::shared_ptr<orm::DGraphOrm> createDGraphOrm(
      const std::string &name, const std::string &client_name);
};

}  // namespace dgraph
#endif  // DGRAPHCLIENTMANGER_H
