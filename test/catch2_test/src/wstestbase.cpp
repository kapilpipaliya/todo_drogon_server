#include "wstestbase.h"
#include "spdlog/spdlog.h"
#include <iostream>
#include <catch2/catch.hpp>
#include <fmt/format.h>

WSTestBase::WSTestBase() { /*init();*/ } // should be called after derived class
WSTestBase::~WSTestBase() {  }
bool WSTestBase::isOpenSuccess() { return openResult; }
bool WSTestBase::isTestSuccess() { return testResult; }

nlohmann::json WSTestBase::jsonparse(std::string msg)
{
    try
    {
        auto j =nlohmann::json::parse(msg);
        return j;
    }
    catch (nlohmann::json::parse_error& e)
    {
        spdlog::error("message: {}", e.what());
        spdlog::error("exception id: {}", e.id);
        spdlog::error("byte position of error:", e.byte);
        throw ("Json can not be parsed");
    }
}

void WSTestBase::setpath(std::string path)
{
    req->setPath(path);
}
void WSTestBase::init()
{
    setMessageHandler();
    setConnectionClosedHandler();
    connectToServer();
    //ExitAfter5s();
    //run();
}
void WSTestBase::setMessageHandler()
{
    wsPtr->setMessageHandler([]( [[maybe_unused]]const std::string &message,
                             [[maybe_unused]] const WebSocketClientPtr &wsPtr,
                                           const WebSocketMessageType &type) {
//        spdlog::info("new message: {}", message);
//        REQUIRE(message.empty() == true);
        if (type == WebSocketMessageType::Pong)
        {
            spdlog::info("recv a pong");
            //if (!continually) { app().getLoop()->quit(); }
        }
    });
}
void WSTestBase::setConnectionClosedHandler()
{
    wsPtr->setConnectionClosedHandler([](
                           [[maybe_unused]] const WebSocketClientPtr &wsPtr) {
        spdlog::info("ws closed!");
    });
}
void WSTestBase::connectToServer()
{
//    req->addCookie("", "");
    wsPtr->connectToServer(req,
                           [this](ReqResult r,
                            [[maybe_unused]] const HttpResponsePtr &resp,
                                       [[maybe_unused]] const WebSocketClientPtr &wsPtr) {
                               if (r == ReqResult::Ok)
                               {
                                   //spdlog::info("ws connected!");
                                   //wsPtr->getConnection()->setPingMessage("", 2s);
                                   //wsPtr->getConnection()->send("hello!");
                               }
                               else
                               {
                                   //if (!continually) { exit(1); } this crash the test.
                                   quit(false, "ws connection failed");
                               }
                           });
}
void WSTestBase::ExitAfter(double seconds=5)
{
    app().getLoop()->runAfter(seconds, []() {
        // if (!continually) { exit(1); }
        app().getLoop()->quit();
    });
}
void WSTestBase::quit(bool isPass, std::string reason)
{
   app().getLoop()->quit();
   // if(app().isRunning()){ app().quit(); }
    testResult = isPass;
    if(!reason.empty()){
         spdlog::info(reason);
    }
}

void WSTestBase::run() { app().run(); }
