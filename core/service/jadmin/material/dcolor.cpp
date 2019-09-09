#include "dcolor.h"

#include <utility>
using namespace jadmin;

DColor::DColor(JAdminContextPtr context_) : context(std::move(context_)) {
  getQuery() =
      sqlb::Query(sqlb::ObjectIdentifier("material", "diamond_color", "gt"));
}

void DColor::setupTable() {
  // m_query.setRowIdColumn("id");
  getQuery().setSelectedColumns({
      sqlb::SelectedColumn({"Id", "id", "", "gt", PG_TYPES::INT8, false}),
      sqlb::SelectedColumn({"Rank", "rank", "", "gt", PG_TYPES::INT4, false}),
      sqlb::SelectedColumn({"Code", "slug", "", "gt", PG_TYPES::TEXT, true}),
      sqlb::SelectedColumn({"Name", "name", "", "gt", PG_TYPES::TEXT, true}),
      sqlb::SelectedColumn(
          {"Created By", "create_user_id", "", "gt", PG_TYPES::INT8, true, 1}),
      sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT,
                            false, 0, 0, false}),
      sqlb::SelectedColumn(
          {"Updated By", "update_user_id", "", "gt", PG_TYPES::INT8, true, 1}),
      sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT,
                            false, 0, 0, false}),
      sqlb::SelectedColumn({"Create Time", "inserted_at", "", "gt",
                            PG_TYPES::TIMESTAMP, true, 0, 0, false}),
      sqlb::SelectedColumn({"Update Time", "updated_at", "", "gt",
                            PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  });

  auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
  auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

  getQuery().setJoins({
      sqlb::Join("left", u1, "gt.create_user_id = u1.id"),
      sqlb::Join("left", u2, "gt.update_user_id = u2.id"),
  });
}

nlohmann::json DColor::ins(nlohmann::json event, nlohmann::json args) {
  return insBase(event, args, "slug, name", "$1, $2",
                 args[0]["slug"].get<std::string>(),
                 args[0]["name"].get<std::string>());
}

nlohmann::json DColor::upd(nlohmann::json event, nlohmann::json args) {
  return updBase(event, args, "slug, name", "$1, $2",
                 args[0]["slug"].get<std::string>(),
                 args[0]["name"].get<std::string>());
}
