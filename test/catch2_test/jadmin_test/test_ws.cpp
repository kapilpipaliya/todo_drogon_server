#include <catch2/catch.hpp>

#include "../src/base/websockettest.h"
#include "../src/base/formatcheck.h"

#include "../src/jadmin/authcheck.h"
#include "../src/jadmin/login.h"
#include "../src/jadmin/signup.h"
#include "../src/jadmin/gettabledata.h"
#include "../src/jadmin/savedelete.h"

#include <QCoreApplication>
#include "spdlogfix.h"
#include "../wsclient/wsclient.h"
#include "../wsclient/once.h"

//To Benchmark do
// https://github.com/catchorg/Catch2/blob/master/docs/benchmarks.md
//BENCHMARK("MY FUNC") { return my_func(); };

TEST_CASE("is connection possible","[WSTest]") {
    char **argv;
    int i = 0;
    QCoreApplication a(i, argv);
    auto w2 = SslEchoClient(QUrl(QStringLiteral("wss://localhost:8401/jadmin")));

    bool r0 =false;
    Once::connect(&w2.m_webSocket, &QWebSocket::connected, [&r0](){
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

TEST_CASE("server reply error on string type of message.","[WSTest]") {
    char **argv;
    int i = 0;
    QCoreApplication a(i, argv);
    auto w2 = SslEchoClient(QUrl(QStringLiteral("wss://localhost:8401/jadmin")));
    std::string str = "hello";
    nlohmann::json j = str;
    // Bind not work because reply is not an array
//    auto b = w2.bindOnce(j, [&a](json r){
//        REQUIRE(r== "Invalid Message only array handled: \"hello\"");
//        a.quit();
//    });
//    REQUIRE(b);
    w2.sendMessage(QString::fromStdString(j.dump()));
    bool r0 =false;
    Once::connect(&w2.m_webSocket, &QWebSocket::textMessageReceived, [&r0](){
        SPDLOG_TRACE("Connection Not successfull");
        REQUIRE(true);
        r0 = true;
    });
    QTimer *timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), &a, SLOT(quit()));
    timer->start(500);
    a.exec();
    REQUIRE(r0);
        //FormatCheck w1;  w1.setpath("/madmin"); w1.init(); w1.run(); REQUIRE(w1.isTestSuccess() == true);
}
TEST_CASE("authorisation check without cookies","[WSTest]") {

char **argv;
int i = 0;
QCoreApplication a(i, argv);
auto w2 = SslEchoClient(QUrl(QStringLiteral("wss://localhost:8401/jadmin")));
json event = json::array({"legacy","auth","is_admin_auth",0} );
json payload = json::array({{event, {{}}}});
//    json j = R"( [ [["user","is_logged_in",0],[[]]]] )"_json;
SPDLOG_TRACE(payload.dump());
bool r0 = false;
auto b = w2.bindOnce(event, [&r0](json r){
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
}

TEST_CASE("login on backend with username and password","[WSTest]") {
    char **argv;
    int i = 0;
    QCoreApplication a(i, argv);
    auto w2 = SslEchoClient(QUrl(QStringLiteral("wss://localhost:8401/jadmin")));
   json event = json::array({"legacy","auth","admin_login",0} );
    json payload = json::array({{event, json::object({{"email", "kapil.pipaliya@yahoo.com"}, {"pass", "3434"}}) }});
    SPDLOG_TRACE(payload.dump());
    bool r0 =false;
    auto b = w2.bindOnce(event, [&r0](json r){
        REQUIRE(r[0]["ok"] == true);
        r0 = true;
    });
    json event2 = json::array({"legacy","auth","set_cookie",0} );
    bool r1 =false;
    auto b1 = w2.bindOnce(event2, [&r1](json r){
    REQUIRE(r[0]["admin"].is_number() == true);
    r1 = true;
    });
    w2.sendMessage(QString::fromStdString(payload.dump()));
    REQUIRE(b);
    REQUIRE(b1);
    QTimer *timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), &a, SLOT(quit()));
    timer->start(500);
    a.exec();
    REQUIRE(r0);
    REQUIRE(r1);
    //LogIn w1; w1.setpath("/madmin"); w1.init(); w1.run(); REQUIRE(w1.isTestSuccess() == true);
}
/* currently this not working.. but make this working in future.
TEST_CASE("signup with a form.","[WSTest]") {
    SignUp w1; w1.setpath("/jadmin"); w1.init(); w1.run(); REQUIRE(w1.isTestSuccess() == true);
}
*/
#define GetTableD(s)\
     {GetTableData w1{s}; w1.setpath("/jadmin"); w1.init(); w1.run(); REQUIRE(w1.isTestSuccess() == true);}

TEST_CASE("check that all table data are correctly replied","[WSTest]") {
    GetTableD("account_type")
    //GetTableD("account")
    GetTableD("account_heading")
    GetTableD("journal_type")
    GetTableD("txn")
    GetTableD("priority")

    GetTableD("node")
    //GetTableD("role")
    //GetTableD("task")

   // GetTableD("department_type")
    //GetTableD("department")
   // GetTableD("casting")
    GetTableD("wax_setting")
    //GetTableD("metal_issue")
    //GetTableD("MFG_txn")
   // GetTableD("refining")
    //GetTableD("m_transfer")

    GetTableD("metal")
    GetTableD("purity")
    GetTableD("tone")
    GetTableD("accessory")

    GetTableD("clarity")
    GetTableD("shape")
    GetTableD("d_color")
    GetTableD("cs_color")
    GetTableD("cs_type")
    GetTableD("size")
    GetTableD("d_size")
    GetTableD("cs_size")

    GetTableD("address_type")
    GetTableD("contact_type")
    GetTableD("entity_type")
    GetTableD("entity")

    GetTableD("setting")
    GetTableD("currency")
    GetTableD("log")
    GetTableD("support")
    GetTableD("image_collection")
    GetTableD("image")
    GetTableD("payment_method")

   // GetTableD("option")
    GetTableD("product")
    GetTableD("post")
    GetTableD("category")
    GetTableD("tag")
    GetTableD("shipping_class")
    GetTableD("setting_type")
    GetTableD("certified_by")
    GetTableD("policy")
}

#define SUD(t, ins, upd, del)\
{SaveDelete w1{t, ins, upd, del}; w1.setpath("/jadmin"); w1.init(); w1.run(); REQUIRE(w1.isTestSuccess() == true);}

TEST_CASE("insert of ","[WSTest]") {
    SUD("account_type",
        R"([{"name":"name"}])",
        R"([               {"name":"name1"},     [null,"=name"]])",
        R"([[null,"=name1"]])"
        )
//    SUD("account",
//        R"({"name":"name", "url": "123456", "description": "Hi whats app"})",
//        R"([      [null,null, "=name"]            ,{"name":"name1", "url": "12345688", "description": "Hi whats app1"}])",
//        R"([[null, null, "=name1"]])"
//        )
    SUD("account_heading",
        R"([{"name":"name", "accno": "12345"}])",
        R"([               {"name":"name1", "accno": "5555"} ,   [null,null, "=name"]   ])",
        R"([[null, null, "=name1"]])"
        )
    SUD("journal_type",
        R"([{"rank": 1234, "name":"name", "description": "Hi whats app"}])",
        R"([             {"rank": 12345, "name":"name1", "description": "Hi whats app1"}  , [null,null, "=name"]   ])",
        R"([[null, null, "=name1"]])"
        )
//    SUD("txn",
//        R"({"rank": 1234, "name":"name", "description": "Hi whats app"})",
//        R"([      [null,null, "=name"]            ,{"rank": 12345, "name":"name1", "description": "Hi whats app1"}])",
//        R"([[null, null, "=name1"]])"
//        )
    SUD("priority",
        R"([{"rank": 1234, "slug": "slug", "name":"name"}])",
        R"([                {"rank": 1234, "slug": "slug1", "name":"name1"}  ,  [null,null, "=slug"]])",
        R"([[null, null, "=slug1"]])"
        )

            //--------Fix this----------
//    SUD("node",
//        R"([{
//        "parent_id": 1,
//        "rank": 1234,
//        "slug": "slug",
//        "label":"label"
//        }])",
//        R"([              {"parent_id": 1,"rank": 1234, "slug": "slug1", "label":"label1"},  [null,null, null, "=slug"]   ])",
//        R"([[null, null, null, "=slug1"]])"
//        )
//    SUD("wax_setting",
//        R"({
//        "name":"name", "url": "123456", "description": "Hi whats app"
//        })",
//        R"([      [null,null, "=name"]            ,{"name":"name1", "url": "12345688", "description": "Hi whats app1"}])",
//        R"([[null, null, "=name1"]])"
//        )
//    SUD("metal",
//        R"({"name":"name", "url": "123456", "description": "Hi whats app"})",
//        R"([      [null,null, "=name"]            ,{"name":"name1", "url": "12345688", "description": "Hi whats app1"}])",
//        R"([[null, null, "=name1"]])"
//        )
//    SUD("purity",
//        R"({"name":"name", "url": "123456", "description": "Hi whats app"})",
//        R"([      [null,null, "=name"]            ,{"name":"name1", "url": "12345688", "description": "Hi whats app1"}])",
//        R"([[null, null, "=name1"]])"
//        )
//    SUD("tone",
//        R"({"name":"name", "url": "123456", "description": "Hi whats app"})",
//        R"([      [null,null, "=name"]            ,{"name":"name1", "url": "12345688", "description": "Hi whats app1"}])",
//        R"([[null, null, "=name1"]])"
//        )
//    SUD("accessory",
//        R"({"name":"name", "url": "123456", "description": "Hi whats app"})",
//        R"([      [null,null, "=name"]            ,{"name":"name1", "url": "12345688", "description": "Hi whats app1"}])",
//        R"([[null, null, "=name1"]])"
//        )
//    SUD("clarity",
//        R"({"name":"name", "url": "123456", "description": "Hi whats app"})",
//        R"([      [null,null, "=name"]            ,{"name":"name1", "url": "12345688", "description": "Hi whats app1"}])",
//        R"([[null, null, "=name1"]])"
//        )
//    SUD("shape",
//        R"({"name":"name", "url": "123456", "description": "Hi whats app"})",
//        R"([      [null,null, "=name"]            ,{"name":"name1", "url": "12345688", "description": "Hi whats app1"}])",
//        R"([[null, null, "=name1"]])"
//        )
//    SUD("d_color",
//        R"({"name":"name", "url": "123456", "description": "Hi whats app"})",
//        R"([      [null,null, "=name"]            ,{"name":"name1", "url": "12345688", "description": "Hi whats app1"}])",
//        R"([[null, null, "=name1"]])"
//        )
//    SUD("cs_color",
//        R"({"name":"name", "url": "123456", "description": "Hi whats app"})",
//        R"([      [null,null, "=name"]            ,{"name":"name1", "url": "12345688", "description": "Hi whats app1"}])",
//        R"([[null, null, "=name1"]])"
//        )
//    SUD("cs_type",
//        R"({"name":"name", "url": "123456", "description": "Hi whats app"})",
//        R"([      [null,null, "=name"]            ,{"name":"name1", "url": "12345688", "description": "Hi whats app1"}])",
//        R"([[null, null, "=name1"]])"
//        )
//    SUD("size",
//        R"({"name":"name", "url": "123456", "description": "Hi whats app"})",
//        R"([      [null,null, "=name"]            ,{"name":"name1", "url": "12345688", "description": "Hi whats app1"}])",
//        R"([[null, null, "=name1"]])"
//        )
//    SUD("d_size",
//        R"({"name":"name", "url": "123456", "description": "Hi whats app"})",
//        R"([      [null,null, "=name"]            ,{"name":"name1", "url": "12345688", "description": "Hi whats app1"}])",
//        R"([[null, null, "=name1"]])"
//        )
//    SUD("cs_size",
//        R"({"name":"name", "url": "123456", "description": "Hi whats app"})",
//        R"([      [null,null, "=name"]            ,{"name":"name1", "url": "12345688", "description": "Hi whats app1"}])",
//        R"([[null, null, "=name1"]])"
//        )
SUD("address_type",
    R"([{"name":"name"}])",
    R"([             {"name":"name1"},   [null,"=name"]   ])",
    R"([[null,"=name1"]])"
    )
SUD("contact_type",
    R"([{"name":"name"}])",
    R"([                 {"name":"name1"},   [null,"=name"]])",
    R"([[null,"=name1"]])"
    )
SUD("entity_type",
    R"([{"name":"name"}])",
    R"([               {"name":"name1"},  [null,"=name"]  ])",
    R"([[null,"=name1"]])"
    )
//    SUD("entity",
//        R"({"name":"name", "url": "123456", "description": "Hi whats app"})",
//        R"([      [null,null, "=name"]            ,{"name":"name1", "url": "12345688", "description": "Hi whats app1"}])",
//        R"([[null, null, "=name1"]])"
//        )
//    SUD("setting",
//        R"({"name":"name", "url": "123456", "description": "Hi whats app"})",
//        R"([      [null,null, "=name"]            ,{"name":"name1", "url": "12345688", "description": "Hi whats app1"}])",
//        R"([[null, null, "=name1"]])"
//        )
    SUD("currency",
        R"([{
        "slug": "slug1",
        "name":"name",
        "symbol": "123456",
        "rounding": 0.02,
        "active":true
        }])",
        R"([               {"slug": "slug2","name":"name1", "symbol": "12345688", "rounding": 0.05, "active": false},    [null, "=slug1"]  ])",
        R"([[null, "=slug2"]])"
        )
    SUD("log",
        R"([{"detail":"name"}])",
        R"([                {"detail":"name1"}, [null,"=name"]  ])",
        R"([[null,  "=name1"]])"
        )
    SUD("support",
        R"([{
        "name":"name",
        "email": "123456",
        "phone": "Hi whats app",
        "message": "Hi whats app"
        }])",
        R"([              {"name":"name1", "email": "12345688", "phone": "Hi whats app1", "message":"Hi 2"}  ,  [null,"=name"]   ])",
        R"([[null, null, "=name1"]])"
        )
