#include "refining.h"

#include <utility>
using namespace  jadmin;

Refining::Refining(JAdminContextPtr context_): context(std::move(context_))
{
    t.m_table = sqlb::ObjectIdentifier("mfg", "refining", "m");

}

void Refining::setupTable()
{
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "m", PG_TYPES::INT8, false}),
            //        sqlb::SelectedColumn({"Rank", "rank", "", "m", PG_TYPES::INT4, false}),
            sqlb::SelectedColumn({"Code", "slug", "", "m", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Name", "name", "", "m", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Specific_density", "specific_density", "", "m", PG_TYPES::DOUBLE, true}),
            sqlb::SelectedColumn({"Melting Point in C", "melting_point_in_c", "", "m", PG_TYPES::DOUBLE, true}),
            sqlb::SelectedColumn({"Currency_id", "currency_id", "", "m", PG_TYPES::INT8, true}),
            sqlb::SelectedColumn({"Price", "price", "", "m", PG_TYPES::DOUBLE, true}),
            sqlb::SelectedColumn({"Created By", "create_user_id", "", "m", PG_TYPES::INT8, true, 1}),
            sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Updated By", "update_user_id", "", "m", PG_TYPES::INT8, true, 1}),
            sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Create Time", "inserted_at", "", "m", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            sqlb::SelectedColumn({"Update Time", "updated_at", "", "m", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };


        auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {

            sqlb::Join("left", u1, "m.create_user_id = u1.id"),
            sqlb::Join("left", u2, "m.update_user_id = u2.id"),
            };
}
json Refining::ins(json event, json args)
{
    return insBase(event, args, "name", "$1",  args[0]["name"].get<std::string>() );
}

json Refining::upd(json event, json args)
{
    return updBase(event, args, "name", "$1", args[0]["name"].get<std::string>());
}
