#ifndef _DGRAPHHTTPCLIENT_H
#define _DGRAPHHTTPCLIENT_H
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <string>

using tcp = boost::asio::ip::tcp;     // from <boost/asio/ip/tcp.hpp>
namespace http = boost::beast::http;  // from <boost/beast/http.hpp>

enum path { alter, query, mutation };

namespace dgraph {
namespace http {
class DGraphHttpClient {
 public:
  DGraphHttpClient();
  ~DGraphHttpClient();
  int version = 11;  // 1.1 is default

  void drogonHttpAPI(std::string host, int port, std::string target,
                     const std::string &method, std::string body,
                     std::string content_type,
                     std::map<std::string, std::string> headers,
                     std::function<void(std::string)> callback);
};
}  // namespace dgraph
}
#endif
