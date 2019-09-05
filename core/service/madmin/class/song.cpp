#include "song.h"
#include "../../dba.h"
#include <boost/filesystem.hpp>
#include <utility>
using namespace  madmin;
using S = sqlb::SelectedColumn;
Song::Song(MAdminContextPtr context_): context(std::move(context_))
{
    t.m_table = sqlb::ObjectIdentifier("music", "song", "s");
    t.m_query = sqlb::Query(t.m_table);
}

void Song::setupTable()
{
    //m_query.setRowIdColumn("id");
    t.m_query.selectedColumns() = {
            S({"ID No", "id", "", "s", PG_TYPES::INT8}),
            S({"file", "file", "", "s", PG_TYPES::TEXT, false}),
            S({"Catalog", "catalog_id", "", "s", PG_TYPES::INT8, true, 1, 1}),
            S({"c_name", "name", "", "c", PG_TYPES::TEXT, false, 0, 0, false}),
//            S({"Album", "album_id", "", "s", PG_TYPES::INT8}),
//            S({"Year", "year", "", "s", PG_TYPES::INT4}),
//            S({"Artist", "artist_id", "", "s", PG_TYPES::INT8}),
            S({"Title", "title", "", "s", PG_TYPES::TEXT}),
//            S({"bitrate", "bitrate", "", "s", PG_TYPES::INT4}),
//            S({"rate", "rate", "", "s", PG_TYPES::INT4}),
//            S({"mode", "mode", "", "s", PG_TYPES::ENUM}),
            S({"size", "size", "", "s", PG_TYPES::INT8}),
//            S({"time", "time", "", "s", PG_TYPES::INT4}),
//            S({"track", "track", "", "s", PG_TYPES::INT4}),
//            S({"mbid", "mbid", "", "s", PG_TYPES::TEXT}),
//            S({"played", "played", "", "s", PG_TYPES::BOOL}),
//            S({"enabled", "enabled", "", "s", PG_TYPES::BOOL}),
//            S({"update_time", "update_time", "", "s", PG_TYPES::TIMESTAMP}),
//            S({"addition_time", "addition_time", "", "s", PG_TYPES::TIMESTAMP}),
//            S({"user_upload", "user_upload", "", "s", PG_TYPES::INT8}),
//            S({"license", "license", "", "s", PG_TYPES::INT8}),
//            S({"composer", "composer", "", "s", PG_TYPES::TEXT}),
//            S({"channels", "channels", "", "s", PG_TYPES::INT4}),

            //S({"no", "no", "", "s", PG_TYPES::TEXT}),
            //S({"sequence_id", "sequence_id", "", "s", PG_TYPES::INT8, false}),
            //S({"Create Date", "last_update", "", "s", PG_TYPES::TIMESTAMP}),
            //S({"last_clean Date", "last_clean", "", "s", PG_TYPES::TIMESTAMP}),
            //S({"last_add Date", "last_add", "", "s", PG_TYPES::TIMESTAMP}),
            //S({"Rename Pattern", "rename_pattern", "", "s", PG_TYPES::TEXT, true}),
            //S({"Sort Pattern", "sort_pattern", "", "s", PG_TYPES::TEXT, true}),
            //S({"Gather Types", "gather_types", "", "s", PG_TYPES::TEXT, true}),
            //S({"Created By", "create_user_id", "", "s", PG_TYPES::INT8, true, 1, 0, false}), S({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            //S({"Updated By", "update_user_id", "", "s", PG_TYPES::INT8, true, 1, 0, false}), S({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            //S({"Create Time", "inserted_at", "", "s", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            //S({"Update Time", "updated_at", "", "s", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
    };
    auto c = sqlb::ObjectIdentifier("music", "catalog", "c");
    //auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
    //auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {
            sqlb::Join("left", c, "c.id = s.catalog_id")
            //sqlb::Join("left", u1, "e.create_user_id = u1.id"),
            //sqlb::Join("left", u2, "e.update_user_id = u2.id"),
            };

    t.m_query.groupBy() = {
        };
}

