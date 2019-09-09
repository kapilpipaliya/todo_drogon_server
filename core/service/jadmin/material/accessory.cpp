#include "accessory.h"

#include <utility>
using namespace jadmin;

Accessory::Accessory(JAdminContextPtr context_) : context(std::move(context_)) {
  getQuery() =
      sqlb::Query(sqlb::ObjectIdentifier("material", "accessory", "a"));
}

void Accessory::setupTable() {
  // m_query.setRowIdColumn("id");
  getQuery().setSelectedColumns({
      sqlb::SelectedColumn({"Id", "id", "", "a", PG_TYPES::INT8, false}),
      //        sqlb::SelectedColumn({"Material", "material_id", "", "a",
      //        PG_TYPES::INT8, true, 1, 2}), sqlb::SelectedColumn({"m_slug",
      //        "slug", "", "m", PG_TYPES::TEXT, false, 0, 0, false}),
      //        sqlb::SelectedColumn({"m_name", "name", "", "m", PG_TYPES::TEXT,
      //        false, 0, 0, false}),
      sqlb::SelectedColumn({"Rank", "rank", "", "a", PG_TYPES::INT4, false}),
      sqlb::SelectedColumn({"Code", "slug", "", "a", PG_TYPES::TEXT, true}),
      sqlb::SelectedColumn({"Name", "name", "", "a", PG_TYPES::TEXT, true}),
      sqlb::SelectedColumn({"Created By", "create_user_id", "", "a",
                            PG_TYPES::INT8, true, 1, 0, false}),
      sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT,
                            false, 0, 0, false}),
      sqlb::SelectedColumn({"Updated By", "update_user_id", "", "a",
                            PG_TYPES::INT8, true, 1, 0, false}),
      sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT,
                            false, 0, 0, false}),
      sqlb::SelectedColumn({"Create Time", "inserted_at", "", "a",
                            PG_TYPES::TIMESTAMP, true, 0, 0, false}),
      sqlb::SelectedColumn({"Update Time", "updated_at", "", "a",
                            PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  });

  //    auto m = sqlb::ObjectIdentifier("material", "metal", "m");
  auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
  auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

  getQuery().setJoins({
      //        sqlb::Join("left", m, "a.material_id = m.id"),
      sqlb::Join("left", u1, "a.create_user_id = u1.id"),
      sqlb::Join("left", u2, "a.update_user_id = u2.id"),
  });
}

nlohmann::json Accessory::ins(nlohmann::json event, nlohmann::json args) {
  return insBase(event, args, "slug, name", "$1, $2",
                 args[0]["slug"].get<std::string>(),
                 args[0]["name"].get<std::string>());
}

nlohmann::json Accessory::upd(nlohmann::json event, nlohmann::json args) {
  return updBase(event, args, "slug, name", "$1, $2",
                 args[0]["slug"].get<std::string>(),
                 args[0]["name"].get<std::string>());
}