SUD("image_collection",
    R"([{"name":"name"}])",
    R"([            {"name":"name1"}  ,   [null,"=name"]  ])",
    R"([[null,"=name1"]])"
    )
//    SUD("image",
//        R"({"name":"name", "url": "123456", "description": "Hi whats app"})",
//        R"([      [null,null, "=name"]            ,{"name":"name1", "url": "12345688", "description": "Hi whats app1"}])",
//        R"([[null, null, "=name1"]])"
//        )
    SUD("payment_method",
        R"([{"name":"name", "url": "123456", "description": "Hi whats app"}])",
        R"([                {"name":"name1", "url": "12345688", "description": "Hi whats app1"}  ,  [null, "=name"]  ])",
        R"([[null, "=name1"]])"
        )
//    SUD("product",
//        R"({"name":"name", "url": "123456", "description": "Hi whats app"})",
//        R"([      [null,null, "=name"]            ,{"name":"name1", "url": "12345688", "description": "Hi whats app1"}])",
//        R"([[null, null, "=name1"]])"
//        )
//    SUD("post",
//        R"({"name":"name", "url": "123456", "description": "Hi whats app"})",
//        R"([      [null,null, "=name"]            ,{"name":"name1", "url": "12345688", "description": "Hi whats app1"}])",
//        R"([[null, null, "=name1"]])"
//        )
    SUD("category",
        R"([{"slug":"slug", "name": "name", "description": "Hi whats app", "display_type": "default", "parent_id": 0, "position": 0}])",
        R"([              {"slug":"slug1", "name": "name1", "description": "Hi whats app1", "display_type": "default", "parent_id": 0, "position" :10},   [null,null,null, null, null,"=name"]   ])",
        R"([[null,null,null, null, null,"=name1"]])"
        )
