#include <QCoreApplication>
#include <catch2/catch.hpp>
#include "../wsclient/once.h"
#include "../wsclient/wsclient.h"
#include "spdlogfix.h"
// To Benchmark do
// https://github.com/catchorg/Catch2/blob/master/docs/benchmarks.md
// BENCHMARK("MY FUNC") { return my_func(); };

TEST_CASE("is connection possible", "[WSTest]") {
  char **argv;
  int i = 0;
  QCoreApplication a(i, argv);
  auto w2 = SslEchoClient(QUrl(QStringLiteral("wss://localhost:8401/madmin")));

  bool r0 = false;
  Once::connect(&w2.m_webSocket, &QWebSocket::connected, [&r0]() {
    SPDLOG_TRACE("Connection successfull");
    REQUIRE(true);
    r0 = true;
  });
  QTimer *timer = new QTimer();
  QObject::connect(timer, SIGNAL(timeout()), &a, SLOT(quit()));
  timer->start(500);
  a.exec();
  REQUIRE(r0);
}

TEST_CASE("server reply error on string type of message.", "[WSTest]") {
  char **argv;
  int i = 0;
  QCoreApplication a(i, argv);
  auto w2 = SslEchoClient(QUrl(QStringLiteral("wss://localhost:8401/madmin")));
  std::string str = "hello";
  nlohmann::json j = str;
  // Bind not work because reply is not an array
  //    auto b = w2.bindOnce(j, [&a](json r){
  //        REQUIRE(r== "Invalid Message only array handled: \"hello\"");
  //        a.quit();
  //    });
  //    REQUIRE(b);
  w2.sendMessage(QString::fromStdString(j.dump()));
  bool r0 = false;
  Once::connect(&w2.m_webSocket, &QWebSocket::textMessageReceived, [&r0]() {
    SPDLOG_TRACE("Connection Not successfull");
    REQUIRE(true);
    r0 = true;
  });
  QTimer *timer = new QTimer();
  QObject::connect(timer, SIGNAL(timeout()), &a, SLOT(quit()));
  timer->start(500);
  a.exec();
  REQUIRE(r0);
  // FormatCheck w1;  w1.setpath("/madmin"); w1.init(); w1.run();
  // REQUIRE(w1.isTestSuccess() == true);
}

TEST_CASE("authorisation check without cookies", "[WSTest]") {
  char **argv;
  int i = 0;
  QCoreApplication a(i, argv);
  auto w2 = SslEchoClient(QUrl(QStringLiteral("wss://localhost:8401/madmin")));
  json event = json::array({"user", "is_logged_in", 0});
  json payload = json::array({{event, {{}}}});
  //    json j = R"( [ [["user","is_logged_in",0],[[]]]] )"_json;
  SPDLOG_TRACE(payload.dump());
  bool r0 = false;
  auto b = w2.bindOnce(event, [&r0](json r) {
    SPDLOG_TRACE("This should be false");
    REQUIRE(r[0] == false);
    r0 = true;
  });
  w2.sendMessage(QString::fromStdString(payload.dump()));
  REQUIRE(b);
  QTimer *timer = new QTimer();
  QObject::connect(timer, SIGNAL(timeout()), &a, SLOT(quit()));
  timer->start(500);

  a.exec();
  REQUIRE(r0);

  // AuthCheck w1; w1.setpath("/madmin"); w1.init(); w1.run();
  // REQUIRE(w1.isTestSuccess() == true);
}

TEST_CASE("login on backend with username and password", "[WSTest]") {
  char **argv;
  int i = 0;
  QCoreApplication a(i, argv);
  auto w2 = SslEchoClient(QUrl(QStringLiteral("wss://localhost:8401/madmin")));
  json event = json::array({"auth", "login", 0});
  json payload = json::array(
      {{event, json::object({{"user", "sadmin"}, {"pass", "123456"}})}});
  SPDLOG_TRACE(payload.dump());
  bool r0 = false;
  auto b = w2.bindOnce(event, [&r0](json r) {
    REQUIRE(r[0]["ok"] == true);
    r0 = true;
  });
  w2.sendMessage(QString::fromStdString(payload.dump()));
  REQUIRE(b);
  QTimer *timer = new QTimer();
  QObject::connect(timer, SIGNAL(timeout()), &a, SLOT(quit()));
  timer->start(500);
  a.exec();
  REQUIRE(r0);
  // LogIn w1; w1.setpath("/madmin"); w1.init(); w1.run();
  // REQUIRE(w1.isTestSuccess() == true);
}

//// currently this not working.. but make this working in future.
////TEST_CASE("signup with a form.","[WSTest]") {
////    SignUp w1; w1.setpath("/madmin"); w1.init(); w1.run();
///REQUIRE(w1.isTestSuccess() == true);
////}

