#include "song.h"
#include <boost/filesystem.hpp>
#include <utility>
#include "../../../sql/dba.h"

music::service::Song::Song(
    std::shared_ptr<websocket::music::MAdminContext> context_)
    : context(std::move(context_)) {
  query = sql::Query(sql::ObjectIdentifier("music", "song", "s"));
  setupTable();
}

void music::service::Song::setupTable() {
  // m_query.setRowIdColumn("id");
  query.setSelectedColumns({
      sql::SelectedColumn({"ID No", "id", "", "s", sql::PG_TYPES::INT8}),
      sql::SelectedColumn(
          {"file", "file", "", "s", sql::PG_TYPES::TEXT, false}),
      sql::SelectedColumn(
          {"Catalog", "catalog_id", "", "s", sql::PG_TYPES::INT8, true, 1, 1}),
      sql::SelectedColumn(
          {"c_name", "name", "", "c", sql::PG_TYPES::TEXT, false, 0, 0, false}),
      //            sql::SelectedColumn({"Album", "album_id", "", "s",
      //            sql::PG_TYPES::INT8}), sql::SelectedColumn({"Year", "year",
      //            "", "s", sql::PG_TYPES::INT4}),
      //            sql::SelectedColumn({"Artist", "artist_id", "", "s",
      //            sql::PG_TYPES::INT8}),
      sql::SelectedColumn({"Title", "title", "", "s", sql::PG_TYPES::TEXT}),
      //            sql::SelectedColumn({"bitrate", "bitrate", "", "s",
      //            sql::PG_TYPES::INT4}), sql::SelectedColumn({"rate", "rate",
      //            "", "s", sql::PG_TYPES::INT4}), sql::SelectedColumn({"mode",
      //            "mode",
      //            "", "s", sql::PG_TYPES::ENUM}),
      sql::SelectedColumn({"size", "size", "", "s", sql::PG_TYPES::INT8}),
      //            sql::SelectedColumn({"time", "time", "", "s",
      //            sql::PG_TYPES::INT4}), sql::SelectedColumn({"track",
      //            "track",
      //            "", "s", sql::PG_TYPES::INT4}), sql::SelectedColumn({"mbid",
      //            "mbid", "", "s", sql::PG_TYPES::TEXT}),
      //            sql::SelectedColumn({"played", "played", "", "s",
      //            sql::PG_TYPES::BOOL}), sql::SelectedColumn({"enabled",
      //            "enabled", "", "s", sql::PG_TYPES::BOOL}),
      //            sql::SelectedColumn({"update_time", "update_time", "", "s",
      //            sql::PG_TYPES::TIMESTAMP}),
      //            sql::SelectedColumn({"addition_time", "addition_time",
      //            "", "s", sql::PG_TYPES::TIMESTAMP}),
      //            sql::SelectedColumn({"user_upload", "user_upload", "", "s",
      //            sql::PG_TYPES::INT8}), sql::SelectedColumn({"license",
      //            "license", "", "s", sql::PG_TYPES::INT8}),
      //            sql::SelectedColumn({"composer", "composer", "", "s",
      //            sql::PG_TYPES::TEXT}), sql::SelectedColumn({"channels",
      //            "channels", "", "s", sql::PG_TYPES::INT4}),

      // sql::SelectedColumn({"no", "no", "", "s", sql::PG_TYPES::TEXT}),
      // sql::SelectedColumn({"sequence_id", "sequence_id", "", "s",
      // sql::PG_TYPES::INT8, false}), sql::SelectedColumn({"Create Date",
      // "last_update", "", "s", sql::PG_TYPES::TIMESTAMP}),
      // sql::SelectedColumn({"last_clean Date", "last_clean", "", "s",
      // sql::PG_TYPES::TIMESTAMP}), sql::SelectedColumn({"last_add Date",
      // "last_add", "", "s", sql::PG_TYPES::TIMESTAMP}),
      // sql::SelectedColumn({"Rename Pattern", "rename_pattern", "", "s",
      // sql::PG_TYPES::TEXT, true}), sql::SelectedColumn({"Sort Pattern",
      // "sort_pattern", "", "s", sql::PG_TYPES::TEXT, true}),
      // sql::SelectedColumn({"Gather Types", "gather_types", "", "s",
      // sql::PG_TYPES::TEXT, true}), sql::SelectedColumn({"Created By",
      // "create_user_id", "", "s", sql::PG_TYPES::INT8, true, 1, 0, false}),
      // sql::SelectedColumn({"u1_username", "username", "", "u1",
      // sql::PG_TYPES::TEXT, false, 0, 0, false}),
      // sql::SelectedColumn({"Updated By", "update_user_id", "", "s",
      // sql::PG_TYPES::INT8, true, 1, 0, false}),
      // sql::SelectedColumn({"u2_username", "username", "", "u2",
      // sql::PG_TYPES::TEXT, false, 0, 0, false}), sql::SelectedColumn({"Create
      // Time", "inserted_at", "", "s", sql::PG_TYPES::TIMESTAMP, true, 0, 0,
      // false}), sql::SelectedColumn({"Update Time", "updated_at", "", "s",
      // sql::PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  });
  auto c = sql::ObjectIdentifier("music", "catalog", "c");
  // auto u1 = sql::ObjectIdentifier("entity", "entity_user", "u1");
  // auto u2 = sql::ObjectIdentifier("entity", "entity_user", "u2");

  query.setJoins({
      sql::Join("left", c, "c.id = s.catalog_id")
      // sql::Join("left", u1, "e.create_user_id = u1.id"),
      // sql::Join("left", u2, "e.update_user_id = u2.id"),
  });
}

nlohmann::json music::service::Song::handleEvent(nlohmann::json event,
                                                 unsigned long next,
                                                 nlohmann::json args) {
  auto event_cmp = event[next].get<std::string>();
  if (event_cmp == "header") {  // required
    return query.headerData(event, args);
  }
  if (event_cmp == "data") {  // required
                              // if(context->getUser().type == "super admin"){
    return query.allData(event, args);
    //} else {
    // return {{event, "unauthorised"}};
    //}
  } else if (event_cmp == "ins") {
    // args[0]["parent_id"] = context->getUserId();

    std::string strSqlTempImage =
        "SELECT name, size, type FROM music.temp_file WHERE id = $1";
    std::string strSqlTempImageDel =
        "DELETE FROM music.temp_file WHERE id = $1";

    auto clientPtr = drogon::app().getDbClient("sce");
    try {
      if (args[0]["temp_id"].is_number_integer()) {
        auto temp_id = args[0]["temp_id"].get<long>();
        if (temp_id != 0) {
          auto z = clientPtr->execSqlSync(strSqlTempImage, temp_id);
          if (z.size() == 1) {
            args[0]["file"] = z[0]["name"].c_str();
            args[0]["size"] = z[0]["size"].as<long>();
            // auto type = z[0]["type"].c_str();
            clientPtr->execSqlSync(strSqlTempImageDel, temp_id);
            return query.ins(event, args);
          }
        }
        nlohmann::json ret;
        ret[0] = websocket::WsFns::successJsonObject(
            event, false, "Please Upload Music First!");
        return ret;
      }
      // nlohmann::json ret; ret[0] = websocket::WsFns::successJsonObject(event,
      // false, "Please Upload Music First!"); return ret;
      return query.ins(event, args);  // Make this to pass test.

    } catch (const std::exception &e) {
      SPDLOG_TRACE(e.what());
      nlohmann::json ret;
      ret[0] = websocket::WsFns::successJsonObject(event, false, e.what());
      return ret;
    }

  } else if (event_cmp == "upd") {
    return query.upd(event, args);
  } else if (event_cmp == "del") {
    return query.del(event, args);
  } else if (event_cmp == "count") {
    return query.count(event, args);
  } else {
    return nullptr;
  }
}

nlohmann::json music::service::Song::handleBinaryEvent(nlohmann::json event,
                                                       unsigned long next,
                                                       std::string &message) {
  if (event[next].get<std::string>() == "song") {
    return save_song_binary(event, message);
  }
  nlohmann::json ret;
  return ret;
}

nlohmann::json music::service::Song::save_song_binary(
    [[maybe_unused]] const nlohmann::json &event, std::string &message) {
  auto session_id = context->sessionId();
  auto strSql =
      sql::CRUDHelper::sel_("music.temp_file_meta", "event,  name, size, type",
                            "where session_id = $1");
  auto clientPtr = drogon::app().getDbClient("sce");
  auto transPtr = clientPtr->newTransaction();
  try {
    auto r = sql::Dba::writeInTrans(transPtr, strSql, session_id);
    sql::Dba::writeInTrans(
        transPtr,
        sql::CRUDHelper::dele_("music.temp_file_meta",
                               "where session_id = $1 and event = $2"),
        session_id, r[0]["event"].as<std::string>());

    // check if file exist else rename a file
    // convert this to json

    auto event_json = nlohmann::json::parse(r[0]["event"].c_str());

    auto home = boost::filesystem::path(getenv("HOME"));

    std::string name = r[0][1].c_str();
    auto size = r[0][2].as<long>();
    auto type = r[0][3].c_str();

    // basic file operations

    std::string new_name = name;
    auto path =
        boost::filesystem::path(home.string() + "/fileuploads/" + new_name);
    int i = 1;
    while (true) {
      if (boost::filesystem::exists(home.string() + "/fileuploads/" +
                                    new_name)) {
        // new_name = path.parent_path().string() + "/" + path.stem().string() +
        // std::to_string(i) + path.extension().string();
        new_name = path.stem().string() + std::to_string(i) +
                   path.extension().string();
      } else {
        break;
      }
      i++;
    }
    name = new_name;

    std::ofstream myfile;
    myfile.open(home.string() + "/fileuploads/" + name);
    myfile << message;
    myfile.close();

    // Insert Image
    std::string strSql =
        "INSERT INTO music.temp_file (name, size, type) VALUES ($1, $2, $3) "
        "RETURNING id";

    nlohmann::json ret;
    nlohmann::json jresult;
    jresult[0] = event_json;
    auto insert_result =
        sql::Dba::writeInTrans(transPtr, strSql, name, size, type);
    jresult[1] = insert_result[0]["id"].as<long>();
    // jresult[1] = e.what();
    ret[0] = jresult;

    return ret;

  } catch (const std::exception &e) {
    SPDLOG_TRACE(e.what());
    nlohmann::json null;
    return null;
  }
}
