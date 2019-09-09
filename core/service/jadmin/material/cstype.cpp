#include "cstype.h"

#include <utility>

namespace jadmin {
CSType::CSType(JAdminContextPtr context_) : context(std::move(context_)) {
  query = sqlb::Query(sqlb::ObjectIdentifier("material", "cs_type", "ct"));
  setupTable();
}

nlohmann::json CSType::handleEvent(nlohmann::json event, unsigned long next,
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

void CSType::setupTable() {
  // m_query.setRowIdColumn("id");
  query.setSelectedColumns({
      sqlb::SelectedColumn({"Id", "id", "", "ct", PG_TYPES::INT8, false}),
      //            sqlb::SelectedColumn({"Rank", "rank", "", "ct",
      //            PG_TYPES::INT4, false}), sqlb::SelectedColumn({"Code",
      //            "slug", "", "ct", PG_TYPES::TEXT, true}),
      sqlb::SelectedColumn({"Name", "name", "", "ct", PG_TYPES::TEXT, true}),
      //            sqlb::SelectedColumn({"Created By", "create_user_id", "",
      //            "ct", PG_TYPES::INT8, true, 1}),
      //            sqlb::SelectedColumn({"u1_username", "username", "", "u1",
      //            PG_TYPES::TEXT, false, 0, 0, false}),
      //            sqlb::SelectedColumn({"Updated By", "update_user_id", "",
      //            "ct", PG_TYPES::INT8, true, 1}),
      //            sqlb::SelectedColumn({"u2_username", "username", "", "u2",
      //            PG_TYPES::TEXT, false, 0, 0, false}),
      //            sqlb::SelectedColumn({"Create Time", "inserted_at", "",
      //            "ct", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
      //            sqlb::SelectedColumn({"Update Time", "updated_at", "", "ct",
      //            PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  });

  //    auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
  //    auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

  query.setJoins({
      //            sqlb::Join("left", u1, "ct.create_user_id = u1.id"),
      //            sqlb::Join("left", u2, "ct.update_user_id = u2.id"),
  });
}

nlohmann::json CSType::ins(nlohmann::json event, nlohmann::json args) {
  return query.insBase(event, args, "name", "$1",
                       args[0]["name"].get<std::string>());
}

nlohmann::json CSType::upd(nlohmann::json event, nlohmann::json args) {
  return query.updBase(event, args, "name", "$1",
                       args[0]["name"].get<std::string>());
}
}  // namespace jadmin