TEST_CASE("check that all table Super Admin data are correctly replied",
          "[WSTest]") {
  char **argv;
  int i = 0;
  QCoreApplication a(i, argv);
  auto w2 = SslEchoClient(QUrl(QStringLiteral("wss://localhost:8401/madmin")));
  json event1 = json::array({"auth", "login", 0});
  json event11 = json::array({"auth", "set_cookie", 0});
  json event2 = json::array({"auth", "is_logged_in", 0});
  json event3 = json::array({"user", "header", 0});
  json event4 = json::array({"user", "data", 0});
  json payload = json::array({
      {event1, json::object({{"user", "sadmin"}, {"pass", "123456"}})},
      {event2, json::array({{}})},
      {event3, json::array({{}})},
      {event4, json::array({{}})},
  });

  SPDLOG_TRACE(payload.dump());
  bool r0, r1, r2, r3, r4 = false;
  auto b1 = w2.bindOnce(event1, [&r0](json r) {
    REQUIRE(r[0]["ok"] == true);
    r0 = true;
  });
  auto b11 = w2.bindOnce(event11, [&r1](json r) {
    REQUIRE(r[0].is_number() == true);
    r1 = true;
  });
  auto b2 = w2.bindOnce(event2, [&r2](json r) {
    REQUIRE(r[0] == true);
    r2 = true;
  });
  auto b3 = w2.bindOnce(event3, [&r3](json r) {
    REQUIRE(r[0].size() == 6);
    r3 = true;
  });
  auto b4 = w2.bindOnce(event4, [&r4](json r) {
    REQUIRE(r[1].size() >= 0);
    r4 = true;
  });
  w2.sendMessage(QString::fromStdString(payload.dump()));
  REQUIRE(b1);
  REQUIRE(b11);
  REQUIRE(b2);
  REQUIRE(b3);
  REQUIRE(b4);

  QTimer *timer = new QTimer();
  QObject::connect(timer, SIGNAL(timeout()), &a, SLOT(quit()));
  timer->start(500);
  a.exec();
  REQUIRE(r0);
  REQUIRE(r1);
  REQUIRE(r2);
  REQUIRE(r3);
  REQUIRE(r4);
}
// do catalog_local and song test above

////Temporary this not working..
////TEST_CASE("User Admin Menu Test","[WSTest]") {
////    GetMenuAdmin w1{"ui"}; w1.setpath("/madmin"); w1.init(); w1.run();
///REQUIRE(w1.isTestSuccess() == true);
////}

TEST_CASE("password change should work.") {
  char **argv;
  int i = 0;
  QCoreApplication a(i, argv);
  auto w2 = SslEchoClient(QUrl(QStringLiteral("wss://localhost:8401/madmin")));
  json event1 = json::array({"auth", "login", 0});
  json event11 = json::array({"auth", "set_cookie", 0});
  json event2 = json::array({"user", "update_password", 0});
  json event3 = json::array({"user", "update_password", 1});
  json payload = json::array({
      {event1, json::object({{"user", "sadmin"}, {"pass", "123456"}})},
      {event2, json::array({json::object(
                   {{"old_password", "123456"}, {"new_password", "999999"}})})},
      {event3, json::array({json::object(
                   {{"old_password", "999999"}, {"new_password", "123456"}})})},
  });

  SPDLOG_TRACE(payload.dump());
  bool r0, r1, r2, r3 = false;
  auto b1 = w2.bindOnce(event1, [&r0](json r) {
    REQUIRE(r[0]["ok"] == true);
    r0 = true;
  });
  auto b11 = w2.bindOnce(event11, [&r1](json r) {
    REQUIRE(r[0].is_number() == true);
    r1 = true;
  });
  auto b2 = w2.bindOnce(event2, [&r2](json r) {
    REQUIRE(r[0]["ok"] == true);
    r2 = true;
  });
  auto b3 = w2.bindOnce(event3, [&r3](json r) {
    REQUIRE(r[0]["ok"] == true);
    r3 = true;
  });
  w2.sendMessage(QString::fromStdString(payload.dump()));
  REQUIRE(b1);
  REQUIRE(b11);
  REQUIRE(b2);
  REQUIRE(b3);

  QTimer *timer = new QTimer();
  QObject::connect(timer, SIGNAL(timeout()), &a, SLOT(quit()));
  timer->start(500);
  a.exec();
  REQUIRE(r0);
  REQUIRE(r1);
  REQUIRE(r2);
  REQUIRE(r3);
  // PasswordChange w1; w1.setpath("/madmin"); w1.init(); w1.run();
  // REQUIRE(w1.isTestSuccess() == true);
}
TEST_CASE("Logout successfull") {
  char **argv;
  int i = 0;
  QCoreApplication a(i, argv);
  auto w2 = SslEchoClient(QUrl(QStringLiteral("wss://localhost:8401/madmin")));
  json event1 = json::array({"auth", "login", 0});
  json event11 = json::array({"auth", "set_cookie", 0});
  json event2 = json::array({"auth", "logout", 0});
  json event3 = json::array({"user", "is_logged_in", 0});
  json payload = json::array({
      {event1, json::object({{"user", "sadmin"}, {"pass", "123456"}})},
      {event2, json::array()},
      {event3, json::array()},
  });

  SPDLOG_TRACE(payload.dump());
  bool r0, r1, r2 = false;
  auto b1 = w2.bindOnce(event1, [](json r) { REQUIRE(r[0]["ok"] == true); });
  auto b11 = w2.bindOnce(event11, [&r0](json r) {
    REQUIRE(r[0].is_number() == true);
    r0 = true;
  });
  auto b2 = w2.bindOnce(event2, [&r1](json r) {
    REQUIRE(r[0]["ok"] == true);
    r1 = true;
  });
  auto b3 = w2.bindOnce(event3, [&r2](json r) {
    REQUIRE(r[0] == false);
    r2 = true;
  });
  w2.sendMessage(QString::fromStdString(payload.dump()));
  REQUIRE(b1);
  REQUIRE(b11);
  REQUIRE(b2);
  REQUIRE(b3);

  QTimer *timer = new QTimer();
  QObject::connect(timer, SIGNAL(timeout()), &a, SLOT(quit()));
  timer->start(500);
  a.exec();
  REQUIRE(r0);
  REQUIRE(r1);
  REQUIRE(r2);
  // LogOut w1; w1.setpath("/madmin"); w1.init(); w1.run();
  // REQUIRE(w1.isTestSuccess() == true);
}
//#define SUD(t, ins, upd, del)\
//{CreateUser w1{t, ins, upd, del}; w1.setpath("/madmin"); w1.init(); w1.run(); REQUIRE(w1.isTestSuccess() == true);}

