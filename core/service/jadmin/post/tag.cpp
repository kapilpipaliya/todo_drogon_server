#include "tag.h"

#include <utility>
#include "../../../strfns.h"
#include "../../dba.h"
using namespace jadmin;

Tag::Tag(JAdminContextPtr context_) : context(std::move(context_)) {
  getQuery() = sqlb::Query(sqlb::ObjectIdentifier("post", "tag", "t"));
}

void Tag::setupTable() {
  // m_query.setRowIdColumn("id");
  getQuery().setSelectedColumns({
      sqlb::SelectedColumn({"Id", "id", "", "t", PG_TYPES::INT8, false}),
      sqlb::SelectedColumn({"Slug", "slug", "", "t", PG_TYPES::TEXT, true}),
      sqlb::SelectedColumn({"Name", "name", "", "t", PG_TYPES::TEXT, true}),
      sqlb::SelectedColumn(
          {"Description", "description", "", "t", PG_TYPES::TEXT, true}),
      // sqlb::SelectedColumn({"Created By", "create_user_id", "", "t",
      // PG_TYPES::INT8, true, 1, 0, false}),
      // sqlb::SelectedColumn({"u1_username", "username", "", "u1",
      // PG_TYPES::TEXT, false, 0, 0, false}), sqlb::SelectedColumn({"Updated
      // By", "update_user_id", "", "t", PG_TYPES::INT8, true, 1, 0, false}),
      // sqlb::SelectedColumn({"u2_username", "username", "", "u2",
      // PG_TYPES::TEXT, false, 0, 0, false}), sqlb::SelectedColumn({"Create
      // Time", "inserted_at", "", "t", PG_TYPES::TIMESTAMP, true, 0, 0,
      // false}), sqlb::SelectedColumn({"Update Time", "updated_at", "", "t",
      // PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  });

  auto m = sqlb::ObjectIdentifier("material", "metal", "m");
  // auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
  // auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

  getQuery().setJoins({
      // sqlb::Join("left", m, "a.material_id = m.id"),
      // sqlb::Join("left", u1, "gt.create_user_id = u1.id"),
      // sqlb::Join("left", u2, "a.update_user_id = u2.id"),
  });
}

nlohmann::json Tag::ins(nlohmann::json event, nlohmann::json args) {
  auto product_table = sqlb::ObjectIdentifier("post", "tag", "t");

  std::string strSql =
      "INSERT INTO %1.%2 (slug, name, description) values($1, $2, $3)";
  ReplaceAll2(strSql, "%1", product_table.schema());
  ReplaceAll2(strSql, "%2", product_table.name());

  auto clientPtr = drogon::app().getDbClient("sce");
  auto transPtr = clientPtr->newTransaction();
  try {
    Dba::writeInTrans(transPtr, strSql, args[0]["slug"].get<std::string>(),
                      args[0]["name"].get<std::string>(),
                      args[0]["description"].get<std::string>());

    nlohmann::json ret;
    ret[0] = simpleJsonSaveResult(event, true, "Done");
    return ret;
  } catch (const std::exception &e) {
    SPDLOG_TRACE(e.what());
    nlohmann::json ret;
    ret[0] = simpleJsonSaveResult(event, false, e.what());
    return ret;
  }
}
nlohmann::json Tag::upd(nlohmann::json event, nlohmann::json args) {
  auto product_table = sqlb::ObjectIdentifier("post", "tag", "t");

  if (args[0]["id"].get<long>()) {
    std::string strSql =
        "update %1.%2 set "
        "(slug, name, description)"
        " = ROW($2, $3, $4) where id=$1";
    ReplaceAll2(strSql, "%1", product_table.schema());
    ReplaceAll2(strSql, "%2", product_table.name());

    auto clientPtr = drogon::app().getDbClient("sce");
    auto transPtr = clientPtr->newTransaction();
    try {
      Dba::writeInTrans(transPtr, strSql, args[0]["id"].get<long>(),
                        args[0]["slug"].get<std::string>(),
                        args[0]["name"].get<std::string>(),
                        args[0]["description"].get<std::string>());

      nlohmann::json ret;
      ret[0] = simpleJsonSaveResult(event, true, "Done");
      return ret;
    } catch (const std::exception &e) {
      SPDLOG_TRACE(e.what());
      nlohmann::json ret;
      ret[0] = simpleJsonSaveResult(event, false, e.what());
      return ret;
    }
  }
  nlohmann::json ret;
  ret[0] = simpleJsonSaveResult(event, false, "Not Valid Structure");
  return ret;
}
