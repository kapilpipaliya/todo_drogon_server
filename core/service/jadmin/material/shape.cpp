#include "shape.h"

#include <utility>

namespace jadmin {
Shape::Shape(std::shared_ptr<websocket::jadmin::JAdminContext> context_)
    : context(std::move(context_)) {
  query = sql::Query(sql::ObjectIdentifier("material", "shape", "gs"));
  setupTable();
}

nlohmann::json Shape::handleEvent(nlohmann::json event, unsigned long next,
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

void Shape::setupTable() {
  // m_query.setRowIdColumn("id");
  query.setSelectedColumns({
      sql::SelectedColumn({"Id", "id", "", "gs", sql::PG_TYPES::INT8, false}),
      //        sql::SelectedColumn({"Material", "material_id", "", "gs",
      //        sql::PG_TYPES::INT8, true, 1, 2}),
      //        sql::SelectedColumn({"m_slug", "slug", "", "m",
      //        sql::PG_TYPES::TEXT, false, 0, 0, false}),
      //        sql::SelectedColumn({"m_name", "name", "", "m",
      //        sql::PG_TYPES::TEXT, false, 0, 0, false}),
      sql::SelectedColumn(
          {"Rank", "rank", "", "gs", sql::PG_TYPES::INT4, false}),
      sql::SelectedColumn(
          {"Code", "slug", "", "gs", sql::PG_TYPES::TEXT, true}),
      sql::SelectedColumn(
          {"Name", "name", "", "gs", sql::PG_TYPES::TEXT, true}),
      sql::SelectedColumn({"Created By", "create_user_id", "", "gs",
                           sql::PG_TYPES::INT8, true, 1}),
      sql::SelectedColumn({"u1_username", "username", "", "u1",
                           sql::PG_TYPES::TEXT, false, 0, 0, false}),
      sql::SelectedColumn({"Updated By", "update_user_id", "", "gs",
                           sql::PG_TYPES::INT8, true, 1}),
      sql::SelectedColumn({"u2_username", "username", "", "u2",
                           sql::PG_TYPES::TEXT, false, 0, 0, false}),
      sql::SelectedColumn({"Create Time", "inserted_at", "", "gs",
                           sql::PG_TYPES::TIMESTAMP, true, 0, 0, false}),
      sql::SelectedColumn({"Update Time", "updated_at", "", "gs",
                           sql::PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  });

  //    auto m = sql::ObjectIdentifier("material", "metal", "m");
  auto u1 = sql::ObjectIdentifier("entity", "entity_user", "u1");
  auto u2 = sql::ObjectIdentifier("entity", "entity_user", "u2");

  query.setJoins({
      //        sql::Join("left", m, "gs.material_id = m.id"),
      sql::Join("left", u1, "gs.create_user_id = u1.id"),
      sql::Join("left", u2, "gs.update_user_id = u2.id"),
  });
}

nlohmann::json Shape::ins(nlohmann::json event, nlohmann::json args) {
  return query.insBase(event, args, "slug, name", "$1, $2",
                       args[0]["slug"].get<std::string>(),
                       args[0]["name"].get<std::string>());
}

nlohmann::json Shape::upd(nlohmann::json event, nlohmann::json args) {
  return query.updBase(event, args, "slug, name", "$1, $2",
                       args[0]["slug"].get<std::string>(),
                       args[0]["name"].get<std::string>());
}
}  // namespace jadmin
