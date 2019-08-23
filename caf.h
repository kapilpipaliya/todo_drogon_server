#ifndef MyCAF_H
#define MyCAF_H

#include "caf/all.hpp"

#include <drogon/WebSocketController.h>
using namespace drogon;
using namespace drogon::orm;
#include "mainactor.h"

#include  "json.hpp"
using nlohmann:: json;

//caf::allowed_unsafe_message_type<WebSocketConnectionPtr>;
//caf::allowed_unsafe_message_type<json>;
CAF_ALLOW_UNSAFE_MESSAGE_TYPE(WebSocketConnectionPtr)
CAF_ALLOW_UNSAFE_MESSAGE_TYPE(json)

class MyCAF
{
  caf::actor_system_config cfg;
public:
  caf::actor_system sys;
    MyCAF();
    caf::scoped_actor self;
    void initialiseMainWector();

//    mainAct_type mainactor;
    caf::actor mainactor;
};

extern MyCAF globalCAF;
#endif // MyCAF_H
