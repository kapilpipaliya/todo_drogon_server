#include "casting.h"

#include <utility>

namespace jadmin {
Casting::Casting(std::shared_ptr<websocket::JAdminContext> context_) : context(std::move(context_)) {
  query = sql::Query(sql::ObjectIdentifier("mfg", "casting", "m"));
  setupTable();
}

nlohmann::json Casting::handleEvent(nlohmann::json event, unsigned long next,
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

void Casting::setupTable() {
  // m_query.setRowIdColumn("id");
  query.setSelectedColumns({
      sql::SelectedColumn({"Id", "id", "", "m", PG_TYPES::INT8, false}),
      //        sql::SelectedColumn({"Rank", "rank", "", "m", PG_TYPES::INT4,
      //        false}),
      sql::SelectedColumn({"Code", "slug", "", "m", PG_TYPES::TEXT, true}),
      sql::SelectedColumn({"Name", "name", "", "m", PG_TYPES::TEXT, true}),
      sql::SelectedColumn({"Specific_density", "specific_density", "", "m",
                            PG_TYPES::DOUBLE, true}),
      sql::SelectedColumn({"Melting Point in C", "melting_point_in_c", "", "m",
                            PG_TYPES::DOUBLE, true}),
      sql::SelectedColumn(
          {"Currency_id", "currency_id", "", "m", PG_TYPES::INT8, true}),
      sql::SelectedColumn({"Price", "price", "", "m", PG_TYPES::DOUBLE, true}),
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

  auto u1 = sql::ObjectIdentifier("entity", "entity_user", "u1");
  auto u2 = sql::ObjectIdentifier("entity", "entity_user", "u2");

  query.setJoins({

      sql::Join("left", u1, "m.create_user_id = u1.id"),
      sql::Join("left", u2, "m.update_user_id = u2.id"),
  });
}

nlohmann::json Casting::ins(nlohmann::json event, nlohmann::json args) {
  return query.insBase(event, args, "name", "$1",
                       args[0]["name"].get<std::string>());
}

nlohmann::json Casting::upd(nlohmann::json event, nlohmann::json args) {
  return query.updBase(event, args, "name", "$1",
                       args[0]["name"].get<std::string>());
}
}  // namespace jadmin
