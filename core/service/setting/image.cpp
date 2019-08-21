#include "image.h"
#include <boost/filesystem.hpp>
#include "../../strfns.h"
#include "../../jsonfns.h"
#include "../auth/auth.h"

#include <drogon/WebSocketController.h>

Image::Image(const WebSocketConnectionPtr& wsConnPtr_): BaseService(wsConnPtr_)
{
    t.m_table = sqlb::ObjectIdentifier("setting", "image", "a");

}

void Image::setupTable()
{
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "a", PG_TYPES::INT8, true}),
            sqlb::SelectedColumn({"Collection", "image_collection_id", "", "a", PG_TYPES::INT8, true, 1, 1}),sqlb::SelectedColumn({"Name", "name", "", "c", PG_TYPES::TEXT, false}),
            sqlb::SelectedColumn({"Position", "position", "", "a", PG_TYPES::INT4, true}),
            sqlb::SelectedColumn({"Title", "title", "", "a", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Url", "url", "", "a", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Description", "description", "", "a", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Name", "name", "", "a", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Size", "size", "", "a", PG_TYPES::INT8, true}),
            sqlb::SelectedColumn({"Type", "type", "", "a", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Version", "version", "", "a", PG_TYPES::TEXT, false}),
            //sqlb::SelectedColumn({"Created By", "create_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            //sqlb::SelectedColumn({"Updated By", "update_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Create Time", "inserted_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            sqlb::SelectedColumn({"Update Time", "updated_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };

        auto c = sqlb::ObjectIdentifier("setting", "image_collection", "c");
    //auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
    //auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {
            sqlb::Join("left", c, "c.id = a.image_collection_id"),
            //sqlb::Join("left", u1, "gt.create_user_id = u1.id"),
            //sqlb::Join("left", u2, "a.update_user_id = u2.id"),
};
}

Json::Value Image::handleEvent(Json::Value event, int next, Json::Value args)
{
    auto event_cmp = event[next].asString();
    if(event_cmp  == "data"){
        return allData(event, args);
    } else if (event_cmp  == "header") {
        return headerData(event, args);
    } else if (event_cmp  == "ins") {
        return ins(event, args);
    } else if (event_cmp  == "upd") {
        return upd(event, args);
    } else if (event_cmp  == "del") {
        return del(event, args);
    } else if (event_cmp  == "thumb_data") {
        return thumb_data(event, args);
    } else {
        return Json::nullValue;
    }
}

Json::Value Image::handleBinaryEvent(Json::Value event, int next, std::string &message)
{
    if(event[next].asString()  == "save_attachment_data"){
        return save_setting_attachment(event, message);
    } else {
        return Json::nullValue;
    }
}

// this is normal images..
Json::Value Image::ins( Json::Value event, Json::Value args) {
    auto metal_purity_table = sqlb::ObjectIdentifier("setting", "image", "c");
    std::string t = "setting.image";
    std::string c = "image_collection_id, name, size, type, title, description, url, position";
    std::string strSqlTempImage = "SELECT name, size, type FROM setting.temp_image_id WHERE id = $1";
    std::string strSqlTempImageDel = "DELETE FROM setting.temp_image_id WHERE id = $1";

    std::string strSql = "INSERT INTO " + t + " (" + c + ") values(NULLIF($1,0), $2, $3, $4, $5, $6, $7, $8)";
    auto transPtr = clientPtr->newTransaction();
    try {
        auto temp_id = args["temp_id"].asInt();
        if (temp_id != 0) {
            auto z = transPtr->execSqlSync(strSqlTempImage, temp_id);
            if (z.size() == 1) {
                transPtr->execSqlSync(strSql, args["image_collection_id"].asInt(), z[0]["name"].c_str(), z[0]["size"].as<int>(),z[0]["type"].c_str(), args["title"].asString(), args["description"].asString(), args["url"].asString(), args["position"].asInt());
                transPtr->execSqlSync(strSqlTempImageDel, temp_id);
            }
        } else {
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, "Please Upload Image"); return ret;
        }

        
        Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
    } catch (const std::exception &e) {
        
        std::cerr << e.what() << std::endl;
        Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
    }
}
// this is normal images..
Json::Value Image::upd( Json::Value event, Json::Value args) {
    auto metal_purity_table = sqlb::ObjectIdentifier("setting", "image", "c");
    std::string t = "setting.image";
    std::string c = "image_collection_id, name, size, type, title, description, url, position";
    std::string strSqlTempImage = "SELECT name, size, type FROM setting.temp_image_id WHERE id = $1";
    std::string strSqlTempImageDel = "DELETE FROM setting.temp_image_id WHERE id = $1";

    if (args["id"].asInt()) {
        std::string strSql = "update " + t + " set (" + c + ", version) = ROW(NULLIF($2, 0), $3, $4, $5, $6, $7, $8, $9, version + 1) where id=$1" ;
        auto transPtr = clientPtr->newTransaction();
        try {
            auto temp_id = args["temp_id"].asInt();
            if (temp_id != 0) {
                auto z = transPtr->execSqlSync(strSqlTempImage, temp_id);
                if (z.size() == 1) {
                    transPtr->execSqlSync(strSql, args["id"].asInt64(), args["image_collection_id"].asInt(), z[0]["name"].c_str(), z[0]["size"].as<int>(),z[0]["type"].c_str(), args["title"].asString(), args["description"].asString(), args["url"].asString(), args["position"].asInt());
                    transPtr->execSqlSync(strSqlTempImageDel, temp_id);
                }
            } else {
                transPtr->execSqlSync("UPDATE setting.image SET (title, description, url, position, version) = ROW($2, $3, $4, $5, version + 1) WHERE id = $1", args["id"].asInt64(), args["title"].asString(), args["description"].asString(), args["url"].asString(), args["position"].asInt());
            }
            

            Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
        } catch (const std::exception &e) {
            
            std::cerr << e.what() << std::endl;
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
        }
    }
}

