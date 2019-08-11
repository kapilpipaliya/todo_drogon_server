#include "settingsave.h"
#include <boost/filesystem.hpp>
#include "wsfunctions.h"

//delFn(setting, "setting.setting");

delFn(currency, "setting.currency");

delFn(log, "setting.log");

delFn(support, "setting.support");

delFn(image_collection, "setting.image_collection");

delFn(image, "setting.image");
delFn(payment_method, "setting.payment_method");

Json::Value delete_setting(const std::string &event1, const std::string &event2, const std::string &no, const WebSocketConnectionPtr& wsConnPtr, Json::Value in)
{
    pqxx::work txn{DD};
    try {\
        txn.exec_params("DELETE FROM setting.setting WHERE key = $1", in[0].asString());
        txn.commit();
        return simpleJsonSaveResult(event1, event2, no, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
        txn.abort();
        std::cerr << e.what() << std::endl;
        return simpleJsonSaveResult(event1, event2, no, wsConnPtr, false, e.what());
    }
}
Json::Value save_setting(const std::string &event1, const std::string &event2, const std::string &no, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
    // check if key exist
    pqxx::work txn{DD};
    pqxx::result y = txn.exec_params("select key from setting.setting where key = $1", in["key"].asString());
    txn.commit();
    if (y.size() != 0) {
        std::string strSql = "update setting.setting set (value_int, value_num, value_text) = ROW($2, $3, $4) where key=$1";
        pqxx::work txn{DD};
        try {
            txn.exec_params(strSql, in["key"].asString(), in["value_int"].asInt(), in["value_num"].asDouble(), in["value_text"].asString());
            txn.commit();
            return simpleJsonSaveResult(event1, event2, no, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            return simpleJsonSaveResult(event1, event2, no, wsConnPtr, false, e.what());
        }
    } else {
        std::string strSql = "INSERT INTO setting.setting (key, value_int, value_num, value_text, setting_type, setting) values($1, $2, $3, $4, $5, $6)";
        pqxx::work txn{DD};
        try {
            txn.exec_params(strSql, in["key"].asString(), in["value_int"].asInt(), in["value_num"].asDouble(), in["value_text"].asString(), in["setting_type"].asString(), in["setting"].toStyledString());
            txn.commit();
            return simpleJsonSaveResult(event1, event2, no, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            return simpleJsonSaveResult(event1, event2, no, wsConnPtr, false, e.what());
        }
    }
}

Json::Value save_currency(const std::string &event1, const std::string &event2, const std::string &no, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
  printJson(in);
  auto metal_purity_table = sqlb::ObjectIdentifier("setting", "currency", "c");

  if (in["id"].asInt()) {
    std::string strSql =
            "update %1.%2 set (slug, name, symbol, rounding, active) = ROW($2, $3, $4, $5, $6) where id=$1";
    ReplaceAll2(strSql, "%1", metal_purity_table.schema());
    ReplaceAll2(strSql, "%2", metal_purity_table.name());

    pqxx::work txn{DD};
    try {
      txn.exec_params(strSql,
                      in["id"].asInt(),
                      in["slug"].asString(),
                      in["name"].asString(),
                      in["symbol"].asString(),
                      in["rounding"].asDouble(),
                      in["active"].asBool()
      );
      txn.commit();
      return simpleJsonSaveResult(event1, event2, no, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
      txn.abort();
      std::cerr << e.what() << std::endl;
      return simpleJsonSaveResult(event1, event2, no, wsConnPtr, false, e.what());
    }
  } else {
    std::string strSql = "INSERT INTO %1.%2 (slug, name, symbol, rounding, active) values($1, $2, $3, $4, $5)";
    ReplaceAll2(strSql, "%1", metal_purity_table.schema());
    ReplaceAll2(strSql, "%2", metal_purity_table.name());

    pqxx::work txn{DD};
    try {
      txn.exec_params(
              strSql,
              in["slug"].asString(),
              in["name"].asString(),
              in["symbol"].asString(),
              in["rounding"].asDouble(),
              in["active"].asBool()
      );
      txn.commit();
      return simpleJsonSaveResult(event1, event2, no, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
      txn.abort();
      std::cerr << e.what() << std::endl;
      return simpleJsonSaveResult(event1, event2, no, wsConnPtr, false, e.what());
    }
  }
}

save_table(log, "setting.log", "name", "$1", "$2", "where id=$1", in["name"].asString());

save_table(support, "setting.support", "name, email, phone, message", "$1, $2, $3, $4", "$2, $3, $4, $5", "where id=$1",
           in["name"].asString(), in["email"].asString(), in["phone"].asString(), in["message"].asString());

save_table(image_collection, "setting.image_collection", "name", "$1", "$2", "where id=$1", in["name"].asString());

// this is normal images..
Json::Value save_image(const std::string &event1, const std::string &event2, const std::string &no, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
    printJson(in);
    auto metal_purity_table = sqlb::ObjectIdentifier("setting", "image", "c");
    std::string t = "setting.image";
    std::string c = "image_collection_id, name, size, type, title, description, url, position";
    std::string strSqlTempImage = "SELECT name, size, type FROM setting.temp_image_id WHERE id = $1";
    std::string strSqlTempImageDel = "DELETE FROM setting.temp_image_id WHERE id = $1";

    if (in["id"].asInt()) {
        std::string strSql = "update " + t + " set (" + c + ") = ROW(NULLIF($2, 0), $3, $4, $5, $6, $7, $8, $9) where id=$1" ;
        pqxx::work txn{DD};
        try {
            auto temp_id = in["temp_id"].asInt();
            if (temp_id != 0) {
                pqxx::result z = txn.exec_params(strSqlTempImage, temp_id);
                if (z.size() == 1) {
                    txn.exec_params(strSql, in["id"].asInt(), in["image_collection_id"].asInt(), z[0][0].c_str(), z[0][1].as<int>(),z[0][2].c_str(), in["title"].asString(), in["description"].asString(), in["url"].asString(), in["position"].asInt());
                    txn.exec_params(strSqlTempImageDel, temp_id);
                }
            } else {
                txn.exec_params("UPDATE setting.image SET (title, description, url, position) = ROW($2, $3, $4, $5) WHERE id = $1", in["id"].asInt(), in["title"].asString(), in["description"].asString(), in["url"].asString(), in["position"].asInt());
            }
            txn.commit();

            return simpleJsonSaveResult(event1, event2, no, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            return simpleJsonSaveResult(event1, event2, no, wsConnPtr, false, e.what());
        }
    } else {
        std::string strSql = "INSERT INTO " + t + " (" + c + ") values(NULLIF($1,0), $2, $3, $4, $5, $6, $7, $8)";
        pqxx::work txn{DD};
        try {
            auto temp_id = in["temp_id"].asInt();
            if (temp_id != 0) {
                pqxx::result z = txn.exec_params(strSqlTempImage, temp_id);
                if (z.size() == 1) {
                    txn.exec_params(strSql, in["image_collection_id"].asInt(), z[0][0].c_str(), z[0][1].as<int>(),z[0][2].c_str(), in["title"].asString(), in["description"].asString(), in["url"].asString(), in["position"].asInt());
                    txn.exec_params(strSqlTempImageDel, temp_id);
                }
            } else {
                return simpleJsonSaveResult(event1, event2, no, wsConnPtr, false, "Please Upload Image");
            }

            txn.commit();
            return simpleJsonSaveResult(event1, event2, no, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            return simpleJsonSaveResult(event1, event2, no, wsConnPtr, false, e.what());
        }
    }
}
save_table(payment_method, "setting.payment_method", "name, url, description", "$1, $2, $3", "$2, $3, $4", "where id=$1", in["name"].asString(), in["url"].asString(), in["description"].asString())

//----
Json::Value saveImageMeta(const std::string &event1, const std::string &event2, const std::string &no, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
  auto c = getAdminContext(wsConnPtr);

  auto strSql = ins("user1.temp_image", "session_id, event_name, name, size, type", "$1, $2, $3, $4, $5");
  pqxx::work txn{DD};
  try {
    auto r = txn.exec_params(strSql, c, in[0].asString(), in[1].asString(), in[2].asInt64(), in[3].asString());
    txn.commit();
    return simpleJsonSaveResult(event1, event2, no, wsConnPtr, true, "done");
  } catch (const std::exception &e) {
    txn.abort();
    std::cerr << e.what() << std::endl;
    return simpleJsonSaveResult(event1, event2, no, wsConnPtr, false, "Error");
  }


}

// save image in disk and return temporary id:
Json::Value save_setting_attachment(const std::string &event1, const std::string &event2, const std::string &no, const WebSocketConnectionPtr &wsConnPtr, std::string &message) {
    auto session_id = getAdminContext(wsConnPtr);
    auto strSql = sel("user1.temp_image", "event_name, name, size, type", "where session_id = $1");
    pqxx::work txn{DD};
    try {
        auto r = txn.exec_params(strSql, session_id);
        txn.exec_params(dele("user1.temp_image", "where session_id = $1"), session_id);

        // check if file exist else rename a file
        auto event_name_meta = r[0][0].c_str();

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

        Json::Value jresult;
        jresult[0] = event_name_meta;
        pqxx::result insert_result = txn.exec_params(strSql, name, size, type);
        jresult[1] = insert_result[0][0].as<int>();
        //jresult[1] = e.what();
        txn.commit();
        //wsConnPtr->send(jresult.toStyledString());
        return jresult;

    } catch (const std::exception &e) {
        txn.abort();
        std::cerr << e.what() << std::endl;
        return Json::Value(Json::nullValue);
    }


}
