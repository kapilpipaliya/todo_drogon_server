#include "jsonfns.h"

void printJson(Json::Value & in)
{
    fprintf(stdout, "%s\n", in.toStyledString().c_str());
    fflush(stdout);
}

Json::Value simpleJsonSaveResult(const std::string &event1, const std::string &event2, const std::string &no, const WebSocketConnectionPtr& wsConnPtr, bool ok, const std::string & error)
{
    Json::Value out;
    out[0]=event1;
    out[1]=event2;
    out[2]=no;

    Json::Value ret;
    ret["ok"]=ok;
    if (!ok) {
        ret["error"]=error;
    }
    out[3]=ret;
    //wsConnPtr->send(out.toStyledString());
    return out;
}

// ---------