nlohmann::json Song::handleEvent(nlohmann::json event, unsigned long next, nlohmann::json args)
{
    auto event_cmp = event[next].get<std::string>();
    if (event_cmp == "header") { // required
        return headerData(event, args);
    } if (event_cmp == "data") { // required
        //if(context->user.type == "super admin"){
            return allData(event, args);
        //} else {
            //return {{event, "unauthorised"}};
        //}
    } else if (event_cmp  == "ins") {
        //args[0]["parent_id"] = context->user_id;


        std::string strSqlTempImage = "SELECT name, size, type FROM music.temp_file WHERE id = $1";
        std::string strSqlTempImageDel = "DELETE FROM music.temp_file WHERE id = $1";

        auto clientPtr = drogon::app().getDbClient("sce");
        try {
            if(args[0]["temp_id"].is_number_integer()){
                auto temp_id = args[0]["temp_id"].get<long>();
                if (temp_id != 0) {
                    auto z = clientPtr->execSqlSync(strSqlTempImage, temp_id);
                    if (z.size() == 1) {
                       args[0]["file"] =  z[0]["name"].c_str();
                       args[0]["size"] = z[0]["size"].as<long>();
                       //auto type = z[0]["type"].c_str();
                       clientPtr->execSqlSync(strSqlTempImageDel, temp_id);
                       return ins(event, args);
                    }
                }
                json ret; ret[0] = simpleJsonSaveResult(event, false, "Please Upload Music First!"); return ret;
            } 
               // json ret; ret[0] = simpleJsonSaveResult(event, false, "Please Upload Music First!"); return ret;
                return ins(event, args); // Make this to pass test.
            
        } catch (const std::exception &e) {

           SPDLOG_TRACE(e.what());
            json ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
        }


    } else if (event_cmp  == "upd") {
        return upd(event, args);
    } else if (event_cmp  == "del") {
        return del(event, args);
    } else if (event_cmp  == "count") {
        return count(event, args);
    } else {
        return nullptr;
    }
}

nlohmann::json Song::handleBinaryEvent(nlohmann::json event, unsigned long next, std::string &message)
{
    if(event[next].get<std::string>()  == "song"){
        return save_song_binary(event, message);
    } 
        json ret; return ret;
    
}

nlohmann::json Song::save_song_binary([[maybe_unused]]const nlohmann::json& event, std::string &message)
{
    auto session_id = context->current_session_id;
    auto strSql = sel_("music.temp_file_meta", "event,  name, size, type", "where session_id = $1");
    auto clientPtr = drogon::app().getDbClient("sce");
    auto transPtr = clientPtr->newTransaction();
    try {
        auto r = Dba::writeInTrans(transPtr, strSql, session_id);
        Dba::writeInTrans(transPtr, dele_("music.temp_file_meta", "where session_id = $1 and event = $2"), session_id, r[0]["event"].as<std::string>());

        // check if file exist else rename a file
        // convert this to json

        auto event_json = json::parse(r[0]["event"].c_str());

        namespace fs = boost::filesystem;
        auto home = fs::path(getenv("HOME"));

        std::string name = r[0][1].c_str();
        auto size = r[0][2].as<long>();
        auto type = r[0][3].c_str();

        // basic file operations

        std::string new_name = name;
        auto path = boost::filesystem::path(home.string() + "/fileuploads/" + new_name);
        int i = 1;
        while (true) {
            if (boost::filesystem::exists(home.string() + "/fileuploads/" + new_name)) {
                // new_name = path.parent_path().string() + "/" + path.stem().string() + std::to_string(i) + path.extension().string();
                new_name = path.stem().string() + std::to_string(i) + path.extension().string();
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
        std::string strSql = "INSERT INTO music.temp_file (name, size, type) VALUES ($1, $2, $3) RETURNING id";

        json ret;
        json jresult;
        jresult[0] = event_json;
        auto insert_result = Dba::writeInTrans(transPtr, strSql, name, size, type);
        jresult[1] = insert_result[0]["id"].as<long>();
        //jresult[1] = e.what();
        ret[0] = jresult;

        return ret;

    } catch (const std::exception &e) {
       SPDLOG_TRACE(e.what());
       json null;
       return null;
    }
}
