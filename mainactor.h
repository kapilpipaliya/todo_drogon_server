#ifndef MESSAGEHANDLE_H
#define MESSAGEHANDLE_H

#include  "json.hpp"
using nlohmann:: json;

#include <drogon/WebSocketController.h>
using namespace drogon;

#include "caf/all.hpp"

using run_atom = caf::atom_constant<caf::atom("run")>;
class MainActor : public caf::event_based_actor
{
public:
    MainActor(caf:: actor_config& cfg );
    ~MainActor() override;
    json handleTextMessage(const WebSocketConnectionPtr &wsConnPtr, std::string &&message, json in);
    json handleBinaryMessage(const WebSocketConnectionPtr &, std::string &message);
private:
    void blocking_run(const WebSocketConnectionPtr &wsConnPtr, std::string &&message, const WebSocketMessageType &type);
    caf:: behavior    running_job; // initial behavior
protected:
   caf::behavior make_behavior() override;
};
#endif // MESSAGEHANDLE_H
