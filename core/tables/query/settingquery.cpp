#include "settingquery.h"
#include <boost/filesystem.hpp>
#include "../../strfns.h"
void query_global_setting(Table &t) {

  t.m_table = sqlb::ObjectIdentifier("setting", "global_setting", "gs");
  t.m_query = sqlb::Query(t.m_table);

  //m_query.setRowIdColumn("id");
  t.m_query.selectedColumns() = {
          sqlb::SelectedColumn({"Setting_key", "setting_key", "", "gs", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Value", "value", "", "gs", PG_TYPES::TEXT, true})
  };

  //auto m = sqlb::ObjectIdentifier("material", "metal", "m");
  //auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
  //auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

  t.m_query.joins() = {
          //sqlb::Join("left", m, "a.material_id = m.id"),
          //sqlb::Join("left", u1, "gt.create_user_id = u1.id"),
          //sqlb::Join("left", u2, "a.update_user_id = u2.id"),
  };

}

void query_currency(Table &t) {

  t.m_table = sqlb::ObjectIdentifier("setting", "currency", "c");
  t.m_query = sqlb::Query(t.m_table);

  //m_query.setRowIdColumn("id");
  t.m_query.selectedColumns() = {
          sqlb::SelectedColumn({"Id", "id", "", "c", PG_TYPES::INT8, false}),
          sqlb::SelectedColumn({"Code", "slug", "", "c", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Name", "name", "", "c", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Symbol", "symbol", "", "c", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Rounding", "rounding", "", "c", PG_TYPES::DOUBLE, true}),
          sqlb::SelectedColumn({"Active", "active", "", "c", PG_TYPES::BOOL, true}),
  };

  //auto m = sqlb::ObjectIdentifier("material", "metal", "m");
  //auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
  //auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

  t.m_query.joins() = {
          //sqlb::Join("left", m, "a.material_id = m.id"),
          //sqlb::Join("left", u1, "gt.create_user_id = u1.id"),
          //sqlb::Join("left", u2, "a.update_user_id = u2.id"),
  };

}

void query_log(Table &t) {

  t.m_table = sqlb::ObjectIdentifier("setting", "simple_log", "a");
  t.m_query = sqlb::Query(t.m_table);

  //m_query.setRowIdColumn("id");
  t.m_query.selectedColumns() = {
          sqlb::SelectedColumn({"Id", "id", "", "a", PG_TYPES::INT8, false}),
          sqlb::SelectedColumn({"Detail", "detail", "", "a", PG_TYPES::TEXT, true}),
          //sqlb::SelectedColumn({"Created By", "create_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
          //sqlb::SelectedColumn({"Updated By", "update_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
          sqlb::SelectedColumn({"Create Time", "inserted_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
          sqlb::SelectedColumn({"Update Time", "updated_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  };

  //auto m = sqlb::ObjectIdentifier("material", "metal", "m");
  //auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
  //auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

  t.m_query.joins() = {
          //sqlb::Join("left", m, "a.material_id = m.id"),
          //sqlb::Join("left", u1, "gt.create_user_id = u1.id"),
          //sqlb::Join("left", u2, "a.update_user_id = u2.id"),
  };
}

void query_support(Table &t) {
  t.m_table = sqlb::ObjectIdentifier("setting", "support", "a");
  t.m_query = sqlb::Query(t.m_table);

  //m_query.setRowIdColumn("id");
  t.m_query.selectedColumns() = {
          sqlb::SelectedColumn({"Id", "id", "", "a", PG_TYPES::INT8, false}),
          sqlb::SelectedColumn({"Name", "name", "", "a", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Email", "email", "", "a", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Phone", "phone", "", "a", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Message", "message", "", "a", PG_TYPES::TEXT, true}),
          //sqlb::SelectedColumn({"Created By", "create_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
          //sqlb::SelectedColumn({"Updated By", "update_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
          sqlb::SelectedColumn({"Create Time", "inserted_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
          sqlb::SelectedColumn({"Update Time", "updated_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  };

  //auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
  //auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

  t.m_query.joins() = {
          //sqlb::Join("left", u1, "gt.create_user_id = u1.id"),
          //sqlb::Join("left", u2, "a.update_user_id = u2.id"),
  };

}

void query_image_collection(Table &t) {

  t.m_table = sqlb::ObjectIdentifier("setting", "image_collection", "a");
  t.m_query = sqlb::Query(t.m_table);

  //m_query.setRowIdColumn("id");
  t.m_query.selectedColumns() = {
          sqlb::SelectedColumn({"Id", "id", "", "a", PG_TYPES::INT8, true}),
          sqlb::SelectedColumn({"Name", "name", "", "a", PG_TYPES::TEXT, true}),
          //sqlb::SelectedColumn({"Created By", "create_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
          //sqlb::SelectedColumn({"Updated By", "update_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
          sqlb::SelectedColumn({"Create Time", "inserted_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
          sqlb::SelectedColumn({"Update Time", "updated_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  };

  //auto m = sqlb::ObjectIdentifier("material", "metal", "m");
  //auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
  //auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

  t.m_query.joins() = {
          //sqlb::Join("left", m, "a.material_id = m.id"),
          //sqlb::Join("left", u1, "gt.create_user_id = u1.id"),
          //sqlb::Join("left", u2, "a.update_user_id = u2.id"),
  };
}

void query_image(Table &t) {

  t.m_table = sqlb::ObjectIdentifier("setting", "image", "a");
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
void query_payment_method(Table &t) {

        t.m_table = sqlb::ObjectIdentifier("setting", "payment_method", "t");
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "t", PG_TYPES::INT8, false}),
            //            sqlb::SelectedColumn({"Code", "slug", "", "t", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Name", "name", "", "t", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Url", "url", "", "t", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Description", "description", "", "t", PG_TYPES::TEXT, true}),
            //sqlb::SelectedColumn({"Created By", "create_user_id", "", "t", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            //sqlb::SelectedColumn({"Updated By", "update_user_id", "", "t", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            //sqlb::SelectedColumn({"Create Time", "inserted_at", "", "t", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            //sqlb::SelectedColumn({"Update Time", "updated_at", "", "t", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };

        //auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
        //auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {
            // sqlb::Join("left", u1, "t.create_user_id = u1.id"),
            // sqlb::Join("left", u2, "t.update_user_id = u2.id"),
            };
}
Json::Value get_setting_thumb_data(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in)
{
    // send meta_data
    Json::Value ret;
    ret[0] = "take_image_meta";
    Json::Value data;
    data[0] = event_name;
    data[1] = 0;
    ret[1] = data;
    wsConnPtr->send(ret.toStyledString());

    namespace fs = boost::filesystem;
    auto home = fs::path(getenv("HOME"));

    pqxx::work txn{DD};
    try {
        auto sql = "SELECT name FROM setting.image WHERE id = $1";
        pqxx::result x = txn.exec_params(sql, in.asInt());
        txn.commit();
        if (x.size() == 1) {
            std::streampos size;
            // http://www.cplusplus.com/doc/tutorial/files/
            // What is the best way to read an entire file into a std::string in C++?
            // https://stackoverflow.com/questions/116038/what-is-the-best-way-to-read-an-entire-file-into-a-stdstring-in-c/116220#116220
            std::ifstream file(home.string() + "/fileuploads/" + x[0][0].c_str(), std::ios::in | std::ios::binary | std::ios::ate);
            if (file.is_open()) {
                auto memblock = read_all(file);
                file.close();

                //std::cout << "the entire file content is in memory";
                wsConnPtr->send(memblock, WebSocketMessageType::Binary); // Note when server not able to send this file, front end crash.
                //delete[] memblock;
            }
        } else {
            // Fix simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
        }
        return Json::Value(Json::nullValue);
    } catch (const std::exception &e) {
        txn.abort();
        std::cerr << e.what() << std::endl;
        //simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
        return Json::Value(Json::nullValue);
    }

    //get binary data and send.
    //wsConnPtr->send();
}
