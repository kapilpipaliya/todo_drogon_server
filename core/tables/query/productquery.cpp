#include "productquery.h"
#include <boost/filesystem.hpp>
#include "../../strfns.h"

//--------------Products
void query_product_options(Table &t) {

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


void query_product(Table &t) {
  t.m_table = sqlb::ObjectIdentifier("post", "post", "post");
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

          sqlb::SelectedColumn({"Product Id", "id", "p.id", "p", PG_TYPES::INT8, false}),
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
          sqlb::SelectedColumn({"On sale", "onsale", "", "p", PG_TYPES::BOOL, true}),
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
          sqlb::SelectedColumn({"Product Type", "product_type", "", "p", PG_TYPES::ENUM, true}),
          sqlb::SelectedColumn(
                  {"Tags", "name", "json_agg(distinct tags.name ORDER BY tags.name ASC)", "tags", PG_TYPES::PSJSON,
                   true}),
          sqlb::SelectedColumn(
                  {"category_id", "category_id", "json_agg(distinct pc.category_id)", "pc", PG_TYPES::PSJSON, false}),
          sqlb::SelectedColumn({"Categories", "category_id_name", "json_agg(distinct c.name)", "pc", PG_TYPES::PSJSON,
                                true}),  // This is to Display on Main Table only.
          sqlb::SelectedColumn(
                  {"tone_id", "tone_id", "json_agg(distinct p_tones.tone_id)", "p_tones", PG_TYPES::PSJSON, false}),
          sqlb::SelectedColumn(
                  {"Tones", "tone_id_name", "json_agg(distinct tones.name)", "tones", PG_TYPES::PSJSON, true}),
          sqlb::SelectedColumn({"clarity_id", "clarity_id",
                                "json_agg(distinct jsonb_build_array(p_clarity.clarity_id, p_clarity.pcs, p_clarity.weight, p_clarity.price, p_clarity.ismain))",
                                "p_clarity", PG_TYPES::PSJSON, false}),
          sqlb::SelectedColumn({"purity_id", "purity_id",
                                "json_agg(distinct jsonb_build_array(p_purities.purity_id, COALESCE(pu_tone.pt2, jsonb_build_array()), p_purities.ismain))",
                                "p_purities", PG_TYPES::PSJSON, false}),
          sqlb::SelectedColumn(
                  {"Purities", "purity_id_name", "json_agg(distinct purities.name)", "purities", PG_TYPES::PSJSON,
                   true}), // This is to Display on Main Table only.
          sqlb::SelectedColumn({"attachement_id", "attachement_id",
                                "json_agg( distinct jsonb_build_array(p_attachments.id, p_attachments.tone_id, 0, p_attachments.main_image))",
                                "p_attachments", PG_TYPES::PSJSON, false}),
          sqlb::SelectedColumn({"diamond_size_id", "diamond_size_id",
                                "json_agg( distinct jsonb_build_array(p_d_size.id, p_d_size.shape_id, p_d_size.color_id, p_d_size.size_id, p_d_size.pcs, p_d_size.setting_type_id, diamond_price.pa))",
                                "p_d_size", PG_TYPES::PSJSON, false}),
          sqlb::SelectedColumn({"cs_size_id", "cs_size_id",
                                "json_agg( distinct jsonb_build_array(p_cs_size.id, p_cs_size.cs_type_id, p_cs_size.shape_id, p_cs_size.color_id, p_cs_size.size_id, p_cs_size.pcs, p_cs_size.setting_type_id, cs_price.pa))",
                                "p_cs_size", PG_TYPES::PSJSON, false}),
          sqlb::SelectedColumn({"p_cs_total", "p_cs_total",
                                "json_agg( distinct jsonb_build_array(p_cs_total.pcs, p_cs_total.weight, p_cs_total.price))",
                                "p_cs_total", PG_TYPES::PSJSON, false}),
          sqlb::SelectedColumn({"Low Stock Amount", "low_stock_amount", "", "p", PG_TYPES::INT4, true}),
          sqlb::SelectedColumn({"Sold Individually", "sold_individually", "", "p", PG_TYPES::BOOL, false}),
          sqlb::SelectedColumn({"Making Charges", "making_charges", "", "p", PG_TYPES::DOUBLE, false}),
          sqlb::SelectedColumn({"Discount Per", "discount_per", "", "p", PG_TYPES::DOUBLE, false}),
          sqlb::SelectedColumn({"Volume", "volume", "", "p", PG_TYPES::DOUBLE, false}),
          sqlb::SelectedColumn({"Tone", "tone_id", "", "p", PG_TYPES::INT8, false}),
          sqlb::SelectedColumn({"Certified By", "certified_by", "json_agg(distinct p_certified_by.certified_by_id)", "p_certified_by", PG_TYPES::PSJSON, false}),
          sqlb::SelectedColumn({"Policy", "post_policy", "json_agg(distinct p_policy.policy_id)", "p_policy", PG_TYPES::PSJSON, false}),

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
  auto post_tag = sqlb::ObjectIdentifier("post", "post_tag", "post_tag");
  auto tags = sqlb::ObjectIdentifier("post", "tag", "tags");
  auto ptones = sqlb::ObjectIdentifier("product", "post_tone", "p_tones");
  auto tones = sqlb::ObjectIdentifier("material", "tone", "tones");
  auto pclarity = sqlb::ObjectIdentifier("product", "post_clarity", "p_clarity");
  auto ppurities = sqlb::ObjectIdentifier("product", "post_purity", "p_purities");
  auto purities = sqlb::ObjectIdentifier("material", "purity", "purities");
  auto post_attachment = sqlb::ObjectIdentifier("product", "post_attachment", "p_attachments");
  auto p_d_size = sqlb::ObjectIdentifier("product", "post_diamond_size", "p_d_size");
  //auto diamond_price = sqlb::ObjectIdentifier("product", "diamond_price", "diamond_price");
  auto p_cs_size = sqlb::ObjectIdentifier("product", "post_color_stone_size", "p_cs_size");
  auto p_cs_total = sqlb::ObjectIdentifier("product", "post_cs_total", "p_cs_total");
  auto p_certified_by = sqlb::ObjectIdentifier("product", "post_certified_by", "p_certified_by");
  auto p_policy = sqlb::ObjectIdentifier("product", "post_policy", "p_policy");
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
          sqlb::Join("left",
                     "( select pt.post_id, pt.purity_id, jsonb_agg(distinct jsonb_build_array(pt.tone_id, pt.weight, pt.price, pt.ismain)) as pt2 from product.purity_tone pt group by pt.post_id, pt.purity_id) as pu_tone",
                     "(pu_tone.post_id = p_purities.post_id and pu_tone.purity_id = p_purities.purity_id)"),
          sqlb::Join("left", purities, "purities.id = p_purities.purity_id"),
          sqlb::Join("left", post_attachment, "p_attachments.post_id = post.id"),
          sqlb::Join("left", p_d_size, "p_d_size.post_id = post.id"),
          sqlb::Join("left", p_cs_size, "p_cs_size.post_id = post.id"),
          sqlb::Join("left", p_cs_total, "p_cs_total.post_id = post.id"),
          sqlb::Join("left", p_certified_by, "p_certified_by.post_id = post.id"),
      sqlb::Join("left", p_policy, "p_policy.post_id = post.id"),

          sqlb::Join("left",
                     "(SELECT dp.diamond_id, jsonb_agg( distinct jsonb_build_array(dp.clarity_id, mc.name, dp.weight, dp.total_weight, dp.rate, dp.price)) AS pa FROM product.diamond_price dp left join material.clarity mc on mc.id = dp.clarity_id group by dp.diamond_id) as diamond_price",
                     "diamond_price.diamond_id = p_d_size.id"),
          sqlb::Join("left",
                     "(SELECT dp.cs_id, jsonb_agg( distinct jsonb_build_array(0, '', dp.weight, dp.total_weight, dp.rate, dp.price)) AS pa FROM product.cs_price dp group by dp.cs_id) as cs_price",
                     "cs_price.cs_id = p_cs_size.id"),


          //sqlb::Join("left", u1, "gt.create_user_id = u1.id"),
          //sqlb::Join("left", u2, "a.update_user_id = u2.id"),
  };

  t.m_query.groupBy() = {
          sqlb::GroupByColumn("post", "id"),
          sqlb::GroupByColumn("p", "id"),
  };

}

