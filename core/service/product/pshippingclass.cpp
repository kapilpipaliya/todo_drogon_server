#include "pshippingclass.h"
#include "../../strfns.h"
#include "../../jsonfns.h"

PShippingClass::PShippingClass(const WebSocketConnectionPtr& wsConnPtr_): BaseService(wsConnPtr_)
{

    t.m_table = sqlb::ObjectIdentifier("product", "shipping_class", "t");
}

void PShippingClass::setupTable()
{
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "t", PG_TYPES::INT8, false}),
            sqlb::SelectedColumn({"Code", "slug", "", "t", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Name", "name", "", "t", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Description", "description", "", "t", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Product Count", "product_count", "", "t", PG_TYPES::INT4, true}),
            //sqlb::SelectedColumn({"Created By", "create_user_id", "", "t", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            //sqlb::SelectedColumn({"Updated By", "update_user_id", "", "t", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            //sqlb::SelectedColumn({"Create Time", "inserted_at", "", "t", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            //sqlb::SelectedColumn({"Update Time", "updated_at", "", "t", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };

        //auto m = sqlb::ObjectIdentifier("material", "metal", "m");
        //auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
        //auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {
            //sqlb::Join("left", m, "t.material_id = m.id"),
            // sqlb::Join("left", u1, "t.create_user_id = u1.id"),
            // sqlb::Join("left", u2, "t.update_user_id = u2.id"),
            };
}

Json::Value PShippingClass::ins(Json::Value event, Json::Value args)
{
    return insBase(event, args, "slug, name, description", "$1, $2, $3",
            args["slug"].asString(),
            args["name"].asString(),
            args["description"].asString());
}

Json::Value PShippingClass::upd(Json::Value event, Json::Value args)
{
    return updBase(event, args, "slug, name, description", "$1, $2, $3",
            args[1]["slug"].asString(),
            args[1]["name"].asString(),
            args[1]["description"].asString());
}
