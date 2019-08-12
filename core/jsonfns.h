#ifndef JSONFNS_H
#define JSONFNS_H

#include <json/json.h>

void printJson(Json::Value & in);
Json::Value simpleJsonSaveResult(Json::Value event, bool ok, const std::string & error);



#endif // JSONFNS_H
