#include "random.h"

#include <utility>

music::service::Random::Random(
    std::shared_ptr<websocket::music::MAdminContext> context_)
    : context(std::move(context_)) {
  setupTable();
}

nlohmann::json music::service::Random::handleEvent(nlohmann::json event,
                                                   unsigned long next,
                                                   nlohmann::json args) {
  auto event_cmp = event[next].get<std::string>();
  if (event_cmp == "data") {
    return query.allData(event, args);
  }
  if (event_cmp == "header") {
    return query.headerData(event, args);
  } else if (event_cmp == "ins") {
    return query.ins(event, args);
  } else if (event_cmp == "upd") {
    return query.upd(event, args);
  } else if (event_cmp == "del") {
    return query.del(event, args);
  } else {
    nlohmann::json ret;
    return ret;
  }
}

void music::service::Random::setupTable() {}
