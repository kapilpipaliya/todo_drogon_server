#include "accountheading.h"
#include "../../strfns.h"
#include "../../jsonfns.h"
AccountHeading::AccountHeading(const WebSocketConnectionPtr& wsConnPtr_): BaseService(wsConnPtr_)
{
    t.m_table = sqlb::ObjectIdentifier("account", "account_heading", "p");
}
    void AccountHeading::setupTable()
{


        t.m_query = sqlb::Query(t.m_table);

            //m_query.setRowIdColumn("id");
            t.m_query.selectedColumns() = {
                sqlb::SelectedColumn({"Id", "id", "", "p", PG_TYPES::INT8, false}),

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
save_table(AccountHeading, "account.account_heading", "name", "$1", "$2", "where id=$1", args["name"].asString())
