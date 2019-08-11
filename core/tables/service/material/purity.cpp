#include "purity.h"

Purity::Purity(const WebSocketConnectionPtr& wsConnPtr): wsConnPtr(wsConnPtr)
{

}

void Purity::setupTable()
{
    t.m_table = sqlb::ObjectIdentifier("material", "purity", "p");
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "p", PG_TYPES::INT8, false}),
            //        sqlb::SelectedColumn({"Metal", "metal_id", "", "p", PG_TYPES::INT8, true, 1, 2}), sqlb::SelectedColumn({"m_slug", "slug", "", "m", PG_TYPES::TEXT, false, 0, 0, false}), sqlb::SelectedColumn({"m_name", "name", "", "m", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Rank", "rank", "", "p", PG_TYPES::INT4, false}),
            sqlb::SelectedColumn({"Code", "slug", "", "p", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Name", "name", "", "p", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Metal", "metal_id", "", "p", PG_TYPES::DOUBLE, true}),
            sqlb::SelectedColumn({"Purity", "purity", "", "p", PG_TYPES::DOUBLE, true}),
            sqlb::SelectedColumn({"Specific Density", "specific_density", "", "m", PG_TYPES::DOUBLE, true}),
            sqlb::SelectedColumn({"purity_tone", "purity_tone",
                                  "json_agg(distinct jsonb_build_array(pt.tone_id, pu_metal.pt2, pt.price))",
                                  //"json_agg(distinct jsonb_build_array(mp.metal_id, mp.purity, mp.price, m.specific_density))",
                                  "pt", PG_TYPES::PSJSON, false}),
            sqlb::SelectedColumn({"Price", "price", "p.price", "p", PG_TYPES::DOUBLE, true}),

            sqlb::SelectedColumn({"Description", "description", "", "p", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Created By", "create_user_id", "", "p", PG_TYPES::INT8, true, 1}),
            sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Updated By", "update_user_id", "", "p", PG_TYPES::INT8, true, 1}),
            sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Create Time", "inserted_at", "", "p", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            sqlb::SelectedColumn({"Update Time", "updated_at", "", "p", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };

        auto pt = sqlb::ObjectIdentifier("material", "purity_tone", "pt");
    auto m = sqlb::ObjectIdentifier("material", "metal", "m");
    auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");
    auto metal_purity = sqlb::ObjectIdentifier("material", "purity_metal", "mp");

        t.m_query.joins() = {
            sqlb::Join("left", pt, "pt.purity_id = p.id"),
            sqlb::Join("left",
                       "( select pm.purity_id, pm.tone_id, jsonb_agg(distinct jsonb_build_array(pm.metal_id, pm.purity, pm.price, m1.specific_density)) as pt2 from material.purity_metal pm left join material.metal m1 on m1.id = pm.metal_id group by pm.purity_id, pm.tone_id) as pu_metal",
                       "(pu_metal.purity_id = pt.purity_id and pu_metal.tone_id = pt.tone_id)"),
            sqlb::Join("left", metal_purity, "mp.purity_id = p.id"),
            sqlb::Join("left", m, "p.metal_id = m.id"),
            sqlb::Join("left", u1, "p.create_user_id = u1.id"),
            sqlb::Join("left", u2, "p.update_user_id = u2.id"),
            };
    t.m_query.groupBy() = {
        sqlb::GroupByColumn("p", "id"),
        sqlb::GroupByColumn("m", "id"),
        sqlb::GroupByColumn("u1", "id"),
        sqlb::GroupByColumn("u2", "id"),
        };
}

HANDLEEVENT(Purity)

HEADERDATA(Purity)
ALLDATA(Purity)
