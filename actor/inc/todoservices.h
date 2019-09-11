#pragma once

#include "wsfns.h"
#include "mainactortype.h"
#include "spdlogfix.h"

#include "context/todocontext.h"

#include "core/service/todo/class/auth.h"
#include "core/service/todo/class/ui.h"
#include "core/service/todo/class/user.h"

template <typename T>
nlohmann::json handleService(std::shared_ptr<todo::TodoContext> contx,
                             nlohmann::json in) {
  try {
    T p{contx};
    auto r = p.handleEvent(in[0], 1, in[1]);
    if (!r.is_null()) return r;
    return nlohmann::json::array();
  } catch (const std::exception &e) {
    SPDLOG_TRACE(e.what());
    return nlohmann::json::array({{e.what()}});
  }
}
