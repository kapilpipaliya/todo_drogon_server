#include "functions.h"



#include "core/sql/objectidentifier.h"
#include "core/sql/query.h"


Json::Value getAllData(Table &t, Json::Value &in)
{
    t.updateFilterBase(in[0]);
    t.updateSortBase(in[1]);
    t.updatePaginationBase(in[2]);
    t.select();
    return t.getJsonData();
}
Json::Value getAllHeaderData(Table &t)
{
    return t.getJsonHeaderData();
}
//Json::Value getAllHiddenColumns(Table &t)
//{
//    auto a = t.m_query.selectedColumns();
//    Json::Value r(Json::arrayValue);
//    for(std::vector<int>::size_type i = 0; i != a.size(); i++) {
//        if(!a[i].isVisible) {
//            r.append(i);
//        }
//    }
//    return r;
//}
//Json::Value getAllOffsetColumns(Table &t)
//{
//    auto a = t.m_query.selectedColumns();
//    Json::Value r(Json::arrayValue);
//    for(std::vector<int>::size_type i = 0; i != a.size(); i++) {
//        r.append(a[i].offset);
//    }
//    return r;
//}
//Json::Value getAllTooltipOffsetColumns(Table &t)
//{
//    auto a = t.m_query.selectedColumns();
//    Json::Value r(Json::arrayValue);
//    for(std::vector<int>::size_type i = 0; i != a.size(); i++) {
//        r.append(a[i].tooltipOffset);
//    }
//    return r;
//}
//Json::Value getAllTooltipOffset(Table &t)
//{
//    auto a = t.m_query.selectedColumns();
//    Json::Value r(Json::arrayValue);
//    for(std::vector<int>::size_type i = 0; i != a.size(); i++) {
//        r.append((int)a[i].column_type);
//    }
//    return r;
//}

QString rtrimChar(const QString& s, QChar c)
{
    QString r = s.trimmed();
    while(r.endsWith(c))
        r.chop(1);
    return r;
}

