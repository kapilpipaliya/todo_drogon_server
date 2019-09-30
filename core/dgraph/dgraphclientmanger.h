#ifndef DGRAPHCLIENTMANGER_H
#define DGRAPHCLIENTMANGER_H
#include <map>
#include <memory>

namespace dgraph {
class DgraphClient;
class DGraphClientStub;
class DGraphClientManger {
 public:
  static std::map<std::string, std::shared_ptr<DgraphClient>> dgraphconns;
  DGraphClientManger();
  static std::shared_ptr<DgraphClient> getDGraphClient(const std::string &name);
  static std::shared_ptr<DgraphClient> createDGraphClient(
      const std::string &name, const dgraph::DGraphClientStub &clientstub);
};
}  // namespace dgraph
#endif  // DGRAPHCLIENTMANGER_H
