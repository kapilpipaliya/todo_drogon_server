#include "support.h"
#include "../../strfns.h"
#include "../../jsonfns.h"

Support::Support(const WebSocketConnectionPtr& wsConnPtr): wsConnPtr(wsConnPtr)
{
    t.m_table = sqlb::ObjectIdentifier("setting", "support", "a");

}

void Support::setupTable()
{
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "a", PG_TYPES::INT8, false}),
            sqlb::SelectedColumn({"Name", "name", "", "a", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Email", "email", "", "a", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Phone", "phone", "", "a", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Message", "message", "", "a", PG_TYPES::TEXT, true}),
            //sqlb::SelectedColumn({"Created By", "create_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            //sqlb::SelectedColumn({"Updated By", "update_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Create Time", "inserted_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            sqlb::SelectedColumn({"Update Time", "updated_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };

        //auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
        //auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {
            //sqlb::Join("left", u1, "gt.create_user_id = u1.id"),
            //sqlb::Join("left", u2, "a.update_user_id = u2.id"),
            };

}

HANDLEEVENT(Support)

HEADERDATA(Support)
ALLDATA(Support)
delFn(Support)

save_table(Support, "setting.support", "name, email, phone, message", "$1, $2, $3, $4", "$2, $3, $4, $5", "where id=$1",
               args["name"].asString(), args["email"].asString(), args["phone"].asString(), args["message"].asString());
