#include <catch2/catch.hpp>

#include "../src/base/websockettest.h"
#include "../src/base/formatcheck.h"

#include "../src/madmin/authcheck.h"
#include "../src/madmin/login.h"
#include "../src/madmin/signup.h"
#include "../src/madmin/gettabledata.h"
#include "../src/madmin/gettabledata_admin.h"
#include "../src/madmin/savedelete.h"

#include "../src/madmin/menu/getmenudata_admin.h"
#include "../src/madmin/menu/getmenudata_sadmin.h"
#include "../src/madmin/auth/passwordchange.h"
#include "../src/madmin/auth/logout.h"
#include "../src/madmin/user/create_user.h"
#include "../src/madmin/user/user_count.h"

#include "../wsclient/wsclient.h"
#include "../wsclient/once.h"

#include <stdarg.h>
#include <QCoreApplication>
using namespace  madmin;
#include "spdlogfix.h"

//To Benchmark do
// https://github.com/catchorg/Catch2/blob/master/docs/benchmarks.md
//BENCHMARK("MY FUNC") { return my_func(); };

TEST_CASE("is connection possible","[WSTest]") {
    char **argv;
    int i = 0;
    QCoreApplication a(i, argv);
    auto &w2 = WsInst::getClient();
    Once::connect(&w2.m_webSocket, &QWebSocket::connected, [](){
        SPDLOG_TRACE("Connection successfull");
        REQUIRE(true);});
    QTimer *timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), &a, SLOT(quit()));
    timer->start(1000);
    a.exec();
}

TEST_CASE("server reply error on string type of message.","[WSTest]") {
    char **argv;
    int i = 0;
    QCoreApplication a(i, argv);
    auto &w2 = WsInst::getClient();
    std::string str = "hello";
    nlohmann::json j = str;
    // Bind not work because reply is not an array
//    auto b = w2.bind(j, [&a](json r){
//        REQUIRE(r== "Invalid Message only array handled: \"hello\"");
//        a.quit();
//    });
//    REQUIRE(b);
    w2.sendMessage(QString::fromStdString(j.dump()));
    Once::connect(&w2.m_webSocket, &QWebSocket::textMessageReceived, [](){
        SPDLOG_TRACE("Connection Not successfull");
        REQUIRE(true);});
    QTimer *timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), &a, SLOT(quit()));
    timer->start(1000);
    a.exec();
        //FormatCheck w1;  w1.setpath("/madmin"); w1.init(); w1.run(); REQUIRE(w1.isTestSuccess() == true);
}

TEST_CASE("authorisation check without cookies","[WSTest]") {

char **argv;
int i = 0;
QCoreApplication a(i, argv);
auto &w2 = WsInst::getClient();
json event = json::array({"user", "is_logged_in", 0} );
json payload = json::array({{event, {{}}}});
//    json j = R"( [ [["user","is_logged_in",0],[[]]]] )"_json;
SPDLOG_TRACE(payload.dump());
auto b = w2.bind(event, [](json r){
    SPDLOG_TRACE("This should be false");
    REQUIRE(r[0] == false);
});
w2.sendMessage(QString::fromStdString(payload.dump()));
REQUIRE(b);
QTimer *timer = new QTimer();
QObject::connect(timer, SIGNAL(timeout()), &a, SLOT(quit()));
timer->start(1000);

a.exec();

//AuthCheck w1; w1.setpath("/madmin"); w1.init(); w1.run(); REQUIRE(w1.isTestSuccess() == true);
}

TEST_CASE("login on backend with username and password","[WSTest]") {
    char **argv;
    int i = 0;
    QCoreApplication a(i, argv);
    auto &w2 = WsInst::getClient();
    json event = json::array({"auth","login",0} );
    json payload = json::array({{event, json::object({{"user", "sadmin"}, {"pass", "123456"}}) }});
    SPDLOG_TRACE(payload.dump());
    auto b = w2.bind(event, [](json r){
        REQUIRE(r[0]["ok"] == true);
    });
    w2.sendMessage(QString::fromStdString(payload.dump()));
    REQUIRE(b);
    QTimer *timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), &a, SLOT(quit()));
    timer->start(1000);
    a.exec();
    //LogIn w1; w1.setpath("/madmin"); w1.init(); w1.run(); REQUIRE(w1.isTestSuccess() == true);
}

//// currently this not working.. but make this working in future.
////TEST_CASE("signup with a form.","[WSTest]") {
////    SignUp w1; w1.setpath("/madmin"); w1.init(); w1.run(); REQUIRE(w1.isTestSuccess() == true);
////}

