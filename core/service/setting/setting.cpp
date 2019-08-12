#include "setting.h"
#include "../../strfns.h"
#include "../../jsonfns.h"

Setting::Setting(const WebSocketConnectionPtr& wsConnPtr): wsConnPtr(wsConnPtr)
{
    t.m_table = sqlb::ObjectIdentifier("setting", "setting", "gs");

}

void Setting::setupTable()
{
    t.m_query = sqlb::Query(t.m_table);
    //m_query.setRowIdColumn("id");
    t.m_query.selectedColumns() = {
        sqlb::SelectedColumn({"Key", "key", "", "gs", PG_TYPES::TEXT, true}),
        sqlb::SelectedColumn({"Setting Type", "setting_type", "", "gs", PG_TYPES::TEXT, true}),
        sqlb::SelectedColumn({"Integer", "value_int", "", "gs", PG_TYPES::INT8, true}),
        sqlb::SelectedColumn({"Decimal", "value_num", "", "gs", PG_TYPES::DOUBLE, true}),
        sqlb::SelectedColumn({"Text", "value_text", "", "gs", PG_TYPES::TEXT, true}),
        sqlb::SelectedColumn({"Internal", "setting", "", "gs", PG_TYPES::PSJSON, true}),
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

HANDLEEVENT(Setting)

HEADERDATA(Setting)
ALLDATA(Setting)
Json::Value Setting::del( Json::Value event, Json::Value args)
{
    pqxx::work txn{DD};
    try {\
        txn.exec_params("DELETE FROM setting.setting WHERE key = $1", args[0].asString());
        txn.commit();
        Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
    } catch (const std::exception &e) {
        txn.abort();
        std::cerr << e.what() << std::endl;
        Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
    }
}
Json::Value Setting::save( Json::Value event, Json::Value args) {
    // check if key exist
    pqxx::work txn{DD};
    pqxx::result y = txn.exec_params("select key from setting.setting where key = $1", args["key"].asString());
    txn.commit();
    if (y.size() != 0) {
        std::string strSql = "update setting.setting set (value_int, value_num, value_text) = ROW($2, $3, $4) where key=$1";
        pqxx::work txn{DD};
        try {
            txn.exec_params(strSql, args["key"].asString(), args["value_int"].asInt(), args["value_num"].asDouble(), args["value_text"].asString());
            txn.commit();
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
        }
    } else {
        std::string strSql = "INSERT INTO setting.setting (key, value_int, value_num, value_text, setting_type, setting) values($1, $2, $3, $4, $5, $6)";
        pqxx::work txn{DD};
        try {
            txn.exec_params(strSql, args["key"].asString(), args["value_int"].asInt(), args["value_num"].asDouble(), args["value_text"].asString(), args["setting_type"].asString(), args["setting"].toStyledString());
            txn.commit();
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
        }
    }
}
