#include "dsize.h"

DSize::DSize(const WebSocketConnectionPtr& wsConnPtr): wsConnPtr(wsConnPtr)
{

}

void DSize::setupTable()
{
    t.m_table = sqlb::ObjectIdentifier("material", "diamond_size_meta", "sm");
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "sm", PG_TYPES::INT8, false}),
            sqlb::SelectedColumn({"Clarity", "clarity_id", "", "sm", PG_TYPES::INT8, true, 2, 2}),
            sqlb::SelectedColumn({"clarity_slug", "slug", "", "clarity", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"clarity_name", "name", "", "clarity", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Shape", "shape_id", "", "sm", PG_TYPES::INT8, true, 2, 2}),
            sqlb::SelectedColumn({"shape_slug", "slug", "", "shape", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"shape_name", "name", "", "shape", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Color", "color_id", "", "sm", PG_TYPES::INT8, true, 2, 2}),
            sqlb::SelectedColumn({"color_slug", "slug", "", "color", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"color_name", "name", "", "color", PG_TYPES::TEXT, false, 0, 0, false}),
            //sqlb::SelectedColumn({"Rank", "rank", "", "sm", PG_TYPES::INT4, false}),
            //sqlb::SelectedColumn({"Code", "slug", "", "sm", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Size", "size_id", "", "sm", PG_TYPES::INT8, true, 1, 1}),
            sqlb::SelectedColumn({"Name", "name", "", "size", PG_TYPES::TEXT, false}),
            sqlb::SelectedColumn({"Weight", "weight", "", "sm", PG_TYPES::DOUBLE, true}),
            sqlb::SelectedColumn({"Currency", "currency_id", "", "sm", PG_TYPES::INT8, true, 1, 2}),
            sqlb::SelectedColumn({"currency_slug", "slug", "", "currency", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"currency_name", "name", "", "currency", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Rate_On", "rate_on_id", "", "sm", PG_TYPES::ENUM, true}),
            sqlb::SelectedColumn({"Rate", "rate", "", "sm", PG_TYPES::DOUBLE, true}),
            sqlb::SelectedColumn({"Created By", "create_user_id", "", "sm", PG_TYPES::INT8, true, 1, 0, false}),
            sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Updated By", "update_user_id", "", "sm", PG_TYPES::INT8, true, 1, 0, false}),
            sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Create Time", "inserted_at", "", "sm", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            sqlb::SelectedColumn({"Update Time", "updated_at", "", "sm", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };

        auto size = sqlb::ObjectIdentifier("material", "size", "size");
    auto clarity = sqlb::ObjectIdentifier("material", "clarity", "clarity");
    auto shape = sqlb::ObjectIdentifier("material", "shape", "shape");
    auto color = sqlb::ObjectIdentifier("material", "diamond_color", "color");
    auto currency = sqlb::ObjectIdentifier("setting", "currency", "currency");
    auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {
            sqlb::Join("left", size, "size.id = sm.size_id"),
            sqlb::Join("left", clarity, "clarity.id = sm.clarity_id"),
            sqlb::Join("left", shape, "shape.id = sm.shape_id"),
            sqlb::Join("left", color, "color.id = sm.color_id"),
            sqlb::Join("left", currency, "currency.id = sm.currency_id"),
            sqlb::Join("left", u1, "sm.create_user_id = u1.id"),
            sqlb::Join("left", u2, "sm.update_user_id = u2.id"),
            };

}

HANDLEEVENT(DSize)

HEADERDATA(DSize)
ALLDATA(DSize)
