#include "poptions.h"

POption::POption(const WebSocketConnectionPtr& wsConnPtr): wsConnPtr(wsConnPtr)
{

}

void POption::setupTable()
{

        t.m_table = sqlb::ObjectIdentifier("product", "option", "o");
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "o", PG_TYPES::INT8, false}),
            sqlb::SelectedColumn({"Name", "name", "", "o", PG_TYPES::INT4, true}),
            sqlb::SelectedColumn({"Value", "value", "", "o", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Autoload", "autoload", "", "o", PG_TYPES::TEXT, true}),
            //sqlb::SelectedColumn({"Created By", "create_user_id", "", "o", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            //sqlb::SelectedColumn({"Updated By", "update_user_id", "", "o", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            //sqlb::SelectedColumn({"Create Time", "inserted_at", "", "o", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            //sqlb::SelectedColumn({"Update Time", "updated_at", "", "o", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };

        auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {
            sqlb::Join("left", u1, "o.create_user_id = u1.id"),
            sqlb::Join("left", u2, "o.update_user_id = u2.id"),
            };
}

HANDLEEVENT(POption)

HEADERDATA(POption)
ALLDATA(POption)
