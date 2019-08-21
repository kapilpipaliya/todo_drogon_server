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

Json::Value Currency::ins(Json::Value event, Json::Value args)
{
    return insBase(event, args, "slug, name, symbol, rounding, active", "$1, $2, $3, $4, $5",
            args[0]["slug"].asString(),
            args[0]["name"].asString(),
            args[0]["symbol"].asString(),
            args[0]["rounding"].asDouble(),
            args[0]["active"].asBool() );
}

Json::Value Currency::upd(Json::Value event, Json::Value args)
{
    return updBase(event, args, "slug, name, symbol, rounding, active", "$1, $2, $3, $4, $5",
                   args[0]["slug"].asString(),
                   args[0]["name"].asString(),
                   args[0]["symbol"].asString(),
                   args[0]["rounding"].asDouble(),
                   args[0]["active"].asBool()
            );
}
