#include "dcolor.h"
#include "../../strfns.h"
#include "../../jsonfns.h"

DColor::DColor(const WebSocketConnectionPtr& wsConnPtr): wsConnPtr(wsConnPtr)
{

    t.m_table = sqlb::ObjectIdentifier("material", "diamond_color", "gt");
}

void DColor::setupTable()
{
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "gt", PG_TYPES::INT8, false}),
            sqlb::SelectedColumn({"Rank", "rank", "", "gt", PG_TYPES::INT4, false}),
            sqlb::SelectedColumn({"Code", "slug", "", "gt", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Name", "name", "", "gt", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Created By", "create_user_id", "", "gt", PG_TYPES::INT8, true, 1}),
            sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Updated By", "update_user_id", "", "gt", PG_TYPES::INT8, true, 1}),
            sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Create Time", "inserted_at", "", "gt", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            sqlb::SelectedColumn({"Update Time", "updated_at", "", "gt", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };

        auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {
            sqlb::Join("left", u1, "gt.create_user_id = u1.id"),
            sqlb::Join("left", u2, "gt.update_user_id = u2.id"),
            };
}

HANDLEEVENT(DColor)

HEADERDATA(DColor)
ALLDATA(DColor)
delFn(DColor)

    Json::Value DColor::save( Json::Value event, Json::Value args) {
    printJson(args);
    auto accessory_table = sqlb::ObjectIdentifier("material", "diamond_color", "c");

    if (args["id"].asInt()) {
        std::string strSql =
            "update %1.%2 set "
            "(slug, name)"
            " = ROW($2, $3) where id=$1";
        ReplaceAll2(strSql, "%1", accessory_table.schema());
        ReplaceAll2(strSql, "%2", accessory_table.name());

        pqxx::work txn{DD};
        try {
            txn.exec_params(strSql,
                            args["id"].asInt(),
                            args["slug"].asString(),
                            args["name"].asString()
                            );
            txn.commit();
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
        }
    } else {
        std::string strSql = "INSERT INTO %1.%2 (slug, name) values($1, $2)";
        ReplaceAll2(strSql, "%1", accessory_table.schema());
        ReplaceAll2(strSql, "%2", accessory_table.name());

        pqxx::work txn{DD};
        try {
            txn.exec_params(
                strSql,
                args["slug"].asString(),
                args["name"].asString()
                );
            txn.commit();
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
        }
    }
}
