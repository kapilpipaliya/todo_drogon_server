#ifndef JSONFNS_H
#define JSONFNS_H

#include  "json.hpp"
using nlohmann:: json;
void printJson(json & in);
json simpleJsonSaveResult(json event, bool ok, const std::string & error);

#endif // JSONFNS_H
