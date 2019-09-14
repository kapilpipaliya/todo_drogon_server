#include "support.h"

#include <utility>

namespace jadmin {
Support::Support(std::shared_ptr<websocket::JAdminContext> context_)
    : context(std::move(context_)) {
  query = sql::Query(sql::ObjectIdentifier("setting", "support", "a"));
  setupTable();
}

nlohmann::json Support::handleEvent(nlohmann::json event, unsigned long next,
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

void Support::setupTable() {
  // m_query.setRowIdColumn("id");
  query.setSelectedColumns({
      sql::SelectedColumn({"Id", "id", "", "a", PG_TYPES::INT8, false}),
      sql::SelectedColumn({"Name", "name", "", "a", PG_TYPES::TEXT, true}),
      sql::SelectedColumn({"Email", "email", "", "a", PG_TYPES::TEXT, true}),
      sql::SelectedColumn({"Phone", "phone", "", "a", PG_TYPES::TEXT, true}),
      sql::SelectedColumn(
          {"Message", "message", "", "a", PG_TYPES::TEXT, true}),
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

  // auto u1 = sql::ObjectIdentifier("entity", "entity_user", "u1");
  // auto u2 = sql::ObjectIdentifier("entity", "entity_user", "u2");

  query.setJoins({
      // sql::Join("left", u1, "gt.create_user_id = u1.id"),
      // sql::Join("left", u2, "a.update_user_id = u2.id"),
  });
}

nlohmann::json Support::ins(nlohmann::json event, nlohmann::json args) {
  return query.insBase(event, args, "name, email, phone, message",
                       "$1, $2, $3, $4", args[0]["name"].get<std::string>(),
                       args[0]["email"].get<std::string>(),
                       args[0]["phone"].get<std::string>(),
                       args[0]["message"].get<std::string>());
}

nlohmann::json Support::upd(nlohmann::json event, nlohmann::json args) {
  return query.updBase(event, args, "name, email, phone, message",
                       "$1, $2, $3, $4", args[0]["name"].get<std::string>(),
                       args[0]["email"].get<std::string>(),
                       args[0]["phone"].get<std::string>(),
                       args[0]["message"].get<std::string>());
}
}  // namespace jadmin
