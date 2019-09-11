#ifndef _BATCHRESULTTEST_H
#define _BATCHRESULTTEST_H

#include <map>
#include <string>
#include "json.hpp"

class BatchResultTest {
 private:
  std::map<nlohmann::json, std::tuple<nlohmann::json, bool> > event;

 public:
  bool addEvent(const nlohmann::json& event_, const nlohmann::json& payload);
  std::string generatePayload();

  bool setResult(const nlohmann::json& event_, bool res = true);

  bool result();

  auto begin() { return event.begin(); }
  auto begin() const { return event.begin(); }
  auto end() { return event.end(); }
  auto end() const { return event.end(); }

 private:
  template <typename T>
  void addEvent(T event_, const nlohmann::json& payload);
  template <typename T>
  void setResult(T event_, bool res = true);
};
#endif
