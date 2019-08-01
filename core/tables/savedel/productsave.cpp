#include "productsave.h"


delFn(category, "product.category");
//delFn(product, "product.product");

delFn(shipping_class, "product.shipping_class");

delFn(setting_type, "product.setting_type");

delFn(certified_by, "product.certified_by");
delFn(policy, "product.policy");

purejoinTableSave(tones, "product.post_tone", "p_tones_tone_id", "post_id", "tone_id");

purejoinTableSave(certified_by, "product.post_certified_by", "p_certified_by_certified_by", "post_id", "certified_by_id");
purejoinTableSave(policy, "product.post_policy", "p_policy_post_policy", "post_id", "policy_id");

void product_tags_process(sqlb::ObjectIdentifier tags_table,
                          sqlb::ObjectIdentifier post_tag_table,
                          Json::Value &in,
                          pqxx::work &txn,
                          int post_id
) {
  std::string strSqlTag = "select id, name FROM %1.%2 where name = $1";
  ReplaceAll2(strSqlTag, "%1", tags_table.schema());
  ReplaceAll2(strSqlTag, "%2", tags_table.name());

  std::string strSqlTagInsert = "INSERT INTO post.tag (name, slug, description) VALUES ($1, $2, $3)";
  ReplaceAll2(strSqlTagInsert, "%1", tags_table.schema());
  ReplaceAll2(strSqlTagInsert, "%2", tags_table.name());

  // post_tag
  std::string strSqlPostTags = "select pt.post_id, pt.tag_id, t.name FROM %1.%2 pt left join %3.%4 t on t.id = pt.tag_id where post_id = $1";
  ReplaceAll2(strSqlPostTags, "%1", post_tag_table.schema());
  ReplaceAll2(strSqlPostTags, "%2", post_tag_table.name());
  ReplaceAll2(strSqlPostTags, "%3", tags_table.schema());
  ReplaceAll2(strSqlPostTags, "%4", tags_table.name());

  std::string strSqlPostTagSimpleFind = "SELECT * FROM %1.%2 WHERE post_id = $1 and tag_id = $2";
  ReplaceAll2(strSqlPostTagSimpleFind, "%1", post_tag_table.schema());
  ReplaceAll2(strSqlPostTagSimpleFind, "%2", post_tag_table.name());

  std::string strSqlPostTagsDel = "DELETE FROM %1.%2 WHERE post_id = $1 and tag_id = $2";
  ReplaceAll2(strSqlPostTagsDel, "%1", post_tag_table.schema());
  ReplaceAll2(strSqlPostTagsDel, "%2", post_tag_table.name());

  std::string strSqlPostTagsInsert = "INSERT INTO %1.%2 (post_id, tag_id) VALUES ($1, $2);";
  ReplaceAll2(strSqlPostTagsInsert, "%1", post_tag_table.schema());
  ReplaceAll2(strSqlPostTagsInsert, "%2", post_tag_table.name());

  auto inNewTags = in["tags_name"].asString();
  std::vector<std::string> inNewTagsVector;
  std::stringstream ss{inNewTags};
  std::string tag;
  // 1.find a tag, if not exist then insert.
  while (ss >> tag) {
    inNewTagsVector.push_back(tag);
    pqxx::result x = txn.exec_params(strSqlTag, tag);
    if (x.size() == 0) {
      txn.exec_params(strSqlTagInsert, tag, tag, tag);
    }
  }
  pqxx::result all_pt = txn.exec_params(strSqlPostTags, post_id);
  // For each saved tags, If saved tag not exist in new tags, delete it.
  for (auto r : all_pt) {
    if (inNewTags.find(r[2].c_str()) == std::string::npos) {
      txn.exec_params(strSqlPostTagsDel, r[0].as<int>(), r[1].as<int>());
    }
  }
  // For each new tags, insert it if it not already exist.
  for (auto r : inNewTagsVector) {
    pqxx::result x = txn.exec_params(strSqlTag, r);

    pqxx::result y = txn.exec_params(strSqlPostTagSimpleFind, post_id, x[0]["id"].as<int>());
    if (y.size() == 0) {
      txn.exec_params(strSqlPostTagsInsert, post_id, x[0][0].as<int>());
    }
  }
}

void save_product_categories(sqlb::ObjectIdentifier post_category_table,
                             Json::Value &in,
                             pqxx::work &txn,
                             int post_id) {
  std::string strSqlPostCategories = "select post_id, category_id FROM %1.%2 where post_id = $1";
  ReplaceAll2(strSqlPostCategories, "%1", post_category_table.schema());
  ReplaceAll2(strSqlPostCategories, "%2", post_category_table.name());

  std::string strSqlPostCategorySimpleFind = "SELECT * FROM %1.%2 WHERE post_id = $1 and category_id = $2";
  ReplaceAll2(strSqlPostCategorySimpleFind, "%1", post_category_table.schema());
  ReplaceAll2(strSqlPostCategorySimpleFind, "%2", post_category_table.name());


  std::string strSqlPostCategoryDel = "DELETE FROM %1.%2 WHERE post_id = $1 and category_id = $2";
  ReplaceAll2(strSqlPostCategoryDel, "%1", post_category_table.schema());
  ReplaceAll2(strSqlPostCategoryDel, "%2", post_category_table.name());

  std::string strSqlPostCategoryInsert = "INSERT INTO %1.%2 (post_id, category_id) VALUES ($1, $2);";
  ReplaceAll2(strSqlPostCategoryInsert, "%1", post_category_table.schema());
  ReplaceAll2(strSqlPostCategoryInsert, "%2", post_category_table.name());

  std::vector<int> inNewCategories;
  for (auto x : in["pc_category_id"]) if (!x.isNull()) inNewCategories.push_back(x.asInt());

  //std::vector<int>updatedCategories;

  pqxx::result all_ct = txn.exec_params(strSqlPostCategories, post_id);
  // For each saved categories, If saved category not exist in new categories, delete it.
  for (auto r : all_ct) {
    std::vector<int>::iterator it = std::find(inNewCategories.begin(), inNewCategories.end(), r[1].as<int>());
    if (it == inNewCategories.end()) {// Element not Found
      txn.exec_params(strSqlPostCategoryDel, r[0].as<int>(), r[1].as<int>());
      //updatedCategories.push_back(r[1].as<int>());
    }
  }

  // For each new categories, insert it if it not already exist.
  for (auto x : inNewCategories) {
    pqxx::result y = txn.exec_params(strSqlPostCategorySimpleFind, post_id, x);
    if (y.size() == 0) {
      txn.exec_params(strSqlPostCategoryInsert, post_id, x);
      //auto it = std::find(inNewCategories.begin(), inNewCategories.end(), x);
      //if (it == inNewCategories.end()) updatedCategories.push_back(x);
    }
  }
}


