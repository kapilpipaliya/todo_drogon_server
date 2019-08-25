#include "jsonfns.h"
#include "spdlog/spdlog.h"
void printJson(json &in)
{
    spdlog::info(in.dump().c_str());
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
