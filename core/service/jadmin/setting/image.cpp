#include "image.h"

#include <utility>
#include "../../../sql/dba.h"

namespace jewel {
namespace service {
Image::Image(std::shared_ptr<websocket::jewel::JAdminContext> context_)
    : context(std::move(context_)) {
  query = sql::Query(sql::ObjectIdentifier("post", "image", "a"));
  setupTable();
}

void Image::setupTable() {
  // m_query.setRowIdColumn("id");
  query.setSelectedColumns({
      sql::SelectedColumn({"Id", "id", "", "a", sql::PG_TYPES::INT8, true}),
      sql::SelectedColumn({"Collection", "image_collection_id", "", "a",
                           sql::PG_TYPES::INT8, true, 1, 1}),
      sql::SelectedColumn(
          {"Name", "name", "", "c", sql::PG_TYPES::TEXT, false}),
      sql::SelectedColumn(
          {"Position", "position", "", "a", sql::PG_TYPES::INT4, true}),
      sql::SelectedColumn(
          {"Title", "title", "", "a", sql::PG_TYPES::TEXT, true}),
      sql::SelectedColumn({"Url", "url", "", "a", sql::PG_TYPES::TEXT, true}),
      sql::SelectedColumn(
          {"Description", "description", "", "a", sql::PG_TYPES::TEXT, true}),
      sql::SelectedColumn({"Name", "name", "", "a", sql::PG_TYPES::TEXT, true}),
      sql::SelectedColumn({"Size", "size", "", "a", sql::PG_TYPES::INT8, true}),
      sql::SelectedColumn({"Type", "type", "", "a", sql::PG_TYPES::TEXT, true}),
      sql::SelectedColumn(
          {"Version", "version", "", "a", sql::PG_TYPES::TEXT, false}),
      // sql::SelectedColumn({"Created By", "create_user_id", "", "a",
      // sql::PG_TYPES::INT8, true, 1, 0, false}),
      // sql::SelectedColumn({"u1_username", "username", "", "u1",
      // sql::PG_TYPES::TEXT, false, 0, 0, false}),
      // sql::SelectedColumn({"Updated By", "update_user_id", "", "a",
      // sql::PG_TYPES::INT8, true, 1, 0, false}),
      // sql::SelectedColumn({"u2_username", "username", "", "u2",
      // sql::PG_TYPES::TEXT, false, 0, 0, false}),
      sql::SelectedColumn({"Create Time", "inserted_at", "", "a",
                           sql::PG_TYPES::TIMESTAMP, true, 0, 0, false}),
      sql::SelectedColumn({"Update Time", "updated_at", "", "a",
                           sql::PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  });

  auto c = sql::ObjectIdentifier("post", "image_collection", "c");
  // auto u1 = sql::ObjectIdentifier("entity", "entity_user", "u1");
  // auto u2 = sql::ObjectIdentifier("entity", "entity_user", "u2");

  query.setJoins({
      sql::Join("left", c, "c.id = a.image_collection_id"),
      // sql::Join("left", u1, "gt.create_user_id = u1.id"),
      // sql::Join("left", u2, "a.update_user_id = u2.id"),
  });
}

nlohmann::json Image::handleEvent(nlohmann::json event, int next,
                                  const nlohmann::json &args) {
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

// this is normal images..
nlohmann::json Image::ins(nlohmann::json event, nlohmann::json args) {
  auto metal_purity_table = sql::ObjectIdentifier("post", "image", "c");
  std::string t = "post.image";
  std::string c =
      "image_collection_id, name, size, type, title, description, url, "
      "position";

  std::string strSqlTempImage =
      "SELECT name, size, type FROM entity.temp_image_id WHERE id = $1";
  std::string strSqlTempImageDel =
      "DELETE FROM entity.temp_image_id WHERE id = $1";

  std::string strSql =
      "INSERT INTO " + t + " (" + c +
      ") values(NULLIF($1,0::bigint), $2, $3, $4, $5, $6, $7, $8)";
  auto clientPtr = drogon::app().getDbClient("sce");
  auto transPtr = clientPtr->newTransaction();
  try {
    auto temp_id = args[0]["temp_id"].get<long>();
    if (temp_id != 0) {
      auto z = sql::Dba::writeInTrans(transPtr, strSqlTempImage, temp_id);
      if (z.size() == 1) {
        sql::Dba::writeInTrans(
            transPtr, strSql, args[0]["image_collection_id"].get<long>(),
            z[0]["name"].c_str(), z[0]["size"].as<long>(), z[0]["type"].c_str(),
            args[0]["title"].get<std::string>(),
            args[0]["description"].get<std::string>(),
            args[0]["url"].get<std::string>(), args[0]["position"].get<int>());
        sql::Dba::writeInTrans(transPtr, strSqlTempImageDel, temp_id);
      }
    } else {
      nlohmann::json ret;
      ret[0] = websocket::WsFns::successJsonObject(event, false,
                                                   "Please Upload Image");
      return ret;
    }

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
// this is normal images..
nlohmann::json Image::upd(nlohmann::json event, nlohmann::json args) {
  auto metal_purity_table = sql::ObjectIdentifier("post", "image", "c");
  std::string t = "post.image";
  std::string c =
      "image_collection_id, name, size, type, title, description, url, "
      "position";
  std::string strSqlTempImage =
      "SELECT name, size, type FROM entity.temp_image_id WHERE id = $1";
  std::string strSqlTempImageDel =
      "DELETE FROM entity.temp_image_id WHERE id = $1";

  if (args[0]["id"].get<long>()) {
    std::string strSql = "update " + t + " set (" + c +
                         ", version) = ROW(NULLIF($2, 0::bigint), $3, $4, $5, "
                         "$6, $7, $8, $9, version + 1) where id=$1";
    auto clientPtr = drogon::app().getDbClient("sce");
    auto transPtr = clientPtr->newTransaction();
    try {
      auto temp_id =
          args[0]["temp_id"].is_null() ? 0 : args[0]["temp_id"].get<long>();
      if (temp_id != 0) {
        auto z = sql::Dba::writeInTrans(transPtr, strSqlTempImage, temp_id);
        if (z.size() == 1) {
          sql::Dba::writeInTrans(transPtr, strSql, args[0]["id"].get<long>(),
                                 args[0]["image_collection_id"].get<long>(),
                                 z[0]["name"].c_str(), z[0]["size"].as<long>(),
                                 z[0]["type"].c_str(),
                                 args[0]["title"].get<std::string>(),
                                 args[0]["description"].get<std::string>(),
                                 args[0]["url"].get<std::string>(),
                                 args[0]["position"].get<int>());
          sql::Dba::writeInTrans(transPtr, strSqlTempImageDel, temp_id);
        }
      } else {
        sql::Dba::writeInTrans(
            transPtr,
            "UPDATE post.image SET (title, description, url, position, "
            "version) = ROW($2, $3, $4, $5, version + 1) WHERE id = $1",
            args[0]["id"].get<long>(), args[0]["title"].get<std::string>(),
            args[0]["description"].get<std::string>(),
            args[0]["url"].get<std::string>(), args[0]["position"].get<int>());
      }

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
}  // namespace jadmin
