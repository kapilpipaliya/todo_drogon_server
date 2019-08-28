#include "jsonfns.h"
#include "spdlogfix.h"
void printJson(json &in)
{
    SPDLOG_TRACE(in.dump().c_str());
}

json simpleJsonSaveResult(json event, bool ok, const std::string & error)
{
    json out;
    out[0]=event;

    json ret;
    ret["ok"]=ok;
    if (!ok) {
        ret["error"]=error;
    }
    out[1]=ret;
    return out;
}

// ---------
