#include "log.h"

#include <utility>

namespace jadmin {
Log::Log(std::shared_ptr<websocket::JAdminContext> context_)
    : context(std::move(context_)) {
  query = sql::Query(sql::ObjectIdentifier("setting", "simple_log", "a"));
  setupTable();
}

nlohmann::json Log::handleEvent(nlohmann::json event, unsigned long next,
                                nlohmann::json args) {
  auto event_cmp = event[next].get<std::string>();
  if (event_cmp == "data") {
    return query.allData(event, args);
  }
  if (event_cmp == "header") {
    return query.headerData(event, args);
  } else if (event_cmp == "ins") {
    return ins(event, args);
  } else if (event_cmp == "upd") {
    return upd(event, args);
  } else if (event_cmp == "del") {
    return query.del(event, args);
  } else {
    nlohmann::json ret;
    return ret;
  }
}

void Log::setupTable() {
  // m_query.setRowIdColumn("id");
  query.setSelectedColumns({
      sql::SelectedColumn({"Id", "id", "", "a", PG_TYPES::INT8, false}),
      sql::SelectedColumn({"Detail", "detail", "", "a", PG_TYPES::TEXT, true}),
      // sql::SelectedColumn({"Created By", "create_user_id", "", "a",
      // PG_TYPES::INT8, true, 1, 0, false}),
      // sql::SelectedColumn({"u1_username", "username", "", "u1",
      // PG_TYPES::TEXT, false, 0, 0, false}), sql::SelectedColumn({"Updated
      // By", "update_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}),
      // sql::SelectedColumn({"u2_username", "username", "", "u2",
      // PG_TYPES::TEXT, false, 0, 0, false}),
      sql::SelectedColumn({"Create Time", "inserted_at", "", "a",
                            PG_TYPES::TIMESTAMP, true, 0, 0, false}),
      sql::SelectedColumn({"Update Time", "updated_at", "", "a",
                            PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  });

  // auto m = sql::ObjectIdentifier("material", "metal", "m");
  // auto u1 = sql::ObjectIdentifier("entity", "entity_user", "u1");
  // auto u2 = sql::ObjectIdentifier("entity", "entity_user", "u2");

  query.setJoins({
      // sql::Join("left", m, "a.material_id = m.id"),
      // sql::Join("left", u1, "gt.create_user_id = u1.id"),
      // sql::Join("left", u2, "a.update_user_id = u2.id"),
  });
}
nlohmann::json Log::ins(nlohmann::json event, nlohmann::json args) {
  return query.insBase(event, args, "detail", "$1",
                       args[0]["detail"].get<std::string>());
}

nlohmann::json Log::upd(nlohmann::json event, nlohmann::json args) {
  return query.updBase(event, args, "detail", "$1",
                       args[0]["detail"].get<std::string>());
}
}  // namespace jadmin
