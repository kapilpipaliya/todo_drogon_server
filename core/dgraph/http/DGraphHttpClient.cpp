
#include "DGraphHttpClient.h"

#include <stdio.h>
//#include <QNetworkRequest>
//#include <QNetworkAccessManager>
//#include <QUrl>
#include <future>
#include "Poco/Net/HTMLForm.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/StreamCopier.h"
#include "drogon/drogon.h"
namespace dgraph {

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

std::string DGraphHttpClient::callAPICurl(
    std::string host, unsigned short port, std::string target,
    http::verb method, std::string body, std::string content_type,
    std::map<std::string, std::string> headers) {
  /*
  QUrl myurl;
  myurl.setScheme("http");  // https also applicable
  myurl.setHost(QString::fromStdString(host));
  myurl.setPort(port);
  myurl.setPath(QString::fromStdString(path));
  myurl.setQuery(QString::fromStdString(query));

  QNetworkRequest request;
  request.setUrl(myurl);
  request.setHeader(QNetworkRequest::ContentTypeHeader,
                    QString::fromStdString(content_type));

  QNetworkAccessManager *restclient; //in class
  restclient = new QNetworkAccessManager(); //constructor
  QNetworkReply *reply = restclient->post(request,QString::fromStdString(body));
  */
  // https://gist.github.com/jeffcrouse/247717dcca0669090cfa
  Poco::Net::HTTPClientSession session(host, port);
  // s.setProxy("localhost", srv.port());
  Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_POST, target);
  request.setContentType(content_type);

  request.setContentLength(body.length());

  // sends request, returns open stream
  std::ostream& os = session.sendRequest(request);
  os << body;  // sends the body
  // req.write(LOG_DEBUG); // print out request

  Poco::Net::HTTPResponse response;
  std::istream& rs = session.receiveResponse(response);
  std::stringstream ss;
  Poco::StreamCopier::copyStream(rs, ss);

  return ss.str();
}

std::string DGraphHttpClient::callAPI(

    std::string host, int port, std::string target, http::verb method,
    std::string body, std::string content_type,
    std::map<std::string, std::string> headers) {
  // The io_context is required for all I/O
  boost::asio::io_context ioc;

  // These objects perform our I/O
  tcp::resolver resolver{ioc};
  tcp::socket socket{ioc};
  http::request<http::string_body> req{method, target, version};
  req.set(http::field::host, host + ":" + std::to_string(port));
  req.set(http::field::content_type, content_type);
  // Look up the domain name
  auto const results = resolver.resolve(host, std::to_string(port));

  // Make the connection on the IP address we get from a lookup
  boost::asio::connect(socket, results.begin(), results.end());

  req.body() = body;
  req.prepare_payload();

  // Send the HTTP request to the remote host
  http::write(socket, req);

  // This buffer is used for reading and must be persisted
  boost::beast::flat_buffer buffer;

  // Declare a container to hold the response
  // Vinnie:
  //    http::response<http::dynamic_body> res;
  //    Well it will return a dynamic_buffer. IF you want a string, use
  //    http::response<http::string_body>
  http::response<http::string_body> res;

  // Receive the HTTP response
  http::read(socket, buffer, res);

  // Write the message to standard out
  LOG_DEBUG << res.body();

  // Gracefully close the socket
  boost::system::error_code ec;
  socket.shutdown(tcp::socket::shutdown_both, ec);
  LOG_DEBUG << "shutting down";

  // not_connected happens sometimes
  // so don't bother reporting it.
  //
  if (ec && ec != boost::system::errc::not_connected)
    throw boost::system::system_error{ec};

  // If we get here then the connection is closed gracefully
  return res.body();
}

void DGraphHttpClient::drogonHttpAPI(
    std::string host, int port, std::string target, http::verb method,
    std::string body, std::string content_type,
    std::map<std::string, std::string> headers,
    std::function<void(std::string)> callback) {
  auto client = drogon::HttpClient::newHttpClient("http://" + host + ":" +
                                                  std::to_string(port));
  auto req = drogon::HttpRequest::newHttpRequest();
  req->setMethod(drogon::Post);
  req->setPath(target);
  // req->setParameter("wd", "weixin");
  req->setBody(body);
  req->setCustomContentTypeString(content_type);

  client->sendRequest(req, [callback](drogon::ReqResult result,
                                      const drogon::HttpResponsePtr& response) {
    switch (result) {
      case drogon::ReqResult::Ok:
        LOG_DEBUG << "receive response!";
        LOG_DEBUG << response->getBody();
        callback(response->getBody());
        break;
      case drogon::ReqResult::Timeout:
        LOG_DEBUG << "Cant make server request.";
        break;
      case drogon::ReqResult::BadResponse:
        LOG_DEBUG << "TimeOut.";
        break;
      case drogon::ReqResult::NetworkFailure:
        LOG_DEBUG << "NetWorkFailer.";
        break;
      case drogon::ReqResult::BadServerAddress:
        LOG_DEBUG << "Bad Server Address.";
        break;
    }
  });
}

}  // namespace dgraph
