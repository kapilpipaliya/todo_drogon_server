#include "clarity.h"
#include "../../strfns.h"
#include "../../jsonfns.h"

Clarity::Clarity(const WebSocketConnectionPtr& wsConnPtr_): BaseService(wsConnPtr_)
{

    t.m_table = sqlb::ObjectIdentifier("material", "clarity", "g");
}

void Clarity::setupTable()
{
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "g", PG_TYPES::INT8, false}),
            //        sqlb::SelectedColumn({"Material", "material_id", "", "g", PG_TYPES::INT8, true, 1, 2}), sqlb::SelectedColumn({"m_slug", "slug", "", "m", PG_TYPES::TEXT, false, 0, 0, false}), sqlb::SelectedColumn({"m_name", "name", "", "m", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Rank", "rank", "", "g", PG_TYPES::INT4, false}),
            sqlb::SelectedColumn({"Code", "slug", "", "g", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Name", "name", "", "g", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Created By", "create_user_id", "", "g", PG_TYPES::INT8, true, 1}),
            sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Updated By", "update_user_id", "", "g", PG_TYPES::INT8, true, 1}),
            sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Create Time", "inserted_at", "", "g", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            sqlb::SelectedColumn({"Update Time", "updated_at", "", "g", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };

        //    auto m = sqlb::ObjectIdentifier("material", "metal", "m");
        auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {
            //        sqlb::Join("left", m, "g.material_id = m.id"),
            sqlb::Join("left", u1, "g.create_user_id = u1.id"),
            sqlb::Join("left", u2, "g.update_user_id = u2.id"),
            };
}

Json::Value Clarity::ins( Json::Value event, Json::Value args) {
    auto accessory_table = sqlb::ObjectIdentifier("material", "clarity", "cl");
    std::string strSql = "INSERT INTO %1.%2 (slug, name) values($1, $2)";
    ReplaceAll2(strSql, "%1", accessory_table.schema());
    ReplaceAll2(strSql, "%2", accessory_table.name());

    auto transPtr = clientPtr->newTransaction();
    try {
        transPtr->execSqlSync(
            strSql,
            args[0]["slug"].asString(),
            args[0]["name"].asString()
            );
        
        Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
    } catch (const std::exception &e) {
        
        std::cerr << e.what() << std::endl;
        Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
    }
}

Json::Value Clarity::upd( Json::Value event, Json::Value args) {
    auto accessory_table = sqlb::ObjectIdentifier("material", "clarity", "cl");

    if (args[0]["id"].asInt()) {
        std::string strSql =
                "update %1.%2 set "
                "(slug, name)"
                " = ROW($2, $3) where id=$1";
        ReplaceAll2(strSql, "%1", accessory_table.schema());
        ReplaceAll2(strSql, "%2", accessory_table.name());

        auto transPtr = clientPtr->newTransaction();
        try {
            transPtr->execSqlSync(strSql,
                            args[0]["id"].asInt64(),
                    args[0]["slug"].asString(),
                    args[0]["name"].asString()
                    );
            
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
        } catch (const std::exception &e) {
            
            std::cerr << e.what() << std::endl;
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
        }
    }
}