void save_product_clarities(sqlb::ObjectIdentifier post_clarity_table,
                            Json::Value &in,
                            pqxx::work &txn,
                            int post_id) {
  std::string strSqlPostCategories = "SELECT clarity_id FROM %1.%2 where post_id = $1";
  ReplaceAll2(strSqlPostCategories, "%1", post_clarity_table.schema());
  ReplaceAll2(strSqlPostCategories, "%2", post_clarity_table.name());

  std::string strSqlPostCategorySimpleFind = "SELECT post_id, clarity_id, pcs, weight, price, ismain FROM %1.%2 WHERE post_id = $1 and clarity_id = $2";
  ReplaceAll2(strSqlPostCategorySimpleFind, "%1", post_clarity_table.schema());
  ReplaceAll2(strSqlPostCategorySimpleFind, "%2", post_clarity_table.name());


  std::string strSqlPostCategoryDel = "DELETE FROM %1.%2 WHERE post_id = $1 and clarity_id = $2";
  ReplaceAll2(strSqlPostCategoryDel, "%1", post_clarity_table.schema());
  ReplaceAll2(strSqlPostCategoryDel, "%2", post_clarity_table.name());

  std::string strSqlPostCategoryInsert = "INSERT INTO %1.%2 (post_id, clarity_id, pcs, weight, price, ismain) VALUES ($1, $2, $3, $4, $5, $6);";
  ReplaceAll2(strSqlPostCategoryInsert, "%1", post_clarity_table.schema());
  ReplaceAll2(strSqlPostCategoryInsert, "%2", post_clarity_table.name());

  std::string strSqlPostCategoryUpdateAtt = "UPDATE product.post_clarity SET (pcs, weight, price, ismain) = ROW($3, $4, $5, $6) WHERE post_id = $1 and clarity_id = $2";

  struct PostClarity {
      int clarity_id;
      int pcs;
      double weight;
      double price;
      bool ismain;
  };
  std::vector<PostClarity> inVector;
  for (auto i : in["p_clarity_clarity_id"]) { // purity_id, weight, price
    if (!i[0].isNull())
      inVector.push_back({i[0].asInt(), i[1].asInt(), i[2].asDouble(), i[3].asDouble(), i[4].asBool()});
  }

  pqxx::result all_ct = txn.exec_params(strSqlPostCategories, post_id);
  // For each saved tones, If saved tone not exist in new tones, delete it.
  for (auto r : all_ct) {
    std::vector<PostClarity>::iterator it = std::find_if(inVector.begin(), inVector.end(), [&](PostClarity t) {
        return t.clarity_id == r[0].as<int>();
    });
    if (it == inVector.end()) {// Element not Found
      txn.exec_params(strSqlPostCategoryDel, post_id, r[0].as<int>());
    }
  }
  // For each new tones, insert it if it not already exist.
  for (auto r : inVector) {
    pqxx::result y = txn.exec_params(strSqlPostCategorySimpleFind, post_id, r.clarity_id);
    if (y.size() == 0) {
      txn.exec_params(strSqlPostCategoryInsert, post_id, r.clarity_id, r.pcs, r.weight, r.price, r.ismain);
    } else { // update
      if (y[0][1].as<int>() != r.clarity_id || y[0][2].as<int>() != r.pcs || y[0][3].as<double>() != r.weight ||
          y[0][4].as<double>() != r.price || y[0][5].as<bool>() != r.ismain) {
        txn.exec_params(strSqlPostCategoryUpdateAtt, post_id, r.clarity_id, r.pcs, r.weight, r.price, r.ismain);
      }
    }
  }
}

void save_purity_tone_(Json::Value &in, pqxx::work &txn, int post_id, int purity_id) {
  std::string strSqlPostCategories = sel("product.purity_tone", "post_id, purity_id, tone_id",
                                         "where post_id = $1 and purity_id = $2");
  std::string strSqlPostCategorySimpleFind = sel("product.purity_tone", "post_id, purity_id, tone_id, weight, price, ismain",
                                                 "where post_id = $1 and purity_id = $2 and tone_id = $3");
  std::string strSqlPostCategoryDel = dele("product.purity_tone",
                                           "where post_id = $1 and purity_id = $2 and tone_id = $3");
  std::string strSqlPostCategoryInsert = ins("product.purity_tone", "post_id, purity_id, tone_id, weight, price, ismain", "$1, $2, $3, $4, $5, $6");
  std::string strSqlPostCategoryUpdateAtt = upd("product.purity_tone", "weight, price, ismain", "$4, $5, $6", "where  post_id = $1 and purity_id = $2 and tone_id = $3");

  struct PurityTone {
      int post_id;
      int purity_id;
      int tone_id;
      double weight;
      double price;
      bool ismain;
  };
  std::vector<PurityTone> inNewPrice; // post_id, purity_id, tone_id
  for (auto i : in) {
    if (!i[0].isNull()) { // to pass null row
      inNewPrice.push_back({post_id, purity_id, i[0].asInt(), i[1].asDouble(), i[2].asDouble(), i[3].asBool()});
    }
  }

  pqxx::result all_ct = txn.exec_params(strSqlPostCategories, post_id, purity_id);
  // For each saved attachments, If it not exist in new attachments, delete it.
  for (auto r : all_ct) {
    std::vector<PurityTone>::iterator it = std::find_if(inNewPrice.begin(), inNewPrice.end(), [&](PurityTone t) {
        return t.post_id == r[0].as<int>() && t.purity_id == r[1].as<int>() && t.tone_id == r[2].as<int>();
    });
    if (it == inNewPrice.end()) {// Element not Found
      txn.exec_params(strSqlPostCategoryDel, post_id, r[1].as<int>(), r[2].as<int>());
    }
  }
  // For each new attachments, insert it if it not already exist.
  for (auto r : inNewPrice) {
    pqxx::result y = txn.exec_params(strSqlPostCategorySimpleFind, r.post_id, r.purity_id, r.tone_id);
    if (y.size() == 0) { // insert
      txn.exec_params(strSqlPostCategoryInsert, post_id, r.purity_id, r.tone_id, r.weight, r.price, r.ismain);
    } else { // update
      if(y[0][3].as<double>() != r.weight || y[0][4].as<double>() != r.price || y[0][5].as<bool>() != r.ismain) {
      txn.exec_params(strSqlPostCategoryUpdateAtt, post_id, r.purity_id, r.tone_id, r.weight, r.price, r.ismain);
      }
    }
  }
}

