#ifndef WSTESTBASE_H
#define WSTESTBASE_H

#include <drogon/HttpAppFramework.h>
#include <drogon/WebSocketClient.h>
#include <trantor/net/EventLoopThread.h>


// using namespace std::chrono_literals;
namespace wstest{
class WSTestBase {
 public:
  WSTestBase();
  virtual ~WSTestBase();
  void setpath(std::string path);
  void init();
  void run();
  bool isOpenSuccess();
  bool isTestSuccess();

  nlohmann::json jsonparse(std::string msg);

 protected:
  bool continually = false;
  bool openResult = false;
  bool testResult = false;

  virtual void setMessageHandler();
  virtual void setConnectionClosedHandler();
  virtual void connectToServer();
  void ExitAfter(double seconds);
  void quit(bool isPass, std::string reason = "");
  auto getWsPtr() { return wsPtr; }
  auto getReqPtr() { return req; }

 private:
  drogon::HttpRequestPtr req = drogon::HttpRequest::newHttpRequest();
  drogon::WebSocketClientPtr wsPtr =
      drogon::WebSocketClient::newWebSocketClient("127.0.0.1", 8400);
};
}
#endif  // WSTESTBASE_H
