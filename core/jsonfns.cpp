#include "jsonfns.h"

void printJson(Json::Value & in)
{
    fprintf(stdout, "%s\n", in.toStyledString().c_str());
    fflush(stdout);
}

Json::Value simpleJsonSaveResult(Json::Value event, bool ok, const std::string & error)
{
    Json::Value out;
    out[0]=event;

    Json::Value ret;
    ret["ok"]=ok;
    if (!ok) {
        ret["error"]=error;
    }
    out[1]=ret;
    return out;
}

// ---------
