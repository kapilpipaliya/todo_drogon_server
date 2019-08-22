#include "jsonfns.h"

void printJson(json &in)
{
    fprintf(stdout, "%s\n", in.dump().c_str());
    fflush(stdout);
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
