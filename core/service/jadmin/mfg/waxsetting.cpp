#include "waxsetting.h"

#include <utility>

namespace jewel {
namespace service {
WaxSetting::WaxSetting(
    std::shared_ptr<websocket::jewel::JAdminContext> context_)
    : context(std::move(context_)) {
  query = sql::Query(sql::ObjectIdentifier("mfg", "wax_setting", "m"));
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
      sql::SelectedColumn({"Id", "id", "", "m", sql::PG_TYPES::INT8, false}),
      sql::SelectedColumn({"Rank", "rank", "", "m", sql::PG_TYPES::INT4, true}),
      sql::SelectedColumn({"No", "no", "", "m", sql::PG_TYPES::TEXT, true}),
      sql::SelectedColumn(
          {"Sequence", "sequence_id", "", "m", sql::PG_TYPES::INT8, true}),
      sql::SelectedColumn(
          {"Date", "date", "", "m", sql::PG_TYPES::TIMESTAMP, true}),
      sql::SelectedColumn({"Department", "department_id", "", "m",
                           sql::PG_TYPES::INT8, false, 1, 1}),
      sql::SelectedColumn(
          {"Name", "name", "", "dep", sql::PG_TYPES::TEXT, false, 0, 0, false}),
      sql::SelectedColumn({"Employee", "employee_id", "", "m",
                           sql::PG_TYPES::INT8, false, 1, 1}),
      sql::SelectedColumn(
          {"e_name", "slug", "", "e", sql::PG_TYPES::TEXT, false, 0, 0, false}),
      sql::SelectedColumn(
          {"Description", "description", "", "m", sql::PG_TYPES::TEXT, true}),
      sql::SelectedColumn(
          {"Status", "status_id", "", "m", sql::PG_TYPES::TEXT, true}),
      sql::SelectedColumn(
          {"Branch", "branch_id", "", "m", sql::PG_TYPES::INT8, true}),
      sql::SelectedColumn({"Created By", "create_user_id", "", "m",
                           sql::PG_TYPES::INT8, true, 1}),
      sql::SelectedColumn({"u1_username", "username", "", "u1",
                           sql::PG_TYPES::TEXT, false, 0, 0, false}),
      sql::SelectedColumn({"Updated By", "update_user_id", "", "m",
                           sql::PG_TYPES::INT8, true, 1}),
      sql::SelectedColumn({"u2_username", "username", "", "u2",
                           sql::PG_TYPES::TEXT, false, 0, 0, false}),
      sql::SelectedColumn({"Create Time", "inserted_at", "", "m",
                           sql::PG_TYPES::TIMESTAMP, true, 0, 0, false}),
      sql::SelectedColumn({"Update Time", "updated_at", "", "m",
                           sql::PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  });

  auto dep = sql::ObjectIdentifier("mfg", "department", "dep");
  auto e = sql::ObjectIdentifier("entity", "entity", "e");
  auto u1 = sql::ObjectIdentifier("entity", "entity_user", "u1");
  auto u2 = sql::ObjectIdentifier("entity", "entity_user", "u2");

  query.setJoins({
      sql::Join("left", dep, "dep.id = m.department_id"),
      sql::Join("left", e, "e.id = m.employee_id"),
      sql::Join("left", u1, "m.create_user_id = u1.id"),
      sql::Join("left", u2, "m.update_user_id = u2.id"),
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
}  // namespace service
}  // namespace jadmin
