#include "EchoWebSocket.h"

// move this functionality to the class:
#include "core/service/auth/auth.h"

using namespace std::literals;



void EchoWebSocket::handleNewMessage(const WebSocketConnectionPtr &wsConnPtr, std::string &&message,
                                   const WebSocketMessageType &type) {
    // fprintf(stdout, "%s\n", message.c_str());
    // fflush(stdout);
    switch (type) {
        case WebSocketMessageType::Text: {
            Json::Value valin;
            std::stringstream txt;
            txt << message;
            Json::CharReaderBuilder rbuilder;
            rbuilder["collectComments"] = false;
            std::string errs;
            bool ok = Json::parseFromStream(rbuilder, txt, &valin, &errs);
            if(ok){
                if (valin.isArray()){
                    Json::Value out(Json::arrayValue);
                    for (auto i : valin) {
                        // printJson(valin);
                        auto result  = msgHandle.handleTextMessage(wsConnPtr, i);
                        for (auto &i : result) {
                            if(!i.isNull()){
                                out.append(i);
                            }
                        }
                    }
                    if(!out.empty()){
                        wsConnPtr->send(out.toStyledString());
                    }
                }
            }
            break;
        }
        case WebSocketMessageType::Binary: {
                 auto result  = msgHandle.handleBinaryMessage(wsConnPtr, message);
                 if(!result.isNull()){
                     wsConnPtr->send(result.toStyledString());
                 }
            break;
        }
        default:
            break;
    }
}
void EchoWebSocket::handleNewConnection(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr) {
    // save the cookie in contex, because its not available on other handler
    LOG_DEBUG << "new websocket connection!\n";
    auto &key=req->getHeader("Sec-WebSocket-Key");
    LOG_DEBUG << key;

    std::shared_ptr<std::map<std::string, std::vector<int> >> k(new std::map<std::string, std::vector<int> >);
    k->insert(std::pair<std::string, std::vector<int> >("admin"s, {0}));
    k->insert(std::pair<std::string, std::vector<int> >("user"s, {0}));
    wsConnPtr->setContext(k);
    auto adminContext = generateContext(req, wsConnPtr, "admin");
    setAdminContext(wsConnPtr, adminContext);
    auto userContext = generateContext(req, wsConnPtr, "user");
    setUserContext(wsConnPtr, userContext);
    // LOG_DEBUG << req->getCookie("admin");
    for (auto i : req->cookies()) {
        printf("%s,%s", i.first.c_str(), i.second.c_str());
        fflush(stdout);
    }
    // create connection to the database and keep it open. Will Increase Performance.
}
void EchoWebSocket::handleConnectionClosed(const WebSocketConnectionPtr &wsConnPtr) {
    LOG_DEBUG << "connection closed!\n" <<wsConnPtr->peerAddr().toIp();
}