void query_category(Table &t) {
  t.m_table = sqlb::ObjectIdentifier("product", "category", "c");
  t.m_query = sqlb::Query(t.m_table);

  //m_query.setRowIdColumn("id");
  t.m_query.selectedColumns() = {
          sqlb::SelectedColumn({"Id", "id", "", "c", PG_TYPES::INT8, false}),
          sqlb::SelectedColumn({"Parent", "parent_id", "", "c", PG_TYPES::INT8, true, 2, 1}),
          sqlb::SelectedColumn({"p_slug", "slug", "", "p", PG_TYPES::TEXT, false, 0, 0, false}),
          sqlb::SelectedColumn({"p_name", "name", "", "p", PG_TYPES::TEXT, false, 0, 0, false}),
          sqlb::SelectedColumn({"Position", "position", "", "c", PG_TYPES::INT8, true}),
          sqlb::SelectedColumn({"Name", "name", "", "c", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Code", "slug", "", "c", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Description", "description", "", "c", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Display Type", "display_type", "", "c", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Created By", "create_user_id", "", "c", PG_TYPES::INT8, true, 1, 0, false}),
          sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
          sqlb::SelectedColumn({"Updated By", "update_user_id", "", "c", PG_TYPES::INT8, true, 1, 0, false}),
          sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
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



void query_shipping_class(Table &t) {

  t.m_table = sqlb::ObjectIdentifier("product", "shipping_class", "t");
  t.m_query = sqlb::Query(t.m_table);

  //m_query.setRowIdColumn("id");
  t.m_query.selectedColumns() = {
          sqlb::SelectedColumn({"Id", "id", "", "t", PG_TYPES::INT8, false}),
          sqlb::SelectedColumn({"Code", "slug", "", "t", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Name", "name", "", "t", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Description", "description", "", "t", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Product Count", "product_count", "", "t", PG_TYPES::INT4, true}),
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


void query_setting_type(Table &t) {

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

void query_certified_by(Table &t) {

  t.m_table = sqlb::ObjectIdentifier("product", "certified_by", "t");
  t.m_query = sqlb::Query(t.m_table);

  //m_query.setRowIdColumn("id");
  t.m_query.selectedColumns() = {
          sqlb::SelectedColumn({"Id", "id", "", "t", PG_TYPES::INT8, false}),
          sqlb::SelectedColumn({"Code", "slug", "", "t", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Name", "name", "", "t", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Title", "title", "", "t", PG_TYPES::TEXT, true}),
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
void query_policy(Table &t) {

        t.m_table = sqlb::ObjectIdentifier("product", "policy", "t");
    t.m_query = sqlb::Query(t.m_table);

        //m_query.setRowIdColumn("id");
        t.m_query.selectedColumns() = {
            sqlb::SelectedColumn({"Id", "id", "", "t", PG_TYPES::INT8, false}),
//            sqlb::SelectedColumn({"Code", "slug", "", "t", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Name", "name", "", "t", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Url", "url", "", "t", PG_TYPES::TEXT, true}),
            sqlb::SelectedColumn({"Description", "description", "", "t", PG_TYPES::TEXT, true}),
            //sqlb::SelectedColumn({"Created By", "create_user_id", "", "t", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
            //sqlb::SelectedColumn({"Updated By", "update_user_id", "", "t", PG_TYPES::INT8, true, 1, 0, false}), sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
            sqlb::SelectedColumn({"Create Time", "inserted_at", "", "t", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            sqlb::SelectedColumn({"Update Time", "updated_at", "", "t", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
            };

        //auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
        //auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {
            // sqlb::Join("left", u1, "t.create_user_id = u1.id"),
            // sqlb::Join("left", u2, "t.update_user_id = u2.id"),
            };
}

//--

void get_product_attachment_data(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
    // send meta_data
    Json::Value ret;
    ret[0] = "take_image_meta";
    Json::Value data;
    data[0] = event_name;
    data[1] = 0;
    ret[1] = data;
    wsConnPtr->send(ret.toStyledString());

    namespace fs = boost::filesystem;
    auto home = fs::path(getenv("HOME"));

    pqxx::work txn{DD};
    try {
        auto sql = "SELECT name FROM product.post_attachment WHERE id = $1";
        pqxx::result x = txn.exec_params(sql, in.asInt());
        txn.commit();
        if (x.size() == 1) {
            std::streampos size;
            // http://www.cplusplus.com/doc/tutorial/files/
            // What is the best way to read an entire file into a std::string in C++?
            // https://stackoverflow.com/questions/116038/what-is-the-best-way-to-read-an-entire-file-into-a-stdstring-in-c/116220#116220
            std::ifstream file(home.string() + "/fileuploads/" + x[0][0].c_str(), std::ios::in | std::ios::binary | std::ios::ate);
            if (file.is_open()) {
                auto memblock = read_all(file);
                file.close();

                //std::cout << "the entire file content is in memory";
                wsConnPtr->send(memblock, WebSocketMessageType::Binary); // Note when server not able to send this file, front end crash.
                //delete[] memblock;
            }
        } else {
            // Fix simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
        }

    } catch (const std::exception &e) {
        txn.abort();
        std::cerr << e.what() << std::endl;
        //simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }

    //get binary data and send.
    //wsConnPtr->send();
}

void get_product_diamond_price_data(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
    Json::Value jresult;
    jresult[0] = event_name;

    auto shape = in[1].asInt();
    auto color = in[2].asInt();
    auto size = in[3].asInt();
    auto pcs = in[4].asInt();

    fprintf(stdout, "%d %d %d\n", shape, color, size);
    fflush(stdout);

    std::string s = "{"; // clarity
    for (auto i : in[6]) {
        s += std::to_string(i[0].asInt()) + ",";
    }
    if (in[6].size() > 0) s.pop_back();
    s += "}";

    pqxx::work txn{DD};
    try {
        // You can't use IN (...) with arrays. You need to use an operator (ex: =, >, <, etc) and ANY/ALL
        auto sql = "SELECT clarity_id, weight, rate FROM material.diamond_size_meta WHERE shape_id = $1 AND color_id = $2 AND size_id = $3 AND  clarity_id = ANY($4::bigint[])";
        pqxx::result x = txn.exec_params(sql, shape, color, size, s);


        Json::Value d(Json::arrayValue);
        for (auto r : x) {
            Json::Value row;
            row[0] = r[0].as<int>();
            row[1] = "";
            row[2] = r[1].as<double>();
            row[3] = r[1].as<double>() * pcs;
            row[4] = r[2].as<double>();
            row[5] = r[1].as<double>() * pcs * r[2].as<double>();
            d.append(row);
        }
        jresult[1] = d;
        wsConnPtr->send(jresult.toStyledString());
        txn.commit();
    } catch (const std::exception &e) {
        txn.abort();
        std::cerr << e.what() << std::endl;
        //simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }

    //get binary data and send.
    //wsConnPtr->send();
}

void get_product_cs_price_data(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
    Json::Value jresult;
    jresult[0] = event_name;

    auto type = in[1].asInt();
    auto shape = in[2].asInt();
    auto color = in[3].asInt();
    auto size = in[4].asInt();
    auto pcs = in[5].asInt();

    pqxx::work txn{DD};
    try {
        // You can't use IN (...) with arrays. You need to use an operator (ex: =, >, <, etc) and ANY/ALL
        auto sql = "SELECT weight, rate FROM material.color_stone_size_meta WHERE cs_type_id = $1 and shape_id = $2 AND size_id = $3";
        pqxx::result x = txn.exec_params(sql, type, shape, size);

        Json::Value d(Json::arrayValue);
        for (auto r : x) {
            Json::Value row;
            row[0] = 0;
            row[1] = "";
            row[2] = r[0].as<double>();
            row[3] = r[0].as<double>() * pcs;
            row[4] = r[1].as<double>();
            row[5] = r[0].as<double>() * pcs * r[1].as<double>();
            d.append(row);
        }
        jresult[1] = d;
        wsConnPtr->send(jresult.toStyledString());
        txn.commit();
    } catch (const std::exception &e) {
        txn.abort();
        std::cerr << e.what() << std::endl;
        //simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }

    //get binary data and send.
    //wsConnPtr->send();
}

void
get_product_category_tree_data(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
    Json::Value jresult;
    jresult[0] = event_name;

    //    auto shape = in[1].asInt();
    //    auto color = in[2].asInt();
    //    auto size = in[3].asInt();
    //    auto pcs = in[4].asInt();

    pqxx::work txn{DD};
    try {
        auto sql = R"(
with recursive tree as (
  select id, array[id] as path, name, 0 as level, array[position] as position from product.category where parent_id is null
union
  select pc.id, tree.path || pc.id, pc.name, tree.level + 1, tree.position || pc.position from tree join product.category pc on (pc.parent_id = tree.id)
)
select * ,
       (repeat(' '::text, (2 * tree."level")) || (tree.name)::text) AS label
       from tree
       ORDER BY tree.position;
)";
        pqxx::result x = txn.exec_params(sql);

        Json::Value d(Json::arrayValue);
        for (auto r : x) {
            Json::Value row;
            row[0] = r[0].as<int>();
            row[1] = r[5].c_str();
            d.append(row);
        }
        jresult[1] = d;
        wsConnPtr->send(jresult.toStyledString());
        txn.commit();
    } catch (const std::exception &e) {
        txn.abort();
        std::cerr << e.what() << std::endl;
        //simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }

    //get binary data and send.
    //wsConnPtr->send();
}
