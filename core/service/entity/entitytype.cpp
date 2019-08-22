#include "entitytype.h"
#include "../../strfns.h"
#include "../../jsonfns.h"

EntityType::EntityType(const WebSocketConnectionPtr& wsConnPtr_): BaseService(wsConnPtr_)
{
t.m_table = sqlb::ObjectIdentifier("entity", "entity_type", "a");
}

void EntityType::setupTable()
{

    t.m_query = sqlb::Query(t.m_table);
    //m_query.setRowIdColumn("id");
    t.m_query.selectedColumns() = {
        sqlb::SelectedColumn({"Id", "id", "", "a", PG_TYPES::INT8, true}),
        sqlb::SelectedColumn({"Name", "name", "", "a", PG_TYPES::TEXT, true}),
        sqlb::SelectedColumn({"Create Time", "inserted_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
        sqlb::SelectedColumn({"Update Time", "updated_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
        };
}



json EntityType::ins(json event, json args)
{
    return insBase(event, args, "name", "$1",  args[0]["name"].get<std::string>());
}

json EntityType::upd(json event, json args)
{
    return updBase(event, args, "name", "$1", args[0]["name"].get<std::string>());
}
