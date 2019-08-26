#ifndef WSTESTBASE_H
#define WSTESTBASE_H

#include <drogon/WebSocketClient.h>
#include <drogon/HttpAppFramework.h>
#include <trantor/net/EventLoopThread.h>
#include "json.hpp"

using namespace drogon;
using namespace std::chrono_literals;

class WSTestBase
{
protected:
  bool continually = false;
  bool openResult = false;
  bool testResult = false;

  HttpRequestPtr req = HttpRequest::newHttpRequest();
  WebSocketClientPtr wsPtr =
            WebSocketClient::newWebSocketClient("127.0.0.1", 8300);

   virtual  void setMessageHandler();
    virtual void setConnectionClosedHandler();
    virtual void connectToServer();
    void ExitAfter(double seconds);
    void quit(bool isPass, std::string reason="");

public:
    void setpath(std::string path);
    void init();
    void run();
    WSTestBase();
    virtual ~WSTestBase();
    bool isOpenSuccess();
    bool isTestSuccess();

    nlohmann::json jsonparse(std::string msg);
};
#endif // WSTESTBASE_H