void save_product_purities(sqlb::ObjectIdentifier post_purity_table,
                           Json::Value &in,
                           pqxx::work &txn,
                           int post_id) {
  std::string strSqlPostCategories = "SELECT purity_id FROM %1.%2 where post_id = $1";
  ReplaceAll2(strSqlPostCategories, "%1", post_purity_table.schema());
  ReplaceAll2(strSqlPostCategories, "%2", post_purity_table.name());

  std::string strSqlPostCategorySimpleFind = "SELECT purity_id, ismain FROM %1.%2 WHERE post_id = $1 and purity_id = $2";
  ReplaceAll2(strSqlPostCategorySimpleFind, "%1", post_purity_table.schema());
  ReplaceAll2(strSqlPostCategorySimpleFind, "%2", post_purity_table.name());


  std::string strSqlPostCategoryDel = "DELETE FROM %1.%2 WHERE post_id = $1 and purity_id = $2";
  ReplaceAll2(strSqlPostCategoryDel, "%1", post_purity_table.schema());
  ReplaceAll2(strSqlPostCategoryDel, "%2", post_purity_table.name());

  std::string strSqlPostCategoryInsert = "INSERT INTO %1.%2 (post_id, purity_id, ismain) VALUES ($1, $2, $3);";
  ReplaceAll2(strSqlPostCategoryInsert, "%1", post_purity_table.schema());
  ReplaceAll2(strSqlPostCategoryInsert, "%2", post_purity_table.name());

  auto strSqlPostCategoryUpdateAtt = upd("product.post_purity", "ismain", "$3", "where post_id = $1 and purity_id = $2");

  struct PostPurity {
      int purity_id;
      bool ismain;
      Json::Value tones;
  };

  std::vector<PostPurity> inVector;
  for (auto i : in["p_purities_purity_id"]) { // purity_id, arry
    if (!i[0].isNull()) inVector.push_back({i[0].asInt(), i[2].asBool(), i[1]});
  }

  pqxx::result all_ct = txn.exec_params(strSqlPostCategories, post_id);
  // For each saved tones, If saved tone not exist in new tones, delete it.
  for (auto r : all_ct) {
    std::vector<PostPurity>::iterator it = std::find_if(inVector.begin(), inVector.end(), [&](PostPurity t) {
        return t.purity_id == r[0].as<int>();
    });
    if (it == inVector.end()) {// Element not Found
      txn.exec_params("DELETE FROM product.purity_tone WHERE post_id = $1 and purity_id = $2", post_id,
                      r[0].as<int>());
      txn.exec_params(strSqlPostCategoryDel, post_id, r[0].as<int>());
    }
  }
  // For each new tones, insert it if it not already exist.
  for (auto r : inVector) {
    pqxx::result y = txn.exec_params(strSqlPostCategorySimpleFind, post_id, r.purity_id);
    if (y.size() == 0) {
      txn.exec_params(strSqlPostCategoryInsert, post_id, r.purity_id, r.ismain);
      save_purity_tone_(r.tones, txn, post_id, r.purity_id);
    } else { // update
      if (y[0][0].as<int>() != r.purity_id || y[0][0].as<int>() != r.ismain) {
        txn.exec_params(strSqlPostCategoryUpdateAtt, post_id, r.purity_id, r.ismain);
      }
      save_purity_tone_(r.tones, txn, post_id, r.purity_id);
    }
  }
}

void save_diamond_price(Json::Value &in, pqxx::work &txn, int diamond_id) {
  std::string strSqlPostCategories = "SELECT diamond_id, clarity_id, weight, total_weight, rate, price FROM product.diamond_price where diamond_id = $1";
  std::string strSqlPostCategorySimpleFind = "SELECT diamond_id, clarity_id, weight, total_weight, rate, price FROM product.diamond_price where diamond_id = $1 and clarity_id = $2";
  std::string strSqlPostCategoryDel = "DELETE FROM product.diamond_price WHERE diamond_id = $1 and clarity_id = $2";
  std::string strSqlPostCategoryInsert = "INSERT INTO product.diamond_price (diamond_id, clarity_id, weight, total_weight, rate, price) VALUES ($1, $2, $3, $4, $5, $6)";
  std::string strSqlPostCategoryUpdateAtt = "UPDATE product.diamond_price SET (weight, total_weight, rate, price) = ROW($3, $4, $5, $6) WHERE diamond_id = $1 and clarity_id = $2";

  struct DiamondPrice {
      int diamond_id;
      int clarity_id;
      double weight;
      double total_weight;
      double rate;
      double price;
  };
  std::vector<DiamondPrice> inNewPrice;
  for (auto i : in) {
    if (!i[0].isNull()) { // to pass null row
      inNewPrice.push_back(
              {diamond_id, i[0].asInt(), i[2].asDouble(), i[3].asDouble(), i[4].asDouble(), i[5].asDouble()});
    }
  }

  pqxx::result all_ct = txn.exec_params(strSqlPostCategories, diamond_id);
  // For each saved attachments, If it not exist in new attachments, delete it.
  for (auto r : all_ct) {
    std::vector<DiamondPrice>::iterator it = std::find_if(inNewPrice.begin(), inNewPrice.end(),
                                                          [&](DiamondPrice t) {
                                                              return t.diamond_id == r[0].as<int>() &&
                                                                     t.clarity_id == r[1].as<int>();
                                                          });
    if (it == inNewPrice.end()) {// Element not Found
      txn.exec_params(strSqlPostCategoryDel, diamond_id, r[1].as<int>());
    }
  }
  // For each new attachments, insert it if it not already exist.
  for (auto r : inNewPrice) {
    pqxx::result y = txn.exec_params(strSqlPostCategorySimpleFind, r.diamond_id, r.clarity_id);
    if (y.size() == 0) { // insert
      txn.exec_params(strSqlPostCategoryInsert, diamond_id, r.clarity_id, r.weight, r.total_weight, r.rate,
                      r.price);
    } else { // update
      //if(y[0][1].as<int>() != r.shape_id || y[0][2].as<int>() != r.color_id || y[0][3].c_str() != r.dsize || y[0][4].as<int>() != r.pcs || y[0][5].as<double>() != r.price) {
      txn.exec_params(strSqlPostCategoryUpdateAtt, diamond_id, r.clarity_id, r.weight, r.total_weight, r.rate,
                      r.price);
      //}
    }
  }
}

