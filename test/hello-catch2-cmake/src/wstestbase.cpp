#include "wstestbase.h"
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
        std::cout << "message: " << e.what() << '\n'
                  << "exception id: " << e.id << '\n'
                  << "byte position of error: " << e.byte << std::endl;
        throw ("Json can not be parsed");
    }
}
void WSTestBase::init()
{
    req->setPath("/echo");
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
//        std::cout << "new message:" << message << std::endl;
//        REQUIRE(message.empty() == true);
        if (type == WebSocketMessageType::Pong)
        {
            std::cout << "recv a pong" << std::endl;
            //if (!continually) { app().getLoop()->quit(); }
        }
    });
}
void WSTestBase::setConnectionClosedHandler()
{
    wsPtr->setConnectionClosedHandler([](
                           [[maybe_unused]] const WebSocketClientPtr &wsPtr) {
        std::cout << "ws closed!" << std::endl;
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
                                   //std::cout << "ws connected!" << std::endl;
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
void WSTestBase::ExitAfter5s()
{
    app().getLoop()->runAfter(5.0, []() {
        // if (!continually) { exit(1); }
        app().getLoop()->quit();
    });
}
void WSTestBase::quit(bool isPass, std::string reason)
{
    app().getLoop()->quit();
    testResult = isPass;
    if(!reason.empty()){
         std::cout << reason << std::endl;
    }
}
void WSTestBase::run() { app().run(); }
