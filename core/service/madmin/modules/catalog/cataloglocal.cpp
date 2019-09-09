#include "cataloglocal.h"

madmin::CatalogLocal::CatalogLocal(const MAdminContextPtr &context_)
    : Catalog(context_) {
  query = sqlb::Query(sqlb::ObjectIdentifier("music", "catalog", "c"));
  setupTable();
}

void madmin::CatalogLocal::setupTable() {
  // m_query.setRowIdColumn("id");
  query.setSelectedColumns({
      sqlb::SelectedColumn({"ID No", "id", "", "c", PG_TYPES::INT8}),
      // sqlb::SelectedColumn({"Catalog Type", "catalog_type", "", "c",
      // PG_TYPES::ENUM}), sqlb::SelectedColumn({"no", "no", "", "c",
      // PG_TYPES::TEXT}), sqlb::SelectedColumn({"sequence_id", "sequence_id",
      // "", "c", PG_TYPES::INT8, false}),
      sqlb::SelectedColumn({"Name", "name", "", "c", PG_TYPES::TEXT, true}),
      // sqlb::SelectedColumn({"Create Date", "last_update", "", "c",
      // PG_TYPES::TIMESTAMP}), sqlb::SelectedColumn({"last_clean Date",
      // "last_clean", "", "c", PG_TYPES::TIMESTAMP}),
      // sqlb::SelectedColumn({"last_add Date", "last_add", "", "c",
      // PG_TYPES::TIMESTAMP}),
      sqlb::SelectedColumn({"Active", "enabled", "", "c", PG_TYPES::BOOL}),
      // sqlb::SelectedColumn({"Rename Pattern", "rename_pattern", "", "c",
      // PG_TYPES::TEXT, true}), sqlb::SelectedColumn({"Sort Pattern",
      // "sort_pattern", "", "c", PG_TYPES::TEXT, true}),
      // sqlb::SelectedColumn({"Gather Types", "gather_types", "", "c",
      // PG_TYPES::TEXT, true}), sqlb::SelectedColumn({"Created By",
      // "create_user_id", "", "c", PG_TYPES::INT8, true, 1, 0, false}),
      // sqlb::SelectedColumn({"u1_username", "username", "", "u1",
      // PG_TYPES::TEXT, false, 0, 0, false}), sqlb::SelectedColumn({"Updated
      // By", "update_user_id", "", "c", PG_TYPES::INT8, true, 1, 0, false}),
      // sqlb::SelectedColumn({"u2_username", "username", "", "u2",
      // PG_TYPES::TEXT, false, 0, 0, false}), sqlb::SelectedColumn({"Create
      // Time", "inserted_at", "", "c", PG_TYPES::TIMESTAMP, true, 0, 0,
      // false}), sqlb::SelectedColumn({"Update Time", "updated_at", "", "c",
      // PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  });
  // auto p = sqlb::ObjectIdentifier("music", "user", "p");
  // auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
  // auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

  query.setJoins({
      // sqlb::Join("left", p, "e.parent_id = p.id")
      // sqlb::Join("left", u1, "e.create_user_id = u1.id"),
      // sqlb::Join("left", u2, "e.update_user_id = u2.id"),
  });
}

nlohmann::json madmin::CatalogLocal::handleEvent(nlohmann::json event,
                                                 unsigned long next,
                                                 nlohmann::json args) {
  auto event_cmp = event[next].get<std::string>();
  if (event_cmp == "header") {  // required
    return query.headerData(event, args);
  }
  if (event_cmp == "data") {  // required
    if (getContext()->getUser().type == "super admin") {
      return query.allData(event, args);
    }
    return {{event, "unauthorised"}};

  } else if (event_cmp == "ins") {
    // args[0]["parent_id"] = context->getUserId();
    return query.ins(event, args);
  } else if (event_cmp == "upd") {
    return query.upd(event, args);
  } else if (event_cmp == "del") {
    if (args[0].is_array()) {
      if (args[0][0].is_number()) {
        if (delet(args[0][0].get<long>(), "local")) {
          return {simpleJsonSaveResult(event, true, "Done")};
        }
      }
    }
    // return del(event,args);
    return {simpleJsonSaveResult(event, false, "UnAuthorised")};
  } else if (event_cmp == "count") {
    return query.count(event, args);
  } else {
    return nullptr;
  }
}
