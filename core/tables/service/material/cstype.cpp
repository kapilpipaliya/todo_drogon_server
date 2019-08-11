#include "cstype.h"

CSType::CSType(const WebSocketConnectionPtr& wsConnPtr): wsConnPtr(wsConnPtr)
{

}

void CSType::setupTable()
{

        t.m_table = sqlb::ObjectIdentifier("material", "cs_type", "ct");
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "ct", PG_TYPES::INT8, false}),
            //            sqlb::SelectedColumn({"Rank", "rank", "", "ct", PG_TYPES::INT4, false}),
            //            sqlb::SelectedColumn({"Code", "slug", "", "ct", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Name", "name", "", "ct", PG_TYPES::TEXT, true}),
            //            sqlb::SelectedColumn({"Created By", "create_user_id", "", "ct", PG_TYPES::INT8, true, 1}),
            //            sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            //            sqlb::SelectedColumn({"Updated By", "update_user_id", "", "ct", PG_TYPES::INT8, true, 1}),
            //            sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            //            sqlb::SelectedColumn({"Create Time", "inserted_at", "", "ct", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            //            sqlb::SelectedColumn({"Update Time", "updated_at", "", "ct", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };

        //    auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
        //    auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {
            //            sqlb::Join("left", u1, "ct.create_user_id = u1.id"),
            //            sqlb::Join("left", u2, "ct.update_user_id = u2.id"),
            };

}

HANDLEEVENT(CSType)

HEADERDATA(CSType)
ALLDATA(CSType)
