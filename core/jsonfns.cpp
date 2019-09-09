#include "jsonfns.h"

#include <utility>
#include "spdlogfix.h"
void printJson(nlohmann::json &in) { SPDLOG_TRACE(in.dump().c_str()); }

nlohmann::json simpleJsonSaveResult(nlohmann::json event, bool ok,
                                    const std::string &error) {
  nlohmann::json out;
  out[0] = std::move(event);

  nlohmann::json ret;
  ret["ok"] = ok;
  if (!ok) {
    ret["error"] = error;
  }
  out[1] = ret;
  return out;
}

// ---------
