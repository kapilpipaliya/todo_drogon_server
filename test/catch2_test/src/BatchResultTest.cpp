
#include "BatchResultTest.h"
#include <iostream>
namespace wstest {
bool BatchResultTest::addEvent(const nlohmann::json &event_,
                               const nlohmann::json &payload) {
  event.insert({event_, {payload, false}});
  return true;
}

std::string BatchResultTest::generatePayload() {
  nlohmann::json payload = nlohmann::json::array();
  for (auto &e : event) {
    payload.push_back(nlohmann::json::array({e.first, std::get<0>(e.second)}));
  }
  printf("generated payload: %s", payload.dump().c_str());
  return payload.dump();
}

bool BatchResultTest::setResult(const nlohmann::json &event_, bool res) {
  auto it = event.find(event_);
  if (it != event.end()) {
    std::get<1>(it->second) = res;
    return true;
  } else {
    return false;
  }
}

bool BatchResultTest::result() {
  bool res = true;
  for (auto &e : event) {
    if (!std::get<1>(e.second)) {
      printf("%s result false", e.first.dump().c_str());
      std::cout.flush();
      return false;
    }
  }
  return res;
}
}