void save_product_diamond_sizes(sqlb::ObjectIdentifier post_diamond_sizes_table,
                                Json::Value &in,
                                pqxx::work &txn,
                                int post_id) {
  std::string strSqlPostCategories = "SELECT id, post_id, shape_id, color_id, size_id, pcs FROM product.post_diamond_size where post_id = $1";
  std::string strSqlPostCategorySimpleFind = "SELECT id, post_id, shape_id, color_id, size_id, pcs, setting_type_id FROM product.post_diamond_size WHERE id = $1";
  std::string strSqlPostCategoryDel = "DELETE FROM product.post_diamond_size WHERE id = $1";
  std::string strSqlPostCategoryInsert = "INSERT INTO product.post_diamond_size (post_id, shape_id, color_id, size_id, pcs, setting_type_id) VALUES ($1, $2, $3, $4, $5, NULLIF($6, 0)) RETURNING id;";
  std::string strSqlPostCategoryUpdateAtt = "UPDATE product.post_diamond_size SET (post_id, shape_id, color_id, size_id, pcs, setting_type_id) = ROW($2, $3, $4, $5, $6, NULLIF($7, 0)) WHERE id = $1;";

  struct PostDiamondSize {
      int id;
      int shape_id;
      int color_id;
      int pcs;
      int setting_type_id;
      std::string dsize;
      Json::Value clarity_price;
  };
  std::vector<PostDiamondSize> inNewAttachments; // id Shape	Color	Size	Pcs
  for (auto i : in["p_d_size_diamond_size_id"]) {
    if (!i[1].isNull()) { // to pass null row
      inNewAttachments.push_back(
              {i[0].asInt(), i[1].asInt(), i[2].asInt(), i[4].asInt(), i[5].asInt(), i[3].asString(), i[6]});
    }
  }

  pqxx::result all_ct = txn.exec_params(strSqlPostCategories, post_id);
  // For each saved attachments, If it not exist in new attachments, delete it.
  for (auto r : all_ct) {
    std::vector<PostDiamondSize>::iterator it = std::find_if(inNewAttachments.begin(), inNewAttachments.end(),
                                                             [&](PostDiamondSize t) {
                                                                 return t.id == r[0].as<int>();
                                                             });
    if (it == inNewAttachments.end()) {// Element not Found
      txn.exec_params("DELETE FROM product.diamond_price WHERE diamond_id = $1", r[0].as<int>());
      txn.exec_params(strSqlPostCategoryDel, r[0].as<int>());
    }
  }
  // For each new attachments, insert it if it not already exist.
  for (auto r : inNewAttachments) {
    pqxx::result y = txn.exec_params(strSqlPostCategorySimpleFind, r.id);
    if (y.size() == 0) { // insert
      auto i = txn.exec_params(strSqlPostCategoryInsert, post_id, r.shape_id, r.color_id, r.dsize, r.pcs,
                               r.setting_type_id);
      save_diamond_price(r.clarity_price, txn, i[0][0].as<int>());
    } else { // update
      auto set_id = y[0][6].is_null() ? 0 : y[0][6].as<int>();
      if (y[0][2].as<int>() != r.shape_id || y[0][3].as<int>() != r.color_id || y[0][4].c_str() != r.dsize ||
          y[0][5].as<int>() != r.pcs || set_id != r.setting_type_id) {
        txn.exec_params(strSqlPostCategoryUpdateAtt, r.id, post_id, r.shape_id, r.color_id, r.dsize, r.pcs,
                        r.setting_type_id);
      }
      save_diamond_price(r.clarity_price, txn, y[0][0].as<int>());
    }
  }
}

void save_cs_price(Json::Value &in, pqxx::work &txn, int cs_id) {
  std::string strSqlPostCategories = "SELECT cs_id, weight, total_weight, rate, price FROM product.cs_price where cs_id = $1";
  std::string strSqlPostCategorySimpleFind = "SELECT cs_id, 0, weight, total_weight, rate, price FROM product.cs_price where cs_id = $1";
  std::string strSqlPostCategoryDel = "DELETE FROM product.cs_price WHERE cs_id = $1";
  std::string strSqlPostCategoryInsert = "INSERT INTO product.cs_price (cs_id, weight, total_weight, rate, price) VALUES ($1, $2, $3, $4, $5)";
  std::string strSqlPostCategoryUpdateAtt = "UPDATE product.cs_price SET (weight, total_weight, rate, price) = ROW($2, $3, $4, $5) WHERE cs_id = $1";

  struct DiamondPrice {
      int cs_id;
      //        int clarity_id;
      double weight;
      double total_weight;
      double rate;
      double price;
  };
  std::vector<DiamondPrice> inNewPrice;
  for (auto i : in) {
    if (!i[0].isNull()) { // to pass null row
      inNewPrice.push_back({cs_id, i[2].asDouble(), i[3].asDouble(), i[4].asDouble(), i[5].asDouble()});
    }
  }

  pqxx::result all_ct = txn.exec_params(strSqlPostCategories, cs_id);
  // For each saved attachments, If it not exist in new attachments, delete it.
  for (auto r : all_ct) {
    std::vector<DiamondPrice>::iterator it = std::find_if(inNewPrice.begin(), inNewPrice.end(),
                                                          [&](DiamondPrice t) {
                                                              return t.cs_id == r[0].as<int>();
                                                          });
    if (it == inNewPrice.end()) {// Element not Found
      txn.exec_params(strSqlPostCategoryDel, cs_id, r[1].as<int>());
    }
  }
  // For each new attachments, insert it if it not already exist.
  for (auto r : inNewPrice) {
    pqxx::result y = txn.exec_params(strSqlPostCategorySimpleFind, r.cs_id);
    if (y.size() == 0) { // insert
      txn.exec_params(strSqlPostCategoryInsert, cs_id, r.weight, r.total_weight, r.rate, r.price);
    } else { // update
      //if(y[0][1].as<int>() != r.shape_id || y[0][2].as<int>() != r.color_id || y[0][3].c_str() != r.dsize || y[0][4].as<int>() != r.pcs || y[0][5].as<double>() != r.price) {
      txn.exec_params(strSqlPostCategoryUpdateAtt, cs_id, r.weight, r.total_weight, r.rate, r.price);
      //}
    }
  }
}

