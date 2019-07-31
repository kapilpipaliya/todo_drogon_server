#include "jsonfns.h"

void printJson(Json::Value & in)
{
    fprintf(stdout, "%s\n", in.toStyledString().c_str());
    fflush(stdout);
}

void simpleJsonSaveResult(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, bool ok, const std::string & error)
{
    Json::Value out;
    out[0]=event_name;

    Json::Value ret;
    ret["ok"]=ok;
    if (!ok) {
        ret["error"]=error;
    }
    out[1]=ret;
    wsConnPtr->send(out.toStyledString());
}

// ---------
