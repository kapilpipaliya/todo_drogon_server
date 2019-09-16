#include "wstestbase.h"
#include <fmt/format.h>
#include <catch2/catch.hpp>
#include <iostream>

namespace wstest{
WSTestBase::WSTestBase() { /*init();*/
}  // should be called after derived class
WSTestBase::~WSTestBase() {}
bool WSTestBase::isOpenSuccess() { return openResult; }
bool WSTestBase::isTestSuccess() { return testResult; }

nlohmann::json WSTestBase::jsonparse(std::string msg) {
  try {
    auto j = nlohmann::json::parse(msg);
    return j;
  } catch (nlohmann::json::parse_error &e) {
    LOG_DEBUG << "message: {}", e.what();
    LOG_DEBUG << "exception id: {}", e.id;
    LOG_DEBUG << "byte position of error:", e.byte;
    throw std::runtime_error("Json can not be parsed");
  }
}

void WSTestBase::setpath(std::string path) { req->setPath(path); }
void WSTestBase::init() {
  setMessageHandler();
  setConnectionClosedHandler();
  connectToServer();
  // ExitAfter5s();
  // run();
}
void WSTestBase::setMessageHandler() {
  wsPtr->setMessageHandler(
      []([[maybe_unused]] const std::string &message,
         [[maybe_unused]] const drogon::WebSocketClientPtr &wsPtr,
         const drogon::WebSocketMessageType &type) {
        //        LOG_DEBUG << "new message: {}", message;
        //        REQUIRE(message.empty() == true);
        if (type == drogon::WebSocketMessageType::Pong) {
          LOG_DEBUG << "recv a pong";
          // if (!continually) { app().getLoop()->quit(); }
        }
      });
}
void WSTestBase::setConnectionClosedHandler() {
  wsPtr->setConnectionClosedHandler(
      []([[maybe_unused]] const drogon::WebSocketClientPtr &wsPtr) {
        LOG_DEBUG << "ws closed!";
      });
}
void WSTestBase::connectToServer() {
  //    req->addCookie("", "");
  wsPtr->connectToServer(
      req, [this](drogon::ReqResult r,
                  [[maybe_unused]] const drogon::HttpResponsePtr &resp,
                  [[maybe_unused]] const drogon::WebSocketClientPtr &wsPtr) {
        if (r == drogon::ReqResult::Ok) {
          // LOG_DEBUG << "ws connected!";
          // wsPtr->getConnection()->setPingMessage("", 2s);
          // wsPtr->getConnection()->send("hello!");
        } else {
          // if (!continually) { exit(1); } this crash the test.
          quit(false, "ws connection failed");
        }
      });
}
void WSTestBase::ExitAfter(double seconds = 5) {
  drogon::app().getLoop()->runAfter(seconds, []() {
    // if (!continually) { exit(1); }
    drogon::app().getLoop()->quit();
  });
}
void WSTestBase::quit(bool isPass, std::string reason) {
  drogon::app().getLoop()->quit();
  // if(app().isRunning()){ app().quit(); }
  testResult = isPass;
  if (!reason.empty()) {
    LOG_DEBUG << reason;
  }
}

void WSTestBase::run() { drogon::app().run(); }
}