void save_product_cs_sizes(sqlb::ObjectIdentifier post_color_stone_size_table,
                           Json::Value &in,
                           pqxx::work &txn,
                           int post_id) {
  std::string strSqlPostCategories = "SELECT id, post_id, shape_id, color_id, size_id, pcs FROM product.post_color_stone_size where post_id = $1";
  std::string strSqlPostCategorySimpleFind = "SELECT id, post_id, shape_id, color_id, size_id, pcs, setting_type_id FROM product.post_color_stone_size WHERE id = $1";
  std::string strSqlPostCategoryDel = "DELETE FROM product.post_color_stone_size WHERE id = $1";
  std::string strSqlPostCategoryInsert = "INSERT INTO product.post_color_stone_size (post_id, cs_type_id, shape_id, color_id, size_id, pcs, setting_type_id) VALUES ($1, $2, $3, $4, $5, $6, NULLIF($7, 0)) RETURNING id;";
  std::string strSqlPostCategoryUpdateAtt = "UPDATE product.post_color_stone_size SET (post_id, cs_type_id, shape_id, color_id, size_id, pcs, setting_type_id) = ROW($2, $3, $4, $5, $6, $7, NULLIF($8, 0)) WHERE id = $1;";

  struct PostCSSize {
      int id;
      int cs_type_id;
      int shape_id;
      int color_id;
      int pcs;
      int setting_type_id;
      std::string dsize;
      Json::Value clarity_price;
  };
  std::vector<PostCSSize> inNewAttachments; // id Shape	Color	Size	Pcs
  for (auto i : in["p_cs_size_cs_size_id"]) {
    if (!i[1].isNull()) { // to pass null row
      inNewAttachments.push_back(
              {i[0].asInt(), i[1].asInt(), i[2].asInt(), i[3].asInt(), i[5].asInt(), i[6].asInt(), i[4].asString(), i[7]});
    }
  }

  pqxx::result all_ct = txn.exec_params(strSqlPostCategories, post_id);
  // For each saved attachments, If it not exist in new attachments, delete it.
  for (auto r : all_ct) {
    std::vector<PostCSSize>::iterator it = std::find_if(inNewAttachments.begin(), inNewAttachments.end(),
                                                             [&](PostCSSize t) {
                                                                 return t.id == r[0].as<int>();
                                                             });
    if (it == inNewAttachments.end()) {// Element not Found
      txn.exec_params("DELETE FROM product.cs_price WHERE cs_id = $1", r[0].as<int>());
      txn.exec_params(strSqlPostCategoryDel, r[0].as<int>());
    }
  }
  // For each new attachments, insert it if it not already exist.
  for (auto r : inNewAttachments) {
    pqxx::result y = txn.exec_params(strSqlPostCategorySimpleFind, r.id);
    if (y.size() == 0) { // insert
      auto i = txn.exec_params(strSqlPostCategoryInsert, post_id, r.cs_type_id, r.shape_id, r.color_id, r.dsize, r.pcs,
                               r.setting_type_id);
      save_cs_price(r.clarity_price, txn, i[0][0].as<int>());
    } else { // update
      auto set_id = y[0][6].is_null() ? 0 : y[0][6].as<int>();
      if (y[0][2].as<int>() != r.shape_id || y[0][3].as<int>() != r.color_id || y[0][4].c_str() != r.dsize ||
          y[0][5].as<int>() != r.pcs || set_id != r.setting_type_id) {
        txn.exec_params(strSqlPostCategoryUpdateAtt, r.id, post_id, r.cs_type_id, r.shape_id, r.color_id, r.dsize, r.pcs,
                        r.setting_type_id);
      }
      save_cs_price(r.clarity_price, txn, y[0][0].as<int>());
    }
  }
}

void save_product_cs_total(sqlb::ObjectIdentifier post_cs_total_table,
                           Json::Value &in,
                           pqxx::work &txn,
                           int post_id) {
  std::string strSqlPostCategories = "SELECT post_id, pcs, weight, price FROM product.post_cs_total where post_id = $1";
  std::string strSqlPostCategorySimpleFind = "SELECT post_id, pcs, weight, price FROM product.post_cs_total WHERE post_id = $1";
  std::string strSqlPostCategoryDel = "DELETE FROM product.post_cs_total WHERE post_id = $1";
  std::string strSqlPostCategoryInsert = "INSERT INTO product.post_cs_total (post_id, pcs, weight, price) VALUES ($1, $2, $3, $4) RETURNING post_id;";
  std::string strSqlPostCategoryUpdateAtt = "UPDATE product.post_cs_total SET (pcs, weight, price) = ROW($2, $3, $4) WHERE post_id = $1;";

  struct PostCSTotal {
      int post_id; // we have to add this, to find index
      int pcs;
      double weight;
      double price;
  };
  std::vector<PostCSTotal> inNewAttachments; // id Shape	Color	Size	Pcs
  for (auto i : in["p_cs_total_p_cs_total"]) {
    if (!i[1].isNull()) { // to pass null row
      inNewAttachments.push_back({post_id, i[0].asInt(), i[1].asDouble(), i[2].asDouble()});
    }
  }

  pqxx::result all_ct = txn.exec_params(strSqlPostCategories, post_id);
  // For each saved attachments, If it not exist in new attachments, delete it.
  for (auto r : all_ct) {
    std::vector<PostCSTotal>::iterator it = std::find_if(inNewAttachments.begin(), inNewAttachments.end(),
                                                         [&](PostCSTotal t) {
                                                             return t.post_id == r[0].as<int>();
                                                         });
    if (it == inNewAttachments.end()) {// Element not Found
      txn.exec_params(strSqlPostCategoryDel, r[0].as<int>());
    }
  }
  // For each new attachments, insert it if it not already exist.
  for (auto r : inNewAttachments) {
    pqxx::result y = txn.exec_params(strSqlPostCategorySimpleFind, r.post_id);
    if (y.size() == 0) { // insert
      auto i = txn.exec_params(strSqlPostCategoryInsert, post_id, r.pcs, r.weight, r.price);
    } else { // update
      if (y[0][0].as<int>() != r.post_id || y[0][1].as<int>() != r.pcs || y[0][2].as<double>() != r.weight ||
          y[0][3].as<double>() != r.price) {
        txn.exec_params(strSqlPostCategoryUpdateAtt, r.post_id, r.pcs, r.weight, r.price);
      }
    }
  }
}

