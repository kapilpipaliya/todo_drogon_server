#include "materialquery.h"

void query_metal(Table &t) {

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
          sqlb::SelectedColumn({"Created By", "create_user_id", "", "m", PG_TYPES::INT8, true, 1}),
          sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
          sqlb::SelectedColumn({"Updated By", "update_user_id", "", "m", PG_TYPES::INT8, true, 1}),
          sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
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

void query_purity(Table &t) {

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

void query_tone(Table &t) {

  t.m_table = sqlb::ObjectIdentifier("material", "tone", "c");
  t.m_query = sqlb::Query(t.m_table);

  //m_query.setRowIdColumn("id");
  t.m_query.selectedColumns() = {
          sqlb::SelectedColumn({"Id", "id", "", "c", PG_TYPES::INT8, false}),
          //        sqlb::SelectedColumn({"Material", "material_id", "", "c", PG_TYPES::INT8, true, 1, 2}), sqlb::SelectedColumn({"m_slug", "slug", "", "m", PG_TYPES::TEXT, false, 0, 0, false}), sqlb::SelectedColumn({"m_name", "name", "", "m", PG_TYPES::TEXT, false, 0, 0, false}),
          sqlb::SelectedColumn({"Rank", "rank", "", "c", PG_TYPES::INT4, false}),
          sqlb::SelectedColumn({"Code", "slug", "", "c", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Name", "name", "", "c", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Created By", "create_user_id", "", "c", PG_TYPES::INT8, true, 1}),
          sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
          sqlb::SelectedColumn({"Updated By", "update_user_id", "", "c", PG_TYPES::INT8, true, 1}),
          sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
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


void query_accessory(Table &t) {

  t.m_table = sqlb::ObjectIdentifier("material", "accessory", "a");
  t.m_query = sqlb::Query(t.m_table);

  //m_query.setRowIdColumn("id");
  t.m_query.selectedColumns() = {
          sqlb::SelectedColumn({"Id", "id", "", "a", PG_TYPES::INT8, false}),
          //        sqlb::SelectedColumn({"Material", "material_id", "", "a", PG_TYPES::INT8, true, 1, 2}), sqlb::SelectedColumn({"m_slug", "slug", "", "m", PG_TYPES::TEXT, false, 0, 0, false}), sqlb::SelectedColumn({"m_name", "name", "", "m", PG_TYPES::TEXT, false, 0, 0, false}),
          sqlb::SelectedColumn({"Rank", "rank", "", "a", PG_TYPES::INT4, false}),
          sqlb::SelectedColumn({"Code", "slug", "", "a", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Name", "name", "", "a", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Created By", "create_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}),
          sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
          sqlb::SelectedColumn({"Updated By", "update_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}),
          sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
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


// -----


void query_clarity(Table &t) {

  t.m_table = sqlb::ObjectIdentifier("material", "clarity", "g");
  t.m_query = sqlb::Query(t.m_table);

  //m_query.setRowIdColumn("id");
  t.m_query.selectedColumns() = {
          sqlb::SelectedColumn({"Id", "id", "", "g", PG_TYPES::INT8, false}),
          //        sqlb::SelectedColumn({"Material", "material_id", "", "g", PG_TYPES::INT8, true, 1, 2}), sqlb::SelectedColumn({"m_slug", "slug", "", "m", PG_TYPES::TEXT, false, 0, 0, false}), sqlb::SelectedColumn({"m_name", "name", "", "m", PG_TYPES::TEXT, false, 0, 0, false}),
          sqlb::SelectedColumn({"Rank", "rank", "", "g", PG_TYPES::INT4, false}),
          sqlb::SelectedColumn({"Code", "slug", "", "g", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Name", "name", "", "g", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Created By", "create_user_id", "", "g", PG_TYPES::INT8, true, 1}),
          sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
          sqlb::SelectedColumn({"Updated By", "update_user_id", "", "g", PG_TYPES::INT8, true, 1}),
          sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
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

void query_shape(Table &t) {

  t.m_table = sqlb::ObjectIdentifier("material", "shape", "gs");
  t.m_query = sqlb::Query(t.m_table);

  //m_query.setRowIdColumn("id");
  t.m_query.selectedColumns() = {
          sqlb::SelectedColumn({"Id", "id", "", "gs", PG_TYPES::INT8, false}),
          //        sqlb::SelectedColumn({"Material", "material_id", "", "gs", PG_TYPES::INT8, true, 1, 2}), sqlb::SelectedColumn({"m_slug", "slug", "", "m", PG_TYPES::TEXT, false, 0, 0, false}), sqlb::SelectedColumn({"m_name", "name", "", "m", PG_TYPES::TEXT, false, 0, 0, false}),
          sqlb::SelectedColumn({"Rank", "rank", "", "gs", PG_TYPES::INT4, false}),
          sqlb::SelectedColumn({"Code", "slug", "", "gs", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Name", "name", "", "gs", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Created By", "create_user_id", "", "gs", PG_TYPES::INT8, true, 1}),
          sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
          sqlb::SelectedColumn({"Updated By", "update_user_id", "", "gs", PG_TYPES::INT8, true, 1}),
          sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
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

void query_d_color(Table &t) {

  t.m_table = sqlb::ObjectIdentifier("material", "diamond_color", "gt");
  t.m_query = sqlb::Query(t.m_table);

  //m_query.setRowIdColumn("id");
  t.m_query.selectedColumns() = {
          sqlb::SelectedColumn({"Id", "id", "", "gt", PG_TYPES::INT8, false}),
          sqlb::SelectedColumn({"Rank", "rank", "", "gt", PG_TYPES::INT4, false}),
          sqlb::SelectedColumn({"Code", "slug", "", "gt", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Name", "name", "", "gt", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Created By", "create_user_id", "", "gt", PG_TYPES::INT8, true, 1}),
          sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
          sqlb::SelectedColumn({"Updated By", "update_user_id", "", "gt", PG_TYPES::INT8, true, 1}),
          sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
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

void query_cs_color(Table &t) {

  t.m_table = sqlb::ObjectIdentifier("material", "cs_color", "gt");
  t.m_query = sqlb::Query(t.m_table);

  //m_query.setRowIdColumn("id");
  t.m_query.selectedColumns() = {
          sqlb::SelectedColumn({"Id", "id", "", "gt", PG_TYPES::INT8, false}),
          sqlb::SelectedColumn({"Rank", "rank", "", "gt", PG_TYPES::INT4, false}),
          sqlb::SelectedColumn({"Code", "slug", "", "gt", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Name", "name", "", "gt", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Created By", "create_user_id", "", "gt", PG_TYPES::INT8, true, 1}),
          sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
          sqlb::SelectedColumn({"Updated By", "update_user_id", "", "gt", PG_TYPES::INT8, true, 1}),
          sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
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
void query_cs_type(Table &t) {

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

void query_size(Table &t) {
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


void query_diamond_size(Table &t) {

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

void query_color_stone_size(Table &t) {

  t.m_table = sqlb::ObjectIdentifier("material", "color_stone_size_meta", "sm");
  t.m_query = sqlb::Query(t.m_table);

  //m_query.setRowIdColumn("id");
  t.m_query.selectedColumns() = {
          sqlb::SelectedColumn({"Id", "id", "", "sm", PG_TYPES::INT8, false}),
          sqlb::SelectedColumn({"Type", "cs_type_id", "", "sm", PG_TYPES::INT8, true, 1, 1}), sqlb::SelectedColumn({"type_name", "name", "", "cs_type", PG_TYPES::TEXT, false, 0, 0, false}),
          sqlb::SelectedColumn({"Shape", "shape_id", "", "sm", PG_TYPES::INT8, true, 2, 2}), sqlb::SelectedColumn({"shape_slug", "slug", "", "shape", PG_TYPES::TEXT, false, 0, 0, false}), sqlb::SelectedColumn({"shape_name", "name", "", "shape", PG_TYPES::TEXT, false, 0, 0, false}),
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

  auto type = sqlb::ObjectIdentifier("material", "cs_type", "cs_type");
  auto size = sqlb::ObjectIdentifier("material", "size", "size");
  //    auto clarity = sqlb::ObjectIdentifier("material", "clarity", "clarity");
  auto shape = sqlb::ObjectIdentifier("material", "shape", "shape");
  //    auto color = sqlb::ObjectIdentifier("material", "cs_color", "color");
  auto currency = sqlb::ObjectIdentifier("setting", "currency", "currency");
  auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
  auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

  t.m_query.joins() = {
          sqlb::Join("left", type, "cs_type.id = sm.cs_type_id"),
          sqlb::Join("left", size, "size.id = sm.size_id"),
          //        sqlb::Join("left", clarity, "clarity.id = sm.clarity_id"),
          sqlb::Join("left", shape, "shape.id = sm.shape_id"),
          //        sqlb::Join("left", color, "color.id = sm.color_id"),
          sqlb::Join("left", currency, "currency.id = sm.currency_id"),
          sqlb::Join("left", u1, "sm.create_user_id = u1.id"),
          sqlb::Join("left", u2, "sm.update_user_id = u2.id"),
  };

}

