#include "department.h"

#include <utility>

namespace jadmin {
Department::Department(std::shared_ptr<websocket::JAdminContext> context_)
    : context(std::move(context_)) {
  query = sql::Query(sql::ObjectIdentifier("mfg", "department", "m"));
  setupTable();
}

nlohmann::json Department::handleEvent(nlohmann::json event, unsigned long next,
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

void Department::setupTable() {
  // m_query.setRowIdColumn("id");
  query.setSelectedColumns({
      sql::SelectedColumn({"Id", "id", "", "m", PG_TYPES::INT8, false}),
      sql::SelectedColumn({"Rank", "rank", "", "m", PG_TYPES::INT4, false}),
      sql::SelectedColumn({"Code", "slug", "", "m", PG_TYPES::TEXT, true}),
      sql::SelectedColumn({"Name", "name", "", "m", PG_TYPES::TEXT, true}),
      sql::SelectedColumn({"Department Type", "department_type_id", "", "m",
                            PG_TYPES::INT8, true, 1, 1}),
      sql::SelectedColumn(
          {"Name", "name", "", "dep_type", PG_TYPES::TEXT, false, 0, 0, false}),
      sql::SelectedColumn(
          {"Parent", "parent_id", "", "m", PG_TYPES::INT8, true}),
      sql::SelectedColumn(
          {"Created By", "create_user_id", "", "m", PG_TYPES::INT8, true, 1}),
      sql::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT,
                            false, 0, 0, false}),
      sql::SelectedColumn(
          {"Updated By", "update_user_id", "", "m", PG_TYPES::INT8, true, 1}),
      sql::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT,
                            false, 0, 0, false}),
      sql::SelectedColumn({"Create Time", "inserted_at", "", "m",
                            PG_TYPES::TIMESTAMP, true, 0, 0, false}),
      sql::SelectedColumn({"Update Time", "updated_at", "", "m",
                            PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  });

  auto dep_type = sql::ObjectIdentifier("mfg", "department_type", "dep_type");
  auto u1 = sql::ObjectIdentifier("entity", "entity_user", "u1");
  auto u2 = sql::ObjectIdentifier("entity", "entity_user", "u2");

  query.setJoins({
      sql::Join("left", dep_type, "dep_type.id = m.department_type_id"),
      sql::Join("left", u1, "m.create_user_id = u1.id"),
      sql::Join("left", u2, "m.update_user_id = u2.id"),
  });
}

nlohmann::json Department::ins(nlohmann::json event, nlohmann::json args) {
  return query.insBase(event, args, "name", "$1",
                       args[0]["name"].get<std::string>());
}

nlohmann::json Department::upd(nlohmann::json event, nlohmann::json args) {
  return query.updBase(event, args, "name", "$1",
                       args[0]["name"].get<std::string>());
}
}  // namespace jadmin