void save_product_Attachments(sqlb::ObjectIdentifier post_attachment_table,
                              Json::Value &in,
                              pqxx::work &txn,
                              int post_id) {
  std::string strSqlPostCategories = "SELECT id FROM %1.%2 where post_id = $1";
  ReplaceAll2(strSqlPostCategories, "%1", post_attachment_table.schema());
  ReplaceAll2(strSqlPostCategories, "%2", post_attachment_table.name());

  std::string strSqlPostCategorySimpleFind = "SELECT id, post_id, tone_id, main_image FROM %1.%2 WHERE id = $1";
  ReplaceAll2(strSqlPostCategorySimpleFind, "%1", post_attachment_table.schema());
  ReplaceAll2(strSqlPostCategorySimpleFind, "%2", post_attachment_table.name());


  std::string strSqlPostCategoryDel = "DELETE FROM %1.%2 WHERE id = $1";
  ReplaceAll2(strSqlPostCategoryDel, "%1", post_attachment_table.schema());
  ReplaceAll2(strSqlPostCategoryDel, "%2", post_attachment_table.name());

  std::string strSqlPostCategoryInsert = "INSERT INTO %1.%2 (post_id, tone_id, name, size, type, main_image) VALUES ($1, $2, $3, $4, $5, $6);";
  ReplaceAll2(strSqlPostCategoryInsert, "%1", post_attachment_table.schema());
  ReplaceAll2(strSqlPostCategoryInsert, "%2", post_attachment_table.name());

  std::string strSqlPostCategoryUpdate = "UPDATE product.post_attachment SET (tone_id, main_image) = ROW($2, $3) WHERE id = $1;";
  std::string strSqlPostCategoryUpdateAtt = "UPDATE product.post_attachment SET (tone_id, name, size, type, main_image) = ROW($2, $3, $4, $5, $6) WHERE id = $1;";

  std::string strSqlTempImage = "SELECT name, size, type FROM setting.temp_image_id WHERE id = $1";
  std::string strSqlTempImageDel = "DELETE FROM setting.temp_image_id WHERE id = $1";

  struct Attachment {
      int id;
      int tone_id;
      int temp_id;
      bool main_image;
  };
  std::vector<Attachment> inNewAttachments; // tone_id, temp_id
  for (auto i : in["p_attachments_attachement_id"]) {
    if (i[1].asInt() == 0) {
      continue;
    }
    inNewAttachments.push_back({i[0].asInt(), i[1].asInt(), i[2].asInt(), i[3].asBool()});
  }

  pqxx::result all_ct = txn.exec_params(strSqlPostCategories, post_id);
  // For each saved attachments, If it not exist in new attachments, delete it.
  for (auto r : all_ct) {
    std::vector<Attachment>::iterator it = std::find_if(inNewAttachments.begin(), inNewAttachments.end(),
                                                        [&](Attachment t) {
                                                            return t.id == r[0].as<int>();
                                                        });
    if (it == inNewAttachments.end()) {// Element not Found
      txn.exec_params(strSqlPostCategoryDel, r[0].as<int>());
    }
  }
  // For each new attachments, insert it if it not already exist.
  for (auto r : inNewAttachments) {
    pqxx::result y = txn.exec_params(strSqlPostCategorySimpleFind, r.id);
    if (y.size() == 0) { // insert
      auto temp_id = r.temp_id;
      if (temp_id != 0) {
        pqxx::result z = txn.exec_params(strSqlTempImage, temp_id);
        if (z.size() == 1) {
          txn.exec_params(strSqlPostCategoryInsert, post_id, r.tone_id, z[0][0].c_str(), z[0][1].as<int>(),
                          z[0][2].c_str(), r.main_image);
          txn.exec_params(strSqlTempImageDel, temp_id);
        }
      }
    } else { // update
      if (y[0][2].as<int>() != r.tone_id || y[0][3].as<bool>() != r.main_image ||
          r.temp_id != 0) { // can also update image
        auto temp_id = r.temp_id;
        if (temp_id != 0) {
          pqxx::result z = txn.exec_params(strSqlTempImage, temp_id);
          if (z.size() == 1) {
            txn.exec_params(strSqlPostCategoryUpdateAtt, y[0][0].as<int>(), r.tone_id, z[0][0].c_str(),
                            z[0][1].as<int>(), z[0][2].c_str(), r.main_image);
            txn.exec_params(strSqlTempImageDel, temp_id);
          }
        } else {
          txn.exec_params(strSqlPostCategoryUpdate, r.id, r.tone_id, r.main_image);
        }

      }
    }
  }
}

