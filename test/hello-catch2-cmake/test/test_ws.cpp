#include <catch2/catch.hpp>

#include "../src/websockettest.h"
#include "../src/auth/formatcheck.h"
#include "../src/auth/authcheck.h"
#include "../src/auth/login.h"
#include "../src/auth/signup.h"
#include "../src/auth/gettabledata.h"

TEST_CASE("is connection possible","[WSTest]") {
    WSTest w1; w1.init(); w1.run(); REQUIRE(w1.isTestSuccess() == true);
}
TEST_CASE("server reply error on string type of message.","[WSTest]") {
        FormatCheck w1; w1.init(); w1.run(); REQUIRE(w1.isTestSuccess() == true);
}
TEST_CASE("authorisation check without cookies","[WSTest]") {
        AuthCheck w1; w1.init(); w1.run(); REQUIRE(w1.isTestSuccess() == true);
}
TEST_CASE("login on backend with username and password","[WSTest]") {
        LogIn w1; w1.init(); w1.run(); REQUIRE(w1.isTestSuccess() == true);
}
/* currently this not working.. but make this working in future.
TEST_CASE("signup with a form.","[WSTest]") {
    LogIn w1; w1.init(); w1.run(); REQUIRE(w1.isTestSuccess() == true);
}
*/
#define GetTableD(s)\
     {GetTableData w1{s}; w1.init(); w1.run(); REQUIRE(w1.isTestSuccess() == true);}

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
//To Benchmark do
// https://github.com/catchorg/Catch2/blob/master/docs/benchmarks.md
//BENCHMARK("MY FUNC") { return my_func(); };
