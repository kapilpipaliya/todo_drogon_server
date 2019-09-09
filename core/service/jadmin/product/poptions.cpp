#include "poptions.h"

#include <utility>

namespace jadmin {
POption::POption(JAdminContextPtr context_) : context(std::move(context_)) {
  query = sqlb::Query(sqlb::ObjectIdentifier("product", "option", "o"));
  setupTable();
}

nlohmann::json POption::handleEvent(nlohmann::json event, unsigned long next,
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

void POption::setupTable() {
  // m_query.setRowIdColumn("id");
  query.setSelectedColumns({
      sqlb::SelectedColumn({"Id", "id", "", "o", PG_TYPES::INT8, false}),
      sqlb::SelectedColumn({"Name", "name", "", "o", PG_TYPES::TEXT, true}),
      sqlb::SelectedColumn({"Value", "value", "", "o", PG_TYPES::TEXT, true}),
      sqlb::SelectedColumn(
          {"Autoload", "autoload", "", "o", PG_TYPES::TEXT, true}),
      // sqlb::SelectedColumn({"Created By", "create_user_id", "", "o",
      // PG_TYPES::INT8, true, 1, 0, false}),
      // sqlb::SelectedColumn({"u1_username", "username", "", "u1",
      // PG_TYPES::TEXT, false, 0, 0, false}), sqlb::SelectedColumn({"Updated
      // By", "update_user_id", "", "o", PG_TYPES::INT8, true, 1, 0, false}),
      // sqlb::SelectedColumn({"u2_username", "username", "", "u2",
      // PG_TYPES::TEXT, false, 0, 0, false}), sqlb::SelectedColumn({"Create
      // Time", "inserted_at", "", "o", PG_TYPES::TIMESTAMP, true, 0, 0,
      // false}), sqlb::SelectedColumn({"Update Time", "updated_at", "", "o",
      // PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  });

  auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
  auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

  query.setJoins({
      sqlb::Join("left", u1, "o.create_user_id = u1.id"),
      sqlb::Join("left", u2, "o.update_user_id = u2.id"),
  });
}

nlohmann::json POption::ins(nlohmann::json event, nlohmann::json args) {
  return query.insBase(event, args, "name, value, auoload", "$1, $2, $3",
                       args[0]["name"].get<std::string>(),
                       args[0]["value"].get<std::string>(),
                       args[0]["auoload"].get<std::string>());
}

nlohmann::json POption::upd(nlohmann::json event, nlohmann::json args) {
  return query.updBase(event, args, "name, value, auoload", "$1, $2, $3",
                       args[0]["name"].get<std::string>(),
                       args[0]["value"].get<std::string>(),
                       args[0]["auoload"].get<std::string>());
}
}  // namespace jadmin