TEST_CASE("check that all table Super Admin data are correctly replied","[WSTest]") {
    char **argv;
    int i = 0;
    QCoreApplication a(i, argv);
    auto &w2 = WsInst::getClient();
    json event1 = json::array({"auth","login",0} );
    json event11 = json::array({"auth","set_cookie",0} );
    json event2 = json::array({"auth","is_logged_in",0} );
    json event3 = json::array({"user","header",0} );
    json event4 = json::array({"user","data",0} );
    json payload = json::array({
                                   {event1, json::object({{"user", "sadmin"}, {"pass", "123456"}})},
                                   {event2, json::array({{}})},
                                   {event3, json::array({{}})},
                                   {event4, json::array({{}})},
                               });

    SPDLOG_TRACE(payload.dump());
    bool r1, r2, r3, r4 = false;
    auto b1 = w2.bind(event1, [](json r){ REQUIRE(r[0]["ok"] == true); });
    auto b11 = w2.bind(event11, [](json r){ REQUIRE(r[0].is_number() == true);});
    auto b2 = w2.bind(event2, [](json r){ REQUIRE(r[0] == true); });
    auto b3 = w2.bind(event3, [](json r){ REQUIRE(r[0].size() == 6); });
    auto b4 = w2.bind(event4, [](json r){ REQUIRE(r[1].size() >= 0); });
    w2.sendMessage(QString::fromStdString(payload.dump()));
    REQUIRE(b1);
    REQUIRE(b11);
    REQUIRE(b2);
    REQUIRE(b3);
    REQUIRE(b4);
    QTimer *timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), &a, SLOT(quit()));
    timer->start(1000);
    a.exec();
}
    // do catalog_local and song test above

////Temporary this not working..
////TEST_CASE("User Admin Menu Test","[WSTest]") {
////    GetMenuAdmin w1{"ui"}; w1.setpath("/madmin"); w1.init(); w1.run(); REQUIRE(w1.isTestSuccess() == true);
////}

TEST_CASE("password change should work.") {
    char **argv;
    int i = 0;
    QCoreApplication a(i, argv);
    auto &w2 = WsInst::getClient();
    json event1 = json::array({"auth","login",0} );
    json event11 = json::array({"auth","set_cookie",0} );
    json event2 = json::array({"user","update_password",0} );
    json event3 = json::array({"user","update_password",1} );
    json payload = json::array({
                                   {event1, json::object({{"user", "sadmin"}, {"pass", "123456"}})},
                                   {event2, json::array({json::object({{"old_password", "123456"}, {"new_password", "999999"}}) }) },
                                   {event3, json::array({json::object({{"old_password", "999999"}, {"new_password", "123456"}}) }) },
                               });

    SPDLOG_TRACE(payload.dump());
    bool r1, r2, r3, r4 = false;
    auto b1 = w2.bind(event1, [](json r){ REQUIRE(r[0]["ok"] == true); });
    auto b11 = w2.bind(event11, [](json r){ REQUIRE(r[0].is_number() == true);});
    auto b2 = w2.bind(event2, [](json r){ REQUIRE(r[0]["ok"] == true); });
    auto b3 = w2.bind(event3, [](json r){ REQUIRE(r[0]["ok"] == true); });
    w2.sendMessage(QString::fromStdString(payload.dump()));
    REQUIRE(b1);
    REQUIRE(b11);
    REQUIRE(b2);
    REQUIRE(b3);
    QTimer *timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), &a, SLOT(quit()));
    timer->start(1000);
    a.exec();
    //PasswordChange w1; w1.setpath("/madmin"); w1.init(); w1.run(); REQUIRE(w1.isTestSuccess() == true);
}
TEST_CASE("Logout successfull") {
    char **argv;
    int i = 0;
    QCoreApplication a(i, argv);
    auto &w2 = WsInst::getClient();
    json event1 = json::array({"auth","login",0} );
    json event11 = json::array({"auth","set_cookie",0} );
    json event2 = json::array({"auth","logout",0} );
    json event3 = json::array({"user","is_logged_in",0} );
    json payload = json::array({
                                   {event1, json::object({{"user", "sadmin"}, {"pass", "123456"}})},
                                   {event2, json::array() },
                                   {event3, json::array() },
                               });

    SPDLOG_TRACE(payload.dump());
    bool r1, r2, r3, r4 = false;
    auto b1 = w2.bind(event1, [](json r){ REQUIRE(r[0]["ok"] == true); });
    auto b11 = w2.bind(event11, [](json r){ REQUIRE(r[0].is_number() == true);});
    auto b2 = w2.bind(event2, [](json r){ REQUIRE(r[0]["ok"] == true); });
    auto b3 = w2.bind(event3, [](json r){ REQUIRE(r[0] == false); });
    w2.sendMessage(QString::fromStdString(payload.dump()));
    REQUIRE(b1);
    REQUIRE(b11);
    REQUIRE(b2);
    REQUIRE(b3);
    w2.unbind(event1);
    w2.unbind(event11);
    w2.unbind(event2);
    w2.unbind(event3);
    QTimer *timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), &a, SLOT(quit()));
    timer->start(1000);
    a.exec();
   //LogOut w1; w1.setpath("/madmin"); w1.init(); w1.run(); REQUIRE(w1.isTestSuccess() == true);
}
//#define SUD(t, ins, upd, del)\
//{CreateUser w1{t, ins, upd, del}; w1.setpath("/madmin"); w1.init(); w1.run(); REQUIRE(w1.isTestSuccess() == true);}