Json::Value save_product(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
  printJson(in);
  auto product_table = sqlb::ObjectIdentifier("product", "product", "p");
  auto post_table = sqlb::ObjectIdentifier("post", "post", "p");
  auto tags_table = sqlb::ObjectIdentifier("post", "tag", "t");
  auto post_tag_table = sqlb::ObjectIdentifier("post", "post_tag", "pt");
  auto post_category_table = sqlb::ObjectIdentifier("product", "post_category", "pt");
  auto post_tone_table = sqlb::ObjectIdentifier("product", "post_tone", "p_tones");
  auto post_clarity_table = sqlb::ObjectIdentifier("product", "post_clarity", "p_clarity");
  auto post_purity_table = sqlb::ObjectIdentifier("product", "post_purity", "p_purities");
  auto post_attachment_table = sqlb::ObjectIdentifier("product", "post_attachment", "p_attachments");
  auto post_diamond_sizes_table = sqlb::ObjectIdentifier("product", "post_diamond_size", "post_diamond_sizes");
  auto post_cs_total_table = sqlb::ObjectIdentifier("product", "post_cs_total", "post_cs_total");
  auto post_certified_by = sqlb::ObjectIdentifier("product", "post_certified_by", "p_certified_by");

  if (in["id"].asInt()) {
    std::string strSqlPost =
            "update %1.%2 set "
            "(comment_status, menu_order, post_excerpt, post_content, post_title, post_name, post_password, post_status, post_date, post_type, visibility)"
            " = ROW($2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12) where id=$1";
    ReplaceAll2(strSqlPost, "%1", post_table.schema());
    ReplaceAll2(strSqlPost, "%2", post_table.name());

    std::string strSqlProduct =
            "update %1.%2 set "
            "(post_id, sku, min_price, max_price, weight, length, width, height, manage_stock, featured, stock_quantity, shipping_class_id, catalog_visibility, product_type, backorders, stock_status, virtual, downloadable, purchase_note, low_stock_amount, sold_individually, making_charges, discount_per, volume, purity_id, tone_id)"
            " = ROW($2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, NULLIF($13, 0), $14, $15, $16, $17, $18, $19, $20, $21, $22, $23, $24, $25, $26, $27) where id=$1";
    ReplaceAll2(strSqlProduct, "%1", product_table.schema());
    ReplaceAll2(strSqlProduct, "%2", product_table.name());

    pqxx::work txn{DD};
    try {
      txn.exec_params(strSqlPost,
                      in["id"].asInt(),
                      in["comment_status"].asBool(),
                      in["menu_order"].asInt(),
                      in["post_excerpt"].asString(),
                      in["post_content"].asString(),
                      in["post_title"].asString(),
                      in["post_name"].asString(),
                      in["post_password"].asString(),
                      in["post_status"].asString(),
                      in["post_date"].asString(),
                      in["post_type"].asString(),
                      in["visibility"].asString()
      );
      auto post_id = in["id"].asInt();
      txn.exec_params(strSqlProduct,
                      in["p_id"].asInt(),
                      post_id,
                      in["p_sku"].asString(),
                      in["p_min_price"].asFloat(),
                      in["p_max_price"].asFloat(),
                      in["p_weight"].asFloat(),
                      in["p_length"].asFloat(),
                      in["p_width"].asFloat(),
                      in["p_height"].asFloat(),
                      in["p_manage_stock"].asBool(),
                      in["p_featured"].asBool(),
                      in["p_stock_quantity"].asFloat(),
                      in["p_shipping_class_id"].asInt(),
                      in["p_catalog_visibility"].asString(),
                      in["p_product_type"].asString(),
                      in["p_backorders"].asString(),
                      in["p_stock_status"].asString(),
                      in["p_virtual"].asBool(),
                      in["p_downloadable"].asBool(),
                      in["p_purchase_note"].asString(),
                      in["p_low_stock_amount"].asInt(),
                      in["p_sold_individually"].asBool(),
                      in["p_making_charges"].asDouble(),
                      in["p_discount_per"].asDouble(),
                      in["p_volume"].asDouble(),
                      in["p_purity_id"].asInt(),
                      in["p_tone_id"].asInt()
      );

      product_tags_process(tags_table, post_tag_table, in, txn, post_id);
      save_product_categories(post_category_table, in, txn, post_id);
      save_product_tones(in, txn, post_id);
      save_product_clarities(post_clarity_table, in, txn, post_id);
      save_product_purities(post_purity_table, in, txn, post_id);
      save_product_Attachments(post_attachment_table, in, txn, post_id);
      save_product_diamond_sizes(post_diamond_sizes_table, in, txn, post_id);
      save_product_cs_sizes(post_diamond_sizes_table, in, txn, post_id);
      save_product_cs_total(post_cs_total_table, in, txn, post_id);
      save_product_certified_by(in, txn, post_id);
      save_product_policy(in, txn, post_id);

      txn.commit();
      return simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
      txn.abort();
      std::cerr << e.what() << std::endl;
      return simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }
  } else {
    std::string strSqlPost =
            "INSERT INTO %1.%2 "
            "(comment_status, menu_order, post_excerpt, post_content, post_title, post_name, post_password, post_status, post_date, post_type, visibility)"
            " VALUES($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11)"
            "RETURNING id";
    ReplaceAll2(strSqlPost, "%1", post_table.schema());
    ReplaceAll2(strSqlPost, "%2", post_table.name());

    std::string strSqlProduct = "INSERT INTO %1.%2 "
                                "(post_id, sku, min_price, max_price, weight, length, width, height, manage_stock, featured, stock_quantity, shipping_class_id, catalog_visibility, product_type, backorders, stock_status, virtual, downloadable, purchase_note, low_stock_amount, sold_individually, making_charges, discount_per, volume, purity_id, tone_id)"
                                " VALUES($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, NULLIF($12, 0), $13, $14, $15, $16, $17, $18, $19, $20, $21, $22, $23, $24, $25, $26)";
    ReplaceAll2(strSqlProduct, "%1", product_table.schema());
    ReplaceAll2(strSqlProduct, "%2", product_table.name());


    pqxx::work txn{DD};
    try {
      pqxx::result x = txn.exec_params(
              strSqlPost,
              in["comment_status"].asBool(),
              in["menu_order"].asInt(),
              in["post_excerpt"].asString(),
              in["post_content"].asString(),
              in["post_title"].asString(),
              in["post_name"].asString(),
              in["post_password"].asString(),
              in["post_status"].asString(),
              in["post_date"].asString(),
              in["post_type"].asString(),
              in["visibility"].asString()
      );
      auto post_id = x[0]["id"].as<int>();

      txn.exec_params(
              strSqlProduct,
              post_id,
              in["p_sku"].asString(),
              in["p_min_price"].asFloat(),
              in["p_max_price"].asFloat(),
              in["p_weight"].asFloat(),
              in["p_length"].asFloat(),
              in["p_width"].asFloat(),
              in["p_height"].asFloat(),
              in["p_manage_stock"].asBool(),
              in["p_featured"].asBool(),
              in["p_stock_quantity"].asFloat(),
              in["p_shipping_class_id"].asInt(),
              in["p_catalog_visibility"].asString(),
              in["p_product_type"].asString(),
              in["p_backorders"].asString(),
              in["p_stock_status"].asString(),
              in["p_virtual"].asBool(),
              in["p_downloadable"].asBool(),
              in["p_purchase_note"].asString(),
              in["p_low_stock_amount"].asInt(),
              in["p_sold_individually"].asBool(),
              in["p_making_charges"].asDouble(),
              in["p_discount_per"].asDouble(),
              in["p_volume"].asDouble(),
              in["p_purity_id"].asInt(),
              in["p_tone_id"].asInt()
      );
      product_tags_process(tags_table, post_tag_table, in, txn, post_id);
      save_product_categories(post_category_table, in, txn, post_id);
      save_product_tones(in, txn, post_id);
      save_product_clarities(post_clarity_table, in, txn, post_id);
      save_product_purities(post_purity_table, in, txn, post_id);
      save_product_Attachments(post_attachment_table, in, txn, post_id);
      save_product_diamond_sizes(post_diamond_sizes_table, in, txn, post_id);
      save_product_cs_sizes(post_diamond_sizes_table, in, txn, post_id);
      save_product_cs_total(post_cs_total_table, in, txn, post_id);
      save_product_certified_by(in, txn, post_id);
      save_product_policy(in, txn, post_id);
      txn.commit();
      return simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
      txn.abort();
      std::cerr << e.what() << std::endl;
      return simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }
  }
}

Json::Value delete_product(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
  printJson(in);

  pqxx::work txn{DD};
  try {
    auto post_del = "DELETE FROM post.post WHERE id = $1";
    auto product_del = "DELETE FROM product.product WHERE post_id = $1";
    //auto tags_del = "DELETE FROM post.tag  WHERE post_id = $1"; // Fix This. If Tag is not used in any product delete it
    auto post_tag_del = "DELETE FROM post.post_tag  WHERE post_id = $1";
    auto post_category_del = "DELETE FROM product.post_category  WHERE post_id = $1";
    auto post_tone_del = "DELETE FROM product.post_tone WHERE post_id = $1";
    auto post_clarity_del = "DELETE FROM product.post_clarity WHERE post_id = $1";
    auto post_purity_del = "DELETE FROM product.post_purity WHERE post_id = $1";
    auto post_purity_tone_del = "DELETE FROM product.purity_tone WHERE post_id = $1";
    auto post_attachment_del = "DELETE FROM product.post_attachment WHERE post_id = $1";
    auto post_diamond_sizes_del = "DELETE FROM product.post_diamond_size WHERE post_id = $1";
    auto post_diamond_price_id = "delete from product.diamond_price dp where dp.diamond_id in (select id from product.post_diamond_size ds where ds.post_id = $1);";
    auto post_cs_sizes_del = "DELETE FROM product.post_color_stone_size WHERE post_id = $1";
    auto post_cs_price_del = "delete from product.cs_price cp where cp.cs_id in (select id from product.post_color_stone_size cs where cs.post_id = $1);";
    auto post_cs_total_del = "DELETE FROM product.post_cs_total WHERE post_id = $1";
    auto post_certified_by_del = "DELETE FROM product.post_certified_by WHERE post_id = $1";
    auto post_policy_del = "DELETE FROM product.post_policy WHERE post_id = $1";

    txn.exec_params(post_policy_del, in[0].asInt());
    txn.exec_params(post_certified_by_del, in[0].asInt());
    txn.exec_params(post_cs_total_del, in[0].asInt());
    txn.exec_params(post_cs_price_del, in[0].asInt());
    txn.exec_params(post_cs_sizes_del, in[0].asInt());
    txn.exec_params(post_diamond_price_id, in[0].asInt());
    txn.exec_params(post_diamond_sizes_del, in[0].asInt());
    txn.exec_params(post_attachment_del, in[0].asInt());
    txn.exec_params(post_purity_tone_del, in[0].asInt());
    txn.exec_params(post_purity_del, in[0].asInt());
    txn.exec_params(post_tone_del, in[0].asInt());
    txn.exec_params(post_tone_del, in[0].asInt());
    txn.exec_params(post_clarity_del, in[0].asInt());
    txn.exec_params(post_category_del, in[0].asInt());
    txn.exec_params(post_tag_del, in[0].asInt());
    //txn.exec_params(tags_del, in[0].asInt()); // Fix This. If Tag is not used in any product delete it
    txn.exec_params(product_del, in[0].asInt());
    txn.exec_params(post_del, in[0].asInt());


    txn.commit();
    return simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
  } catch (const std::exception &e) {
    txn.abort();
    std::cerr << e.what() << std::endl;
    return simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
  }
}


