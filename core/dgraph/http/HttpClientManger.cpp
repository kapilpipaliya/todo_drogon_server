
#include "HttpClientManger.h"
#include <cassert>
#include <string>
#include "DGraphHttpClient.h"
namespace dgraph {

std::map<std::string, std::shared_ptr<DGraphHttpClient>>
    HttpClientManager::conns = {};
HttpClientManager::HttpClientManager() {  // conns = {};
}

std::shared_ptr<DGraphHttpClient> HttpClientManager::getClient(
    const std::string &name) {
  assert(conns.find(name) != conns.end());
  return conns[name];
}

void HttpClientManager::createClient(const std::string &name,
                                     const std::string &host,
                                     const std::string &port,
                                     const std::string &target) {
  auto ptr = std::make_shared<DGraphHttpClient>();
  conns[name] = ptr;
}

}  // namespace dgraph
