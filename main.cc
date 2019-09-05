#include <drogon/drogon.h>
#include "spdlogfix.h"

int main()
{
    spdlog::set_pattern("[source %s] [function %!] [line %#] %v");
    //auto console = spdlog::stdout_logger_mt("console");
    //spdlog::set_default_logger(console);

    //SPDLOG_TRACE("global output with arg {}", 1); // [source main.cpp] [function main] [line 16] global output with arg 1
    //SPDLOG_LOGGER_TRACE(console, "logger output with arg {}", 2); // [source main.cpp] [function main] [line 17] logger output with arg 2
    //console->info("invoke member function");

    drogon::app().registerPostHandlingAdvice(
    [](const drogon::HttpResponsePtr &resp) {
        //LOG_DEBUG << "postHandling1";
        resp->addHeader("Access-Control-Allow-Origin", "*");
        //resp->addHeader("Access-Control-Allow-Credentials", "true");
    });
    // drogon::app().addListener("0.0.0.0",8300);
    drogon::app().loadConfigFile("./config.json").run();
    return 0;
}