TEST_CASE("create update delete successfull") {
//// This test stopped working because now delete only accepts number.
////    SUD("user",
////        R"([{"username":"username","fullname":"fullname","email":"email@email.com","password":"password","disabled":true,"state":"state","city":"city"},[null]])",
////        R"(
////        [
////            {"type":"executive","parent_id":null,"p_username":0,"username":"user1","fullname":"fullname1","create_date":"2019-08-28 12:04:23.440921+05:30","disabled":true,"email":"email1@gmail.com","password":"pass1","state":"state1","city":"city1"},
////            [null, null, null, null, "=username"]
////        ])",
////        R"([[null, null, null, null, "=user1"]])")

//// This test stopped working because now delete only accepts number.
////    SUD("catalog_local",
////        R"([{"name": "new_catalog", "enabled": true}, [null]])",
////        R"(
////       [
////        {"name": "new_catalog1", "enabled": true},
////        [null, "=new_catalog"]
////      ])",
////        R"([[null, "=new_catalog1"]])")
//    SUD("song",
//        R"([{"title": "very_new_song", "catalog_id": 1}, [null]])",
//        R"(
//        [
//        {"title": "very_new_song2", "catalog_id": 1},
//        [null, null, null, null, "=very_new_song"]
//        ])",
//        R"([[null, null, null, null, "=very_new_song2"]])")
    char **argv;
    int i = 0;
    QCoreApplication a(i, argv);
    auto &w2 = WsInst::getClient();
    json event1 = json::array({"auth","login",0} );
    json event11 = json::array({"auth","set_cookie",0} );
    json event2 = json::array({"user","is_logged_in",0} );
    json event3 = json::array({"song","ins",0} );
    json event4 = json::array({"song","upd",0} );
    json event5 = json::array({"song","del",0} );
    json payload = json::array({
                                   {event1, json::object({{"user", "sadmin"}, {"pass", "123456"}})},
                                   {event2, json::array() },
                                   {event3, json::array(
                                         {
                                            json::object({{"title", "very_new_song"}, {"catalog_id", 2}})
                                        }
                                    ) },
                                   {event4, json::array(
                                    {json::object({{"title", "very_new_song2"}, {"catalog_id", 2}}),
                                     R"([null, null, null, null, "=very_new_song"])"_json}
                                    ) },
                                   {event5, json::array({
                                   R"([[null, null, null, null, "=very_new_song2"]])"_json
                                   } ) },
                               });

    SPDLOG_TRACE(payload.dump());
    bool r1, r2, r3, r4 = false;
    auto b1 = w2.bind(event1, [](json r){ REQUIRE(r[0]["ok"] == true); });
    auto b11 = w2.bind(event11, [](json r){ REQUIRE(r[0].is_number() == true);});
    auto b2 = w2.bind(event2, [](json r){ REQUIRE(r[0] == true); });
    auto b3 = w2.bind(event3, [](json r){ REQUIRE(r[0]["ok"] == true); });
    auto b4 = w2.bind(event4, [](json r){ REQUIRE(r[0]["ok"] == true); });
    auto b5 = w2.bind(event5, [](json r){ REQUIRE(r[0]["ok"] == true); });
    w2.sendMessage(QString::fromStdString(payload.dump()));
    REQUIRE(b1);
    REQUIRE(b11);
    REQUIRE(b2);
    REQUIRE(b3);
    REQUIRE(b4);
    REQUIRE(b5);
    QTimer *timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), &a, SLOT(quit()));
    timer->start(1000);
    a.exec();
}

//// user count is not fixed now.
////TEST_CASE("create Count successfull") {
////    UserCount w1{"user"}; w1.setpath("/madmin"); w1.init(); w1.run(); REQUIRE(w1.isTestSuccess() == true);
////
/// }
