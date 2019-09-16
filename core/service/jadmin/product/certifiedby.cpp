#include "certifiedby.h"

#include <utility>

namespace jewel {
namespace service {
CertifiedBy::CertifiedBy(
    std::shared_ptr<websocket::jewel::JAdminContext> context_)
    : context(std::move(context_)) {
  query = sql::Query(sql::ObjectIdentifier("product", "certified_by", "t"));
  setupTable();
}

nlohmann::json CertifiedBy::handleEvent(nlohmann::json event,
                                        unsigned long next,
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

void CertifiedBy::setupTable() {
  // m_query.setRowIdColumn("id");
  query.setSelectedColumns({
      sql::SelectedColumn({"Id", "id", "", "t", sql::PG_TYPES::INT8, false}),
      sql::SelectedColumn({"Code", "slug", "", "t", sql::PG_TYPES::TEXT, true}),
      sql::SelectedColumn({"Name", "name", "", "t", sql::PG_TYPES::TEXT, true}),
      sql::SelectedColumn(
          {"Title", "title", "", "t", sql::PG_TYPES::TEXT, true}),
      sql::SelectedColumn(
          {"Description", "description", "", "t", sql::PG_TYPES::TEXT, true}),
      //        sql::SelectedColumn({"Product Count", " "",product_count", "t",
      //        sql::PG_TYPES::INT4, true}),
      // sql::SelectedColumn({"Created By", "create_user_id", "", "t",
      // sql::PG_TYPES::INT8, true, 1, 0, false}),
      // sql::SelectedColumn({"u1_username", "username", "", "u1",
      // sql::PG_TYPES::TEXT, false, 0, 0, false}),
      // sql::SelectedColumn({"Updated By", "update_user_id", "", "t",
      // sql::PG_TYPES::INT8, true, 1, 0, false}),
      // sql::SelectedColumn({"u2_username", "username", "", "u2",
      // sql::PG_TYPES::TEXT, false, 0, 0, false}), sql::SelectedColumn({"Create
      // Time", "inserted_at", "", "t", sql::PG_TYPES::TIMESTAMP, true, 0, 0,
      // false}), sql::SelectedColumn({"Update Time", "updated_at", "", "t",
      // sql::PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  });

  // auto m = sql::ObjectIdentifier("material", "metal", "m");
  // auto u1 = sql::ObjectIdentifier("entity", "entity_user", "u1");
  // auto u2 = sql::ObjectIdentifier("entity", "entity_user", "u2");

  query.setJoins({
      // sql::Join("left", m, "t.material_id = m.id"),
      // sql::Join("left", u1, "t.create_user_id = u1.id"),
      // sql::Join("left", u2, "t.update_user_id = u2.id"),
  });
}

nlohmann::json CertifiedBy::ins(nlohmann::json event, nlohmann::json args) {
  return query.insBase(event, args, "slug, name, title, description",
                       "$1, $2, $3, $4", args[0]["slug"].get<std::string>(),
                       args[0]["name"].get<std::string>(),
                       args[0]["title"].get<std::string>(),
                       args[0]["description"].get<std::string>());
}

nlohmann::json CertifiedBy::upd(nlohmann::json event, nlohmann::json args) {
  return query.updBase(event, args, "slug, name, title, description",
                       "$1, $2, $3, $4", args[0]["slug"].get<std::string>(),
                       args[0]["name"].get<std::string>(),
                       args[0]["title"].get<std::string>(),
                       args[0]["description"].get<std::string>());
}

}  // namespace service
}  // namespace jadmin
