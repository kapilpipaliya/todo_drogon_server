#include "cataloglocal.h"

madmin::CatalogLocal::CatalogLocal(const std::shared_ptr<websocket::MAdminContext> &context_)
    : Catalog(context_) {
  query = sql::Query(sql::ObjectIdentifier("music", "catalog", "c"));
  setupTable();
}

void madmin::CatalogLocal::setupTable() {
  // m_query.setRowIdColumn("id");
  query.setSelectedColumns({
      sql::SelectedColumn({"ID No", "id", "", "c", PG_TYPES::INT8}),
      // sql::SelectedColumn({"Catalog Type", "catalog_type", "", "c",
      // PG_TYPES::ENUM}), sql::SelectedColumn({"no", "no", "", "c",
      // PG_TYPES::TEXT}), sql::SelectedColumn({"sequence_id", "sequence_id",
      // "", "c", PG_TYPES::INT8, false}),
      sql::SelectedColumn({"Name", "name", "", "c", PG_TYPES::TEXT, true}),
      // sql::SelectedColumn({"Create Date", "last_update", "", "c",
      // PG_TYPES::TIMESTAMP}), sql::SelectedColumn({"last_clean Date",
      // "last_clean", "", "c", PG_TYPES::TIMESTAMP}),
      // sql::SelectedColumn({"last_add Date", "last_add", "", "c",
      // PG_TYPES::TIMESTAMP}),
      sql::SelectedColumn({"Active", "enabled", "", "c", PG_TYPES::BOOL}),
      // sql::SelectedColumn({"Rename Pattern", "rename_pattern", "", "c",
      // PG_TYPES::TEXT, true}), sql::SelectedColumn({"Sort Pattern",
      // "sort_pattern", "", "c", PG_TYPES::TEXT, true}),
      // sql::SelectedColumn({"Gather Types", "gather_types", "", "c",
      // PG_TYPES::TEXT, true}), sql::SelectedColumn({"Created By",
      // "create_user_id", "", "c", PG_TYPES::INT8, true, 1, 0, false}),
      // sql::SelectedColumn({"u1_username", "username", "", "u1",
      // PG_TYPES::TEXT, false, 0, 0, false}), sql::SelectedColumn({"Updated
      // By", "update_user_id", "", "c", PG_TYPES::INT8, true, 1, 0, false}),
      // sql::SelectedColumn({"u2_username", "username", "", "u2",
      // PG_TYPES::TEXT, false, 0, 0, false}), sql::SelectedColumn({"Create
      // Time", "inserted_at", "", "c", PG_TYPES::TIMESTAMP, true, 0, 0,
      // false}), sql::SelectedColumn({"Update Time", "updated_at", "", "c",
      // PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  });
  // auto p = sql::ObjectIdentifier("music", "user", "p");
  // auto u1 = sql::ObjectIdentifier("entity", "entity_user", "u1");
  // auto u2 = sql::ObjectIdentifier("entity", "entity_user", "u2");

  query.setJoins({
      // sql::Join("left", p, "e.parent_id = p.id")
      // sql::Join("left", u1, "e.create_user_id = u1.id"),
      // sql::Join("left", u2, "e.update_user_id = u2.id"),
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
          return {websocket::WsFns::successJsonObject(event, true, "Done")};
        }
      }
    }
    // return del(event,args);
    return {websocket::WsFns::successJsonObject(event, false, "UnAuthorised")};
  } else if (event_cmp == "count") {
    return query.count(event, args);
  } else {
    return nullptr;
  }
}
