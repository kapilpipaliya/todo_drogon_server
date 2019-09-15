#include "pcategory.h"

#include <utility>
namespace jadmin {

PCategory::PCategory(std::shared_ptr<websocket::jadmin::JAdminContext> context_)
    : context(std::move(context_)) {
  query = sql::Query(sql::ObjectIdentifier("product", "category", "c"));
  setupTable();
}

nlohmann::json PCategory::handleEvent(nlohmann::json event, unsigned long next,
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

void PCategory::setupTable() {
  // m_query.setRowIdColumn("id");
  query.setSelectedColumns({
      sql::SelectedColumn({"Id", "id", "", "c", sql::PG_TYPES::INT8, false}),
      sql::SelectedColumn(
          {"Parent", "parent_id", "", "c", sql::PG_TYPES::INT8, true, 2, 1}),
      sql::SelectedColumn(
          {"p_slug", "slug", "", "p", sql::PG_TYPES::TEXT, false, 0, 0, false}),
      sql::SelectedColumn(
          {"p_name", "name", "", "p", sql::PG_TYPES::TEXT, false, 0, 0, false}),
      sql::SelectedColumn(
          {"Position", "position", "", "c", sql::PG_TYPES::INT4, true}),
      sql::SelectedColumn({"Name", "name", "", "c", sql::PG_TYPES::TEXT, true}),
      sql::SelectedColumn({"Code", "slug", "", "c", sql::PG_TYPES::TEXT, true}),
      sql::SelectedColumn(
          {"Description", "description", "", "c", sql::PG_TYPES::TEXT, true}),
      sql::SelectedColumn(
          {"Display Type", "display_type", "", "c", sql::PG_TYPES::TEXT, true}),
      sql::SelectedColumn({"Created By", "create_user_id", "", "c",
                           sql::PG_TYPES::INT8, true, 1, 0, false}),
      sql::SelectedColumn({"u1_username", "username", "", "u1",
                           sql::PG_TYPES::TEXT, false, 0, 0, false}),
      sql::SelectedColumn({"Updated By", "update_user_id", "", "c",
                           sql::PG_TYPES::INT8, true, 1, 0, false}),
      sql::SelectedColumn({"u2_username", "username", "", "u2",
                           sql::PG_TYPES::TEXT, false, 0, 0, false}),
      sql::SelectedColumn({"Create Time", "inserted_at", "", "c",
                           sql::PG_TYPES::TIMESTAMP, true, 0, 0, false}),
      sql::SelectedColumn({"Update Time", "updated_at", "", "c",
                           sql::PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  });

  auto p = sql::ObjectIdentifier("product", "category", "p");
  auto u1 = sql::ObjectIdentifier("entity", "entity_user", "u1");
  auto u2 = sql::ObjectIdentifier("entity", "entity_user", "u2");

  query.setJoins({
      sql::Join("left", p, "c.parent_id = p.id"),
      sql::Join("left", u1, "c.create_user_id = u1.id"),
      sql::Join("left", u2, "c.update_user_id = u2.id"),
  });
}

nlohmann::json PCategory::ins(nlohmann::json event, nlohmann::json args) {
  return query.insBase(
      event, args, "slug, name, description, display_type, parent_id, position",
      "$1, $2, $3, $4, NULLIF($5, 0::bigint), $6",
      args[0]["slug"].get<std::string>(), args[0]["name"].get<std::string>(),
      args[0]["description"].get<std::string>(),
      args[0]["display_type"].get<std::string>(),
      args[0]["parent_id"]
          .get<long>(),  // why this ask for get<int>()? otherwise error: ERROR:
                         // incorrect binary data format in bind parameter 5
      args[0]["position"].get<int>());
}

nlohmann::json PCategory::upd(nlohmann::json event, nlohmann::json args) {
  return query.updBase(
      event, args, "slug, name, description, display_type, parent_id, position",
      "$1, $2, $3, $4, NULLIF($5, 0::bigint), $6",
      args[0]["slug"].get<std::string>(), args[0]["name"].get<std::string>(),
      args[0]["description"].get<std::string>(),
      args[0]["display_type"].get<std::string>(),
      args[0]["parent_id"].get<long>(),  // why this ask for get<int>()?
      args[0]["position"].get<int>());
}
}  // namespace jadmin
