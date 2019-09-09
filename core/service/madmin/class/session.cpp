#include <utility>

#include "../../dba.h"
#include "./session.h"

madmin::Session::Session(MAdminContextPtr context_)
    : context(std::move(context_)) {
  setupTable();
}

nlohmann::json madmin::Session::handleEvent(nlohmann::json event,
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

void madmin::Session::setupTable() {}

bool madmin::Session::destroy(long key) {
  if (!key) {  // !key.empty()
    return false;
  }

  // Remove anything and EVERYTHING
  std::string sql = "DELETE FROM music.session WHERE id = $1";
  auto r = Dba::write(sql, key);
  return r.affectedRows() == 1;
  // debug_event("SESSION", "Deleting Session with key:" . key, 6);

  // session_name  = AmpConfig::get("session_name");
  // cookie_path   = AmpConfig::get("cookie_path");
  // cookie_domain = null;
  // cookie_secure = AmpConfig::get("cookie_secure");

  // Destroy our cookie!
  // setcookie(session_name, null, -1, cookie_path, cookie_domain,
  // cookie_secure); setcookie(session_name . "_user", null, -1, cookie_path,
  // cookie_domain, cookie_secure); setcookie(session_name . "_lang", null, -1,
  // cookie_path, cookie_domain, cookie_secure);

  // return true;
}