//    SUD("tag",
//        R"({"name":"name", "url": "123456", "description": "Hi whats app"})",
//        R"([      [null,null, "=name"]            ,{"name":"name1", "url": "12345688", "description": "Hi whats app1"}])",
//        R"([[null, null, "=name1"]])"
//        )
    SUD("shipping_class",
        R"([{"slug":"slug", "name": "name", "description": "Hi whats app"}])",
        R"([                 {"slug":"slug1", "name": "name1", "description": "Hi whats app1"} ,  [null,"=slug"] ])",
        R"([[null, "=slug1"]])"
        )
    SUD("setting_type",
        R"([{"name":"name", "description": "Hi whats app"}])",
        R"([                {"name":"name1", "description": "Hi whats app1"},   [null,"=name"] ])",
        R"([[null, "=name1"]])"
        )
    SUD("certified_by",
        R"([{"slug":"slug","name":"name","title":"title","description":"discription"}])",
        R"([               {"slug":"slug1","name":"name1","title":"title1","description":"discription1"},  [null,"=slug",null,null,null]  ])",
        R"([[null,"=slug1",null,null,null]])"
        )

    SUD("policy",
        R"([{"name":"name", "url": "123456", "description": "Hi whats app"}])",
        R"([               {"name":"name1", "url": "12345688", "description": "Hi whats app1"}, [null, "=name"]   ])",
        R"([[null, "=name1"]])"
        )

}
/*More Test:
 * Binary data test
 * test for product related functions
 * image function
 * */
