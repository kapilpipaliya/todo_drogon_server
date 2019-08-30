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
    GetTableD("catalog_local")
    GetTableD("song")
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
#define SUD(t, ins, upd, del)\
{CreateUser w1{t, ins, upd, del}; w1.setpath("/madmin"); w1.init(); w1.run(); REQUIRE(w1.isTestSuccess() == true);}

TEST_CASE("create User successfull") {
    SUD("user",
        R"([{"username":"username","fullname":"fullname","email":"email@email.com","password":"password","disabled":true,"state":"state","city":"city"},[null]])",
        R"(
        [
            {"type":"executive","parent_id":null,"p_username":0,"username":"user1","fullname":"fullname1","create_date":"2019-08-28 12:04:23.440921+05:30","disabled":true,"email":"email1@gmail.com","password":"pass1","state":"state1","city":"city1"},
            [null, null, null, null, "=username"]
        ])",
        R"([[null, null, null, null, "=user1"]])")

    SUD("catalog_local",
        R"([{"name": "new_catalog", "enabled": true}, [null]])",
        R"(
       [
        {"name": "new_catalog1", "enabled": true},
        [null, "=new_catalog"]
      ])",
        R"([[null, "=new_catalog1"]])")
    SUD("song",
        R"([{"title": "very_new_song", "catalog_id": 1}, [null]])",
        R"(
        [
        {"title": "very_new_song2", "catalog_id": 1},
        [null, null, null, "=very_new_song"]
        ])",
        R"([[null, null, null, "=very_new_song2"]])")
}
TEST_CASE("create Count successfull") {
    UserCount w1{"user"}; w1.setpath("/madmin"); w1.init(); w1.run(); REQUIRE(w1.isTestSuccess() == true);
}
