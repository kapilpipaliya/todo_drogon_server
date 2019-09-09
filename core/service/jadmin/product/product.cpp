#include "product.h"
#include <boost/filesystem.hpp>
#include <utility>
#include "../../../strfns.h"
#include "../../dba.h"
using namespace jadmin;

Product::Product(JAdminContextPtr context_) : context(std::move(context_)) {
  getQuery() = sqlb::Query(sqlb::ObjectIdentifier("post", "post", "post"));
}

void Product::setupTable() {
  // m_query.setRowIdColumn("id");
  getQuery().setSelectedColumns({
      sqlb::SelectedColumn({"Id", "id", "", "post", PG_TYPES::INT8, true}),
      // sqlb::SelectedColumn({"Directory", "dir_path", "", "p", PG_TYPES::TEXT,
      // true}), sqlb::SelectedColumn({"File Name", " "",file_name", "p",
      // PG_TYPES::TEXT, true}), sqlb::SelectedColumn({"Color", "color_id", "",
      // "p", PG_TYPES::INT8, true, 1, 2}), sqlb::SelectedColumn({"C_slug",
      // "slug", "", "c", PG_TYPES::TEXT, false, 0, 0, false}),
      // sqlb::SelectedColumn({"C_name", "name", "", "c", PG_TYPES::TEXT, false,
      // 0, 0, false}), sqlb::SelectedColumn({"Category", "part_group_id", "",
      // "p", PG_TYPES::INT8, true, 1, 2}), sqlb::SelectedColumn({"Pg_slug",
      // "slug", "", "pg", PG_TYPES::TEXT, false, 0, 0, false}),
      // sqlb::SelectedColumn({"Pg_name", "name", "", "pg", PG_TYPES::TEXT,
      // false, 0, 0, false}),
      sqlb::SelectedColumn(
          {"Purchase_Note", "purchase_note", "", "p", PG_TYPES::TEXT, false}),

      sqlb::SelectedColumn(
          {"Product Id", "id", "p.id", "p", PG_TYPES::INT8, false}),
      sqlb::SelectedColumn({"Product_short_description", "excerpt", "", "post",
                            PG_TYPES::TEXT, false}),
      sqlb::SelectedColumn(
          {"Product_Content", "content", "", "post", PG_TYPES::TEXT, false}),
      sqlb::SelectedColumn(
          {"Menu_Order", "menu_order", "", "post", PG_TYPES::INT8, false}),
      sqlb::SelectedColumn(
          {"Date", "date", "", "post", PG_TYPES::TIMESTAMP, true}),
      sqlb::SelectedColumn(
          {"Title", "title", "", "post", PG_TYPES::TEXT, true}),
      sqlb::SelectedColumn({"Slug", "name", "", "post", PG_TYPES::TEXT, true}),
      sqlb::SelectedColumn(
          {"Status", "status", "", "post", PG_TYPES::ENUM, true}),
      sqlb::SelectedColumn(
          {"Comment", "comment_status", "", "post", PG_TYPES::BOOL, true}),
      sqlb::SelectedColumn(
          {"Password", "password", "", "post", PG_TYPES::TEXT, false}),
      sqlb::SelectedColumn(
          {"Modified", "modified", "", "post", PG_TYPES::TIMESTAMP, true}),
      sqlb::SelectedColumn(
          {"Parent", "parent", "", "post", PG_TYPES::INT8, true}),
      sqlb::SelectedColumn(
          {"Post Type", "type", "", "post", PG_TYPES::ENUM, true}),
      sqlb::SelectedColumn(
          {"MIME Type", "post_mime_type", "", "post", PG_TYPES::ENUM, false}),
      sqlb::SelectedColumn(
          {"Comment Count", "comment_count", "", "post", PG_TYPES::INT8, true}),

      sqlb::SelectedColumn({"SKU", "sku", "", "p", PG_TYPES::TEXT, true}),
      sqlb::SelectedColumn(
          {"Virtual", "virtual", "", "p", PG_TYPES::BOOL, false}),
      sqlb::SelectedColumn(
          {"Downloadable", "downloadable", "", "p", PG_TYPES::BOOL, false}),
      sqlb::SelectedColumn(
          {"Min Price", "min_price", "", "p", PG_TYPES::DOUBLE, false}),
      sqlb::SelectedColumn(
          {"Max Price", "max_price", "", "p", PG_TYPES::DOUBLE, false}),
      sqlb::SelectedColumn(
          {"Weight", "weight", "", "p", PG_TYPES::DOUBLE, true}),
      sqlb::SelectedColumn(
          {"Purity", "purity_id", "", "p", PG_TYPES::INT8, true}),
      sqlb::SelectedColumn(
          {"Length", "length", "", "p", PG_TYPES::DOUBLE, true}),
      sqlb::SelectedColumn({"Width", "width", "", "p", PG_TYPES::DOUBLE, true}),
      sqlb::SelectedColumn(
          {"Height", "height", "", "p", PG_TYPES::DOUBLE, true}),
      sqlb::SelectedColumn(
          {"On sale", "onsale", "", "p", PG_TYPES::BOOL, true}),
      sqlb::SelectedColumn({"Stock Quantity", "stock_quantity", "", "p",
                            PG_TYPES::DOUBLE, true}),
      sqlb::SelectedColumn(
          {"Stock Status", "stock_status", "", "p", PG_TYPES::ENUM, true}),
      sqlb::SelectedColumn(
          {"Rating Count", "rating_count", "", "p", PG_TYPES::INT4, true}),
      sqlb::SelectedColumn({"Average Rating", "average_rating", "", "p",
                            PG_TYPES::DOUBLE, true}),
      sqlb::SelectedColumn(
          {"Total Sales", "total_sales", "", "p", PG_TYPES::INT8, true}),
      sqlb::SelectedColumn(
          {"Featured", "featured", "", "p", PG_TYPES::BOOL, true}),
      sqlb::SelectedColumn({"Shipping Class", "shipping_class_id", "", "p",
                            PG_TYPES::INT8, true}),
      sqlb::SelectedColumn(
          {"Manage Stock", "manage_stock", "", "p", PG_TYPES::BOOL, false}),
      sqlb::SelectedColumn(
          {"Visibility", "visibility", "", "post", PG_TYPES::ENUM, true}),
      sqlb::SelectedColumn({"Catalog Visibility", "catalog_visibility", "", "p",
                            PG_TYPES::ENUM, true}),
      sqlb::SelectedColumn(
          {"Backorders", "backorders", "", "p", PG_TYPES::ENUM, true}),
      sqlb::SelectedColumn(
          {"Product Type", "product_type", "", "p", PG_TYPES::ENUM, true}),
      sqlb::SelectedColumn(
          {"Tags", "name",
           "json_agg(distinct tags.name ORDER BY tags.name ASC)", "tags",
           PG_TYPES::PSJSON, true}),
      sqlb::SelectedColumn({"category_id", "category_id",
                            "json_agg(distinct pc.category_id)", "pc",
                            PG_TYPES::PSJSON, false}),
      sqlb::SelectedColumn({"Categories", "category_id_name",
                            "json_agg(distinct c.name)", "pc", PG_TYPES::PSJSON,
                            true}),  // This is to Display on Main Table only.
      sqlb::SelectedColumn({"tone_id", "tone_id",
                            "json_agg(distinct p_tones.tone_id)", "p_tones",
                            PG_TYPES::PSJSON, false}),
      sqlb::SelectedColumn({"Tones", "tone_id_name",
                            "json_agg(distinct tones.name)", "tones",
                            PG_TYPES::PSJSON, true}),
      sqlb::SelectedColumn(
          {"clarity_id", "clarity_id",
           "json_agg(distinct jsonb_build_array(p_clarity.clarity_id, "
           "p_clarity.pcs, p_clarity.weight, p_clarity.price, "
           "p_clarity.ismain))",
           "p_clarity", PG_TYPES::PSJSON, false}),
      sqlb::SelectedColumn(
          {"purity_id", "purity_id",
           "json_agg(distinct jsonb_build_array(p_purities.purity_id, "
           "COALESCE(pu_tone.pt2, jsonb_build_array()), p_purities.ismain))",
           "p_purities", PG_TYPES::PSJSON, false}),
      sqlb::SelectedColumn({"Purities", "purity_id_name",
                            "json_agg(distinct purities.name)", "purities",
                            PG_TYPES::PSJSON,
                            true}),  // This is to Display on Main Table only.
      sqlb::SelectedColumn(
          {"attachement_id", "attachement_id",
           "json_agg( distinct jsonb_build_array(p_attachments.id, "
           "p_attachments.tone_id, 0, p_attachments.main_image, version))",
           "p_attachments", PG_TYPES::PSJSON, false}),
      sqlb::SelectedColumn(
          {"diamond_size_id", "diamond_size_id",
           "json_agg( distinct jsonb_build_array(p_d_size.id, "
           "p_d_size.shape_id, p_d_size.color_id, p_d_size.size_id, "
           "p_d_size.pcs, p_d_size.setting_type_id, diamond_price.pa))",
           "p_d_size", PG_TYPES::PSJSON, false}),
      sqlb::SelectedColumn(
          {"cs_size_id", "cs_size_id",
           "json_agg( distinct jsonb_build_array(p_cs_size.id, "
           "p_cs_size.cs_type_id, p_cs_size.shape_id, p_cs_size.color_id, "
           "p_cs_size.size_id, p_cs_size.pcs, p_cs_size.setting_type_id, "
           "cs_price.pa))",
           "p_cs_size", PG_TYPES::PSJSON, false}),
      sqlb::SelectedColumn(
          {"p_cs_total", "p_cs_total",
           "json_agg( distinct jsonb_build_array(p_cs_total.pcs, "
           "p_cs_total.weight, p_cs_total.price))",
           "p_cs_total", PG_TYPES::PSJSON, false}),
      sqlb::SelectedColumn({"Low Stock Amount", "low_stock_amount", "", "p",
                            PG_TYPES::INT4, true}),
      sqlb::SelectedColumn({"Sold Individually", "sold_individually", "", "p",
                            PG_TYPES::BOOL, false}),
      sqlb::SelectedColumn({"Making Charges", "making_charges", "", "p",
                            PG_TYPES::DOUBLE, false}),
      sqlb::SelectedColumn(
          {"Discount Per", "discount_per", "", "p", PG_TYPES::DOUBLE, false}),
      sqlb::SelectedColumn(
          {"Volume", "volume", "", "p", PG_TYPES::DOUBLE, false}),
      sqlb::SelectedColumn({"Tone", "tone_id", "", "p", PG_TYPES::INT8, false}),
      sqlb::SelectedColumn({"Certified By", "certified_by",
                            "json_agg(distinct p_certified_by.certified_by_id)",
                            "p_certified_by", PG_TYPES::PSJSON, false}),
      sqlb::SelectedColumn({"Policy", "post_policy",
                            "json_agg(distinct p_policy.policy_id)", "p_policy",
                            PG_TYPES::PSJSON, false}),

      // sqlb::SelectedColumn({"Create Time", "inserted_at", "", "p",
      // PG_TYPES::TIMESTAMP, true, 0, 0, false}), sqlb::SelectedColumn({"Update
      // Time", "updated_at", "", "p", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  });
  // select json_agg(nlohmann::json_build_array(a,b,c)) from (values (1, 'foo',
  // true),(2,'bar',false)) v(a,b,c); --> [[1, "foo", true], [2, "bar", false]]
  /*
    "id"

    "modified"
    "parent"
    "type"
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
  auto pclarity =
      sqlb::ObjectIdentifier("product", "post_clarity", "p_clarity");
  auto ppurities =
      sqlb::ObjectIdentifier("product", "post_purity", "p_purities");
  auto purities = sqlb::ObjectIdentifier("material", "purity", "purities");
  auto post_attachment =
      sqlb::ObjectIdentifier("product", "post_attachment", "p_attachments");
  auto p_d_size =
      sqlb::ObjectIdentifier("product", "post_diamond_size", "p_d_size");
  // auto diamond_price = sqlb::ObjectIdentifier("product", "diamond_price",
  // "diamond_price");
  auto p_cs_size =
      sqlb::ObjectIdentifier("product", "post_color_stone_size", "p_cs_size");
  auto p_cs_total =
      sqlb::ObjectIdentifier("product", "post_cs_total", "p_cs_total");
  auto p_certified_by =
      sqlb::ObjectIdentifier("product", "post_certified_by", "p_certified_by");
  auto p_policy = sqlb::ObjectIdentifier("product", "post_policy", "p_policy");
  // auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
  // auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

  getQuery().setJoins({
      // sqlb::Join("left", c, "p.color_id = c.id"),
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
                 "( select pt.post_id, pt.purity_id, jsonb_agg(distinct "
                 "jsonb_build_array(pt.tone_id, pt.weight, pt.price, "
                 "pt.ismain)) as pt2 from product.purity_tone pt group by "
                 "pt.post_id, pt.purity_id) as pu_tone",
                 "(pu_tone.post_id = p_purities.post_id and pu_tone.purity_id "
                 "= p_purities.purity_id)"),
      sqlb::Join("left", purities, "purities.id = p_purities.purity_id"),
      sqlb::Join("left", post_attachment, "p_attachments.post_id = post.id"),
      sqlb::Join("left", p_d_size, "p_d_size.post_id = post.id"),
      sqlb::Join("left", p_cs_size, "p_cs_size.post_id = post.id"),
      sqlb::Join("left", p_cs_total, "p_cs_total.post_id = post.id"),
      sqlb::Join("left", p_certified_by, "p_certified_by.post_id = post.id"),
      sqlb::Join("left", p_policy, "p_policy.post_id = post.id"),

      sqlb::Join(
          "left",
          "(SELECT dp.diamond_id, jsonb_agg( distinct "
          "jsonb_build_array(dp.clarity_id, mc.name, dp.weight, "
          "dp.total_weight, dp.rate, dp.price)) AS pa FROM "
          "product.diamond_price dp left join material.clarity mc on mc.id = "
          "dp.clarity_id group by dp.diamond_id) as diamond_price",
          "diamond_price.diamond_id = p_d_size.id"),
      sqlb::Join("left",
                 "(SELECT dp.cs_id, jsonb_agg( distinct jsonb_build_array(0, "
                 "'', dp.weight, dp.total_weight, dp.rate, dp.price)) AS pa "
                 "FROM product.cs_price dp group by dp.cs_id) as cs_price",
                 "cs_price.cs_id = p_cs_size.id"),

      // sqlb::Join("left", u1, "gt.create_user_id = u1.id"),
      // sqlb::Join("left", u2, "a.update_user_id = u2.id"),
  });

  getQuery().setGroupBy({
      sqlb::GroupByColumn("post", "id"),
      sqlb::GroupByColumn("p", "id"),
  });
}

nlohmann::json Product::handleEvent(nlohmann::json event, int next,
                                    const nlohmann::json& args) {
  auto event_cmp = event[next].get<std::string>();
  if (event_cmp == "data") {
    return allData(event, args);
  }
  if (event_cmp == "header") {
    return headerData(event, args);
  } else if (event_cmp == "ins") {
    return ins(event, args);
  } else if (event_cmp == "upd") {
    return upd(event, args);
  } else if (event_cmp == "del") {
    return del(event, args);

  } else if (event_cmp == "diamond_price_data") {
    return get_product_diamond_price_data(event, args);
  } else if (event_cmp == "cs_price_data") {
    return get_product_cs_price_data(event, args);
  } else if (event_cmp == "categorytreedata") {
    return get_product_category_tree_data(event, args);
  } else {
    nlohmann::json ret;
    return ret;
  }
}

#define purejoinTableSave(f, t, inKey, id1, id2)                              \
  void save_product_##f(nlohmann::json& args,                                 \
                        std::shared_ptr<Transaction> transPtr, long idv1) {   \
    std::string strSqlPostCategories =                                        \
        "SELECT " id1 ", " id2 " FROM " t " where " id1 " = $1";              \
    std::string strSqlPostCategorySimpleFind =                                \
        "SELECT * FROM " t " WHERE " id1 " = $1 and " id2 " = $2";            \
    std::string strSqlPostCategoryDel =                                       \
        "DELETE FROM " t " WHERE " id1 " = $1 and " id2 " = $2";              \
    std::string strSqlPostCategoryInsert =                                    \
        "INSERT INTO " t " (" id1 ", " id2 ") VALUES ($1, $2);";              \
    std::vector<long> inNewTones;                                             \
    for (auto i : args[inKey]) {                                              \
      if (!i.is_null()) inNewTones.push_back(i);                              \
    }                                                                         \
                                                                              \
    auto all_ct = Dba::writeInTrans(transPtr, strSqlPostCategories, idv1);    \
    /* For each saved tones, If saved tone not exist in new tones, delete     \
     * it.*/                                                                  \
    for (auto r : all_ct) {                                                   \
      std::vector<long>::iterator it =                                        \
          std::find(inNewTones.begin(), inNewTones.end(), r[1].as<long>());   \
      if (it == inNewTones.end()) { /* Element not Found*/                    \
        Dba::writeInTrans(transPtr, strSqlPostCategoryDel, r[id1].as<long>(), \
                          r[id2].as<long>());                                 \
      }                                                                       \
    }                                                                         \
    /* For each new tones, insert it if it not already exist.*/               \
    for (auto x : inNewTones) {                                               \
      auto y =                                                                \
          Dba::writeInTrans(transPtr, strSqlPostCategorySimpleFind, idv1, x); \
      if (y.size() == 0) {                                                    \
        Dba::writeInTrans(transPtr, strSqlPostCategoryInsert, idv1, x);       \
      }                                                                       \
    }                                                                         \
  }

void purejoinTableSaveF(const std::string& t, nlohmann::json& args,
                        const std::shared_ptr<Transaction>& transPtr,
                        const std::string& inKey, const std::string& id1,
                        const std::string& id2, long idv1) {
  std::string strSqlPostCategories =
      "SELECT " + id1 + ", " + id2 + " FROM " + t + " where " + id1 + " = $1";
  std::string strSqlPostCategorySimpleFind =
      "SELECT * FROM " + t + " WHERE " + id1 + " = $1 and " + id2 + " = $2";
  std::string strSqlPostCategoryDel =
      "DELETE FROM " + t + " WHERE " + id1 + " = $1 and " + id2 + " = $2";
  std::string strSqlPostCategoryInsert =
      "INSERT INTO " + t + " (" + id1 + ", " + id2 + ") VALUES ($1, $2);";
  std::vector<long> inNewTones;
  for (const auto& i : args[0][inKey]) {
    if (!i.is_null()) inNewTones.push_back(i);
  }

  auto all_ct = Dba::writeInTrans(transPtr, strSqlPostCategories, idv1);
  /* For each saved tones, If saved tone not exist in new tones, delete it.*/
  for (const auto& r : all_ct) {
    auto it = std::find(inNewTones.begin(), inNewTones.end(), r[1].as<long>());
    if (it == inNewTones.end()) { /* Element not Found*/
      Dba::writeInTrans(transPtr, strSqlPostCategoryDel, r[id1].as<long>(),
                        r[id2].as<long>());
    }
  }
  /* For each new tones, insert it if it not already exist.*/
  for (auto x : inNewTones) {
    auto y = Dba::writeInTrans(transPtr, strSqlPostCategorySimpleFind, idv1, x);
    if (y.empty()) {
      Dba::writeInTrans(transPtr, strSqlPostCategoryInsert, idv1, x);
    }
  }
}

purejoinTableSave(tones, "product.post_tone", "p_tones_tone_id", "post_id",
                  "tone_id");
purejoinTableSave(certified_by, "product.post_certified_by",
                  "p_certified_by_certified_by", "post_id", "certified_by_id");
purejoinTableSave(policy, "product.post_policy", "p_policy_post_policy",
                  "post_id", "policy_id");

void product_tags_process(const sqlb::ObjectIdentifier& tags_table,
                          const sqlb::ObjectIdentifier& post_tag_table,
                          nlohmann::json& args,
                          const std::shared_ptr<Transaction>& transPtr,
                          long post_id) {
  std::string strSqlTag = "select id, name FROM %1.%2 where name = $1";
  ReplaceAll2(strSqlTag, "%1", tags_table.schema());
  ReplaceAll2(strSqlTag, "%2", tags_table.name());

  std::string strSqlTagInsert =
      "INSERT INTO post.tag (name, slug, description) VALUES ($1, $2, $3)";
  ReplaceAll2(strSqlTagInsert, "%1", tags_table.schema());
  ReplaceAll2(strSqlTagInsert, "%2", tags_table.name());

  // post_tag
  std::string strSqlPostTags =
      "select pt.post_id, pt.tag_id, t.name FROM %1.%2 pt left join %3.%4 t on "
      "t.id = pt.tag_id where post_id = $1";
  ReplaceAll2(strSqlPostTags, "%1", post_tag_table.schema());
  ReplaceAll2(strSqlPostTags, "%2", post_tag_table.name());
  ReplaceAll2(strSqlPostTags, "%3", tags_table.schema());
  ReplaceAll2(strSqlPostTags, "%4", tags_table.name());

  std::string strSqlPostTagSimpleFind =
      "SELECT * FROM %1.%2 WHERE post_id = $1 and tag_id = $2";
  ReplaceAll2(strSqlPostTagSimpleFind, "%1", post_tag_table.schema());
  ReplaceAll2(strSqlPostTagSimpleFind, "%2", post_tag_table.name());

  std::string strSqlPostTagsDel =
      "DELETE FROM %1.%2 WHERE post_id = $1 and tag_id = $2";
  ReplaceAll2(strSqlPostTagsDel, "%1", post_tag_table.schema());
  ReplaceAll2(strSqlPostTagsDel, "%2", post_tag_table.name());

  std::string strSqlPostTagsInsert =
      "INSERT INTO %1.%2 (post_id, tag_id) VALUES ($1, $2);";
  ReplaceAll2(strSqlPostTagsInsert, "%1", post_tag_table.schema());
  ReplaceAll2(strSqlPostTagsInsert, "%2", post_tag_table.name());

  auto inNewTags = args[0]["tags_name"].get<std::string>();
  std::vector<std::string> inNewTagsVector;
  std::stringstream ss{inNewTags};
  std::string tag;
  // 1.find a tag, if not exist then insert.
  while (ss >> tag) {
    inNewTagsVector.push_back(tag);
    auto x = Dba::writeInTrans(transPtr, strSqlTag, tag);
    if (x.empty()) {
      Dba::writeInTrans(transPtr, strSqlTagInsert, tag, tag, tag);
    }
  }
  auto all_pt = Dba::writeInTrans(transPtr, strSqlPostTags, post_id);
  // For each saved tags, If saved tag not exist in new tags, delete it.
  for (const auto& r : all_pt) {
    if (inNewTags.find(r[2].c_str()) == std::string::npos) {
      Dba::writeInTrans(transPtr, strSqlPostTagsDel, r["post_id"].as<long>(),
                        r["tag_id"].as<long>());
    }
  }
  // For each new tags, insert it if it not already exist.
  for (const auto& r : inNewTagsVector) {
    auto x = Dba::writeInTrans(transPtr, strSqlTag, r);

    auto y = Dba::writeInTrans(transPtr, strSqlPostTagSimpleFind, post_id,
                               x[0]["id"].as<long>());
    if (y.empty()) {
      Dba::writeInTrans(transPtr, strSqlPostTagsInsert, post_id,
                        x[0]["id"].as<long>());
    }
  }
}

void save_product_categories(const sqlb::ObjectIdentifier& post_category_table,
                             nlohmann::json& args,
                             const std::shared_ptr<Transaction>& transPtr,
                             long post_id) {
  std::string strSqlPostCategories =
      "select post_id, category_id FROM %1.%2 where post_id = $1";
  ReplaceAll2(strSqlPostCategories, "%1", post_category_table.schema());
  ReplaceAll2(strSqlPostCategories, "%2", post_category_table.name());

  std::string strSqlPostCategorySimpleFind =
      "SELECT * FROM %1.%2 WHERE post_id = $1 and category_id = $2";
  ReplaceAll2(strSqlPostCategorySimpleFind, "%1", post_category_table.schema());
  ReplaceAll2(strSqlPostCategorySimpleFind, "%2", post_category_table.name());

  std::string strSqlPostCategoryDel =
      "DELETE FROM %1.%2 WHERE post_id = $1 and category_id = $2";
  ReplaceAll2(strSqlPostCategoryDel, "%1", post_category_table.schema());
  ReplaceAll2(strSqlPostCategoryDel, "%2", post_category_table.name());

  std::string strSqlPostCategoryInsert =
      "INSERT INTO %1.%2 (post_id, category_id) VALUES ($1, $2);";
  ReplaceAll2(strSqlPostCategoryInsert, "%1", post_category_table.schema());
  ReplaceAll2(strSqlPostCategoryInsert, "%2", post_category_table.name());

  std::vector<long> inNewCategories;
  for (const auto& x : args[0]["pc_category_id"])
    if (!x.is_null()) inNewCategories.push_back(x.get<long>());

  // std::vector<long>updatedCategories;

  auto all_ct = Dba::writeInTrans(transPtr, strSqlPostCategories, post_id);
  // For each saved categories, If saved category not exist in new categories,
  // delete it.
  for (const auto& r : all_ct) {
    auto it = std::find(inNewCategories.begin(), inNewCategories.end(),
                        r[1].as<long>());
    if (it == inNewCategories.end()) {  // Element not Found
      Dba::writeInTrans(transPtr, strSqlPostCategoryDel,
                        r["post_id"].as<long>(), r[1].as<long>());
      // updatedCategories.push_back(r[1].as<long>());
    }
  }

  // For each new categories, insert it if it not already exist.
  for (auto x : inNewCategories) {
    auto y =
        Dba::writeInTrans(transPtr, strSqlPostCategorySimpleFind, post_id, x);
    if (y.empty()) {
      Dba::writeInTrans(transPtr, strSqlPostCategoryInsert, post_id, x);
      // auto it = std::find(inNewCategories.begin(), inNewCategories.end(), x);
      // if (it == inNewCategories.end()) updatedCategories.push_back(x);
    }
  }
}

void save_product_clarities(const sqlb::ObjectIdentifier& post_clarity_table,
                            nlohmann::json& args,
                            const std::shared_ptr<Transaction>& transPtr,
                            long post_id) {
  std::string strSqlPostCategories =
      "SELECT clarity_id FROM %1.%2 where post_id = $1";
  ReplaceAll2(strSqlPostCategories, "%1", post_clarity_table.schema());
  ReplaceAll2(strSqlPostCategories, "%2", post_clarity_table.name());

  std::string strSqlPostCategorySimpleFind =
      "SELECT post_id, clarity_id, pcs, weight, price, ismain FROM %1.%2 WHERE "
      "post_id = $1 and clarity_id = $2";
  ReplaceAll2(strSqlPostCategorySimpleFind, "%1", post_clarity_table.schema());
  ReplaceAll2(strSqlPostCategorySimpleFind, "%2", post_clarity_table.name());

  std::string strSqlPostCategoryDel =
      "DELETE FROM %1.%2 WHERE post_id = $1 and clarity_id = $2";
  ReplaceAll2(strSqlPostCategoryDel, "%1", post_clarity_table.schema());
  ReplaceAll2(strSqlPostCategoryDel, "%2", post_clarity_table.name());

  std::string strSqlPostCategoryInsert =
      "INSERT INTO %1.%2 (post_id, clarity_id, pcs, weight, price, ismain) "
      "VALUES ($1, $2, $3, $4, $5, $6);";
  ReplaceAll2(strSqlPostCategoryInsert, "%1", post_clarity_table.schema());
  ReplaceAll2(strSqlPostCategoryInsert, "%2", post_clarity_table.name());

  std::string strSqlPostCategoryUpdateAtt =
      "UPDATE product.post_clarity SET (pcs, weight, price, ismain) = ROW($3, "
      "$4, $5, $6) WHERE post_id = $1 and clarity_id = $2";

  struct PostClarity {
    long clarity_id;
    int pcs;
    double weight;
    double price;
    bool ismain;
  };
  std::vector<PostClarity> inVector;
  for (auto i : args[0]["p_clarity_clarity_id"]) {  // purity_id, weight, price
    if (!i[0].is_null())
      inVector.push_back({i[0].get<long>(), i[1].get<int>(), i[2].get<double>(),
                          i[3].get<double>(), i[4].get<bool>()});
  }

  auto all_ct = Dba::writeInTrans(transPtr, strSqlPostCategories, post_id);
  // For each saved tones, If saved tone not exist in new tones, delete it.
  for (auto r : all_ct) {
    auto it =
        std::find_if(inVector.begin(), inVector.end(), [&](PostClarity t) {
          return t.clarity_id == r["clarity_id"].as<long>();
        });
    if (it == inVector.end()) {  // Element not Found
      Dba::writeInTrans(transPtr, strSqlPostCategoryDel, post_id,
                        r["clarity_id"].as<long>());
    }
  }
  // For each new tones, insert it if it not already exist.
  for (auto r : inVector) {
    auto y = Dba::writeInTrans(transPtr, strSqlPostCategorySimpleFind, post_id,
                               r.clarity_id);
    if (y.empty()) {
      Dba::writeInTrans(transPtr, strSqlPostCategoryInsert, post_id,
                        r.clarity_id, r.pcs, r.weight, r.price, r.ismain);
    } else {  // update
      auto c_id = y[0]["clarity_id"].as<long>();
      auto pcs_ = y[0]["pcs"].as<int>();
      auto wt_ = y[0]["weight"].as<double>();
      auto pri_ = y[0]["price"].as<double>();
      auto b_ = y[0]["ismain"].as<bool>();
      if (c_id != r.clarity_id || pcs_ != r.pcs || wt_ != r.weight ||
          pri_ != r.price || b_ != r.ismain) {
        Dba::writeInTrans(transPtr, strSqlPostCategoryUpdateAtt, post_id,
                          r.clarity_id, r.pcs, r.weight, r.price, r.ismain);
      }
    }
  }
}

void save_purity_tone_(nlohmann::json& args,
                       const std::shared_ptr<Transaction>& transPtr,
                       long post_id, long purity_id) {
  std::string strSqlPostCategories =
      sel_("product.purity_tone", "post_id, purity_id, tone_id",
           "where post_id = $1 and purity_id = $2");
  std::string strSqlPostCategorySimpleFind =
      sel_("product.purity_tone",
           "post_id, purity_id, tone_id, weight, price, ismain",
           "where post_id = $1 and purity_id = $2 and tone_id = $3");
  std::string strSqlPostCategoryDel =
      dele_("product.purity_tone",
            "where post_id = $1 and purity_id = $2 and tone_id = $3");
  std::string strSqlPostCategoryInsert =
      ins_("product.purity_tone",
           "post_id, purity_id, tone_id, weight, price, ismain",
           "$1, $2, $3, $4, $5, $6");
  std::string strSqlPostCategoryUpdateAtt =
      upd_("product.purity_tone", "weight, price, ismain", "$4, $5, $6",
           "where  post_id = $1 and purity_id = $2 and tone_id = $3");

  struct PurityTone {
    long post_id;
    long purity_id;
    long tone_id;
    double weight;
    double price;
    bool ismain;
  };
  std::vector<PurityTone> inNewPrice;  // post_id, purity_id, tone_id
  for (auto i : args) {
    if (!i[0].is_null()) {  // to pass null row
      inNewPrice.push_back({post_id, purity_id, i[0].get<long>(),
                            i[1].get<double>(), i[2].get<double>(),
                            i[3].get<bool>()});
    }
  }

  auto all_ct =
      Dba::writeInTrans(transPtr, strSqlPostCategories, post_id, purity_id);
  // For each saved attachments, If it not exist in new attachments, delete it.
  for (auto r : all_ct) {
    auto it =
        std::find_if(inNewPrice.begin(), inNewPrice.end(), [&](PurityTone t) {
          return t.post_id == r["post_id"].as<long>() &&
                 t.purity_id == r["purity_id"].as<long>() &&
                 t.tone_id == r["tone_id"].as<long>();
        });
    if (it == inNewPrice.end()) {  // Element not Found
      Dba::writeInTrans(transPtr, strSqlPostCategoryDel, post_id,
                        r[1].as<long>(), r[2].as<long>());
    }
  }
  // For each new attachments, insert it if it not already exist.
  for (auto r : inNewPrice) {
    auto y = Dba::writeInTrans(transPtr, strSqlPostCategorySimpleFind,
                               r.post_id, r.purity_id, r.tone_id);
    if (y.empty()) {  // insert
      Dba::writeInTrans(transPtr, strSqlPostCategoryInsert, post_id,
                        r.purity_id, r.tone_id, r.weight, r.price, r.ismain);
    } else {  // update
      if (y[0]["weight"].as<double>() != r.weight ||
          y[0]["price"].as<double>() != r.price ||
          y[0]["ismain"].as<bool>() != r.ismain) {
        Dba::writeInTrans(transPtr, strSqlPostCategoryUpdateAtt, post_id,
                          r.purity_id, r.tone_id, r.weight, r.price, r.ismain);
      }
    }
  }
}

void save_product_purities(const sqlb::ObjectIdentifier& post_purity_table,
                           nlohmann::json& args,
                           const std::shared_ptr<Transaction>& transPtr,
                           long post_id) {
  std::string strSqlPostCategories =
      "SELECT purity_id FROM %1.%2 where post_id = $1";
  ReplaceAll2(strSqlPostCategories, "%1", post_purity_table.schema());
  ReplaceAll2(strSqlPostCategories, "%2", post_purity_table.name());

  std::string strSqlPostCategorySimpleFind =
      "SELECT purity_id, ismain FROM %1.%2 WHERE post_id = $1 and purity_id = "
      "$2";
  ReplaceAll2(strSqlPostCategorySimpleFind, "%1", post_purity_table.schema());
  ReplaceAll2(strSqlPostCategorySimpleFind, "%2", post_purity_table.name());

  std::string strSqlPostCategoryDel =
      "DELETE FROM %1.%2 WHERE post_id = $1 and purity_id = $2";
  ReplaceAll2(strSqlPostCategoryDel, "%1", post_purity_table.schema());
  ReplaceAll2(strSqlPostCategoryDel, "%2", post_purity_table.name());

  std::string strSqlPostCategoryInsert =
      "INSERT INTO %1.%2 (post_id, purity_id, ismain) VALUES ($1, $2, $3);";
  ReplaceAll2(strSqlPostCategoryInsert, "%1", post_purity_table.schema());
  ReplaceAll2(strSqlPostCategoryInsert, "%2", post_purity_table.name());

  auto strSqlPostCategoryUpdateAtt =
      upd_("product.post_purity", "ismain", "$3",
           "where post_id = $1 and purity_id = $2");

  struct PostPurity {
    long purity_id;
    bool ismain;
    nlohmann::json tones;
  };

  std::vector<PostPurity> inVector;
  for (auto i : args[0]["p_purities_purity_id"]) {  // purity_id, arry
    if (!i[0].is_null())
      inVector.push_back({i[0].get<long>(), i[2].get<bool>(), i[1]});
  }

  auto all_ct = Dba::writeInTrans(transPtr, strSqlPostCategories, post_id);
  // For each saved tones, If saved tone not exist in new tones, delete it.
  for (auto r : all_ct) {
    auto it = std::find_if(inVector.begin(), inVector.end(),
                           [&](const PostPurity& t) {
                             return t.purity_id == r["purity_id"].as<long>();
                           });
    if (it == inVector.end()) {  // Element not Found
      Dba::writeInTrans(transPtr,
                        "DELETE FROM product.purity_tone WHERE post_id = $1 "
                        "and purity_id = $2",
                        post_id, r["purity_id"].as<long>());
      Dba::writeInTrans(transPtr, strSqlPostCategoryDel, post_id,
                        r["purity_id"].as<long>());
    }
  }
  // For each new tones, insert it if it not already exist.
  for (auto r : inVector) {
    auto y = Dba::writeInTrans(transPtr, strSqlPostCategorySimpleFind, post_id,
                               r.purity_id);
    if (y.empty()) {
      Dba::writeInTrans(transPtr, strSqlPostCategoryInsert, post_id,
                        r.purity_id, r.ismain);
      save_purity_tone_(r.tones, transPtr, post_id, r.purity_id);
    } else {  // update
      if (y[0]["purity_id"].as<long>() != r.purity_id ||
          y[0]["ismain"].as<bool>() != r.ismain) {
        Dba::writeInTrans(transPtr, strSqlPostCategoryUpdateAtt, post_id,
                          r.purity_id, r.ismain);
      }
      save_purity_tone_(r.tones, transPtr, post_id, r.purity_id);
    }
  }
}

void save_diamond_price(nlohmann::json& args,
                        const std::shared_ptr<Transaction>& transPtr,
                        long diamond_id) {
  std::string strSqlPostCategories =
      "SELECT diamond_id, clarity_id, weight, total_weight, rate, price FROM "
      "product.diamond_price where diamond_id = $1";
  std::string strSqlPostCategorySimpleFind =
      "SELECT diamond_id, clarity_id, weight, total_weight, rate, price FROM "
      "product.diamond_price where diamond_id = $1 and clarity_id = $2";
  std::string strSqlPostCategoryDel =
      "DELETE FROM product.diamond_price WHERE diamond_id = $1 and clarity_id "
      "= $2";
  std::string strSqlPostCategoryInsert =
      "INSERT INTO product.diamond_price (diamond_id, clarity_id, weight, "
      "total_weight, rate, price) VALUES ($1, $2, $3, $4, $5, $6)";
  std::string strSqlPostCategoryUpdateAtt =
      "UPDATE product.diamond_price SET (weight, total_weight, rate, price) = "
      "ROW($3, $4, $5, $6) WHERE diamond_id = $1 and clarity_id = $2";

  struct DiamondPrice {
    long diamond_id;
    long clarity_id;
    double weight;
    double total_weight;
    double rate;
    double price;
  };
  std::vector<DiamondPrice> inNewPrice;
  for (auto i : args) {
    if (!i[0].is_null()) {  // to pass null row
      inNewPrice.push_back({diamond_id, i[0].get<long>(), i[2].get<double>(),
                            i[3].get<double>(), i[4].get<double>(),
                            i[5].get<double>()});
    }
  }

  auto all_ct = Dba::writeInTrans(transPtr, strSqlPostCategories, diamond_id);
  // For each saved attachments, If it not exist in new attachments, delete it.
  for (auto r : all_ct) {
    auto it =
        std::find_if(inNewPrice.begin(), inNewPrice.end(), [&](DiamondPrice t) {
          return t.diamond_id == r["diamond_id"].as<long>() &&
                 t.clarity_id == r[1].as<long>();
        });
    if (it == inNewPrice.end()) {  // Element not Found
      Dba::writeInTrans(transPtr, strSqlPostCategoryDel, diamond_id,
                        r[1].as<long>());
    }
  }
  // For each new attachments, insert it if it not already exist.
  for (auto r : inNewPrice) {
    auto y = Dba::writeInTrans(transPtr, strSqlPostCategorySimpleFind,
                               r.diamond_id, r.clarity_id);
    if (y.empty()) {  // insert
      Dba::writeInTrans(transPtr, strSqlPostCategoryInsert, diamond_id,
                        r.clarity_id, r.weight, r.total_weight, r.rate,
                        r.price);
    } else {  // update
      // if(y[0][1].as<long>() != r.shape_id || y[0][2].as<long>() != r.color_id
      // || y[0][3].c_str() != r.dsize || y[0][4].as<int>() != r.pcs ||
      // y[0][5].as<double>() != r.price) {
      Dba::writeInTrans(transPtr, strSqlPostCategoryUpdateAtt, diamond_id,
                        r.clarity_id, r.weight, r.total_weight, r.rate,
                        r.price);
      //}
    }
  }
}

void save_product_diamond_sizes(
    const sqlb::ObjectIdentifier& /*post_diamond_sizes_table*/,
    nlohmann::json& args, const std::shared_ptr<Transaction>& transPtr,
    long post_id) {
  std::string strSqlPostCategories =
      "SELECT id, post_id, shape_id, color_id, size_id, pcs FROM "
      "product.post_diamond_size where post_id = $1";
  std::string strSqlPostCategorySimpleFind =
      "SELECT id, post_id, shape_id, color_id, size_id, pcs, setting_type_id "
      "FROM product.post_diamond_size WHERE id = $1";
  std::string strSqlPostCategoryDel =
      "DELETE FROM product.post_diamond_size WHERE id = $1";
  std::string strSqlPostCategoryInsert =
      "INSERT INTO product.post_diamond_size (post_id, shape_id, color_id, "
      "size_id, pcs, setting_type_id) VALUES ($1, $2, $3, $4, $5, NULLIF($6, "
      "0::bigint)) RETURNING id;";
  std::string strSqlPostCategoryUpdateAtt =
      "UPDATE product.post_diamond_size SET (post_id, shape_id, color_id, "
      "size_id, pcs, setting_type_id) = ROW($2, $3, $4, $5, $6, NULLIF($7, "
      "0::bigint)) WHERE id = $1;";

  struct PostDiamondSize {
    long id;
    long shape_id;
    long color_id;
    int pcs;
    long setting_type_id;
    long dsize_id;
    nlohmann::json clarity_price;
  };
  std::vector<PostDiamondSize>
      inNewAttachments;  // id Shape	Color	Size	Pcs
  for (auto i : args[0]["p_d_size_diamond_size_id"]) {
    if (!i[1].is_null()) {  // to pass null row
      inNewAttachments.push_back({i[0].get<long>(), i[1].get<long>(),
                                  i[2].get<long>(), i[4].get<int>(),
                                  i[5].is_null() ? 0L : i[5].get<long>(),
                                  i[3].get<long>(), i[6]});
    }
  }

  auto all_ct = Dba::writeInTrans(transPtr, strSqlPostCategories, post_id);
  // For each saved attachments, If it not exist in new attachments, delete it.
  for (auto r : all_ct) {
    auto it = std::find_if(
        inNewAttachments.begin(), inNewAttachments.end(),
        [&](const PostDiamondSize& t) { return t.id == r["id"].as<long>(); });
    if (it == inNewAttachments.end()) {  // Element not Found
      Dba::writeInTrans(
          transPtr, "DELETE FROM product.diamond_price WHERE diamond_id = $1",
          r["id"].as<long>());
      Dba::writeInTrans(transPtr, strSqlPostCategoryDel, r["id"].as<long>());
    }
  }
  // For each new attachments, insert it if it not already exist.
  for (auto r : inNewAttachments) {
    auto y = Dba::writeInTrans(transPtr, strSqlPostCategorySimpleFind, r.id);
    if (y.empty()) {  // insert
      auto i = Dba::writeInTrans(transPtr, strSqlPostCategoryInsert, post_id,
                                 r.shape_id, r.color_id, r.dsize_id, r.pcs,
                                 r.setting_type_id);
      save_diamond_price(r.clarity_price, transPtr, i[0]["id"].as<long>());
    } else {  // update
      auto set_id = y[0]["setting_type_id"].isNull()
                        ? 0
                        : y[0]["setting_type_id"].as<long>();
      if (y[0]["shape_id"].as<long>() != r.shape_id ||
          y[0]["color_id"].as<long>() != r.color_id ||
          y[0]["size_id"].as<long>() != r.dsize_id ||
          y[0]["pcs"].as<int>() != r.pcs || set_id != r.setting_type_id) {
        Dba::writeInTrans(transPtr, strSqlPostCategoryUpdateAtt, r.id, post_id,
                          r.shape_id, r.color_id, r.dsize_id, r.pcs,
                          r.setting_type_id);
      }
      save_diamond_price(r.clarity_price, transPtr, y[0]["id"].as<long>());
    }
  }
}

void save_cs_price(nlohmann::json& args,
                   const std::shared_ptr<Transaction>& transPtr, long cs_id) {
  std::string strSqlPostCategories =
      "SELECT cs_id, weight, total_weight, rate, price FROM product.cs_price "
      "where cs_id = $1";
  std::string strSqlPostCategorySimpleFind =
      "SELECT cs_id, 0, weight, total_weight, rate, price FROM "
      "product.cs_price where cs_id = $1";
  std::string strSqlPostCategoryDel =
      "DELETE FROM product.cs_price WHERE cs_id = $1";
  std::string strSqlPostCategoryInsert =
      "INSERT INTO product.cs_price (cs_id, weight, total_weight, rate, price) "
      "VALUES ($1, $2, $3, $4, $5)";
  std::string strSqlPostCategoryUpdateAtt =
      "UPDATE product.cs_price SET (weight, total_weight, rate, price) = "
      "ROW($2, $3, $4, $5) WHERE cs_id = $1";

  struct DiamondPrice {
    long cs_id;
    //        long clarity_id;
    double weight;
    double total_weight;
    double rate;
    double price;
  };
  std::vector<DiamondPrice> inNewPrice;
  for (auto i : args) {
    if (!i[0].is_null()) {  // to pass null row
      inNewPrice.push_back({cs_id, i[2].get<double>(), i[3].get<double>(),
                            i[4].get<double>(), i[5].get<double>()});
    }
  }

  auto all_ct = Dba::writeInTrans(transPtr, strSqlPostCategories, cs_id);
  // For each saved attachments, If it not exist in new attachments, delete it.
  for (auto r : all_ct) {
    auto it = std::find_if(
        inNewPrice.begin(), inNewPrice.end(),
        [&](DiamondPrice t) { return t.cs_id == r["cs_id"].as<long>(); });
    if (it == inNewPrice.end()) {  // Element not Found
      Dba::writeInTrans(transPtr, strSqlPostCategoryDel, cs_id,
                        r[1].as<long>());
    }
  }
  // For each new attachments, insert it if it not already exist.
  for (auto r : inNewPrice) {
    auto y = Dba::writeInTrans(transPtr, strSqlPostCategorySimpleFind, r.cs_id);
    if (y.empty()) {  // insert
      Dba::writeInTrans(transPtr, strSqlPostCategoryInsert, cs_id, r.weight,
                        r.total_weight, r.rate, r.price);
    } else {  // update
      // if(y[0][1].as<long>() != r.shape_id || y[0][2].as<long>() != r.color_id
      // || y[0][3].c_str() != r.dsize || y[0][4].as<int>() != r.pcs ||
      // y[0][5].as<double>() != r.price) {
      Dba::writeInTrans(transPtr, strSqlPostCategoryUpdateAtt, cs_id, r.weight,
                        r.total_weight, r.rate, r.price);
      //}
    }
  }
}

void save_product_cs_sizes(
    const sqlb::ObjectIdentifier& /*post_color_stone_size_table*/,
    nlohmann::json& args, const std::shared_ptr<Transaction>& transPtr,
    long post_id) {
  std::string strSqlPostCategories =
      "SELECT id, post_id, shape_id, color_id, size_id, pcs FROM "
      "product.post_color_stone_size where post_id = $1";
  std::string strSqlPostCategorySimpleFind =
      "SELECT id, post_id, shape_id, color_id, size_id, pcs, setting_type_id "
      "FROM product.post_color_stone_size WHERE id = $1";
  std::string strSqlPostCategoryDel =
      "DELETE FROM product.post_color_stone_size WHERE id = $1";
  std::string strSqlPostCategoryInsert =
      "INSERT INTO product.post_color_stone_size (post_id, cs_type_id, "
      "shape_id, color_id, size_id, pcs, setting_type_id) VALUES ($1, $2, $3, "
      "$4, $5, $6, NULLIF($7, 0::bigint)) RETURNING id;";
  std::string strSqlPostCategoryUpdateAtt =
      "UPDATE product.post_color_stone_size SET (post_id, cs_type_id, "
      "shape_id, color_id, size_id, pcs, setting_type_id) = ROW($2, $3, $4, "
      "$5, $6, $7, NULLIF($8, 0::bigint)) WHERE id = $1;";

  struct PostCSSize {
    long id;
    long cs_type_id;
    long shape_id;
    long color_id;
    int pcs;
    long setting_type_id;
    long dsize_id;
    nlohmann::json clarity_price;
  };
  std::vector<PostCSSize> inNewAttachments;  // id Shape	Color Size
                                             // Pcs
  for (auto i : args[0]["p_cs_size_cs_size_id"]) {
    if (!i[1].is_null()) {  // to pass null row
      inNewAttachments.push_back(
          {i[0].get<long>(), i[1].get<long>(), i[2].get<long>(),
           i[3].get<long>(), i[5].get<int>(),
           i[6].is_null() ? 0L : i[6].get<long>(), i[4].get<long>(), i[7]});
    }
  }

  auto all_ct = Dba::writeInTrans(transPtr, strSqlPostCategories, post_id);
  // For each saved attachments, If it not exist in new attachments, delete it.
  for (auto r : all_ct) {
    auto it = std::find_if(
        inNewAttachments.begin(), inNewAttachments.end(),
        [&](const PostCSSize& t) { return t.id == r["id"].as<long>(); });
    if (it == inNewAttachments.end()) {  // Element not Found
      Dba::writeInTrans(transPtr,
                        "DELETE FROM product.cs_price WHERE cs_id = $1",
                        r["id"].as<long>());
      Dba::writeInTrans(transPtr, strSqlPostCategoryDel, r["id"].as<long>());
    }
  }
  // For each new attachments, insert it if it not already exist.
  for (auto r : inNewAttachments) {
    auto y = Dba::writeInTrans(transPtr, strSqlPostCategorySimpleFind, r.id);
    if (y.empty()) {  // insert
      auto i = Dba::writeInTrans(transPtr, strSqlPostCategoryInsert, post_id,
                                 r.cs_type_id, r.shape_id, r.color_id,
                                 r.dsize_id, r.pcs, r.setting_type_id);
      save_cs_price(r.clarity_price, transPtr, i[0]["id"].as<long>());
    } else {  // update
      auto set_id = y[0]["setting_type_id"].isNull()
                        ? 0
                        : y[0]["setting_type_id"].as<long>();
      if (y[0][2].as<long>() != r.shape_id ||
          y[0][3].as<long>() != r.color_id ||
          y[0][4].as<long>() != r.dsize_id || y[0][5].as<int>() != r.pcs ||
          set_id != r.setting_type_id) {
        Dba::writeInTrans(transPtr, strSqlPostCategoryUpdateAtt, r.id, post_id,
                          r.cs_type_id, r.shape_id, r.color_id, r.dsize_id,
                          r.pcs, r.setting_type_id);
      }
      save_cs_price(r.clarity_price, transPtr, y[0]["id"].as<long>());
    }
  }
}

void save_product_cs_total(
    const sqlb::ObjectIdentifier& /*post_cs_total_table*/, nlohmann::json& args,
    const std::shared_ptr<Transaction>& transPtr, long post_id) {
  std::string strSqlPostCategories =
      "SELECT post_id, pcs, weight, price FROM product.post_cs_total where "
      "post_id = $1";
  std::string strSqlPostCategorySimpleFind =
      "SELECT post_id, pcs, weight, price FROM product.post_cs_total WHERE "
      "post_id = $1";
  std::string strSqlPostCategoryDel =
      "DELETE FROM product.post_cs_total WHERE post_id = $1";
  std::string strSqlPostCategoryInsert =
      "INSERT INTO product.post_cs_total (post_id, pcs, weight, price) VALUES "
      "($1, $2, $3, $4) RETURNING post_id;";
  std::string strSqlPostCategoryUpdateAtt =
      "UPDATE product.post_cs_total SET (pcs, weight, price) = ROW($2, $3, $4) "
      "WHERE post_id = $1;";

  struct PostCSTotal {
    long post_id;  // we have to add this, to find index
    int pcs;
    double weight;
    double price;
  };
  std::vector<PostCSTotal> inNewAttachments;  // id Shape	Color	Size
                                              // Pcs
  for (auto i : args[0]["p_cs_total_p_cs_total"]) {
    if (!i[1].is_null()) {  // to pass null row
      inNewAttachments.push_back(
          {post_id, i[0].get<int>(), i[1].get<double>(), i[2].get<double>()});
    }
  }

  auto all_ct = Dba::writeInTrans(transPtr, strSqlPostCategories, post_id);
  // For each saved attachments, If it not exist in new attachments, delete it.
  for (auto r : all_ct) {
    auto it = std::find_if(
        inNewAttachments.begin(), inNewAttachments.end(),
        [&](PostCSTotal t) { return t.post_id == r["post_id"].as<long>(); });
    if (it == inNewAttachments.end()) {  // Element not Found
      Dba::writeInTrans(transPtr, strSqlPostCategoryDel,
                        r["post_id"].as<long>());
    }
  }
  // For each new attachments, insert it if it not already exist.
  for (auto r : inNewAttachments) {
    auto y =
        Dba::writeInTrans(transPtr, strSqlPostCategorySimpleFind, r.post_id);
    if (y.empty()) {  // insert
      auto i = Dba::writeInTrans(transPtr, strSqlPostCategoryInsert, post_id,
                                 r.pcs, r.weight, r.price);
    } else {  // update
      if (y[0]["post_id"].as<long>() != r.post_id ||
          y[0]["pcs"].as<int>() != r.pcs ||
          y[0]["weight"].as<double>() != r.weight ||
          y[0]["price"].as<double>() != r.price) {
        Dba::writeInTrans(transPtr, strSqlPostCategoryUpdateAtt, r.post_id,
                          r.pcs, r.weight, r.price);
      }
    }
  }
}

void save_product_Attachments(
    const sqlb::ObjectIdentifier& post_attachment_table, nlohmann::json& args,
    const std::shared_ptr<Transaction>& transPtr, long post_id) {
  std::string strSqlPostCategories = "SELECT id FROM %1.%2 where post_id = $1";
  ReplaceAll2(strSqlPostCategories, "%1", post_attachment_table.schema());
  ReplaceAll2(strSqlPostCategories, "%2", post_attachment_table.name());

  std::string strSqlPostCategorySimpleFind =
      "SELECT id, post_id, tone_id, main_image FROM %1.%2 WHERE id = $1";
  ReplaceAll2(strSqlPostCategorySimpleFind, "%1",
              post_attachment_table.schema());
  ReplaceAll2(strSqlPostCategorySimpleFind, "%2", post_attachment_table.name());

  std::string strSqlPostCategoryDel = "DELETE FROM %1.%2 WHERE id = $1";
  ReplaceAll2(strSqlPostCategoryDel, "%1", post_attachment_table.schema());
  ReplaceAll2(strSqlPostCategoryDel, "%2", post_attachment_table.name());

  std::string strSqlPostCategoryInsert =
      "INSERT INTO %1.%2 (post_id, tone_id, name, size, type, main_image) "
      "VALUES ($1, $2, $3, $4, $5, $6);";
  ReplaceAll2(strSqlPostCategoryInsert, "%1", post_attachment_table.schema());
  ReplaceAll2(strSqlPostCategoryInsert, "%2", post_attachment_table.name());

  std::string strSqlPostCategoryUpdate =
      "UPDATE product.post_attachment SET (tone_id, main_image) = ROW($2, $3) "
      "WHERE id = $1;";
  std::string strSqlPostCategoryUpdateAtt =
      "UPDATE product.post_attachment SET (tone_id, name, size, type, "
      "main_image, version) = ROW($2, $3, $4, $5, $6, version + 1) WHERE id = "
      "$1;";

  std::string strSqlTempImage =
      "SELECT name, size, type FROM setting.temp_image_id WHERE id = $1";
  std::string strSqlTempImageDel =
      "DELETE FROM setting.temp_image_id WHERE id = $1";

  struct Attachment {
    long id;
    long tone_id;
    long temp_id;
    bool main_image;
  };
  std::vector<Attachment> inNewAttachments;  // tone_id, temp_id
  for (auto i : args[0]["p_attachments_attachement_id"]) {
    if (i[1].is_null() || i[1].get<long>() == 0) {
      continue;
    }
    auto ismain = i[3].is_null() ? false : i[3].get<bool>();
    inNewAttachments.push_back(
        {i[0].get<long>(), i[1].get<long>(), i[2].get<long>(), ismain});
  }

  auto all_ct = Dba::writeInTrans(transPtr, strSqlPostCategories, post_id);
  // For each saved attachments, If it not exist in new attachments, delete it.
  for (auto r : all_ct) {
    auto it =
        std::find_if(inNewAttachments.begin(), inNewAttachments.end(),
                     [&](Attachment t) { return t.id == r["id"].as<long>(); });
    if (it == inNewAttachments.end()) {  // Element not Found
      Dba::writeInTrans(transPtr, strSqlPostCategoryDel, r["id"].as<long>());
    }
  }
  // For each new attachments, insert it if it not already exist.
  for (auto r : inNewAttachments) {
    auto y = Dba::writeInTrans(transPtr, strSqlPostCategorySimpleFind, r.id);
    if (y.empty()) {  // insert
      auto temp_id = r.temp_id;
      if (temp_id != 0) {
        auto z = Dba::writeInTrans(transPtr, strSqlTempImage, temp_id);
        if (z.size() == 1) {
          Dba::writeInTrans(transPtr, strSqlPostCategoryInsert, post_id,
                            r.tone_id, z[0]["name"].as<std::string>(),
                            z[0]["size"].as<long>(),
                            z[0]["type"].as<std::string>(), r.main_image);
          Dba::writeInTrans(transPtr, strSqlTempImageDel, temp_id);
        }
      }
    } else {  // update
      if (y[0]["tone_id"].as<long>() != r.tone_id ||
          y[0]["main_image"].as<bool>() != r.main_image ||
          r.temp_id != 0) {  // can also update image
        auto temp_id = r.temp_id;
        if (temp_id != 0) {
          auto z = Dba::writeInTrans(transPtr, strSqlTempImage, temp_id);
          if (z.size() == 1) {
            auto name = z[0]["name"].as<std::string>();
            auto size = z[0]["size"].as<long>();
            auto type = z[0]["type"].as<std::string>();
            Dba::writeInTrans(transPtr, strSqlPostCategoryUpdateAtt, r.id,
                              r.tone_id, name, size, type, r.main_image);
            Dba::writeInTrans(transPtr, strSqlTempImageDel, temp_id);
          }
        } else {
          Dba::writeInTrans(transPtr, strSqlPostCategoryUpdate, r.id, r.tone_id,
                            r.main_image);
        }
      }
    }
  }
}

nlohmann::json Product::ins(nlohmann::json event, nlohmann::json args) {
  auto product_table = sqlb::ObjectIdentifier("product", "product", "p");
  auto post_table = sqlb::ObjectIdentifier("post", "post", "p");
  auto tags_table = sqlb::ObjectIdentifier("post", "tag", "t");
  auto post_tag_table = sqlb::ObjectIdentifier("post", "post_tag", "pt");
  auto post_category_table =
      sqlb::ObjectIdentifier("product", "post_category", "pt");
  auto post_tone_table =
      sqlb::ObjectIdentifier("product", "post_tone", "p_tones");
  auto post_clarity_table =
      sqlb::ObjectIdentifier("product", "post_clarity", "p_clarity");
  auto post_purity_table =
      sqlb::ObjectIdentifier("product", "post_purity", "p_purities");
  auto post_attachment_table =
      sqlb::ObjectIdentifier("product", "post_attachment", "p_attachments");
  auto post_diamond_sizes_table = sqlb::ObjectIdentifier(
      "product", "post_diamond_size", "post_diamond_sizes");
  auto post_cs_total_table =
      sqlb::ObjectIdentifier("product", "post_cs_total", "post_cs_total");
  auto post_certified_by =
      sqlb::ObjectIdentifier("product", "post_certified_by", "p_certified_by");

  std::string strSqlPost =
      "INSERT INTO %1.%2 "
      "(comment_status, menu_order, excerpt, content, title, name, password, "
      "status, date, type, visibility)"
      " VALUES($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11)"
      "RETURNING id";
  ReplaceAll2(strSqlPost, "%1", post_table.schema());
  ReplaceAll2(strSqlPost, "%2", post_table.name());

  std::string strSqlProduct =
      "INSERT INTO %1.%2 "
      "(post_id, sku, min_price, max_price, weight, length, width, height, "
      "manage_stock, featured, stock_quantity, shipping_class_id, "
      "catalog_visibility, product_type, backorders, stock_status, virtual, "
      "downloadable, purchase_note, low_stock_amount, sold_individually, "
      "making_charges, discount_per, volume, purity_id, tone_id)"
      " VALUES($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, NULLIF($12, "
      "0::bigint), $13, $14, $15, $16, $17, $18, $19, $20, $21, $22, $23, $24, "
      "$25, $26)";
  ReplaceAll2(strSqlProduct, "%1", product_table.schema());
  ReplaceAll2(strSqlProduct, "%2", product_table.name());

  auto clientPtr = drogon::app().getDbClient("sce");
  auto transPtr = clientPtr->newTransaction();
  try {
    auto x = Dba::writeInTrans(
        transPtr, strSqlPost, args[0]["comment_status"].get<bool>(),
        args[0]["menu_order"].get<int>(), args[0]["excerpt"].get<std::string>(),
        args[0]["content"].get<std::string>(),
        args[0]["title"].get<std::string>(), args[0]["name"].get<std::string>(),
        args[0]["password"].get<std::string>(),
        args[0]["status"].get<std::string>(),
        args[0]["date"].get<std::string>(), args[0]["type"].get<std::string>(),
        args[0]["visibility"].get<std::string>());
    auto post_id = x[0]["id"].as<long>();

    Dba::writeInTrans(
        transPtr, strSqlProduct, post_id, args[0]["p_sku"].get<std::string>(),
        args[0]["p_min_price"].get<double>(),
        args[0]["p_max_price"].get<double>(), args[0]["p_weight"].get<double>(),
        args[0]["p_length"].get<double>(), args[0]["p_width"].get<double>(),
        args[0]["p_height"].get<double>(),
        args[0]["p_manage_stock"].get<bool>(),
        args[0]["p_featured"].get<bool>(),
        args[0]["p_stock_quantity"].get<double>(),
        args[0]["p_shipping_class_id"].is_null()
            ? 0L
            : args[0]["p_shipping_class_id"].get<long>(),
        args[0]["p_catalog_visibility"].get<std::string>(),
        args[0]["p_product_type"].get<std::string>(),
        args[0]["p_backorders"].get<std::string>(),
        args[0]["p_stock_status"].get<std::string>(),
        args[0]["p_virtual"].get<bool>(), args[0]["p_downloadable"].get<bool>(),
        args[0]["p_purchase_note"].get<std::string>(),
        args[0]["p_low_stock_amount"].get<double>(),
        args[0]["p_sold_individually"].get<bool>(),
        args[0]["p_making_charges"].get<double>(),
        args[0]["p_discount_per"].get<double>(),
        args[0]["p_volume"].get<double>(), args[0]["p_purity_id"].get<long>(),
        args[0]["p_tone_id"].get<long>());
    product_tags_process(tags_table, post_tag_table, args, transPtr, post_id);
    save_product_categories(post_category_table, args, transPtr, post_id);
    purejoinTableSaveF("product.post_tone", args, transPtr, "p_tones_tone_id",
                       "post_id", "tone_id", post_id);
    save_product_clarities(post_clarity_table, args, transPtr, post_id);
    save_product_purities(post_purity_table, args, transPtr, post_id);
    save_product_Attachments(post_attachment_table, args, transPtr, post_id);
    save_product_diamond_sizes(post_diamond_sizes_table, args, transPtr,
                               post_id);
    save_product_cs_sizes(post_diamond_sizes_table, args, transPtr, post_id);
    save_product_cs_total(post_cs_total_table, args, transPtr, post_id);
    purejoinTableSaveF("product.post_certified_by", args, transPtr,
                       "p_certified_by_certified_by", "post_id",
                       "certified_by_id", post_id);
    purejoinTableSaveF("product.post_policy", args, transPtr,
                       "p_policy_post_policy", "post_id", "policy_id", post_id);

    nlohmann::json ret;
    ret[0] = simpleJsonSaveResult(event, true, "Done");
    return ret;
  } catch (const std::exception& e) {
    SPDLOG_TRACE(e.what());
    nlohmann::json ret;
    ret[0] = simpleJsonSaveResult(event, false, e.what());
    return ret;
  }
}
nlohmann::json Product::upd(nlohmann::json event, nlohmann::json args) {
  auto product_table = sqlb::ObjectIdentifier("product", "product", "p");
  auto post_table = sqlb::ObjectIdentifier("post", "post", "p");
  auto tags_table = sqlb::ObjectIdentifier("post", "tag", "t");
  auto post_tag_table = sqlb::ObjectIdentifier("post", "post_tag", "pt");
  auto post_category_table =
      sqlb::ObjectIdentifier("product", "post_category", "pt");
  auto post_tone_table =
      sqlb::ObjectIdentifier("product", "post_tone", "p_tones");
  auto post_clarity_table =
      sqlb::ObjectIdentifier("product", "post_clarity", "p_clarity");
  auto post_purity_table =
      sqlb::ObjectIdentifier("product", "post_purity", "p_purities");
  auto post_attachment_table =
      sqlb::ObjectIdentifier("product", "post_attachment", "p_attachments");
  auto post_diamond_sizes_table = sqlb::ObjectIdentifier(
      "product", "post_diamond_size", "post_diamond_sizes");
  auto post_cs_total_table =
      sqlb::ObjectIdentifier("product", "post_cs_total", "post_cs_total");
  auto post_certified_by =
      sqlb::ObjectIdentifier("product", "post_certified_by", "p_certified_by");

  if (args[0]["id"].get<long>()) {
    std::string strSqlPost =
        "update %1.%2 set "
        "(comment_status, menu_order, excerpt, content, title, name, password, "
        "status, date, type, visibility)"
        " = ROW($2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12) where id=$1";
    ReplaceAll2(strSqlPost, "%1", post_table.schema());
    ReplaceAll2(strSqlPost, "%2", post_table.name());

    std::string strSqlProduct =
        "update %1.%2 set "
        "(post_id, sku, min_price, max_price, weight, length, width, height, "
        "manage_stock, featured, stock_quantity, shipping_class_id, "
        "catalog_visibility, product_type, backorders, stock_status, virtual, "
        "downloadable, purchase_note, low_stock_amount, sold_individually, "
        "making_charges, discount_per, volume, purity_id, tone_id)"
        " = ROW($2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, NULLIF($13, "
        "0::bigint), $14, $15, $16, $17, $18, $19, $20, $21, $22, $23, $24, "
        "$25, $26, $27) where id=$1";
    ReplaceAll2(strSqlProduct, "%1", product_table.schema());
    ReplaceAll2(strSqlProduct, "%2", product_table.name());

    auto clientPtr = drogon::app().getDbClient("sce");
    auto transPtr = clientPtr->newTransaction();
    try {
      Dba::writeInTrans(transPtr, strSqlPost, args[0]["id"].get<long>(),
                        args[0]["comment_status"].get<bool>(),
                        args[0]["menu_order"].get<int>(),
                        args[0]["excerpt"].get<std::string>(),
                        args[0]["content"].get<std::string>(),
                        args[0]["title"].get<std::string>(),
                        args[0]["name"].get<std::string>(),
                        args[0]["password"].get<std::string>(),
                        args[0]["status"].get<std::string>(),
                        args[0]["date"].get<std::string>(),
                        args[0]["type"].get<std::string>(),
                        args[0]["visibility"].get<std::string>());
      auto post_id = args[0]["id"].get<long>();
      Dba::writeInTrans(
          transPtr, strSqlProduct, args[0]["p_id"].get<long>(), post_id,
          args[0]["p_sku"].get<std::string>(),
          args[0]["p_min_price"].get<double>(),
          args[0]["p_max_price"].get<double>(),
          args[0]["p_weight"].get<double>(), args[0]["p_length"].get<double>(),
          args[0]["p_width"].get<double>(), args[0]["p_height"].get<double>(),
          args[0]["p_manage_stock"].get<bool>(),
          args[0]["p_featured"].get<bool>(),
          args[0]["p_stock_quantity"].get<double>(),
          args[0]["p_shipping_class_id"].is_null()
              ? 0L
              : args[0]["p_shipping_class_id"].get<long>(),
          args[0]["p_catalog_visibility"].get<std::string>(),
          args[0]["p_product_type"].get<std::string>(),
          args[0]["p_backorders"].get<std::string>(),
          args[0]["p_stock_status"].get<std::string>(),
          args[0]["p_virtual"].get<bool>(),
          args[0]["p_downloadable"].get<bool>(),
          args[0]["p_purchase_note"].get<std::string>(),
          args[0]["p_low_stock_amount"].get<double>(),
          args[0]["p_sold_individually"].get<bool>(),
          args[0]["p_making_charges"].get<double>(),
          args[0]["p_discount_per"].get<double>(),
          args[0]["p_volume"].get<double>(), args[0]["p_purity_id"].get<long>(),
          args[0]["p_tone_id"].get<long>());
      try {
        product_tags_process(tags_table, post_tag_table, args, transPtr,
                             post_id);
      } catch (const std::exception& e) {
        SPDLOG_TRACE(e.what());
        nlohmann::json ret;
        ret[0] = simpleJsonSaveResult(event, false, e.what());
        return ret;
      }
      try {
        save_product_categories(post_category_table, args, transPtr, post_id);
      } catch (const std::exception& e) {
        SPDLOG_TRACE(e.what());
        nlohmann::json ret;
        ret[0] = simpleJsonSaveResult(event, false, e.what());
        return ret;
      }
      try {
        purejoinTableSaveF("product.post_tone", args, transPtr,
                           "p_tones_tone_id", "post_id", "tone_id", post_id);
      } catch (const std::exception& e) {
        SPDLOG_TRACE(e.what());
        nlohmann::json ret;
        ret[0] = simpleJsonSaveResult(event, false, e.what());
        return ret;
      }
      try {
        save_product_clarities(post_clarity_table, args, transPtr, post_id);
      } catch (const std::exception& e) {
        SPDLOG_TRACE(e.what());
        nlohmann::json ret;
        ret[0] = simpleJsonSaveResult(event, false, e.what());
        return ret;
      }
      try {
        save_product_purities(post_purity_table, args, transPtr, post_id);
      } catch (const std::exception& e) {
        SPDLOG_TRACE(e.what());
        nlohmann::json ret;
        ret[0] = simpleJsonSaveResult(event, false, e.what());
        return ret;
      }
      try {
        save_product_Attachments(post_attachment_table, args, transPtr,
                                 post_id);
      } catch (const std::exception& e) {
        SPDLOG_TRACE(e.what());
        nlohmann::json ret;
        ret[0] = simpleJsonSaveResult(event, false, e.what());
        return ret;
      }
      try {
        save_product_diamond_sizes(post_diamond_sizes_table, args, transPtr,
                                   post_id);
      } catch (const std::exception& e) {
        SPDLOG_TRACE(e.what());
        nlohmann::json ret;
        ret[0] = simpleJsonSaveResult(event, false, e.what());
        return ret;
      }
      try {
        save_product_cs_sizes(post_diamond_sizes_table, args, transPtr,
                              post_id);
      } catch (const std::exception& e) {
        SPDLOG_TRACE(e.what());
        nlohmann::json ret;
        ret[0] = simpleJsonSaveResult(event, false, e.what());
        return ret;
      }
      try {
        save_product_cs_total(post_cs_total_table, args, transPtr, post_id);
      } catch (const std::exception& e) {
        SPDLOG_TRACE(e.what());
        nlohmann::json ret;
        ret[0] = simpleJsonSaveResult(event, false, e.what());
        return ret;
      }
      try {
        purejoinTableSaveF("product.post_certified_by", args, transPtr,
                           "p_certified_by_certified_by", "post_id",
                           "certified_by_id", post_id);
      } catch (const std::exception& e) {
        SPDLOG_TRACE(e.what());
        nlohmann::json ret;
        ret[0] = simpleJsonSaveResult(event, false, e.what());
        return ret;
      }
      try {
        purejoinTableSaveF("product.post_policy", args, transPtr,
                           "p_policy_post_policy", "post_id", "policy_id",
                           post_id);
      } catch (const std::exception& e) {
        SPDLOG_TRACE(e.what());
        nlohmann::json ret;
        ret[0] = simpleJsonSaveResult(event, false, e.what());
        return ret;
      }

      nlohmann::json ret;
      ret[0] = simpleJsonSaveResult(event, true, "Done");
      return ret;
    } catch (const std::exception& e) {
      SPDLOG_TRACE(e.what());
      nlohmann::json ret;
      ret[0] = simpleJsonSaveResult(event, false, e.what());
      return ret;
    }
  }
  nlohmann::json ret;
  ret[0] = simpleJsonSaveResult(event, false, "Not Valid Structure");
  return ret;
}

nlohmann::json Product::del(nlohmann::json event, nlohmann::json args) {
  // to support global filter, get first all ids b selected filter and for each
  // id delete.
  auto clientPtr = drogon::app().getDbClient("sce");
  auto transPtr = clientPtr->newTransaction();
  try {
    auto post_del = "DELETE FROM post.post WHERE id = $1";
    auto product_del = "DELETE FROM product.product WHERE post_id = $1";
    // auto tags_del = "DELETE FROM post.tag  WHERE post_id = $1"; // Fix This.
    // If Tag is not used in any product delete it
    auto post_tag_del = "DELETE FROM post.post_tag  WHERE post_id = $1";
    auto post_category_del =
        "DELETE FROM product.post_category  WHERE post_id = $1";
    auto post_tone_del = "DELETE FROM product.post_tone WHERE post_id = $1";
    auto post_clarity_del =
        "DELETE FROM product.post_clarity WHERE post_id = $1";
    auto post_purity_del = "DELETE FROM product.post_purity WHERE post_id = $1";
    auto post_purity_tone_del =
        "DELETE FROM product.purity_tone WHERE post_id = $1";
    auto post_attachment_del =
        "DELETE FROM product.post_attachment WHERE post_id = $1";
    auto post_diamond_sizes_del =
        "DELETE FROM product.post_diamond_size WHERE post_id = $1";
    auto post_diamond_price_id =
        "delete from product.diamond_price dp where dp.diamond_id in (select "
        "id from product.post_diamond_size ds where ds.post_id = $1);";
    auto post_cs_sizes_del =
        "DELETE FROM product.post_color_stone_size WHERE post_id = $1";
    auto post_cs_price_del =
        "delete from product.cs_price cp where cp.cs_id in (select id from "
        "product.post_color_stone_size cs where cs.post_id = $1);";
    auto post_cs_total_del =
        "DELETE FROM product.post_cs_total WHERE post_id = $1";
    auto post_certified_by_del =
        "DELETE FROM product.post_certified_by WHERE post_id = $1";
    auto post_policy_del = "DELETE FROM product.post_policy WHERE post_id = $1";

    auto post_id = args[0][0].get<long>();
    Dba::writeInTrans(transPtr, post_policy_del, post_id);
    Dba::writeInTrans(transPtr, post_certified_by_del, post_id);
    Dba::writeInTrans(transPtr, post_cs_total_del, post_id);
    Dba::writeInTrans(transPtr, post_cs_price_del, post_id);
    Dba::writeInTrans(transPtr, post_cs_sizes_del, post_id);
    Dba::writeInTrans(transPtr, post_diamond_price_id, post_id);
    Dba::writeInTrans(transPtr, post_diamond_sizes_del, post_id);
    Dba::writeInTrans(transPtr, post_attachment_del, post_id);
    Dba::writeInTrans(transPtr, post_purity_tone_del, post_id);
    Dba::writeInTrans(transPtr, post_purity_del, post_id);
    Dba::writeInTrans(transPtr, post_tone_del, post_id);
    Dba::writeInTrans(transPtr, post_tone_del, post_id);
    Dba::writeInTrans(transPtr, post_clarity_del, post_id);
    Dba::writeInTrans(transPtr, post_category_del, post_id);
    Dba::writeInTrans(transPtr, post_tag_del, post_id);
    // Dba::writeInTrans(transPtr, tags_del, post_id); // Fix This. If Tag is
    // not used in any product delete it
    Dba::writeInTrans(transPtr, product_del, post_id);
    Dba::writeInTrans(transPtr, post_del, post_id);

    nlohmann::json ret;
    ret[0] = simpleJsonSaveResult(event, true, "Done");
    return ret;
  } catch (const std::exception& e) {
    SPDLOG_TRACE(e.what());
    nlohmann::json ret;
    ret[0] = simpleJsonSaveResult(event, false, e.what());
    return ret;
  }
}

nlohmann::json save_category(const nlohmann::json& event, nlohmann::json args) {
  auto product_table = sqlb::ObjectIdentifier("product", "category", "p");

  if (args[0]["id"].get<long>()) {
    std::string strSql =
        "update %1.%2 set "
        "(slug, name, description, display_type, parent_id, position)"
        " = ROW($2, $3, $4, $5, NULLIF($6, 0::bigint), $7) where id=$1";
    ReplaceAll2(strSql, "%1", product_table.schema());
    ReplaceAll2(strSql, "%2", product_table.name());

    auto clientPtr = drogon::app().getDbClient("sce");
    auto transPtr = clientPtr->newTransaction();
    try {
      Dba::writeInTrans(transPtr, strSql, args[0]["id"].get<long>(),
                        args[0]["slug"].get<std::string>(),
                        args[0]["name"].get<std::string>(),
                        args[0]["description"].get<std::string>(),
                        args[0]["display_type"].get<std::string>(),
                        args[0]["parent_id"].get<long>(),
                        args[0]["position"].get<int>());

      nlohmann::json ret;
      ret[0] = simpleJsonSaveResult(event, true, "Done");
      return ret;
    } catch (const std::exception& e) {
      SPDLOG_TRACE(e.what());
      nlohmann::json ret;
      ret[0] = simpleJsonSaveResult(event, false, e.what());
      return ret;
    }
  } else {
    std::string strSql =
        "INSERT INTO %1.%2 (slug, name, description, display_type, parent_id, "
        "position) values($1, $2, $3, $4, NULLIF($5, 0::bigint), $6)";
    ReplaceAll2(strSql, "%1", product_table.schema());
    ReplaceAll2(strSql, "%2", product_table.name());

    auto clientPtr = drogon::app().getDbClient("sce");
    auto transPtr = clientPtr->newTransaction();
    try {
      Dba::writeInTrans(transPtr, strSql, args[0]["slug"].get<std::string>(),
                        args[0]["name"].get<std::string>(),
                        args[0]["description"].get<std::string>(),
                        args[0]["display_type"].get<std::string>(),
                        args[0]["parent_id"].get<long>(),
                        args[0]["position"].get<int>());

      nlohmann::json ret;
      ret[0] = simpleJsonSaveResult(event, true, "Done");
      return ret;
    } catch (const std::exception& e) {
      SPDLOG_TRACE(e.what());
      nlohmann::json ret;
      ret[0] = simpleJsonSaveResult(event, false, e.what());
      return ret;
    }
  }
}

nlohmann::json Product::get_product_diamond_price_data(nlohmann::json event,
                                                       nlohmann::json args) {
  nlohmann::json batch;
  nlohmann::json jresult;
  jresult[0] = std::move(event);

  if (args.is_array() && args.size() >= 7) {
    auto shape = args[1].get<long>();
    auto color = args[2].get<long>();
    auto size = args[3].get<long>();
    auto pcs = args[4].get<int>();

    std::string s = "{";  // clarity
    for (auto i : args[6]) {
      s += std::to_string(i[0].get<long>()) + ",";
    }
    if (!args[6].empty()) s.pop_back();
    s += "}";

    auto clientPtr = drogon::app().getDbClient("sce");
    auto transPtr = clientPtr->newTransaction();
    try {
      // You can't use IN (...) with arrays. You need to use an operator (ex: =,
      // >, <, etc) and ANY/ALL
      auto sql =
          "SELECT clarity_id, weight, rate FROM material.diamond_size_meta "
          "WHERE "
          "shape_id = $1 AND color_id = $2 AND size_id = $3 AND  clarity_id = "
          "ANY($4::bigint[])";
      auto x = Dba::writeInTrans(transPtr, sql, shape, color, size, s);

      nlohmann::json d(nlohmann::json::array());
      for (const auto& r : x) {
        nlohmann::json row;
        row[0] = r["clarity_id"].as<long>();
        row[1] = "";
        row[2] = r["weight"].as<double>();
        row[3] = r["weight"].as<double>() * pcs;
        row[4] = r["rate"].as<double>();
        row[5] = r["weight"].as<double>() * pcs * r["rate"].as<double>();
        d.push_back(row);
      }
      jresult[1] = d;

      batch[0] = jresult;
      return batch;
    } catch (const std::exception& e) {
      SPDLOG_TRACE(e.what());
      // simpleJsonSaveResult(event, false, e.what());
      return nlohmann::json::array();
    }
  }
  return nlohmann::json::array();
}

nlohmann::json Product::get_product_cs_price_data(nlohmann::json event,
                                                  nlohmann::json args) {
  nlohmann::json batch;
  nlohmann::json jresult;
  jresult[0] = std::move(event);

  if (args.is_array() && args.size() >= 7) {
    auto type = args[1].get<long>();
    auto shape = args[2].get<long>();
    // auto color = args[3].get<long>();
    auto size = args[4].get<long>();
    auto pcs = args[5].get<int>();

    auto clientPtr = drogon::app().getDbClient("sce");
    auto transPtr = clientPtr->newTransaction();
    try {
      // You can't use IN (...) with arrays. You need to use an operator (ex: =,
      // >, <, etc) and ANY/ALL
      auto sql =
          "SELECT weight, rate FROM material.color_stone_size_meta WHERE "
          "cs_type_id = $1 and shape_id = $2 AND size_id = $3";
      auto x = Dba::writeInTrans(transPtr, sql, type, shape, size);

      nlohmann::json d(nlohmann::json::array());
      for (const auto& r : x) {
        nlohmann::json row;
        row[0] = 0;
        row[1] = "";
        row[2] = r["weight"].as<double>();
        row[3] = r["weight"].as<double>() * pcs;
        row[4] = r["rate"].as<double>();
        row[5] = r["weight"].as<double>() * pcs * r["rate"].as<double>();
        d.push_back(row);
      }
      jresult[1] = d;

      batch[0] = jresult;
      return batch;
    } catch (const std::exception& e) {
      SPDLOG_TRACE(e.what());
      // simpleJsonSaveResult(event, false, e.what());
      nlohmann::json ret;
      return ret;
    }
  }
  nlohmann::json r;
  return r;
}

nlohmann::json Product::get_product_category_tree_data(
    nlohmann::json event, const nlohmann::json& /*args*/) {
  nlohmann::json batch;
  nlohmann::json jresult;
  jresult[0] = std::move(event);

  //    auto shape = args[1].get<long>();
  //    auto color = args[2].get<long>();
  //    auto size = args[3].get<long>();
  //    auto pcs = args[4].get<int>();

  auto clientPtr = drogon::app().getDbClient("sce");
  auto transPtr = clientPtr->newTransaction();
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
    auto x = Dba::writeInTrans(transPtr, sql);

    nlohmann::json d(nlohmann::json::array());
    for (const auto& r : x) {
      nlohmann::json row;
      row[0] = r["id"].as<long>();
      row[1] = r["label"].c_str();
      d.push_back(row);
    }
    jresult[1] = d;
    batch[0] = jresult;

    return batch;
  } catch (const std::exception& e) {
    SPDLOG_TRACE(e.what());
    // simpleJsonSaveResult(event, false, e.what());
    nlohmann::json r;
    return r;
  }
}
