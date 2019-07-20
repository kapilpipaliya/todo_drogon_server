#include <drogon/drogon.h>


int main()
{
    //Set HTTP listener address and port

    drogon::app().registerPostHandlingAdvice(
    [](const drogon::HttpRequestPtr &req, const drogon::HttpResponsePtr &resp) {
        //LOG_DEBUG << "postHandling1";
        resp->addHeader("Access-Control-Allow-Origin", "*");
        //resp->addHeader("Access-Control-Allow-Credentials", "true");
    });

    // drogon::app().addListener("0.0.0.0",8300);
    // drogon::app().addListener("0.0.0.0",443);
    drogon::app().addListener("0.0.0.0",8800);

    //Load config file
    //drogon::app().loadConfigFile("../config.json");
    //Run HTTP framework,the method will block in the internal event loop
    drogon::app().run();
    return 0;
}

/*
<kapilp> Kapil Piapliya i have my server running but how to make it ruuning in background and access its output again when i ssh?
i make a C++ console application

4:13 PM <grawity> Mantas Mikulėnas <grawity@gmail.com> server applications shouldn't have an interactive console
4:13 PM if you made one, run it inside tmux or Screen
4:14 PM but really it should only log messages to syslog, and have some *remote* control
4:15 PM → ghostbox and ChrisWarrick joined  ⇐ poljar quit  ↔ PsychoTron nipped out
4:17 PM <Khorne> Have it dump to stdout and let systemd/journald capture it by running it as a service
4:19 PM Khorne: systemd-cat
<Khorne> !give kapilp aw systemd
Systemd - https://wiki.archlinux.org/index.php/Systemd
*/
