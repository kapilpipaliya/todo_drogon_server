#include "addresstype.h"

#include <utility>
using namespace  jadmin;

AddressType::AddressType(JAdminContextPtr context_): context(std::move(context_))
{

    t.m_table = sqlb::ObjectIdentifier("entity", "address_type", "a");
}

void AddressType::setupTable()
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



json AddressType::ins(json event, json args)
{
    return insBase(event, args, "name", "$1",  args[0]["name"].get<std::string>());
}

json AddressType::upd(json event, json args)
{
    return updBase(event, args, "name", "$1", args[0]["name"].get<std::string>());
}
