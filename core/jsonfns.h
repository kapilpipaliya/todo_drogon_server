#ifndef JSONFNS_H
#define JSONFNS_H

#include "json.hpp"

void printJson(nlohmann::json& in);
nlohmann::json simpleJsonSaveResult(nlohmann::json event, bool ok,
                                    const std::string& error);

#endif  // JSONFNS_H
