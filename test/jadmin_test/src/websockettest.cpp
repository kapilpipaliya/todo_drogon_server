#include "websockettest.h"

void WSTest::connectToServer()
{
    wsPtr->connectToServer(req,
                           [this](ReqResult r,
                            [[maybe_unused]] const HttpResponsePtr &resp,
                                       [[maybe_unused]] const WebSocketClientPtr &wsPtr) {
                               if (r == ReqResult::Ok)
                               {
                                   quit(true);
                               }
                               else
                               {
                                   quit(false, "ws connection failed");
                               }
                           });
}
