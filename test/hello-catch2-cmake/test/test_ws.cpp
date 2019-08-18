#include <catch2/catch.hpp>

#include "../src/websockettest.h"
#include "../src/auth/formatcheck.h"
#include "../src/auth/authcheck.h"
#include "../src/auth/login.h"

TEST_CASE("is connection possible","[WSTest]") {
    {
        WSTest w1;
        w1.init();
        w1.run();
        REQUIRE(w1.isTestSuccess() == true);
    }
}
TEST_CASE("server reply error on string type of message.","[WSTest]") {
    {
        FormatCheck w1;
        w1.init();
        w1.run();
        REQUIRE(w1.isTestSuccess() == true);
    }
}
TEST_CASE("authorisation check without cookies","[WSTest]") {
    {
        AuthCheck w1;
        w1.init();
        w1.run();
        REQUIRE(w1.isTestSuccess() == true);
    }
}
TEST_CASE("login on backend test","[WSTest]") {
    {
        AuthCheck w1;
        w1.init();
        w1.run();
        REQUIRE(w1.isTestSuccess() == true);
    }
}
