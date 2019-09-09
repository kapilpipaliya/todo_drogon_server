#include "waxsetting.h"

#include <utility>

namespace jadmin {
WaxSetting::WaxSetting(std::shared_ptr<JAdminContext> context_)
    : context(std::move(context_)) {
  query = sqlb::Query(sqlb::ObjectIdentifier("mfg", "wax_setting", "m"));
  setupTable();
}

nlohmann::json WaxSetting::handleEvent(nlohmann::json event, unsigned long next,
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

void WaxSetting::setupTable() {
  // m_query.setRowIdColumn("id");
  query.setSelectedColumns({
      sqlb::SelectedColumn({"Id", "id", "", "m", PG_TYPES::INT8, false}),
      sqlb::SelectedColumn({"Rank", "rank", "", "m", PG_TYPES::INT4, true}),
      sqlb::SelectedColumn({"No", "no", "", "m", PG_TYPES::TEXT, true}),
      sqlb::SelectedColumn(
          {"Sequence", "sequence_id", "", "m", PG_TYPES::INT8, true}),
      sqlb::SelectedColumn(
          {"Date", "date", "", "m", PG_TYPES::TIMESTAMP, true}),
      sqlb::SelectedColumn({"Department", "department_id", "", "m",
                            PG_TYPES::INT8, false, 1, 1}),
      sqlb::SelectedColumn(
          {"Name", "name", "", "dep", PG_TYPES::TEXT, false, 0, 0, false}),
      sqlb::SelectedColumn(
          {"Employee", "employee_id", "", "m", PG_TYPES::INT8, false, 1, 1}),
      sqlb::SelectedColumn(
          {"e_name", "slug", "", "e", PG_TYPES::TEXT, false, 0, 0, false}),
      sqlb::SelectedColumn(
          {"Description", "description", "", "m", PG_TYPES::TEXT, true}),
      sqlb::SelectedColumn(
          {"Status", "status_id", "", "m", PG_TYPES::TEXT, true}),
      sqlb::SelectedColumn(
          {"Branch", "branch_id", "", "m", PG_TYPES::INT8, true}),
      sqlb::SelectedColumn(
          {"Created By", "create_user_id", "", "m", PG_TYPES::INT8, true, 1}),
      sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT,
                            false, 0, 0, false}),
      sqlb::SelectedColumn(
          {"Updated By", "update_user_id", "", "m", PG_TYPES::INT8, true, 1}),
      sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT,
                            false, 0, 0, false}),
      sqlb::SelectedColumn({"Create Time", "inserted_at", "", "m",
                            PG_TYPES::TIMESTAMP, true, 0, 0, false}),
      sqlb::SelectedColumn({"Update Time", "updated_at", "", "m",
                            PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  });

  auto dep = sqlb::ObjectIdentifier("mfg", "department", "dep");
  auto e = sqlb::ObjectIdentifier("entity", "entity", "e");
  auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
  auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

  query.setJoins({
      sqlb::Join("left", dep, "dep.id = m.department_id"),
      sqlb::Join("left", e, "e.id = m.employee_id"),
      sqlb::Join("left", u1, "m.create_user_id = u1.id"),
      sqlb::Join("left", u2, "m.update_user_id = u2.id"),
  });
}

nlohmann::json WaxSetting::ins(nlohmann::json event, nlohmann::json args) {
  return query.insBase(
      event, args, "date, department_id, employee_id, description, status_id",
      "$1, $2, $3, $4, $5", args[0]["date"].get<std::string>(),
      args[0]["department_id"].get<long>(), args[0]["employee_id"].get<long>(),
      args[0]["description"].get<std::string>(),
      args[0]["status_id"].get<std::string>());
}

nlohmann::json WaxSetting::upd(nlohmann::json event, nlohmann::json args) {
  return query.updBase(
      event, args, "date, department_id, employee_id, description, status_id",
      "$1, $2, $3, $4, $5", args[0]["date"].get<std::string>(),
      args[0]["department_id"].get<long>(), args[0]["employee_id"].get<long>(),
      args[0]["description"].get<std::string>(),
      args[0]["status_id"].get<std::string>());
}
}  // namespace jadmin
