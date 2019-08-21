#include "accountheading.h"
#include "../../strfns.h"
#include "../../jsonfns.h"
AccountHeading::AccountHeading(const WebSocketConnectionPtr& wsConnPtr_): BaseService(wsConnPtr_)
{
    t.m_table = sqlb::ObjectIdentifier("account", "account_heading", "a");
}
    void AccountHeading::setupTable()
{


        t.m_query = sqlb::Query(t.m_table);

            //m_query.setRowIdColumn("id");
            t.m_query.selectedColumns() = {
                sqlb::SelectedColumn({"Id", "id", "", "a", PG_TYPES::INT8, false}),
                sqlb::SelectedColumn({"Acc No", "accno", "", "a", PG_TYPES::INT8, true}),
                sqlb::SelectedColumn({"Name", "name", "", "a", PG_TYPES::TEXT, true}),
                };

            //auto pg = sqlb::ObjectIdentifier("part", "part_category", "pg");
            //auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
            //auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

            t.m_query.joins() = {
                //sqlb::Join("left", c, "p.color_id = c.id"),
                //sqlb::Join("left", pg, "p.part_group_id = pg.id"),
                //sqlb::Join("left", u1, "gt.create_user_id = u1.id"),
                //sqlb::Join("left", u2, "a.update_user_id = u2.id"),
                };
}
Json::Value AccountHeading::ins(Json::Value event, Json::Value args)
{
    return insBase(event, args, "name, accno", "$1, $2",  args[0]["name"].asString(), args[0]["accno"].asString());
}

Json::Value AccountHeading::upd(Json::Value event, Json::Value args)
{
    return updBase(event, args, "name, accno", "$1, $2", args[0]["name"].asString(), args[0]["accno"].asString());
}
