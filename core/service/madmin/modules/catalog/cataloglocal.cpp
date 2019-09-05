#include "cataloglocal.h"
using namespace madmin;
using S = sqlb::SelectedColumn;

CatalogLocal::CatalogLocal(const MAdminContextPtr &context_)
    : Catalog(context_) {
  t.m_table = sqlb::ObjectIdentifier("music", "catalog", "c");
  t.m_query = sqlb::Query(t.m_table);
}

void CatalogLocal::setupTable() {
  // m_query.setRowIdColumn("id");
  t.m_query.selectedColumns() = {
      S({"ID No", "id", "", "c", PG_TYPES::INT8}),
      // S({"Catalog Type", "catalog_type", "", "c", PG_TYPES::ENUM}),
      // S({"no", "no", "", "c", PG_TYPES::TEXT}),
      // S({"sequence_id", "sequence_id", "", "c", PG_TYPES::INT8, false}),
      S({"Name", "name", "", "c", PG_TYPES::TEXT, true}),
      // S({"Create Date", "last_update", "", "c", PG_TYPES::TIMESTAMP}),
      // S({"last_clean Date", "last_clean", "", "c", PG_TYPES::TIMESTAMP}),
      // S({"last_add Date", "last_add", "", "c", PG_TYPES::TIMESTAMP}),
      S({"Active", "enabled", "", "c", PG_TYPES::BOOL}),
      // S({"Rename Pattern", "rename_pattern", "", "c", PG_TYPES::TEXT, true}),
      // S({"Sort Pattern", "sort_pattern", "", "c", PG_TYPES::TEXT, true}),
      // S({"Gather Types", "gather_types", "", "c", PG_TYPES::TEXT, true}),
      // S({"Created By", "create_user_id", "", "c", PG_TYPES::INT8, true, 1, 0,
      // false}), S({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false,
      // 0, 0, false}), S({"Updated By", "update_user_id", "", "c",
      // PG_TYPES::INT8, true, 1, 0, false}), S({"u2_username", "username", "",
      // "u2", PG_TYPES::TEXT, false, 0, 0, false}), S({"Create Time",
      // "inserted_at", "", "c", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
      // S({"Update Time", "updated_at", "", "c", PG_TYPES::TIMESTAMP, true, 0,
      // 0, false}),
  };
  // auto p = sqlb::ObjectIdentifier("music", "user", "p");
  // auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
  // auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

  t.m_query.joins() = {
      // sqlb::Join("left", p, "e.parent_id = p.id")
      // sqlb::Join("left", u1, "e.create_user_id = u1.id"),
      // sqlb::Join("left", u2, "e.update_user_id = u2.id"),
  };

  t.m_query.groupBy() = {};
}

nlohmann::json CatalogLocal::handleEvent(nlohmann::json event,
                                         unsigned long next,
                                         nlohmann::json args) {
  auto event_cmp = event[next].get<std::string>();
  if (event_cmp == "header") {  // required
    return headerData(event, args);
  }
  if (event_cmp == "data") {  // required
    if (context->user.type == "super admin") {
      return allData(event, args);
    }
    return {{event, "unauthorised"}};

  } else if (event_cmp == "ins") {
    // args[0]["parent_id"] = context->user_id;
    return ins(event, args);
  } else if (event_cmp == "upd") {
    return upd(event, args);
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
    return count(event, args);
  } else {
    return nullptr;
  }
}
