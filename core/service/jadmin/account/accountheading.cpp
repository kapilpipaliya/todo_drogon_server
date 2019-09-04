#include "accountheading.h"
using namespace  jadmin;
AccountHeading::AccountHeading(const JAdminContextPtr &context_): BaseService(context_)
{
    t.m_table = sqlb::ObjectIdentifier("account", "account_heading", "a");
}
    void AccountHeading::setupTable()
{


        t.m_query = sqlb::Query(t.m_table);

            //m_query.setRowIdColumn("id");
            t.m_query.selectedColumns() = {
                sqlb::SelectedColumn({"Id", "id", "", "a", PG_TYPES::INT8, false}),
                sqlb::SelectedColumn({"Acc No", "accno", "", "a", PG_TYPES::TEXT, true}),
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
json AccountHeading::ins(json event, json args)
{
    return insBase(event, args, "name, accno", "$1, $2",  args[0]["name"].get<std::string>(), args[0]["accno"].get<std::string>());
}

json AccountHeading::upd(json event, json args)
{
    return updBase(event, args, "name, accno", "$1, $2", args[0]["name"].get<std::string>(), args[0]["accno"].get<std::string>());
}
