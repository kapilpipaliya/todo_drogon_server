#include "tag.h"

#include <boost/algorithm/string/replace.hpp>
#include <utility>
#include "../../../sql/dba.h"
#include "../../../strfns.h"
namespace jewel {
namespace service {
Tag::Tag(std::shared_ptr<websocket::jewel::JAdminContext> context_)
    : context(std::move(context_)) {
  query = sql::Query(sql::ObjectIdentifier("post", "tag", "t"));
  setupTable();
}

nlohmann::json Tag::handleEvent(nlohmann::json event, unsigned long next,
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

void Tag::setupTable() {
  // m_query.setRowIdColumn("id");
  query.setSelectedColumns({
      sql::SelectedColumn({"Id", "id", "", "t", sql::PG_TYPES::INT8, false}),
      sql::SelectedColumn({"Slug", "slug", "", "t", sql::PG_TYPES::TEXT, true}),
      sql::SelectedColumn({"Name", "name", "", "t", sql::PG_TYPES::TEXT, true}),
      sql::SelectedColumn(
          {"Description", "description", "", "t", sql::PG_TYPES::TEXT, true}),
      // sql::SelectedColumn({"Created By", "create_user_id", "", "t",
      // sql::PG_TYPES::INT8, true, 1, 0, false}),
      // sql::SelectedColumn({"u1_username", "username", "", "u1",
      // sql::PG_TYPES::TEXT, false, 0, 0, false}),
      // sql::SelectedColumn({"Updated By", "update_user_id", "", "t",
      // sql::PG_TYPES::INT8, true, 1, 0, false}),
      // sql::SelectedColumn({"u2_username", "username", "", "u2",
      // sql::PG_TYPES::TEXT, false, 0, 0, false}),
      // sql::SelectedColumn({"Create Time", "inserted_at", "", "t",
      // sql::PG_TYPES::TIMESTAMP, true, 0, 0, false}),
      // sql::SelectedColumn({"Update Time", "updated_at", "", "t",
      // sql::PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  });

  auto m = sql::ObjectIdentifier("material", "metal", "m");
  // auto u1 = sql::ObjectIdentifier("entity", "entity_user", "u1");
  // auto u2 = sql::ObjectIdentifier("entity", "entity_user", "u2");

  query.setJoins({
      // sql::Join("left", m, "a.material_id = m.id"),
      // sql::Join("left", u1, "gt.create_user_id = u1.id"),
      // sql::Join("left", u2, "a.update_user_id = u2.id"),
  });
}

nlohmann::json Tag::ins(nlohmann::json event, nlohmann::json args) {
  auto product_table = sql::ObjectIdentifier("post", "tag", "t");

  std::string strSql =
      "INSERT INTO %1.%2 (slug, name, description) values($1, $2, $3)";
  boost::replace_all(strSql, "%1", product_table.schema());
  boost::replace_all(strSql, "%2", product_table.name());

  auto clientPtr = drogon::app().getDbClient("sce");
  auto transPtr = clientPtr->newTransaction();
  try {
    sql::Dba::writeInTrans(transPtr, strSql, args[0]["slug"].get<std::string>(),
                           args[0]["name"].get<std::string>(),
                           args[0]["description"].get<std::string>());

    nlohmann::json ret;
    ret[0] = websocket::WsFns::successJsonObject(event, true, "Done");
    return ret;
  } catch (const std::exception &e) {
    SPDLOG_TRACE(e.what());
    nlohmann::json ret;
    ret[0] = websocket::WsFns::successJsonObject(event, false, e.what());
    return ret;
  }
}
nlohmann::json Tag::upd(nlohmann::json event, nlohmann::json args) {
  auto product_table = sql::ObjectIdentifier("post", "tag", "t");

  if (args[0]["id"].get<long>()) {
    std::string strSql =
        "update %1.%2 set "
        "(slug, name, description)"
        " = ROW($2, $3, $4) where id=$1";
    boost::replace_all(strSql, "%1", product_table.schema());
    boost::replace_all(strSql, "%2", product_table.name());

    auto clientPtr = drogon::app().getDbClient("sce");
    auto transPtr = clientPtr->newTransaction();
    try {
      sql::Dba::writeInTrans(transPtr, strSql, args[0]["id"].get<long>(),
                             args[0]["slug"].get<std::string>(),
                             args[0]["name"].get<std::string>(),
                             args[0]["description"].get<std::string>());

      nlohmann::json ret;
      ret[0] = websocket::WsFns::successJsonObject(event, true, "Done");
      return ret;
    } catch (const std::exception &e) {
      SPDLOG_TRACE(e.what());
      nlohmann::json ret;
      ret[0] = websocket::WsFns::successJsonObject(event, false, e.what());
      return ret;
    }
  }
  nlohmann::json ret;
  ret[0] =
      websocket::WsFns::successJsonObject(event, false, "Not Valid Structure");
  return ret;
}
}  // namespace service
}  // namespace jewel
