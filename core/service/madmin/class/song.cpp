#include "song.h"
#include <boost/filesystem.hpp>
#include <utility>
#include "../../dba.h"

madmin::Song::Song(std::shared_ptr<MAdminContext> context_) : context(std::move(context_)) {
  query = sqlb::Query(sqlb::ObjectIdentifier("music", "song", "s"));
  setupTable();
}

void madmin::Song::setupTable() {
  // m_query.setRowIdColumn("id");
  query.setSelectedColumns({
      sqlb::SelectedColumn({"ID No", "id", "", "s", PG_TYPES::INT8}),
      sqlb::SelectedColumn({"file", "file", "", "s", PG_TYPES::TEXT, false}),
      sqlb::SelectedColumn(
          {"Catalog", "catalog_id", "", "s", PG_TYPES::INT8, true, 1, 1}),
      sqlb::SelectedColumn(
          {"c_name", "name", "", "c", PG_TYPES::TEXT, false, 0, 0, false}),
      //            sqlb::SelectedColumn({"Album", "album_id", "", "s",
      //            PG_TYPES::INT8}), sqlb::SelectedColumn({"Year", "year", "",
      //            "s", PG_TYPES::INT4}), sqlb::SelectedColumn({"Artist",
      //            "artist_id", "", "s", PG_TYPES::INT8}),
      sqlb::SelectedColumn({"Title", "title", "", "s", PG_TYPES::TEXT}),
      //            sqlb::SelectedColumn({"bitrate", "bitrate", "", "s",
      //            PG_TYPES::INT4}), sqlb::SelectedColumn({"rate", "rate", "",
      //            "s", PG_TYPES::INT4}), sqlb::SelectedColumn({"mode", "mode",
      //            "", "s", PG_TYPES::ENUM}),
      sqlb::SelectedColumn({"size", "size", "", "s", PG_TYPES::INT8}),
      //            sqlb::SelectedColumn({"time", "time", "", "s",
      //            PG_TYPES::INT4}), sqlb::SelectedColumn({"track", "track",
      //            "", "s", PG_TYPES::INT4}), sqlb::SelectedColumn({"mbid",
      //            "mbid", "", "s", PG_TYPES::TEXT}),
      //            sqlb::SelectedColumn({"played", "played", "", "s",
      //            PG_TYPES::BOOL}), sqlb::SelectedColumn({"enabled",
      //            "enabled", "", "s", PG_TYPES::BOOL}),
      //            sqlb::SelectedColumn({"update_time", "update_time", "", "s",
      //            PG_TYPES::TIMESTAMP}),
      //            sqlb::SelectedColumn({"addition_time", "addition_time",
      //            "", "s", PG_TYPES::TIMESTAMP}),
      //            sqlb::SelectedColumn({"user_upload", "user_upload", "", "s",
      //            PG_TYPES::INT8}), sqlb::SelectedColumn({"license",
      //            "license", "", "s", PG_TYPES::INT8}),
      //            sqlb::SelectedColumn({"composer", "composer", "", "s",
      //            PG_TYPES::TEXT}), sqlb::SelectedColumn({"channels",
      //            "channels", "", "s", PG_TYPES::INT4}),

      // sqlb::SelectedColumn({"no", "no", "", "s", PG_TYPES::TEXT}),
      // sqlb::SelectedColumn({"sequence_id", "sequence_id", "", "s",
      // PG_TYPES::INT8, false}), sqlb::SelectedColumn({"Create Date",
      // "last_update", "", "s", PG_TYPES::TIMESTAMP}),
      // sqlb::SelectedColumn({"last_clean Date", "last_clean", "", "s",
      // PG_TYPES::TIMESTAMP}), sqlb::SelectedColumn({"last_add Date",
      // "last_add", "", "s", PG_TYPES::TIMESTAMP}),
      // sqlb::SelectedColumn({"Rename Pattern", "rename_pattern", "", "s",
      // PG_TYPES::TEXT, true}), sqlb::SelectedColumn({"Sort Pattern",
      // "sort_pattern", "", "s", PG_TYPES::TEXT, true}),
      // sqlb::SelectedColumn({"Gather Types", "gather_types", "", "s",
      // PG_TYPES::TEXT, true}), sqlb::SelectedColumn({"Created By",
      // "create_user_id", "", "s", PG_TYPES::INT8, true, 1, 0, false}),
      // sqlb::SelectedColumn({"u1_username", "username", "", "u1",
      // PG_TYPES::TEXT, false, 0, 0, false}), sqlb::SelectedColumn({"Updated
      // By", "update_user_id", "", "s", PG_TYPES::INT8, true, 1, 0, false}),
      // sqlb::SelectedColumn({"u2_username", "username", "", "u2",
      // PG_TYPES::TEXT, false, 0, 0, false}), sqlb::SelectedColumn({"Create
      // Time", "inserted_at", "", "s", PG_TYPES::TIMESTAMP, true, 0, 0,
      // false}), sqlb::SelectedColumn({"Update Time", "updated_at", "", "s",
      // PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  });
  auto c = sqlb::ObjectIdentifier("music", "catalog", "c");
  // auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
  // auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

  query.setJoins({
      sqlb::Join("left", c, "c.id = s.catalog_id")
      // sqlb::Join("left", u1, "e.create_user_id = u1.id"),
      // sqlb::Join("left", u2, "e.update_user_id = u2.id"),
  });
}

nlohmann::json madmin::Song::handleEvent(nlohmann::json event,
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
        ret[0] =
            simpleJsonSaveResult(event, false, "Please Upload Music First!");
        return ret;
      }
      // nlohmann::json ret; ret[0] = simpleJsonSaveResult(event, false, "Please
      // Upload Music First!"); return ret;
      return query.ins(event, args);  // Make this to pass test.

    } catch (const std::exception &e) {
      SPDLOG_TRACE(e.what());
      nlohmann::json ret;
      ret[0] = simpleJsonSaveResult(event, false, e.what());
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

nlohmann::json madmin::Song::handleBinaryEvent(nlohmann::json event,
                                               unsigned long next,
                                               std::string &message) {
  if (event[next].get<std::string>() == "song") {
    return save_song_binary(event, message);
  }
  nlohmann::json ret;
  return ret;
}

nlohmann::json madmin::Song::save_song_binary(
    [[maybe_unused]] const nlohmann::json &event, std::string &message) {
  auto session_id = context->sessionId();
  auto strSql = sel_("music.temp_file_meta", "event,  name, size, type",
                     "where session_id = $1");
  auto clientPtr = drogon::app().getDbClient("sce");
  auto transPtr = clientPtr->newTransaction();
  try {
    auto r = Dba::writeInTrans(transPtr, strSql, session_id);
    Dba::writeInTrans(
        transPtr,
        dele_("music.temp_file_meta", "where session_id = $1 and event = $2"),
        session_id, r[0]["event"].as<std::string>());

    // check if file exist else rename a file
    // convert this to json

    auto event_json = nlohmann::json::parse(r[0]["event"].c_str());

    namespace fs = boost::filesystem;
    auto home = fs::path(getenv("HOME"));

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
    auto insert_result = Dba::writeInTrans(transPtr, strSql, name, size, type);
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
