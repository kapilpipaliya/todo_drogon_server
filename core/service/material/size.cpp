#include "size.h"
#include "../../strfns.h"
#include "../../jsonfns.h"

Size::Size(const WebSocketConnectionPtr& wsConnPtr_): BaseService(wsConnPtr_)
{
    t.m_table = sqlb::ObjectIdentifier("material", "size", "s");

}

void Size::setupTable()
{
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "s", PG_TYPES::INT8, false}),
            sqlb::SelectedColumn({"Name", "name", "", "s", PG_TYPES::TEXT, true}),
            //sqlb::SelectedColumn({"Created By", "create_user_id", "", "sm", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            //sqlb::SelectedColumn({"Updated By", "update_user_id", "", "sm", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            //sqlb::SelectedColumn({"Create Time", "inserted_at", "", "sm", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            //sqlb::SelectedColumn({"Update Time", "updated_at", "", "sm", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };
    auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");
    t.m_query.joins() = {};

}

Json::Value Size::ins(Json::Value event, Json::Value args)
{
    return insBase(event, args, "name", "$1",  args[0]["name"].asString() );
}

Json::Value Size::upd(Json::Value event, Json::Value args)
{
    return updBase(event, args, "name", "$1", args[0]["name"].asString());
}
