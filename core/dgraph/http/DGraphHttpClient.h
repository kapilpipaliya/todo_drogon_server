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
class DGraphHttpClient {
 public:
  DGraphHttpClient();
  ~DGraphHttpClient();
  int version = 11;  // 1.1 is default

  std::string callAPICurl(std::string host, unsigned short port,
                          std::string target, boost::beast::http::verb method,
                          std::string body, std::string content_type,
                          std::map<std::string, std::string> headers);
  std::string callAPI(std::string host, int port, std::string target,
                      boost::beast::http::verb method, std::string body,
                      std::string content_type,
                      std::map<std::string, std::string> headers);
  void drogonHttpAPI(std::string host, int port, std::string target,
                     boost::beast::http::verb method, std::string body,
                     std::string content_type,
                     std::map<std::string, std::string> headers,
                     std::function<void(std::string)> callback);
};
}  // namespace dgraph
#endif
