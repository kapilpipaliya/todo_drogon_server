#include "account.h"

#include <utility>
namespace jadmin {
Account::Account(std::shared_ptr<websocket::JAdminContext> context_)
    : context(std::move(context_)) {
  query = sql::Query(sql::ObjectIdentifier("account", "account", "a"));
  setupTable();
}

nlohmann::json Account::handleEvent(nlohmann::json event, unsigned long next,
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

void Account::setupTable() {
  // m_query.setRowIdColumn("id");
  query.setSelectedColumns({
      sql::SelectedColumn({"Id", "id", "", "a", PG_TYPES::INT8, false}),
      sql::SelectedColumn(
          {"Material", "material_id", "", "a", PG_TYPES::INT8, true, 1, 2}),
      sql::SelectedColumn({"m_slug", "slug", "", "m", PG_TYPES::TEXT, false}),
      sql::SelectedColumn({"m_name", "name", "", "m", PG_TYPES::TEXT, false}),
      sql::SelectedColumn({"Rank", "rank", "", "a", PG_TYPES::INT4, false}),
      sql::SelectedColumn({"Code", "slug", "", "a", PG_TYPES::TEXT, true}),
      sql::SelectedColumn({"Name", "name", "", "a", PG_TYPES::TEXT, true}),
      sql::SelectedColumn({"Created By", "create_user_id", "", "a",
                           PG_TYPES::INT8, true, 1, 0, false}),
      sql::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT,
                           false, 0, 0, false}),
      sql::SelectedColumn({"Updated By", "update_user_id", "", "a",
                           PG_TYPES::INT8, true, 1, 0, false}),
      sql::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT,
                           false, 0, 0, false}),
      sql::SelectedColumn({"Create Time", "inserted_at", "", "a",
                           PG_TYPES::TIMESTAMP, true, 0, 0, false}),
      sql::SelectedColumn({"Update Time", "updated_at", "", "a",
                           PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  });

  auto m = sql::ObjectIdentifier("material", "metal", "m");
  auto u1 = sql::ObjectIdentifier("entity", "entity_user", "u1");
  auto u2 = sql::ObjectIdentifier("entity", "entity_user", "u2");

  query.setJoins({
      sql::Join("left", m, "a.material_id = m.id"),
      sql::Join("left", u1, "a.create_user_id = u1.id"),
      sql::Join("left", u2, "a.update_user_id = u2.id"),
  });
}

nlohmann::json Account::ins(nlohmann::json event, nlohmann::json args) {
  return query.insBase(event, args, "rank, name, description", "$1, $2, $3",
                       args[0]["rank"].get<int>(),
                       args[0]["name"].get<std::string>(),
                       args[0]["description"].get<std::string>());
}

nlohmann::json Account::upd(nlohmann::json event, nlohmann::json args) {
  return query.updBase(event, args, "rank, name, description", "$1, $2, $3",
                       args[0]["rank"].get<int>(),
                       args[0]["name"].get<std::string>(),
                       args[0]["description"].get<std::string>());
}

}  // namespace jadmin
