#include "setting.h"
#include "../../strfns.h"
#include "../../jsonfns.h"

Setting::Setting(const WebSocketConnectionPtr& wsConnPtr_): BaseService(wsConnPtr_)
{
    t.m_table = sqlb::ObjectIdentifier("setting", "setting", "gs");

}

Json::Value Setting::handleEvent(Json::Value event, int next, Json::Value args)
{
    auto event_cmp = event[next].asString();
    if(event_cmp == "data"){
        return allData(event, args);
    } else if (event_cmp == "header") {
        return headerData(event, args);
    } else if (event_cmp  == "save") {
        return save(event, args);
    } else if (event_cmp  == "del") {
        return del(event, args);
    } else {
        return Json::nullValue;
    }
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

// where key = $1
Json::Value Setting::del( Json::Value event, Json::Value args)
{
    auto transPtr = clientPtr->newTransaction();
    try {
        transPtr->execSqlSync("DELETE FROM setting.setting WHERE key = $1", args[0].asString());
        
        Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
    } catch (const std::exception &e) {
        
        std::cerr << e.what() << std::endl;
        Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
    }
}
Json::Value Setting::save( Json::Value event, Json::Value args) {
    // check if key exist
    auto transPtr = clientPtr->newTransaction();
    auto y = transPtr->execSqlSync("select key from setting.setting where key = $1", args[0]["key"].asString());
    
    if (y.size() != 0) {
        std::string strSql = "update setting.setting set (value_int, value_num, value_text) = ROW($2, $3, $4) where key=$1";
        auto transPtr = clientPtr->newTransaction();
        try {
            transPtr->execSqlSync(strSql, args[0]["key"].asString(), args[0]["value_int"].asInt(), args[0]["value_num"].asDouble(), args[0]["value_text"].asString());
            
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
        } catch (const std::exception &e) {
            
            std::cerr << e.what() << std::endl;
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
        }
    } else {
        std::string strSql = "INSERT INTO setting.setting (key, value_int, value_num, value_text, setting_type, setting) values($1, $2, $3, $4, $5, $6)";
        auto transPtr = clientPtr->newTransaction();
        try {
            transPtr->execSqlSync(strSql, args[0]["key"].asString(), args[0]["value_int"].asInt(), args[0]["value_num"].asDouble(), args[0]["value_text"].asString(), args[0]["setting_type"].asString(), args[0]["setting"].toStyledString());
            
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
        } catch (const std::exception &e) {
            
            std::cerr << e.what() << std::endl;
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
        }
    }
}
