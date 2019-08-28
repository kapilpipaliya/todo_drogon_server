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

using namespace  madmin;

//To Benchmark do
// https://github.com/catchorg/Catch2/blob/master/docs/benchmarks.md
//BENCHMARK("MY FUNC") { return my_func(); };


TEST_CASE("is connection possible","[WSTest]") {
    WSTest w1; w1.setpath("/madmin"); w1.init(); w1.run(); REQUIRE(w1.isTestSuccess() == true);
}

TEST_CASE("server reply error on string type of message.","[WSTest]") {
        FormatCheck w1;  w1.setpath("/madmin"); w1.init(); w1.run(); REQUIRE(w1.isTestSuccess() == true);
}

TEST_CASE("authorisation check without cookies","[WSTest]") {
        AuthCheck w1; w1.setpath("/madmin"); w1.init(); w1.run(); REQUIRE(w1.isTestSuccess() == true);
}

TEST_CASE("login on backend with username and password","[WSTest]") {
        LogIn w1; w1.setpath("/madmin"); w1.init(); w1.run(); REQUIRE(w1.isTestSuccess() == true);
}

// currently this not working.. but make this working in future.
//TEST_CASE("signup with a form.","[WSTest]") {
//    SignUp w1; w1.setpath("/madmin"); w1.init(); w1.run(); REQUIRE(w1.isTestSuccess() == true);
//}

#define GetTableD(s)\
     {GetTableData w1{s}; w1.setpath("/madmin"); w1.init(); w1.run(); REQUIRE(w1.isTestSuccess() == true);}

TEST_CASE("check that all table Super Admin data are correctly replied","[WSTest]") {
    GetTableD("user")
}


#define GetTableD(s)\
     {GetTableDataAdmin w1{s}; w1.setpath("/madmin"); w1.init(); w1.run(); REQUIRE(w1.isTestSuccess() == true);}

TEST_CASE("check that all table Admin data are correctly replied","[WSTest]") {
    GetTableD("user")
}

TEST_CASE("User SAdmin Menu Test","[WSTest]") {
    GetMenuSAdmin w1{"ui"}; w1.setpath("/madmin"); w1.init(); w1.run(); REQUIRE(w1.isTestSuccess() == true);
}
TEST_CASE("User Admin Menu Test","[WSTest]") {
    GetMenuAdmin w1{"ui"}; w1.setpath("/madmin"); w1.init(); w1.run(); REQUIRE(w1.isTestSuccess() == true);
}

TEST_CASE("password change should work.") {
        PasswordChange w1; w1.setpath("/madmin"); w1.init(); w1.run(); REQUIRE(w1.isTestSuccess() == true);
}
TEST_CASE("Logout successfull") {
        LogOut w1; w1.setpath("/madmin"); w1.init(); w1.run(); REQUIRE(w1.isTestSuccess() == true);
}
