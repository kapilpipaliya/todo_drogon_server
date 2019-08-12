#include <drogon/drogon.h>
int main()
{
    drogon::app().registerPostHandlingAdvice(
    [](const drogon::HttpRequestPtr &req, const drogon::HttpResponsePtr &resp) {
        //LOG_DEBUG << "postHandling1";
        resp->addHeader("Access-Control-Allow-Origin", "*");
        //resp->addHeader("Access-Control-Allow-Credentials", "true");
    });
    //Set HTTP listener address and port
    // drogon::app().addListener("0.0.0.0",8300);
    drogon::app().loadConfigFile("./config.json");
    drogon::app().run();
    return 0;
}