Json::Value Image::thumb_data( Json::Value event, Json::Value args)
{
    // send meta_data
    Json::Value batch;
    Json::Value ret;

    Json::Value data1;
    data1[0] = "take_image_meta";
    ret[0] = data1;
    ret[1] = event;

    batch[0] = ret;
    wsConnPtr->send(batch.toStyledString());

    namespace fs = boost::filesystem;
    auto home = fs::path(getenv("HOME"));

    auto transPtr = clientPtr->newTransaction();
    try {
        auto sql = "SELECT name FROM setting.image WHERE id = $1";
        auto x = transPtr->execSqlSync(sql, args.asInt());
        
        if (x.size() == 1) {
            std::streampos size;
            // http://www.cplusplus.com/doc/tutorial/files/
            // What is the best way to read an entire file into a std::string in C++?
            // https://stackoverflow.com/questions/116038/what-is-the-best-way-to-read-an-entire-file-into-a-stdstring-in-c/116220#116220
            std::ifstream file(home.string() + "/fileuploads/" + x[0]["name"].c_str(), std::ios::in | std::ios::binary | std::ios::ate);
            if (file.is_open()) {
                auto memblock = read_all(file);
                file.close();

                //std::cout << "the entire file content is in memory";
                wsConnPtr->send(memblock, WebSocketMessageType::Binary); // Note when server not able to send this file, front end crash.
                //delete[] memblock;
            }
        } else {
            // Fix simpleJsonSaveResult(event, true, "Done");
        }
        return Json::Value(Json::nullValue);
    } catch (const std::exception &e) {
        
        std::cerr << e.what() << std::endl;
        //simpleJsonSaveResult(event, false, e.what());
        return Json::Value(Json::nullValue);
    }

    //get binary data and send.
}
// save image in disk and return temporary id:
Json::Value Image::save_setting_attachment(Json::Value event, std::string &message)
{
    auto session_id = getAdminContext(wsConnPtr);
    auto strSql = sel_("user1.temp_image", "event,  name, size, type", "where session_id = $1");
    auto transPtr = clientPtr->newTransaction();
    try {
        auto r = transPtr->execSqlSync(strSql, session_id);
        transPtr->execSqlSync(dele_("user1.temp_image", "where session_id = $1"), session_id);

        // check if file exist else rename a file
        // convert this to json
        Json::Value event_json;
        std::stringstream txt;
        txt <<  r[0]["temp_image"].c_str();
        Json::CharReaderBuilder rbuilder;
        rbuilder["collectComments"] = false;
        std::string errs;
        bool ok = Json::parseFromStream(rbuilder, txt, &event_json, &errs);
        (void)ok;

        namespace fs = boost::filesystem;
        auto home = fs::path(getenv("HOME"));

        std::string name = r[0][1].c_str();
        auto size = r[0][2].as<int>();
        auto type = r[0][3].c_str();


        fprintf(stdout, "%s %d %s\n", name.c_str(), size, type);
        fflush(stdout);

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
        auto temp_image_table = sqlb::ObjectIdentifier("setting", "temp_image_id", "pa");
        std::string strSql = "INSERT INTO %1.%2 (name, size, type) VALUES ($1, $2, $3) RETURNING id";
        ReplaceAll2(strSql, "%1", temp_image_table.schema());
        ReplaceAll2(strSql, "%2", temp_image_table.name());

        Json::Value ret;
        Json::Value jresult;
        jresult[0] = event_json;
        auto insert_result = transPtr->execSqlSync(strSql, name, size, type);
        jresult[1] = insert_result[0]["id"].as<int>();
        //jresult[1] = e.what();
        ret[0] = jresult;
        
        return ret;

    } catch (const std::exception &e) {
        
        std::cerr << e.what() << std::endl;
        return Json::nullValue;
    }

}