Json::Value save_category(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
  printJson(in);
  auto product_table = sqlb::ObjectIdentifier("product", "category", "p");

  if (in["id"].asInt()) {
    std::string strSql =
            "update %1.%2 set "
            "(slug, name, description, display_type, parent_id, position)"
            " = ROW($2, $3, $4, $5, NULLIF($6, 0), $7) where id=$1";
    ReplaceAll2(strSql, "%1", product_table.schema());
    ReplaceAll2(strSql, "%2", product_table.name());

    pqxx::work txn{DD};
    try {
      txn.exec_params(strSql,
                      in["id"].asInt(),
                      in["slug"].asString(),
                      in["name"].asString(),
                      in["description"].asString(),
                      in["display_type"].asString(),
                      in["parent_id"].asInt(),
                      in["position"].asInt()
      );
      txn.commit();
      return simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
      txn.abort();
      std::cerr << e.what() << std::endl;
      return simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }
  } else {
    std::string strSql = "INSERT INTO %1.%2 (slug, name, description, display_type, parent_id, position) values($1, $2, $3, $4, NULLIF($5, 0), $6)";
    ReplaceAll2(strSql, "%1", product_table.schema());
    ReplaceAll2(strSql, "%2", product_table.name());

    pqxx::work txn{DD};
    try {
      txn.exec_params(
              strSql,
              in["slug"].asString(),
              in["name"].asString(),
              in["description"].asString(),
              in["display_type"].asString(),
              in["parent_id"].asInt(),
              in["position"].asInt()
      );
      txn.commit();
      return simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
      txn.abort();
      std::cerr << e.what() << std::endl;
      return simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }
  }
}

Json::Value save_shipping_class(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
  printJson(in);
  auto product_table = sqlb::ObjectIdentifier("product", "shipping_class", "s");

  if (in["id"].asInt()) {
    std::string strSql =
            "update %1.%2 set "
            "(slug, name, description)"
            " = ROW($2, $3, $4) where id=$1";
    ReplaceAll2(strSql, "%1", product_table.schema());
    ReplaceAll2(strSql, "%2", product_table.name());

    pqxx::work txn{DD};
    try {
      txn.exec_params(strSql,
                      in["id"].asInt(),
                      in["slug"].asString(),
                      in["name"].asString(),
                      in["description"].asString()
      );
      txn.commit();
      return simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
      txn.abort();
      std::cerr << e.what() << std::endl;
      return simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }
  } else {
    std::string strSql = "INSERT INTO %1.%2 (slug, name, description) values($1, $2, $3)";
    ReplaceAll2(strSql, "%1", product_table.schema());
    ReplaceAll2(strSql, "%2", product_table.name());

    pqxx::work txn{DD};
    try {
      txn.exec_params(
              strSql,
              in["slug"].asString(),
              in["name"].asString(),
              in["description"].asString()
      );
      txn.commit();
      return simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
      txn.abort();
      std::cerr << e.what() << std::endl;
      return simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }
  }
}

Json::Value save_setting_type(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
  printJson(in);
  auto setting_type_table = sqlb::ObjectIdentifier("product", "setting_type", "s");

  if (in["id"].asInt()) {
    std::string strSql =
            "update %1.%2 set "
            "(name, description)"
            " = ROW($2, $3) where id=$1";
    ReplaceAll2(strSql, "%1", setting_type_table.schema());
    ReplaceAll2(strSql, "%2", setting_type_table.name());

    pqxx::work txn{DD};
    try {
      txn.exec_params(strSql,
                      in["id"].asInt(),
              //in["slug"].asString(),
                      in["name"].asString(),
                      in["description"].asString()
      );
      txn.commit();
      return simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
      txn.abort();
      std::cerr << e.what() << std::endl;
      return simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }
  } else {
    std::string strSql = "INSERT INTO %1.%2 (name, description) values($1, $2)";
    ReplaceAll2(strSql, "%1", setting_type_table.schema());
    ReplaceAll2(strSql, "%2", setting_type_table.name());

    pqxx::work txn{DD};
    try {
      txn.exec_params(
              strSql,
              //in["slug"].asString(),
              in["name"].asString(),
              in["description"].asString()
      );
      txn.commit();
      return simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
      txn.abort();
      std::cerr << e.what() << std::endl;
      return simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }
  }
}

Json::Value save_certified_by(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
  auto setting_type_table = sqlb::ObjectIdentifier("product", "certified_by", "s");

  if (in["id"].asInt()) {
    std::string strSql =
            "update %1.%2 set "
            "(slug, name, title, description)"
            " = ROW($2, $3, $4, $5) where id=$1";
    ReplaceAll2(strSql, "%1", setting_type_table.schema());
    ReplaceAll2(strSql, "%2", setting_type_table.name());

    pqxx::work txn{DD};
    try {
      txn.exec_params(strSql,
                      in["id"].asInt(),
                      in["slug"].asString(),
                      in["name"].asString(),
                      in["title"].asString(),
                      in["description"].asString()
      );
      txn.commit();
      return simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
      txn.abort();
      std::cerr << e.what() << std::endl;
      return simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }
  } else {
    std::string strSql = "INSERT INTO %1.%2 (slug, name, title, description) values($1, $2, $3, $4)";
    ReplaceAll2(strSql, "%1", setting_type_table.schema());
    ReplaceAll2(strSql, "%2", setting_type_table.name());

    pqxx::work txn{DD};
    try {
      txn.exec_params(
              strSql,
              in["slug"].asString(),
              in["name"].asString(),
              in["title"].asString(),
              in["description"].asString()
      );
      txn.commit();
      return simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
      txn.abort();
      std::cerr << e.what() << std::endl;
      return simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }
  }
}

save_table(policy, "product.policy", "name, url, description", "$1, $2, $3", "$2, $3, $4", "where id=$1", in["name"].asString(), in["url"].asString(), in["description"].asString())
