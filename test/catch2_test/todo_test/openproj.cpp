#include <drogon/drogon.h>
#include <QCoreApplication>
#include <catch2/catch.hpp>
#include "../src/BatchResultTest.h"
#include "../wsclient/once.h"
#include "../wsclient/wsclient.h"

TEST_CASE("is connection possible", "[WSTest]") {
  char **argv;
  int i = 0;
  QCoreApplication a(i, argv);
  auto w2 =
      wstest::SslEchoClient(QUrl(QStringLiteral("wss://localhost:8401/todo")));

  bool r0 = false;
  Once::connect(&w2.getWebSocket(), &QWebSocket::connected, [&r0]() {
    LOG_DEBUG << "Connection successfull";
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
  auto w2 =
      wstest::SslEchoClient(QUrl(QStringLiteral("wss://localhost:8401/todo")));
  std::string str = "hello";
  nlohmann::json j = str;
  w2.sendMessage(QString::fromStdString(j.dump()));
  bool r0 = false;
  Once::connect(&w2.getWebSocket(), &QWebSocket::textMessageReceived, [&r0]() {
    LOG_DEBUG << "Connection Not successfull";
    REQUIRE(true);
    r0 = true;
  });
  QTimer *timer = new QTimer();
  QObject::connect(timer, SIGNAL(timeout()), &a, SLOT(quit()));
  timer->start(500);
  a.exec();
  REQUIRE(r0);
}

TEST_CASE("seed", "[WSTest]") {
  char **argv;
  int i = 0;
  QCoreApplication a(i, argv);
  auto w2 =
      wstest::SslEchoClient(QUrl(QStringLiteral("wss://localhost:8401/todo")));
  nlohmann::json event = nlohmann::json::array({"seed", "seed1", 0});
  nlohmann::json payload = nlohmann::json::array(
      {{event,
        nlohmann::json::object({{"user", "sadmin"}, {"pass", "123456"}})}});
  LOG_DEBUG << payload.dump();
  bool r0 = false;
  auto b = w2.bindOnce(event, [&r0](nlohmann::json r) {
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
}
TEST_CASE("seed2", "[WSTest]") {
    char **argv;
    int i = 0;
    QCoreApplication a(i, argv);
    auto w2 =
          wstest::SslEchoClient(QUrl(QStringLiteral("wss://localhost:8401/todo")));
//    nlohmann::json event1 = nlohmann::json::array({"seed", "seed1", 0});
//    nlohmann::json event2 = nlohmann::json::array({"seed", "seed2", 0});
    nlohmann::json event3 = nlohmann::json::array({"seed", "seedall", 0});

    nlohmann::json payload = nlohmann::json::array({
//      {event1, nlohmann::json::object({})},
//      {event2, nlohmann::json::array({{}})},
      {event3, nlohmann::json::array({{}})}
    });
    LOG_DEBUG << payload.dump();
    bool r0 = false, r2 = false, r3 = false;
//    auto b = w2.bindOnce(event1, [&r0](nlohmann::json r) {
//          REQUIRE(r[0]["ok"] == true);
//    r0 = true;
//    });
//    auto b2 = w2.bindOnce(event2, [&r2](nlohmann::json r) {
//    REQUIRE(r[0]["ok"] == true);
//    r2 = true;
//    });
    auto b3 = w2.bindOnce(event3, [&r3](nlohmann::json r) {
            REQUIRE(r[0]["ok"] == true);
    r3 = true;
    });
    w2.sendMessage(QString::fromStdString(payload.dump()));
//    REQUIRE(b);
//    REQUIRE(b2);
        REQUIRE(b3);
    QTimer *timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), &a, SLOT(quit()));
    timer->start(500);
    a.exec();
//    REQUIRE(r0);
//    REQUIRE(r2);
    REQUIRE(r3);
}

