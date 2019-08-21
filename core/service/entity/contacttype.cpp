#include "contacttype.h"
#include "../../strfns.h"
#include "../../jsonfns.h"

ContactType::ContactType(const WebSocketConnectionPtr& wsConnPtr_): BaseService(wsConnPtr_)
{

    t.m_table = sqlb::ObjectIdentifier("entity", "contact_type", "a");
}

void ContactType::setupTable()
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



Json::Value ContactType::ins(Json::Value event, Json::Value args)
{
    return insBase(event, args, "name", "$1",  args["name"].asString());
}

Json::Value ContactType::upd(Json::Value event, Json::Value args)
{
    return updBase(event, args, "name", "$1", args[1]["name"].asString());
}