std::string rtrimChar(const std::string& s, char c) {
    auto r = trim_copy(s);
    if (r.at(r.size() - 1) == c) {
        r.pop_back();
    }
    return s;
}
//------------------


    void query_metal(Table & t)
{

        t.m_table = sqlb::ObjectIdentifier("material", "metal", "m");
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
            sqlb::SelectedColumn({"Created By", "create_user_id", "", "m", PG_TYPES::INT8, true, 1}), sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Updated By", "update_user_id", "", "m", PG_TYPES::INT8, true, 1}), sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
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

    void query_purity(Table & t)
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
            //        sqlb::SelectedColumn({"Purity", "purity", "", "p", PG_TYPES::DOUBLE, true}),
            //        sqlb::SelectedColumn({"Specific Density", "specific_density", "m.specific_density * p.purity / 100 as specific_density", "m", PG_TYPES::DOUBLE, true}),
            sqlb::SelectedColumn({"metal_purity", "metal_purity", "json_agg(distinct jsonb_build_array(mp.metal_id, mp.purity, mp.price, mp.ismain, m.specific_density))", "mp", PG_TYPES::PSJSON, false}),
            sqlb::SelectedColumn({"Price", "price", "p.price", "p", PG_TYPES::DOUBLE, true}),

            sqlb::SelectedColumn({"Description", "description", "", "p", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Created By", "create_user_id", "", "p", PG_TYPES::INT8, true, 1}), sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Updated By", "update_user_id", "", "p", PG_TYPES::INT8, true, 1}), sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Create Time", "inserted_at", "", "p", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            sqlb::SelectedColumn({"Update Time", "updated_at", "", "p", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };

        auto m = sqlb::ObjectIdentifier("material", "metal", "m");
    auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");
    auto metal_purity = sqlb::ObjectIdentifier("material", "purity_metal", "mp");

        t.m_query.joins() = {
            sqlb::Join("left", metal_purity, "mp.purity_id = p.id"),
            sqlb::Join("left", m, "mp.metal_id = m.id"),
            sqlb::Join("left", u1, "p.create_user_id = u1.id"),
            sqlb::Join("left", u2, "p.update_user_id = u2.id"),
            };
    t.m_query.groupBy() = {
        sqlb::GroupByColumn("p", "id"),
        sqlb::GroupByColumn("u1", "id"),
        sqlb::GroupByColumn("u2", "id"),
        };
}
void query_tone(Table & t)
{

        t.m_table = sqlb::ObjectIdentifier("material", "tone", "c");
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "c", PG_TYPES::INT8, false}),
            //        sqlb::SelectedColumn({"Material", "material_id", "", "c", PG_TYPES::INT8, true, 1, 2}), sqlb::SelectedColumn({"m_slug", "slug", "", "m", PG_TYPES::TEXT, false, 0, 0, false}), sqlb::SelectedColumn({"m_name", "name", "", "m", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Rank", "rank", "", "c", PG_TYPES::INT4, false}),
            sqlb::SelectedColumn({"Code", "slug", "", "c", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Name", "name", "", "c", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Created By", "create_user_id", "", "c", PG_TYPES::INT8, true, 1}), sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Updated By", "update_user_id", "", "c", PG_TYPES::INT8, true, 1}), sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Create Time", "inserted_at", "", "c", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            sqlb::SelectedColumn({"Update Time", "updated_at", "", "c", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };

        //auto m = sqlb::ObjectIdentifier("material", "metal", "m");
        auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {
            //sqlb::Join("left", m, "c.material_id = m.id"),
            sqlb::Join("left", u1, "c.create_user_id = u1.id"),
            sqlb::Join("left", u2, "c.update_user_id = u2.id"),
            };
}


    void query_accessory(Table & t)
{

        t.m_table = sqlb::ObjectIdentifier("material", "accessory", "a");
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "a", PG_TYPES::INT8, false}),
            //        sqlb::SelectedColumn({"Material", "material_id", "", "a", PG_TYPES::INT8, true, 1, 2}), sqlb::SelectedColumn({"m_slug", "slug", "", "m", PG_TYPES::TEXT, false, 0, 0, false}), sqlb::SelectedColumn({"m_name", "name", "", "m", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Rank", "rank", "", "a", PG_TYPES::INT4, false}),
            sqlb::SelectedColumn({"Code", "slug", "", "a", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Name", "name", "", "a", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Created By", "create_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Updated By", "update_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Create Time", "inserted_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            sqlb::SelectedColumn({"Update Time", "updated_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };

        //    auto m = sqlb::ObjectIdentifier("material", "metal", "m");
        auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {
            //        sqlb::Join("left", m, "a.material_id = m.id"),
            sqlb::Join("left", u1, "a.create_user_id = u1.id"),
            sqlb::Join("left", u2, "a.update_user_id = u2.id"),
            };
}






    void query_clarity(Table & t)
{

        t.m_table = sqlb::ObjectIdentifier("material", "clarity", "g");
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "g", PG_TYPES::INT8, false}),
            //        sqlb::SelectedColumn({"Material", "material_id", "", "g", PG_TYPES::INT8, true, 1, 2}), sqlb::SelectedColumn({"m_slug", "slug", "", "m", PG_TYPES::TEXT, false, 0, 0, false}), sqlb::SelectedColumn({"m_name", "name", "", "m", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Rank", "rank", "", "g", PG_TYPES::INT4, false}),
            sqlb::SelectedColumn({"Code", "slug", "", "g", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Name", "name", "", "g", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Created By", "create_user_id", "", "g", PG_TYPES::INT8, true, 1}), sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Updated By", "update_user_id", "", "g", PG_TYPES::INT8, true, 1}), sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Create Time", "inserted_at", "", "g", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            sqlb::SelectedColumn({"Update Time", "updated_at", "", "g", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };

        //    auto m = sqlb::ObjectIdentifier("material", "metal", "m");
        auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {
            //        sqlb::Join("left", m, "g.material_id = m.id"),
            sqlb::Join("left", u1, "g.create_user_id = u1.id"),
            sqlb::Join("left", u2, "g.update_user_id = u2.id"),
            };
}

    void query_shape(Table & t)
{

        t.m_table = sqlb::ObjectIdentifier("material", "shape", "gs");
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "gs", PG_TYPES::INT8, false}),
            //        sqlb::SelectedColumn({"Material", "material_id", "", "gs", PG_TYPES::INT8, true, 1, 2}), sqlb::SelectedColumn({"m_slug", "slug", "", "m", PG_TYPES::TEXT, false, 0, 0, false}), sqlb::SelectedColumn({"m_name", "name", "", "m", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Rank", "rank", "", "gs", PG_TYPES::INT4, false}),
            sqlb::SelectedColumn({"Code", "slug", "", "gs", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Name", "name", "", "gs", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Created By", "create_user_id", "", "gs", PG_TYPES::INT8, true, 1}), sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Updated By", "update_user_id", "", "gs", PG_TYPES::INT8, true, 1}), sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Create Time", "inserted_at", "", "gs", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            sqlb::SelectedColumn({"Update Time", "updated_at", "", "gs", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };

        //    auto m = sqlb::ObjectIdentifier("material", "metal", "m");
        auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {
            //        sqlb::Join("left", m, "gs.material_id = m.id"),
            sqlb::Join("left", u1, "gs.create_user_id = u1.id"),
            sqlb::Join("left", u2, "gs.update_user_id = u2.id"),
            };

}

    void query_d_color(Table & t)
{

        t.m_table = sqlb::ObjectIdentifier("material", "diamond_color", "gt");
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "gt", PG_TYPES::INT8, false}),
            sqlb::SelectedColumn({"Rank", "rank", "", "gt", PG_TYPES::INT4, false}),
            sqlb::SelectedColumn({"Code", "slug", "", "gt", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Name", "name", "", "gt", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Created By", "create_user_id", "", "gt", PG_TYPES::INT8, true, 1}), sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Updated By", "update_user_id", "", "gt", PG_TYPES::INT8, true, 1}), sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Create Time", "inserted_at", "", "gt", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            sqlb::SelectedColumn({"Update Time", "updated_at", "", "gt", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };

        auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {
            sqlb::Join("left", u1, "gt.create_user_id = u1.id"),
            sqlb::Join("left", u2, "gt.update_user_id = u2.id"),
            };

}
void query_cs_color(Table & t)
{

        t.m_table = sqlb::ObjectIdentifier("material", "cs_color", "gt");
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "gt", PG_TYPES::INT8, false}),
            sqlb::SelectedColumn({"Rank", "rank", "", "gt", PG_TYPES::INT4, false}),
            sqlb::SelectedColumn({"Code", "slug", "", "gt", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Name", "name", "", "gt", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Created By", "create_user_id", "", "gt", PG_TYPES::INT8, true, 1}), sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Updated By", "update_user_id", "", "gt", PG_TYPES::INT8, true, 1}), sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Create Time", "inserted_at", "", "gt", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            sqlb::SelectedColumn({"Update Time", "updated_at", "", "gt", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };

        auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {
            sqlb::Join("left", u1, "gt.create_user_id = u1.id"),
            sqlb::Join("left", u2, "gt.update_user_id = u2.id"),
            };

}

    void query_size(Table &t)
{
    t.m_table = sqlb::ObjectIdentifier("material", "size", "s");
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "s", PG_TYPES::INT8, false}),
            sqlb::SelectedColumn({"Name", "name", "", "s", PG_TYPES::TEXT, true}),
            //sqlb::SelectedColumn({"Created By", "create_user_id", "", "sm", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            //sqlb::SelectedColumn({"Updated By", "update_user_id", "", "sm", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            //sqlb::SelectedColumn({"Create Time", "inserted_at", "", "sm", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            //sqlb::SelectedColumn({"Update Time", "updated_at", "", "sm", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };
    auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");
    t.m_query.joins() = {};

}


    void query_diamond_size(Table & t)
{

        t.m_table = sqlb::ObjectIdentifier("material", "diamond_size_meta", "sm");
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "sm", PG_TYPES::INT8, false}),
            sqlb::SelectedColumn({"Clarity", "clarity_id", "", "sm", PG_TYPES::INT8, true, 2, 2}), sqlb::SelectedColumn({"clarity_slug", "slug", "", "clarity", PG_TYPES::TEXT, false, 0, 0, false}), sqlb::SelectedColumn({"clarity_name", "name", "", "clarity", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Shape", "shape_id", "", "sm", PG_TYPES::INT8, true, 2, 2}), sqlb::SelectedColumn({"shape_slug", "slug", "", "shape", PG_TYPES::TEXT, false, 0, 0, false}), sqlb::SelectedColumn({"shape_name", "name", "", "shape", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Color", "color_id", "", "sm", PG_TYPES::INT8, true, 2, 2}), sqlb::SelectedColumn({"color_slug", "slug", "", "color", PG_TYPES::TEXT, false, 0, 0, false}), sqlb::SelectedColumn({"color_name", "name", "", "color", PG_TYPES::TEXT, false, 0, 0, false}),
            //sqlb::SelectedColumn({"Rank", "rank", "", "sm", PG_TYPES::INT4, false}),
            //sqlb::SelectedColumn({"Code", "slug", "", "sm", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Size", "size_id", "", "sm", PG_TYPES::INT8, true, 1, 1}), sqlb::SelectedColumn({"Name", "name", "", "size", PG_TYPES::TEXT, false}),
            sqlb::SelectedColumn({"Weight", "weight", "", "sm", PG_TYPES::DOUBLE, true}),
            sqlb::SelectedColumn({"Currency", "currency_id", "", "sm", PG_TYPES::INT8, true, 1, 2}),sqlb::SelectedColumn({"currency_slug", "slug", "", "currency", PG_TYPES::TEXT, false, 0, 0, false}), sqlb::SelectedColumn({"currency_name", "name", "", "currency", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Rate_On", "rate_on_id", "", "sm", PG_TYPES::ENUM, true}),
            sqlb::SelectedColumn({"Rate", "rate", "", "sm", PG_TYPES::DOUBLE, true}),
            sqlb::SelectedColumn({"Created By", "create_user_id", "", "sm", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Updated By", "update_user_id", "", "sm", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
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

    void query_color_stone_size(Table & t)
{

        t.m_table = sqlb::ObjectIdentifier("material", "color_stone_size_meta", "sm");
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "sm", PG_TYPES::INT8, false}),
            sqlb::SelectedColumn({"Shape", "shape_id", "", "sm", PG_TYPES::INT8, true, 2, 2}), sqlb::SelectedColumn({"shape_slug", "slug", "", "shape", PG_TYPES::TEXT, false, 0, 0, false}), sqlb::SelectedColumn({"shape_name", "name", "", "shape", PG_TYPES::TEXT, false, 0, 0, false}),
            //sqlb::SelectedColumn({"Rank", "rank", "", "sm", PG_TYPES::INT4, false}),
            //sqlb::SelectedColumn({"Code", "slug", "", "sm", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Size", "size_id", "", "sm", PG_TYPES::INT8, true, 1, 1}), sqlb::SelectedColumn({"Name", "name", "", "size", PG_TYPES::TEXT, false}),
            sqlb::SelectedColumn({"Weight", "weight", "", "sm", PG_TYPES::DOUBLE, true}),
            sqlb::SelectedColumn({"Currency", "currency_id", "", "sm", PG_TYPES::INT8, true, 1, 2}),sqlb::SelectedColumn({"currency_slug", "slug", "", "currency", PG_TYPES::TEXT, false, 0, 0, false}), sqlb::SelectedColumn({"currency_name", "name", "", "currency", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Rate_On", "rate_on_id", "", "sm", PG_TYPES::ENUM, true}),
            sqlb::SelectedColumn({"Rate", "rate", "", "sm", PG_TYPES::DOUBLE, true}),
            sqlb::SelectedColumn({"Created By", "create_user_id", "", "sm", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Updated By", "update_user_id", "", "sm", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Create Time", "inserted_at", "", "sm", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            sqlb::SelectedColumn({"Update Time", "updated_at", "", "sm", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };

        auto size = sqlb::ObjectIdentifier("material", "size", "size");
    //    auto clarity = sqlb::ObjectIdentifier("material", "clarity", "clarity");
    auto shape = sqlb::ObjectIdentifier("material", "shape", "shape");
    //    auto color = sqlb::ObjectIdentifier("material", "cs_color", "color");
    auto currency = sqlb::ObjectIdentifier("setting", "currency", "currency");
    auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {
            sqlb::Join("left", size, "size.id = sm.size_id"),
            //        sqlb::Join("left", clarity, "clarity.id = sm.clarity_id"),
            sqlb::Join("left", shape, "shape.id = sm.shape_id"),
            //        sqlb::Join("left", color, "color.id = sm.color_id"),
            sqlb::Join("left", currency, "currency.id = sm.currency_id"),
            sqlb::Join("left", u1, "sm.create_user_id = u1.id"),
            sqlb::Join("left", u2, "sm.update_user_id = u2.id"),
            };

}

    // ------
    void query_account(Table & t)
{

        t.m_table = sqlb::ObjectIdentifier("account", "account", "a");
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "a", PG_TYPES::INT8, false}),
            sqlb::SelectedColumn({"Material", "material_id", "", "a", PG_TYPES::INT8, true, 1, 2}), sqlb::SelectedColumn({"m_slug", "slug", "", "m", PG_TYPES::TEXT, false}), sqlb::SelectedColumn({"m_name", "name", "", "m", PG_TYPES::TEXT, false}),
            sqlb::SelectedColumn({"Rank", "rank", "", "a", PG_TYPES::INT4, false}),
            sqlb::SelectedColumn({"Code", "slug", "", "a", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Name", "name", "", "a", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Created By", "create_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Updated By", "update_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Create Time", "inserted_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            sqlb::SelectedColumn({"Update Time", "updated_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };

        auto m = sqlb::ObjectIdentifier("material", "metal", "m");
    auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {
            sqlb::Join("left", m, "a.material_id = m.id"),
            sqlb::Join("left", u1, "a.create_user_id = u1.id"),
            sqlb::Join("left", u2, "a.update_user_id = u2.id"),
            };
}

    void query_account_heading(Table & t)
{

        t.m_table = sqlb::ObjectIdentifier("account", "account_heading", "p");
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
void query_address_type(Table & t)
{
    t.m_table = sqlb::ObjectIdentifier("entity", "address_type", "a");
    t.m_query = sqlb::Query(t.m_table);
    //m_query.setRowIdColumn("id");
    t.m_query.selectedColumns() = {
        sqlb::SelectedColumn({"Id", "id", "", "a", PG_TYPES::INT8, true}),
        sqlb::SelectedColumn({"Name", "name", "", "a", PG_TYPES::TEXT, true}),
        sqlb::SelectedColumn({"Create Time", "inserted_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
        sqlb::SelectedColumn({"Update Time", "updated_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
        };
}
void query_contact_type(Table & t)
{
    t.m_table = sqlb::ObjectIdentifier("entity", "contact_type", "a");
    t.m_query = sqlb::Query(t.m_table);
    //m_query.setRowIdColumn("id");
    t.m_query.selectedColumns() = {
        sqlb::SelectedColumn({"Id", "id", "", "a", PG_TYPES::INT8, true}),
        sqlb::SelectedColumn({"Name", "name", "", "a", PG_TYPES::TEXT, true}),
        sqlb::SelectedColumn({"Create Time", "inserted_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
        sqlb::SelectedColumn({"Update Time", "updated_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
        };
}
    void query_entity_type(Table & t)
{
    t.m_table = sqlb::ObjectIdentifier("entity", "entity_type", "a");
    t.m_query = sqlb::Query(t.m_table);
    //m_query.setRowIdColumn("id");
    t.m_query.selectedColumns() = {
        sqlb::SelectedColumn({"Id", "id", "", "a", PG_TYPES::INT8, true}),
        sqlb::SelectedColumn({"Name", "name", "", "a", PG_TYPES::TEXT, true}),
        sqlb::SelectedColumn({"Create Time", "inserted_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
        sqlb::SelectedColumn({"Update Time", "updated_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
        };
}
typedef sqlb::SelectedColumn S;

void query_entity(Table & t)
{
    t.m_table = sqlb::ObjectIdentifier("entity", "entity", "e");
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
        S({"id", "id", "", "e", PG_TYPES::INT8}),
        S({"Entity Type", "entity_type_id", "", "e", PG_TYPES::INT8, true, 1, 1 }), sqlb::SelectedColumn({"et_name", "name", "", "et", PG_TYPES::TEXT, false, 0, 0, false}),
        S({"no", "no", "", "e", PG_TYPES::TEXT }),
        S({"sequence_id", "sequence_id", "", "e", PG_TYPES::INT8, false}),
        S({"slug", "slug", "", "e", PG_TYPES::TEXT}),
        S({"Parent", "parent_id", "", "e", PG_TYPES::INT8}),
        S({"legal_name", "legal_name", "", "e", PG_TYPES::TEXT}),
        S({"tax_no", "tax_no", "", "e", PG_TYPES::TEXT}),
        S({"First Name", "first_name", "", "e", PG_TYPES::TEXT}),
        S({"Middle Name", "middle_name", "", "e", PG_TYPES::TEXT}),
        S({"Last Name", "last_name", "", "e", PG_TYPES::TEXT}),
        S({"Birth Date", "birth_date", "", "e", PG_TYPES::TIMESTAMP}),
        S({"Start Date", "start_date", "", "e", PG_TYPES::TIMESTAMP}),
        S({"End Date", "end_date", "", "e", PG_TYPES::TIMESTAMP}),
        S({"Salary", "salary", "", "e", PG_TYPES::DOUBLE, false}),
        S({"Rate", "rate", "", "e", PG_TYPES::DOUBLE, false}),
        S({"Active", "active", "", "e", PG_TYPES::BOOL }),
        S({"Pay To Name", "pay_to_name", "", "e", PG_TYPES::TEXT}),
        S({"Threshold", "threshold", "", "e", PG_TYPES::DOUBLE}),
        S({"Credit Limit", "credit_limit", "", "e", PG_TYPES::DOUBLE}),
        S({"Terms", "terms", "", "e", PG_TYPES::INT4}),
        S({"Discount", "discount", "", "e", PG_TYPES::DOUBLE}),
        S({"Discount Terms", "discount_terms", "", "e", PG_TYPES::INT4}),
        S({"discount_account_id", "discount_account_id", "", "e", PG_TYPES::INT8, false}),
        S({"ar_ap_account_id", "ar_ap_account_id", "", "e", PG_TYPES::INT8, false}),
        S({"cash_account_id", "cash_account_id", "", "e", PG_TYPES::INT8, false}),
        S({"currency_id", "currency_id", "", "e", PG_TYPES::INT8, false}),
        S({"price_group_id", "price_group_id", "", "e", PG_TYPES::INT8, false}),
        S({"tax_included", "tax_included", "", "e", PG_TYPES::BOOL, false}),
        S({"Email", "email", "", "e", PG_TYPES::TEXT, true}),
        S({"Password", "password", "", "eu", PG_TYPES::TEXT, true}),


        //S({"Created By", "create_user_id", "", "e", PG_TYPES::INT8, true, 1, 0, false}), S({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
        //S({"Updated By", "update_user_id", "", "e", PG_TYPES::INT8, true, 1, 0, false}), S({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
        //S({"Create Time", "inserted_at", "", "e", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
        //S({"Update Time", "updated_at", "", "e", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
        S({"Addresses", "entity_address", "json_agg(distinct jsonb_build_array(ea.id, ea.address_type_id, ea.line1, ea.line2, ea.line3, ea.city, ea.state, ea.country, ea.zipcode, ea.phone ))", "ea", PG_TYPES::PSJSON, true})
      };
    auto entity_type = sqlb::ObjectIdentifier("entity", "entity_type", "et");
    auto entity_address = sqlb::ObjectIdentifier("entity", "entity_address", "ea");
    auto entity_user = sqlb::ObjectIdentifier("entity", "entity_user", "eu");
    auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {
        sqlb::Join("inner", entity_type, "et.id = e.entity_type_id"),
        sqlb::Join("left", entity_address, "ea.entity_id = e.id"),
        sqlb::Join("left", entity_user, "eu.entity_id = e.id"),
            sqlb::Join("left", u1, "e.create_user_id = u1.id"),
            sqlb::Join("left", u2, "e.update_user_id = u2.id"),
            };
        t.m_query.groupBy() = {
            sqlb::GroupByColumn("et", "id"),
            sqlb::GroupByColumn("e", "id"),
            sqlb::GroupByColumn("eu", "id"),
            };
}

void query_global_setting(Table & t)
{

    t.m_table = sqlb::ObjectIdentifier("setting", "global_setting", "gs");
    t.m_query = sqlb::Query(t.m_table);

    //m_query.setRowIdColumn("id");
    t.m_query.selectedColumns() = {
        sqlb::SelectedColumn({"Setting_key", "setting_key", "", "gs", PG_TYPES::TEXT, true}),
        sqlb::SelectedColumn({"Value", "value", "", "gs", PG_TYPES::TEXT, true})
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

    void query_currency(Table & t)
{

        t.m_table = sqlb::ObjectIdentifier("setting", "currency", "c");
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "c", PG_TYPES::INT8, false}),
            sqlb::SelectedColumn({"Code", "slug", "", "c", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Name", "name", "", "c", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Symbol", "symbol", "", "c", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Rounding", "rounding", "", "c", PG_TYPES::DOUBLE, true}),
            sqlb::SelectedColumn({"Active", "active", "", "c", PG_TYPES::BOOL, true}),
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
void query_log(Table & t)
{

        t.m_table = sqlb::ObjectIdentifier("setting", "simple_log", "a");
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "a", PG_TYPES::INT8, false}),
            sqlb::SelectedColumn({"Detail", "detail", "", "a", PG_TYPES::TEXT, true}),
            //sqlb::SelectedColumn({"Created By", "create_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            //sqlb::SelectedColumn({"Updated By", "update_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Create Time", "inserted_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            sqlb::SelectedColumn({"Update Time", "updated_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
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



    void query_order(Table & t)
{

        t.m_table = sqlb::ObjectIdentifier("account", "order", "a");
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "a", PG_TYPES::INT8, false}),
            sqlb::SelectedColumn({"Material", "material_id", "", "a", PG_TYPES::INT8, true, 1, 2}), sqlb::SelectedColumn({"m_slug", "slug", "", "m", PG_TYPES::TEXT, false, 0, 0, false}), sqlb::SelectedColumn({"m_name", "name", "", "m", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Rank", "rank", "", "a", PG_TYPES::INT4, false}),
            sqlb::SelectedColumn({"Code", "slug", "", "a", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Name", "name", "", "a", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Created By", "create_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Updated By", "update_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Create Time", "inserted_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            sqlb::SelectedColumn({"Update Time", "updated_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };

        auto m = sqlb::ObjectIdentifier("material", "metal", "m");
    auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {
            sqlb::Join("left", m, "a.material_id = m.id"),
            sqlb::Join("left", u1, "gt.create_user_id = u1.id"),
            sqlb::Join("left", u2, "a.update_user_id = u2.id"),
            };

}

    void query_part_group(Table & t)
{

        t.m_table = sqlb::ObjectIdentifier("part", "part_category", "p");
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "p", PG_TYPES::INT8, false}),
            sqlb::SelectedColumn({"Parent", "parent_id", "", "p", PG_TYPES::INT8, true, 1, 2}), sqlb::SelectedColumn({"p_slug", "slug", "", "p2", PG_TYPES::TEXT, false, 0, 0, false}), sqlb::SelectedColumn({"p_name", "name", "", "p2", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Code", "slug", "", "p", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Name", "name", "", "p", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Created By", "create_user_id", "", "p", PG_TYPES::INT8, true, 1}), sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Updated By", "update_user_id", "", "p", PG_TYPES::INT8, true, 1}), sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Create Time", "inserted_at", "", "p", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            sqlb::SelectedColumn({"Update Time", "updated_at", "", "p", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };

        auto m = sqlb::ObjectIdentifier("part", "part_category", "p2");
    auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {
            sqlb::Join("left", m, "p.parent_id = p2.id"),
            sqlb::Join("left", u1, "u1.id = p.create_user_id"),
            sqlb::Join("left", u2, "u2.id = p.update_user_id"),
            };

}


    void query_part_type(Table & t)
{

        t.m_table = sqlb::ObjectIdentifier("part", "part_type", "pt");
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "pt", PG_TYPES::INT8, false}),
            //sqlb::SelectedColumn({"Rank", "rank", "", "pt", PG_TYPES::INT4, false}),
            //sqlb::SelectedColumn({"Code", "slug", "", "pt", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Name", "name", "", "pt", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Created By", "create_user_id", "", "pt", PG_TYPES::INT8, true, 1}), sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Updated By", "update_user_id", "", "pt", PG_TYPES::INT8, true, 1}), sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Create Time", "inserted_at", "", "pt", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            sqlb::SelectedColumn({"Update Time", "updated_at", "", "pt", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };

        //auto m = sqlb::ObjectIdentifier("material", "metal", "m");
        auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {
            //sqlb::Join("left", m, "a.material_id = m.id"),
            sqlb::Join("left", u1, "pt.create_user_id = u1.id"),
            sqlb::Join("left", u2, "pt.update_user_id = u2.id"),
            };

}

    void query_sale(Table & t)
{

        t.m_table = sqlb::ObjectIdentifier("account", "sale", "a");
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "a", PG_TYPES::INT8, false}),
            sqlb::SelectedColumn({"Material", "material_id", "", "a", PG_TYPES::INT8, true, 1, 2}), sqlb::SelectedColumn({"m_slug", "slug", "", "m", PG_TYPES::TEXT, false, 0, 0, false}), sqlb::SelectedColumn({"m_name", "name", "", "m", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Rank", "rank", "", "a", PG_TYPES::INT4, false}),
            sqlb::SelectedColumn({"Code", "slug", "", "a", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Name", "name", "", "a", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Created By", "create_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Updated By", "update_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Create Time", "inserted_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            sqlb::SelectedColumn({"Update Time", "updated_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };

        auto m = sqlb::ObjectIdentifier("material", "metal", "m");
    auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {
            sqlb::Join("left", m, "a.material_id = m.id"),
            sqlb::Join("left", u1, "gt.create_user_id = u1.id"),
            sqlb::Join("left", u2, "a.update_user_id = u2.id"),
            };

}

    void query_transaction(Table & t)
{

        t.m_table = sqlb::ObjectIdentifier("account", "transaction", "a");
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "a", PG_TYPES::INT8, false}),
            sqlb::SelectedColumn({"Material", "material_id", "", "a", PG_TYPES::INT8, true, 1, 2}), sqlb::SelectedColumn({"m_slug", "slug", "", "m", PG_TYPES::TEXT, false, 0, 0, false}), sqlb::SelectedColumn({"m_name", "name", "", "m", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Rank", "rank", "", "a", PG_TYPES::INT4, false}),
            sqlb::SelectedColumn({"Code", "slug", "", "a", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Name", "name", "", "a", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Created By", "create_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Updated By", "update_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Create Time", "inserted_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            sqlb::SelectedColumn({"Update Time", "updated_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };

        auto m = sqlb::ObjectIdentifier("material", "metal", "m");
    auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {
            sqlb::Join("left", m, "a.material_id = m.id"),
            sqlb::Join("left", u1, "gt.create_user_id = u1.id"),
            sqlb::Join("left", u2, "a.update_user_id = u2.id"),
            };
}
//--------------Products
void query_product_options(Table & t)
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
void query_post(Table & t)
{
    t.m_table = sqlb::ObjectIdentifier("product", "post", "post");
    t.m_query = sqlb::Query(t.m_table);

        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "post", PG_TYPES::INT8, true}),
            sqlb::SelectedColumn({"Post Type", "post_type", "", "post", PG_TYPES::ENUM, true}),
            sqlb::SelectedColumn({"Visibility", "visibility", "", "post", PG_TYPES::ENUM, true}),
            sqlb::SelectedColumn({"Title", "post_title", "", "post", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Slug", "post_name", "", "post", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Product_short_description", "post_excerpt", "", "post", PG_TYPES::TEXT, false}),
            sqlb::SelectedColumn({"Product_Content", "post_content", "", "post", PG_TYPES::TEXT, false}),
            sqlb::SelectedColumn({"Menu_Order", "menu_order", "", "post", PG_TYPES::INT8, false}),
            sqlb::SelectedColumn({"Date", "post_date", "", "post", PG_TYPES::TIMESTAMP, true}),
            sqlb::SelectedColumn({"Status", "post_status", "", "post", PG_TYPES::ENUM, true}),
            sqlb::SelectedColumn({"Comment", "comment_status", "", "post", PG_TYPES::BOOL, true}),
            sqlb::SelectedColumn({"Password", "post_password", "", "post", PG_TYPES::TEXT, false}),
            sqlb::SelectedColumn({"Modified", "post_modified", "", "post", PG_TYPES::TIMESTAMP, true}),
            //sqlb::SelectedColumn({"Parent", "post_parent", "", "post", PG_TYPES::INT8, true}),
            //sqlb::SelectedColumn({"MIME Type", "post_mime_type", "", "post", PG_TYPES::ENUM, false}),
            sqlb::SelectedColumn({"Comment Count", "comment_count", "", "post", PG_TYPES::INT8, true}),
            };
}
void query_product(Table & t)
{
    t.m_table = sqlb::ObjectIdentifier("product", "post", "post");
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "post", PG_TYPES::INT8, true}),
            //sqlb::SelectedColumn({"Directory", "dir_path", "", "p", PG_TYPES::TEXT, true}),
            //sqlb::SelectedColumn({"File Name", " "",file_name", "p", PG_TYPES::TEXT, true}),
            //sqlb::SelectedColumn({"Color", "color_id", "", "p", PG_TYPES::INT8, true, 1, 2}),
            //sqlb::SelectedColumn({"C_slug", "slug", "", "c", PG_TYPES::TEXT, false, 0, 0, false}),
            //sqlb::SelectedColumn({"C_name", "name", "", "c", PG_TYPES::TEXT, false, 0, 0, false}),
            //sqlb::SelectedColumn({"Category", "part_group_id", "", "p", PG_TYPES::INT8, true, 1, 2}),
            //sqlb::SelectedColumn({"Pg_slug", "slug", "", "pg", PG_TYPES::TEXT, false, 0, 0, false}),
            //sqlb::SelectedColumn({"Pg_name", "name", "", "pg", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Purchase_Note", "purchase_note", "", "p", PG_TYPES::TEXT, false}),

            sqlb::SelectedColumn({"Product Id", "id","p.id", "p", PG_TYPES::INT8, false}),
            sqlb::SelectedColumn({"Product_short_description", "post_excerpt", "", "post", PG_TYPES::TEXT, false}),
            sqlb::SelectedColumn({"Product_Content", "post_content", "", "post", PG_TYPES::TEXT, false}),
            sqlb::SelectedColumn({"Menu_Order", "menu_order", "", "post", PG_TYPES::INT8, false}),
            sqlb::SelectedColumn({"Date", "post_date", "", "post", PG_TYPES::TIMESTAMP, true}),
            sqlb::SelectedColumn({"Title", "post_title", "", "post", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Slug", "post_name", "", "post", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Status", "post_status", "", "post", PG_TYPES::ENUM, true}),
            sqlb::SelectedColumn({"Comment", "comment_status", "", "post", PG_TYPES::BOOL, true}),
            sqlb::SelectedColumn({"Password", "post_password", "", "post", PG_TYPES::TEXT, false}),
            sqlb::SelectedColumn({"Modified", "post_modified", "", "post", PG_TYPES::TIMESTAMP, true}),
            sqlb::SelectedColumn({"Parent", "post_parent", "", "post", PG_TYPES::INT8, true}),
            sqlb::SelectedColumn({"Post Type", "post_type", "", "post", PG_TYPES::ENUM, true}),
            sqlb::SelectedColumn({"MIME Type", "post_mime_type", "", "post", PG_TYPES::ENUM, false}),
            sqlb::SelectedColumn({"Comment Count", "comment_count", "", "post", PG_TYPES::INT8, true}),

            sqlb::SelectedColumn({"SKU", "sku", "", "p", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Virtual", "virtual", "", "p", PG_TYPES::BOOL, false}),
            sqlb::SelectedColumn({"Downloadable", "downloadable", "", "p", PG_TYPES::BOOL, false}),
            sqlb::SelectedColumn({"Min Price", "min_price", "", "p", PG_TYPES::DOUBLE, false}),
            sqlb::SelectedColumn({"Max Price", "max_price", "", "p", PG_TYPES::DOUBLE, false}),
            sqlb::SelectedColumn({"Weight", "weight", "", "p", PG_TYPES::DOUBLE, true}),
            sqlb::SelectedColumn({"Purity", "purity_id", "", "p", PG_TYPES::INT8, true}),
            sqlb::SelectedColumn({"Length", "length", "", "p", PG_TYPES::DOUBLE, true}),
            sqlb::SelectedColumn({"Width", "width", "", "p", PG_TYPES::DOUBLE, true}),
            sqlb::SelectedColumn({"Height", "height", "", "p", PG_TYPES::DOUBLE, true}),
            sqlb::SelectedColumn({"On sale", "onsale","", "p", PG_TYPES::BOOL, true}),
            sqlb::SelectedColumn({"Stock Quantity", "stock_quantity", "", "p", PG_TYPES::DOUBLE, true}),
            sqlb::SelectedColumn({"Stock Status", "stock_status", "", "p", PG_TYPES::ENUM, true}),
            sqlb::SelectedColumn({"Rating Count", "rating_count", "", "p", PG_TYPES::INT4, true}),
            sqlb::SelectedColumn({"Average Rating", "average_rating", "", "p", PG_TYPES::DOUBLE, true}),
            sqlb::SelectedColumn({"Total Sales", "total_sales", "", "p", PG_TYPES::INT8, true}),
            sqlb::SelectedColumn({"Featured", "featured", "", "p", PG_TYPES::BOOL, true}),
            sqlb::SelectedColumn({"Shipping Class", "shipping_class_id", "", "p", PG_TYPES::INT8, true}),
            sqlb::SelectedColumn({"Manage Stock", "manage_stock", "", "p", PG_TYPES::BOOL, false}),
            sqlb::SelectedColumn({"Visibility", "visibility", "", "post", PG_TYPES::ENUM, true}),
            sqlb::SelectedColumn({"Catalog Visibility", "catalog_visibility", "", "p", PG_TYPES::ENUM, true}),
            sqlb::SelectedColumn({"Backorders", "backorders", "", "p", PG_TYPES::ENUM, true}),
            sqlb::SelectedColumn({"Product Type", "product_type","", "p", PG_TYPES::ENUM, true}),
            sqlb::SelectedColumn({"Tags", "tags_id", "json_agg(distinct tags.name ORDER BY tags.name ASC)", "tags", PG_TYPES::PSJSON, true}),
            sqlb::SelectedColumn({"category_id", "category_id", "json_agg(distinct pc.category_id)", "pc", PG_TYPES::PSJSON, false}),
            sqlb::SelectedColumn({"Categories", "category_id_name", "json_agg(distinct c.name)", "pc", PG_TYPES::PSJSON, true}),  // This is to Display on Main Table only.
            sqlb::SelectedColumn({"tone_id", "tone_id", "json_agg(distinct p_tones.tone_id)", "p_tones", PG_TYPES::PSJSON, false}),
            sqlb::SelectedColumn({"Tones", "tone_id_name", "json_agg(distinct tones.name)", "tones", PG_TYPES::PSJSON, true}),
            sqlb::SelectedColumn({"clarity_id", "clarity_id", "json_agg(distinct jsonb_build_array(p_clarity.clarity_id, p_clarity.pcs, p_clarity.weight, p_clarity.price, p_clarity.ismain))", "p_clarity", PG_TYPES::PSJSON, false}),
            sqlb::SelectedColumn({"purity_id", "purity_id", "json_agg(distinct jsonb_build_array(p_purities.purity_id, p_purities.weight, p_purities.price, pu_tone.pt2))", "p_purities", PG_TYPES::PSJSON, false}),
            sqlb::SelectedColumn({"Purities", "purity_id_name", "json_agg(distinct purities.name)", "purities", PG_TYPES::PSJSON, true}), // This is to Display on Main Table only.
            sqlb::SelectedColumn({"attachement_id", "attachement_id", "json_agg( distinct jsonb_build_array(p_attachments.id, p_attachments.tone_id, 0, p_attachments.main_image))", "p_attachments", PG_TYPES::PSJSON, false}),
            sqlb::SelectedColumn({"diamond_size_id", "diamond_size_id","json_agg( distinct jsonb_build_array(p_d_size.id, p_d_size.shape_id, p_d_size.color_id, p_d_size.size_id, p_d_size.pcs, diamond_price.pa))", "p_d_size", PG_TYPES::PSJSON, false}),
            sqlb::SelectedColumn({"cs_size_id", "cs_size_id", "json_agg( distinct jsonb_build_array(p_cs_size.id, p_cs_size.shape_id, p_cs_size.color_id, p_cs_size.size_id, p_cs_size.pcs, cs_price.pa))", "p_cs_size", PG_TYPES::PSJSON, false}),
            sqlb::SelectedColumn({"p_cs_total", "p_cs_total", "json_agg( distinct jsonb_build_array(p_cs_total.pcs, p_cs_total.weight, p_cs_total.price))", "p_cs_total", PG_TYPES::PSJSON, false}),
            sqlb::SelectedColumn({"Low Stock Amount", "low_stock_amount", "", "p", PG_TYPES::INT4, true}),
            sqlb::SelectedColumn({"Sold Individually", "sold_individually", "", "p", PG_TYPES::BOOL, false}),
            sqlb::SelectedColumn({"Setting Type", "setting_type_id", "", "p", PG_TYPES::INT8, false, 1, 1}), sqlb::SelectedColumn({"s_type_name", "name", "", "s_type", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Making Charges", "making_charges", "", "p", PG_TYPES::DOUBLE, false}),
            sqlb::SelectedColumn({"Discount Per", "discount_per", "", "p", PG_TYPES::DOUBLE, false}),
            sqlb::SelectedColumn({"Volume", "volume", "", "p", PG_TYPES::DOUBLE, false}),
            sqlb::SelectedColumn({"Certified By", "certified_by", "json_agg(distinct p_certified_by.certified_by_id)", "p_certified_by", PG_TYPES::PSJSON, false}),

            //sqlb::SelectedColumn({"Create Time", "inserted_at", "", "p", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            //sqlb::SelectedColumn({"Update Time", "updated_at", "", "p", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };
    //select json_agg(json_build_array(a,b,c)) from (values (1, 'foo', true),(2,'bar',false)) v(a,b,c); --> [[1, "foo", true], [2, "bar", false]]
    /*
        "id"

        "post_modified"
        "post_parent"
        "post_type"
        "post_mime_type"
        "comment_count"
        "p_onsale"
        "p_rating_count"
        "p_average_rating"
        "p_total_sales"

        "tones_tone_id_name"
        "purities_purity_id_name"
        "s_type_name"
        "p_inserted_at"
        "p_updated_at"
    */
    auto product = sqlb::ObjectIdentifier("product", "product", "p");
    auto pc = sqlb::ObjectIdentifier("product", "post_category", "pc");
    auto category = sqlb::ObjectIdentifier("product", "category", "c");
    auto post_tag = sqlb::ObjectIdentifier("product", "post_tag", "post_tag");
    auto tags = sqlb::ObjectIdentifier("product", "tag", "tags");
    auto ptones = sqlb::ObjectIdentifier("product", "post_tone", "p_tones");
    auto tones = sqlb::ObjectIdentifier("material", "tone", "tones");
    auto pclarity = sqlb::ObjectIdentifier("product", "post_clarity", "p_clarity");
    auto ppurities = sqlb::ObjectIdentifier("product", "post_purity", "p_purities");
    auto purities = sqlb::ObjectIdentifier("material", "purity", "purities");
    auto post_attachment = sqlb::ObjectIdentifier("product", "post_attachment", "p_attachments");
    auto s_type = sqlb::ObjectIdentifier("product", "setting_type", "s_type");
    auto p_d_size = sqlb::ObjectIdentifier("product", "post_diamond_size", "p_d_size");
    //auto diamond_price = sqlb::ObjectIdentifier("product", "diamond_price", "diamond_price");
    auto p_cs_size = sqlb::ObjectIdentifier("product", "post_color_stone_size", "p_cs_size");
    auto p_cs_total = sqlb::ObjectIdentifier("product", "post_cs_total", "p_cs_total");
    auto p_certified_by = sqlb::ObjectIdentifier("product", "post_certified_by", "p_certified_by");
    //auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
    //auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {
            //sqlb::Join("left", c, "p.color_id = c.id"),
            sqlb::Join("left", product, "p.post_id = post.id"),
            sqlb::Join("left", pc, "pc.post_id = post.id"),
            sqlb::Join("left", category, "c.id = pc.category_id"),
            sqlb::Join("left", post_tag, "post_tag.post_id = post.id"),
            sqlb::Join("left", tags, "tags.id = post_tag.tag_id"),
            sqlb::Join("left", ptones, "p_tones.post_id = post.id"),
            sqlb::Join("left", tones, "tones.id = p_tones.tone_id"),
            sqlb::Join("left", pclarity, "p_clarity.post_id = post.id"),
            sqlb::Join("left", ppurities, "p_purities.post_id = post.id"),
            sqlb::Join("left", "( select pt.post_id, pt.purity_id, jsonb_agg(distinct pt.tone_id) as pt2 from product.purity_tone pt group by pt.post_id, pt.purity_id) as pu_tone", "(pu_tone.post_id = p_purities.post_id and pu_tone.purity_id = p_purities.purity_id)"),
            sqlb::Join("left", purities, "purities.id = p_purities.purity_id"),
            sqlb::Join("left", post_attachment, "p_attachments.post_id = post.id"),
            sqlb::Join("left", s_type, "s_type.id = p.setting_type_id"),
            sqlb::Join("left", p_d_size, "p_d_size.post_id = post.id"),
            sqlb::Join("left", p_cs_size, "p_cs_size.post_id = post.id"),
            sqlb::Join("left", p_cs_total, "p_cs_total.post_id = post.id"),
            sqlb::Join("left", p_certified_by, "p_certified_by.post_id = post.id"),

            sqlb::Join("left", "(SELECT dp.diamond_id, jsonb_agg( distinct jsonb_build_array(dp.clarity_id, mc.name, dp.weight, dp.total_weight, dp.rate, dp.price)) AS pa FROM product.diamond_price dp left join material.clarity mc on mc.id = dp.clarity_id group by dp.diamond_id) as diamond_price", "diamond_price.diamond_id = p_d_size.id"),
            sqlb::Join("left", "(SELECT dp.cs_id, jsonb_agg( distinct jsonb_build_array(0, '', dp.weight, dp.total_weight, dp.rate, dp.price)) AS pa FROM product.cs_price dp group by dp.cs_id) as cs_price", "cs_price.cs_id = p_cs_size.id"),


            //sqlb::Join("left", u1, "gt.create_user_id = u1.id"),
            //sqlb::Join("left", u2, "a.update_user_id = u2.id"),
            };

        t.m_query.groupBy() = {
            sqlb::GroupByColumn("post", "id"),
            sqlb::GroupByColumn("p", "id"),
            sqlb::GroupByColumn("s_type", "id"),
            };

}

    void query_category(Table & t)
{
    t.m_table = sqlb::ObjectIdentifier("product", "category", "c");
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "c", PG_TYPES::INT8, false}),
            sqlb::SelectedColumn({"Parent", "parent_id", "", "c", PG_TYPES::INT8, true, 2, 1}), sqlb::SelectedColumn({"p_slug", "slug", "", "p", PG_TYPES::TEXT, false, 0, 0, false}), sqlb::SelectedColumn({"p_name", "name", "", "p", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Position", "position", "", "c", PG_TYPES::INT8, true}),
            sqlb::SelectedColumn({"Name", "name", "", "c", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Code", "slug", "", "c", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Description", "description", "", "c", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Display Type", "display_type", "", "c", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Created By", "create_user_id", "", "c", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Updated By", "update_user_id", "", "c", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Create Time", "inserted_at", "", "c", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            sqlb::SelectedColumn({"Update Time", "updated_at", "", "c", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };

        auto p = sqlb::ObjectIdentifier("product", "category", "p");
    auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {
            sqlb::Join("left", p, "c.parent_id = p.id"),
            sqlb::Join("left", u1, "c.create_user_id = u1.id"),
            sqlb::Join("left", u2, "c.update_user_id = u2.id"),
            };
}

    void query_tag(Table & t)
{

        t.m_table = sqlb::ObjectIdentifier("product", "tag", "t");
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "t", PG_TYPES::INT8, false}),
            sqlb::SelectedColumn({"Slug", "slug", "", "t", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Name", "name", "", "t", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Description", "description", "", "t", PG_TYPES::TEXT, true}),
            //sqlb::SelectedColumn({"Created By", "create_user_id", "", "t", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            //sqlb::SelectedColumn({"Updated By", "update_user_id", "", "t", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            //sqlb::SelectedColumn({"Create Time", "inserted_at", "", "t", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            //sqlb::SelectedColumn({"Update Time", "updated_at", "", "t", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };

        auto m = sqlb::ObjectIdentifier("material", "metal", "m");
    //auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
    //auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {
            //sqlb::Join("left", m, "a.material_id = m.id"),
            // sqlb::Join("left", u1, "gt.create_user_id = u1.id"),
            // sqlb::Join("left", u2, "a.update_user_id = u2.id"),
            };
}
void query_shipping_class(Table & t)
{

        t.m_table = sqlb::ObjectIdentifier("product", "shipping_class", "t");
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "t", PG_TYPES::INT8, false}),
            sqlb::SelectedColumn({"Code", "slug", "", "t", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Name", "name", "", "t", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Description", "description", "", "t", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Product Count", "product_count","", "t", PG_TYPES::INT4, true}),
            //sqlb::SelectedColumn({"Created By", "create_user_id", "", "t", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            //sqlb::SelectedColumn({"Updated By", "update_user_id", "", "t", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            //sqlb::SelectedColumn({"Create Time", "inserted_at", "", "t", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            //sqlb::SelectedColumn({"Update Time", "updated_at", "", "t", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };

        //auto m = sqlb::ObjectIdentifier("material", "metal", "m");
        //auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
        //auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {
            //sqlb::Join("left", m, "t.material_id = m.id"),
            // sqlb::Join("left", u1, "t.create_user_id = u1.id"),
            // sqlb::Join("left", u2, "t.update_user_id = u2.id"),
            };
}



    void query_setting_type(Table &t)
{

        t.m_table = sqlb::ObjectIdentifier("product", "setting_type", "t");
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "t", PG_TYPES::INT8, false}),
            //        sqlb::SelectedColumn({"Code", "slug", "", "t", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Name", "name", "", "t", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Description", "description", "", "t", PG_TYPES::TEXT, true}),
            //        sqlb::SelectedColumn({"Product Count", " "",product_count", "t", PG_TYPES::INT4, true}),
            //sqlb::SelectedColumn({"Created By", "create_user_id", "", "t", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            //sqlb::SelectedColumn({"Updated By", "update_user_id", "", "t", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            //sqlb::SelectedColumn({"Create Time", "inserted_at", "", "t", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            //sqlb::SelectedColumn({"Update Time", "updated_at", "", "t", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };

        //auto m = sqlb::ObjectIdentifier("material", "metal", "m");
        //auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
        //auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {
            //sqlb::Join("left", m, "t.material_id = m.id"),
            // sqlb::Join("left", u1, "t.create_user_id = u1.id"),
            // sqlb::Join("left", u2, "t.update_user_id = u2.id"),
            };
}
void query_certified_by(Table &t)
{

        t.m_table = sqlb::ObjectIdentifier("product", "certified_by", "t");
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "t", PG_TYPES::INT8, false}),
            sqlb::SelectedColumn({"Code", "slug", "", "t", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Name", "name", "", "t", PG_TYPES::TEXT, true}),
        S({"Title", "title", "", "t", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Description", "description", "", "t", PG_TYPES::TEXT, true}),
            //        sqlb::SelectedColumn({"Product Count", " "",product_count", "t", PG_TYPES::INT4, true}),
            //sqlb::SelectedColumn({"Created By", "create_user_id", "", "t", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            //sqlb::SelectedColumn({"Updated By", "update_user_id", "", "t", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            //sqlb::SelectedColumn({"Create Time", "inserted_at", "", "t", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            //sqlb::SelectedColumn({"Update Time", "updated_at", "", "t", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };

        //auto m = sqlb::ObjectIdentifier("material", "metal", "m");
        //auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
        //auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {
            //sqlb::Join("left", m, "t.material_id = m.id"),
            // sqlb::Join("left", u1, "t.create_user_id = u1.id"),
            // sqlb::Join("left", u2, "t.update_user_id = u2.id"),
            };
}



void serveImages(std::string &path)
{

    auto query = "SELECT  tone_id, name, inserted_at, updated_at, size, type FROM product.post_attachment WHERE id = $1";

}

void processCookie(const HttpRequestPtr &req, const WebSocketConnectionPtr &wsConnPtr)
{
    // If admin is empty send cookie:::
    auto c = req->getCookie("admin");
    if(c.empty()){
        // ask to login
        Json::Value lresult;
        lresult[0]="require_login";
        wsConnPtr->send(lresult.toStyledString());
        wsConnPtr->setContext(0);
    } else {
        auto sqlSession = "SELECT * FROM setting.session where id = $1";
        pqxx::work txn{DD};
        try {
            auto r = txn.exec_params( sqlSession, c );
            if(r.size() != 0){
                auto i = r[0][0].as<int>();
                wsConnPtr->setContext(i);
            } else {
                 wsConnPtr->setContext(0);
            }
            txn.commit();
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            wsConnPtr->setContext(0);
        }
    }
}
void deleteSession(const WebSocketConnectionPtr &wsConnPtr)
{
    auto c = std::any_cast<int>(wsConnPtr->getContext());
    if(c != 0){
        auto sqlSession = "DELETE FROM setting.session where id = $1";
        pqxx::work txn{DD};
        try {
            auto r = txn.exec_params( sqlSession, c );
            txn.commit();
            wsConnPtr->setContext(0);
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
        }
    }
}

std::string getEventName(const WebSocketConnectionPtr& wsConnPtr)
{
    auto c = std::any_cast<int>(wsConnPtr->getContext());
    auto sqlSession = "SELECT event_name FROM setting.temp_image where session_id = $1";
    pqxx::work txn{DD};
    try {
        auto r = txn.exec_params( sqlSession, c );
        txn.commit();
        return r[0][0].c_str();
    } catch (const std::exception &e) {
        txn.abort();
        std::cerr << e.what() << std::endl;
        return "";
    }

}