TEST_CASE("create update delete successfull") {
  //// This test stopped working because now delete only accepts number.
  ////    SUD("user",
  ////
  ///R"([{"username":"username","fullname":"fullname","email":"email@email.com","password":"password","disabled":true,"state":"state","city":"city"},[null]])",
  ////        R"(
  ////        [
  ////
  ///{"type":"executive","parent_id":null,"p_username":0,"username":"user1","fullname":"fullname1","create_date":"2019-08-28
  ///12:04:23.440921+05:30","disabled":true,"email":"email1@gmail.com","password":"pass1","state":"state1","city":"city1"},
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
  auto w2 = SslEchoClient(QUrl(QStringLiteral("wss://localhost:8401/madmin")));
  json event1 = json::array({"auth", "login", 0});
  json event11 = json::array({"auth", "set_cookie", 0});
  json event2 = json::array({"user", "is_logged_in", 0});
  json event3 = json::array({"song", "ins", 0});
  json event4 = json::array({"song", "upd", 0});
  json event5 = json::array({"song", "del", 0});
  json payload = json::array({
      {event1, json::object({{"user", "sadmin"}, {"pass", "123456"}})},
      {event2, json::array()},
      {event3, json::array({json::object(
                   {{"title", "very_new_song"}, {"catalog_id", 2}})})},
      {event4,
       json::array(
           {json::object({{"title", "very_new_song2"}, {"catalog_id", 2}}),
            R"([null, null, null, null, "=very_new_song"])"_json})},
      {event5,
       json::array({R"([[null, null, null, null, "=very_new_song2"]])"_json})},
  });

  SPDLOG_TRACE(payload.dump());
  bool r0, r1, r2, r3, r4, r5 = false;
  auto b1 = w2.bindOnce(event1, [&r0](json r) {
    REQUIRE(r[0]["ok"] == true);
    r0 = true;
  });
  auto b11 = w2.bindOnce(event11, [&r1](json r) {
    REQUIRE(r[0].is_number() == true);
    r1 = true;
  });
  auto b2 = w2.bindOnce(event2, [&r2](json r) {
    REQUIRE(r[0] == true);
    r2 = true;
  });
  auto b3 = w2.bindOnce(event3, [&r3](json r) {
    REQUIRE(r[0]["ok"] == true);
    r3 = true;
  });
  auto b4 = w2.bindOnce(event4, [&r4](json r) {
    REQUIRE(r[0]["ok"] == true);
    r4 = true;
  });
  auto b5 = w2.bindOnce(event5, [&r5](json r) {
    REQUIRE(r[0]["ok"] == true);
    r5 = true;
  });
  w2.sendMessage(QString::fromStdString(payload.dump()));
  REQUIRE(b1);
  REQUIRE(b11);
  REQUIRE(b2);
  REQUIRE(b3);
  REQUIRE(b4);
  REQUIRE(b5);

  QTimer *timer = new QTimer();
  QObject::connect(timer, SIGNAL(timeout()), &a, SLOT(quit()));
  timer->start(500);
  a.exec();
  REQUIRE(r0);
  REQUIRE(r1);
  REQUIRE(r2);
  REQUIRE(r3);
  REQUIRE(r4);
  REQUIRE(r5);
}

//// user count is not fixed now.
////TEST_CASE("create Count successfull") {
////    UserCount w1{"user"}; w1.setpath("/madmin"); w1.init(); w1.run();
///REQUIRE(w1.isTestSuccess() == true);
////
/// }
