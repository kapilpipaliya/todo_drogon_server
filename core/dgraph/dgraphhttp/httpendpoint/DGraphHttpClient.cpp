
#include "DGraphHttpClient.h"

#include <stdio.h>
//#include <QNetworkRequest>
//#include <QNetworkAccessManager>
//#include <QUrl>
#include <future>
/*#include "Poco/Net/HTMLForm.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/StreamCopier.h"*/

namespace dgraph {
namespace http {
DGraphHttpClient::DGraphHttpClient() {
  // Set up an HTTP GET request message
  /*
  req_alter =
      http::request<http::string_body>{http::verb::post, target_alter, version};
  req_query =
      http::request<http::string_body>{http::verb::post, target_query, version};
  req_mutation = http::request<http::string_body>{http::verb::post,
                                                  target_mutation, version};
  req_alter.set(http::field::host, host + ":" + port);
  req_query.set(http::field::host, host + ":" + port);
  req_mutation.set(http::field::host, host + ":" + port);
  req_query.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
  req_query.set(http::field::content_type, "application/graphql+-");
  req_mutation.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
  req_mutation.set(http::field::content_type, "application/rdf");
  //  req_mutation.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
  //  req_alter.set(http::field::content_type, "application/graphql+-");
*/
}

DGraphHttpClient::~DGraphHttpClient() {}

void DGraphHttpClient::drogonHttpAPI(
    std::string host, int port, std::string target, const std::string& method,
    std::string body, std::string content_type,
    std::map<std::string, std::string> headers,
    std::function<void(std::string)> callback) {
  /*
  auto client = drogon::HttpClient::newHttpClient("http://" + host + ":" +
                                                  std::to_string(port));
  auto req = drogon::HttpRequest::newHttpRequest();
  req->setMethod(drogon::Post);
  req->setPath(target);
  // req->setParameter("wd", "weixin");
  req->setBody(body);
  if (!content_type.empty()) {
    req->setCustomContentTypeString("content-type: " + content_type + "\r\n");
  }
  // std::cout << host << port << target << body << content_type << std::endl;

  client->sendRequest(req, [callback](drogon::ReqResult result,
                                      const drogon::HttpResponsePtr& response) {
    switch (result) {
      case drogon::ReqResult::Ok:
        std::cout << "receive response!" << std::endl;
        std::cout << response->getBody() << std::endl;
        callback(response->getBody());
        break;
      case drogon::ReqResult::Timeout:
        std::cout << "Cant make server request." << std::endl;
        break;
      case drogon::ReqResult::BadResponse:
        std::cout << "TimeOut." << std::endl;
        break;
      case drogon::ReqResult::NetworkFailure:
        std::cout << "NetWorkFailer." << std::endl;
        break;
      case drogon::ReqResult::BadServerAddress:
        std::cout << "Bad Server Address." << std::endl;
        break;
    }
  });
  */
}
}  // namespace http
}  // namespace dgraph
