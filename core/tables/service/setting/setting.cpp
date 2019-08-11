#include "setting.h"

Setting::Setting(const WebSocketConnectionPtr& wsConnPtr): wsConnPtr(wsConnPtr)
{

}

void Setting::setupTable()
{
    t.m_table = sqlb::ObjectIdentifier("setting", "setting", "gs");
    t.m_query = sqlb::Query(t.m_table);
    //m_query.setRowIdColumn("id");
    t.m_query.selectedColumns() = {
        sqlb::SelectedColumn({"Key", "key", "", "gs", PG_TYPES::TEXT, true}),
        sqlb::SelectedColumn({"Setting Type", "setting_type", "", "gs", PG_TYPES::TEXT, true}),
        sqlb::SelectedColumn({"Integer", "value_int", "", "gs", PG_TYPES::INT8, true}),
        sqlb::SelectedColumn({"Decimal", "value_num", "", "gs", PG_TYPES::DOUBLE, true}),
        sqlb::SelectedColumn({"Text", "value_text", "", "gs", PG_TYPES::TEXT, true}),
        sqlb::SelectedColumn({"Internal", "setting", "", "gs", PG_TYPES::PSJSON, true}),
        };
    //auto m = sqlb::ObjectIdentifier("material", "metal", "m");
    //auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
    //auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");
    t.m_query.joins() = {
        //sqlb::Join("left", m, "a.material_id = m.id"),
        //sqlb::Join("left", u1, "gt.create_user_id = u1.id"),
        //sqlb::Join("left", u2, "a.update_user_id = u2.id"),
        };
}

HANDLEEVENT(Setting)

HEADERDATA(Setting)
ALLDATA(Setting)
