#ifndef TIMESERVICEHANDLE_H
#define TIMESERVICEHANDLE_H

#include <string>
#include <tuple>
#include <vector>

#include "todoactor.h"
class ServiceBase;
class TimeServiceHandle {
 public:
  TimeServiceHandle();
  void runService(std::shared_ptr<websocket::todo::TodoContext> contx, const nlohmann::json &in);

 private:
  //    std::vector<std::tuple<int, ServiceBase> > services;

  template <typename T>
  void handleService(std::shared_ptr<websocket::todo::TodoContext> contx,
                     nlohmann::json in) {
    try {
      T p{contx};
      auto r = p.handleEvent(in[0], 1, in[1]);
      if (!r.is_null()) return r;

    } catch (const std::exception& e) {
      LOG_DEBUG << e.what();
    }
  }
};

#endif  // TIMESERVICEHANDLE_H
