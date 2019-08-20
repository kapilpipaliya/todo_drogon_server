#include "currency.h"
#include "../../strfns.h"
#include "../../jsonfns.h"

Currency::Currency(const WebSocketConnectionPtr& wsConnPtr_): BaseService(wsConnPtr_)
{
    t.m_table = sqlb::ObjectIdentifier("setting", "currency", "c");

}

void Currency::setupTable()
{
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

Json::Value Currency::ins( Json::Value event, Json::Value args) {
    printJson(args);
    auto metal_purity_table = sqlb::ObjectIdentifier("setting", "currency", "c");

    std::string strSql = "INSERT INTO %1.%2 (slug, name, symbol, rounding, active) values($1, $2, $3, $4, $5)";
    ReplaceAll2(strSql, "%1", metal_purity_table.schema());
    ReplaceAll2(strSql, "%2", metal_purity_table.name());

    pqxx::work txn{DD};
    try {
        txn.exec_params(
            strSql,
            args["slug"].asString(),
            args["name"].asString(),
            args["symbol"].asString(),
            args["rounding"].asDouble(),
            args["active"].asBool()
            );
        txn.commit();
        Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
    } catch (const std::exception &e) {
        txn.abort();
        std::cerr << e.what() << std::endl;
        Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
    }
}
Json::Value Currency::upd( Json::Value event, Json::Value args) {
    printJson(args);
    auto metal_purity_table = sqlb::ObjectIdentifier("setting", "currency", "c");

    if (args["id"].asInt()) {
        std::string strSql =
                "update %1.%2 set (slug, name, symbol, rounding, active) = ROW($2, $3, $4, $5, $6) where id=$1";
        ReplaceAll2(strSql, "%1", metal_purity_table.schema());
        ReplaceAll2(strSql, "%2", metal_purity_table.name());

        pqxx::work txn{DD};
        try {
            txn.exec_params(strSql,
                            args["id"].asInt64(),
                    args["slug"].asString(),
                    args["name"].asString(),
                    args["symbol"].asString(),
                    args["rounding"].asDouble(),
                    args["active"].asBool()
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
