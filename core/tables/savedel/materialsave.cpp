#include "materialsave.h"


delFn(metal, "material.metal");

//delFn(purity, "material.purity");
delFn(tone, "material.tone");

delFn(accessory, "material.accessory");

delFn(clarity, "material.clarity");

delFn(shape, "material.shape");

delFn(d_color, "material.diamond_color");

delFn(cs_color, "material.cs_color");
delFn(cs_type, "material.cs_type");
//delFn(diamond_size, "material.diamond_size_meta");
//delFn(color_stone_size, "material.color_stone_size_meta");

//-----------
Json::Value save_metal(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
  printJson(in);
  auto metal_table = sqlb::ObjectIdentifier("material", "metal", "m");

  if (in["id"].asInt()) {
    std::string strSql =
            "update %1.%2 set "
            "(slug, name, specific_density, price, melting_point_in_c)"
            " = ROW($2, $3, $4, $5, $6) where id=$1";
    ReplaceAll2(strSql, "%1", metal_table.schema());
    ReplaceAll2(strSql, "%2", metal_table.name());

    pqxx::work txn{DD};
    try {
      txn.exec_params(strSql,
                      in["id"].asInt(),
                      in["slug"].asString(),
                      in["name"].asString(),
                      in["specific_density"].asDouble(),
                      in["price"].asDouble(),
                      in["melting_point_in_c"].asDouble()
      );
      //1 purity_metal
      auto pr_update = R"(
update material.purity_metal pm
set (price) = row(pm.purity * m.price / 100)
from material.metal m
where
m.id = pm.metal_id and
pm.metal_id = $1
returning pm.purity_id;
)";
      auto pr = txn.exec_params(pr_update, in["id"].asInt());

      ids2(pr, id1);
      //2. purity
      auto pr_update01 = R"(
update material.purity p
set (price) = row(p.purity * m.price / 100)
from material.metal m
where
m.id = p.metal_id and
p.metal_id = $1
returning p.id;
)";
      auto pr0 = txn.exec_params(pr_update01, in["id"].asInt());
      ids2(pr, id2);
      //3. purity_tone
      auto pr_update2 = R"(
update material.purity_tone pt
set (price) = row(
            (select SUM(pm.price)
             FROM material.purity_metal pm
             WHERE pt.purity_id = pm.purity_id and pt.tone_id = pt.tone_id)
                +
            (select p.price
             FROM material.purity p
             WHERE pt.purity_id = p.id and pt.tone_id = pt.tone_id)
            )
where
pt.purity_id = ANY($1::bigint[]) or pt.purity_id = ANY($2::bigint[])
)";
      auto pr2 = txn.exec_params(pr_update2, id1, id2);

      auto pr_update3 = R"(
update product.product p
set (volume) = row(
             p.weight / (
                        (select SUM(purity.purity * m.specific_density / 100)
                         FROM material.purity purity left join material.metal m on m.id = purity.metal_id
                         WHERE purity.id = p.purity_id)
                                            +
                        (select SUM(pm.purity * m.specific_density / 100)
                         FROM material.purity_metal pm left join material.metal m on m.id = pm.metal_id
                         WHERE pm.purity_id = p.purity_id and pm.tone_id = p.tone_id)

                        )

             )
where
p.purity_id = ANY($1::bigint[]) or p.purity_id = ANY($2::bigint[]) returning p.post_id
)";
      auto product_update = txn.exec_params(pr_update3, id1, id2);
      ids2(product_update, id3);

      auto pr_update4 = R"(
UPDATE product.purity_tone pt
SET (weight, price) = row(pr.volume * (sub_q0.sum_val + sub_q.sum_val), pr.volume * (sub_q0.sum_val + sub_q.sum_val) * (mpt.price))
FROM
    (
        select purity.id, (purity.purity * m.specific_density / 100) as sum_val
             FROM material.purity purity left join material.metal m on m.id = purity.metal_id
    ) AS sub_q0,
    (
        select pm.purity_id, pm.tone_id, SUM(pm.purity * m.specific_density / 100) as sum_val
             FROM material.purity_metal pm left join material.metal m on m.id = pm.metal_id
            group by pm.purity_id, pm.tone_id
    ) AS sub_q, product.product pr, material.purity_tone mpt
where
sub_q0.id = pt.purity_id
and sub_q.purity_id = pt.purity_id and sub_q.tone_id = pt.tone_id
and pr.post_id = pt.post_id -- to get volume from pr
and mpt.purity_id = pt.purity_id and mpt.tone_id = pt.tone_id -- to get price from mpt
and (pt.purity_id = ANY($1::bigint[]) or pt.purity_id = ANY($2::bigint[]) or pt.post_id = ANY($3::bigint[]) )
--returning pt.post_id, pt.purity_id, pt.weight, pt.price
)";


      auto pr4 = txn.exec_params(pr_update4, id1, id2, id3);

      txn.commit();
      return simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
      txn.abort();
      std::cerr << e.what() << std::endl;
      return simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }
  } else {
    std::string strSql = "INSERT INTO %1.%2 (slug, name, specific_density, price, melting_point_in_c) values($1, $2, $3, $4, $5)";
    ReplaceAll2(strSql, "%1", metal_table.schema());
    ReplaceAll2(strSql, "%2", metal_table.name());

    pqxx::work txn{DD};
    try {
      txn.exec_params(
              strSql,
              in["slug"].asString(),
              in["name"].asString(),
              in["specific_density"].asDouble(),
              in["price"].asDouble(),
              in["melting_point_in_c"].asDouble()
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
void save_purity_metal_(Json::Value &in, pqxx::work &txn, int purity_id, int tone_id) {
    std::string strSqlPostCategories = "SELECT metal_id FROM material.purity_metal where purity_id = $1 and tone_id = $2";
    std::string strSqlPostCategorySimpleFind = "SELECT purity_id, tone_id, metal_id, purity, price FROM material.purity_metal WHERE purity_id = $1 and tone_id = $2 and metal_id = $3";
    std::string strSqlPostCategoryDel = "DELETE FROM material.purity_metal WHERE purity_id = $1 and tone_id = $2 and metal_id = $3";
    std::string strSqlPostCategoryInsert = "INSERT INTO material.purity_metal (purity_id, tone_id, metal_id, purity, price) VALUES ($1, $2, $3, $4, $5);";
    std::string strSqlPostCategoryUpdateAtt = "UPDATE material.purity_metal SET (purity, price) = ROW($4, $5) WHERE purity_id = $1 and tone_id = $2 and metal_id = $3";

    struct PriceMetal {
        int metal_id;
        double purity;
        double price;
    };
    std::vector<PriceMetal> inVector;
    for (auto i : in) {
        if (!i[0].isNull()) inVector.push_back({i[0].asInt(), i[1].asDouble(), i[2].asDouble()});
    }

    pqxx::result all_ct = txn.exec_params(strSqlPostCategories, purity_id, tone_id);
    // For each saved tones, If saved tone not exist in new tones, delete it.
    for (auto r : all_ct) {
        std::vector<PriceMetal>::iterator it = std::find_if(inVector.begin(), inVector.end(), [&](PriceMetal t) {
            return t.metal_id == r[0].as<int>();
        });
        if (it == inVector.end()) {// Element not Found
            txn.exec_params(strSqlPostCategoryDel, purity_id, tone_id, r[0].as<int>());
        }
    }
    // For each new tones, insert it if it not already exist.
    for (auto r : inVector) {
        pqxx::result y = txn.exec_params(strSqlPostCategorySimpleFind, purity_id, tone_id, r.metal_id);
        if (y.size() == 0) {
            txn.exec_params(strSqlPostCategoryInsert, purity_id, tone_id, r.metal_id, r.purity, r.price);
        } else { // update
            if (y[0][2].as<int>() != r.metal_id || y[0][3].as<double>() != r.purity || y[0][4].as<double>() != r.price) {
                txn.exec_params(strSqlPostCategoryUpdateAtt, purity_id, tone_id, r.metal_id, r.purity, r.price);
            }
        }
    }
}
void save_purity_tone_(Json::Value &in, pqxx::work &txn, int purity_id) {
  std::string strSqlPostCategories = "SELECT tone_id FROM material.purity_tone where purity_id = $1";
  std::string strSqlPostCategorySimpleFind = "SELECT purity_id, tone_id, price FROM material.purity_tone WHERE purity_id = $1 and tone_id = $2";
  std::string strSqlPostCategoryDel = "DELETE FROM material.purity_tone WHERE purity_id = $1 and tone_id = $2";
  std::string strSqlPostCategoryInsert = "INSERT INTO material.purity_tone (purity_id, tone_id, price) VALUES ($1, $2, $3) returning purity_id, tone_id;";
  std::string strSqlPostCategoryUpdateAtt = "UPDATE material.purity_tone SET (price) = ROW($3) WHERE purity_id = $1 and tone_id = $2";

  struct PurityTone {
      int tone_id;
      double price;
      Json::Value j;
  };
  std::vector<PurityTone> inVector;
  for (auto i : in["pt_purity_tone"]) {
    if (!i[0].isNull()) inVector.push_back({i[0].asInt(), i[2].asDouble(), i[1]});
  }

  pqxx::result all_ct = txn.exec_params(strSqlPostCategories, purity_id);
  // For each saved tones, If saved tone not exist in new tones, delete it.
  for (auto r : all_ct) {
    std::vector<PurityTone>::iterator it = std::find_if(inVector.begin(), inVector.end(), [&](PurityTone t) {
        return t.tone_id == r[0].as<int>();
    });
    if (it == inVector.end()) {// Element not Found
        // because when tone_id change it actually inserting new entries..
        txn.exec_params(dele("material.purity_metal", "where purity_id = $1 and tone_id = $2"), purity_id, r[0].as<int>());
        txn.exec_params(strSqlPostCategoryDel, purity_id, r[0].as<int>());
    }
  }
  // For each new tones, insert it if it not already exist.
  for (auto r : inVector) {
    pqxx::result y = txn.exec_params(strSqlPostCategorySimpleFind, purity_id, r.tone_id);
    if (y.size() == 0) {
      auto z = txn.exec_params(strSqlPostCategoryInsert, purity_id, r.tone_id, r.price);
      save_purity_metal_(r.j, txn, z[0][0].as<int>(), z[0][1].as<int>());
    } else { // update
      if (y[0][1].as<int>() != r.tone_id || y[0][2].as<double>() != r.price) {
        txn.exec_params(strSqlPostCategoryUpdateAtt, purity_id, r.tone_id, r.price);
      }
      save_purity_metal_(r.j, txn, purity_id, r.tone_id);
    }
  }
}

Json::Value save_purity(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
  printJson(in);
  auto metal_purity_table = sqlb::ObjectIdentifier("material", "purity", "p");
  auto purity_metal_table = sqlb::ObjectIdentifier("material", "purity_metal", "mp");


  if (in["id"].asInt()) {
    std::string strSql =
            "update %1.%2 set (slug, name, metal_id, purity, price, description) = ROW($2, $3, $4, $5, $6, $7) where id=$1";
    ReplaceAll2(strSql, "%1", metal_purity_table.schema());
    ReplaceAll2(strSql, "%2", metal_purity_table.name());

    pqxx::work txn{DD};
    try {
      txn.exec_params(strSql,
                      in["id"].asInt(),
                      in["slug"].asString(),
                      in["name"].asString(),
                        in["metal_id"].asInt(),
                        in["purity"].asDouble(),
                        in["price"].asDouble(),
                      in["description"].asString()
      );
      auto purity_id = in["id"].asInt();
      save_purity_tone_(in, txn, purity_id);

      auto pr_update3 = R"(
update product.product p
set (volume) = row(
             p.weight / (
                        (select SUM(purity.purity * m.specific_density / 100)
                         FROM material.purity purity left join material.metal m on m.id = purity.metal_id
                         WHERE purity.id = p.purity_id)
                                            +
                        (select SUM(pm.purity * m.specific_density / 100)
                         FROM material.purity_metal pm left join material.metal m on m.id = pm.metal_id
                         WHERE pm.purity_id = p.purity_id and pm.tone_id = p.tone_id)

                        )

             )
where
p.purity_id = $1 returning p.post_id
)";

      auto product_update = txn.exec_params(pr_update3, in["id"].asInt());
      ids2(product_update, ids);
      auto pr_update4 = R"(
UPDATE product.purity_tone pt
SET (weight, price) = row(pr.volume * (sub_q0.sum_val + sub_q.sum_val), pr.volume * (sub_q0.sum_val + sub_q.sum_val) * (mpt.price))
FROM
    (
        select purity.id, (purity.purity * m.specific_density / 100) as sum_val
             FROM material.purity purity left join material.metal m on m.id = purity.metal_id
    ) AS sub_q0,
    (
        select pm.purity_id, pm.tone_id, SUM(pm.purity * m.specific_density / 100) as sum_val
             FROM material.purity_metal pm left join material.metal m on m.id = pm.metal_id
            group by pm.purity_id, pm.tone_id
    ) AS sub_q, product.product pr, material.purity_tone mpt
where
sub_q0.id = pt.purity_id
and sub_q.purity_id = pt.purity_id and sub_q.tone_id = pt.tone_id
and pr.post_id = pt.post_id -- to get volume from pr
and mpt.purity_id = pt.purity_id and mpt.tone_id = pt.tone_id -- to get price from mpt
and (pt.purity_id = $1 or pt.post_id = ANY($2::bigint[]) )
--returning pt.post_id, pt.purity_id, pt.weight, pt.price
)";

      auto pr = txn.exec_params(pr_update4, purity_id, ids);

      txn.commit();
      return simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
      txn.abort();
      std::cerr << e.what() << std::endl;
      return simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }
  } else {
    std::string strSql = "INSERT INTO %1.%2 (slug, name, metal_id, purity, price, description) values($1, $2, $3, $4, $5, $6) returning id";
    ReplaceAll2(strSql, "%1", metal_purity_table.schema());
    ReplaceAll2(strSql, "%2", metal_purity_table.name());

    pqxx::work txn{DD};
    try {
      pqxx::result x = txn.exec_params(
              strSql,
              in["slug"].asString(),
              in["name"].asString(),
            in["metal_id"].asInt(),
            in["purity"].asDouble(),
            in["price"].asDouble(),
              in["description"].asString()
      );
      auto purity_id = x[0]["id"].as<int>();
      save_purity_tone_(in, txn, purity_id);
      txn.commit();
      return simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
      txn.abort();
      std::cerr << e.what() << std::endl;
      return simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }
  }
}

Json::Value delete_purity(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
  pqxx::work txn{DD};
  try {
        txn.exec_params("DELETE FROM " "material.purity_metal" " WHERE purity_id = $1", in[0].asInt());
        txn.exec_params("DELETE FROM " "material.purity_tone" " WHERE purity_id = $1", in[0].asInt());
        txn.exec_params("DELETE FROM " "material.purity" " WHERE id = $1", in[0].asInt());
        txn.commit();
        return simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
  } catch (const std::exception &e) {
    txn.abort();
    std::cerr << e.what() << std::endl;
    return simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
  }
}

Json::Value save_tone(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
  printJson(in);
  auto product_table = sqlb::ObjectIdentifier("material", "tone", "t");

  if (in["id"].asInt()) {
    std::string strSql =
            "update %1.%2 set "
            "(slug, name)"
            " = ROW($2, $3) where id=$1";
    ReplaceAll2(strSql, "%1", product_table.schema());
    ReplaceAll2(strSql, "%2", product_table.name());

    pqxx::work txn{DD};
    try {
      txn.exec_params(strSql,
                      in["id"].asInt(),
                      in["slug"].asString(),
                      in["name"].asString()
      );
      txn.commit();
      return simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
      txn.abort();
      std::cerr << e.what() << std::endl;
      return simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }
  } else {
    std::string strSql = "INSERT INTO %1.%2 (slug, name) values($1, $2)";
    ReplaceAll2(strSql, "%1", product_table.schema());
    ReplaceAll2(strSql, "%2", product_table.name());

    pqxx::work txn{DD};
    try {
      txn.exec_params(
              strSql,
              in["slug"].asString(),
              in["name"].asString()
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

Json::Value save_accessory(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
  printJson(in);
  auto accessory_table = sqlb::ObjectIdentifier("material", "accessory", "t");

  if (in["id"].asInt()) {
    std::string strSql =
            "update %1.%2 set "
            "(slug, name)"
            " = ROW($2, $3) where id=$1";
    ReplaceAll2(strSql, "%1", accessory_table.schema());
    ReplaceAll2(strSql, "%2", accessory_table.name());

    pqxx::work txn{DD};
    try {
      txn.exec_params(strSql,
                      in["id"].asInt(),
                      in["slug"].asString(),
                      in["name"].asString()
      );
      txn.commit();
      return simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
      txn.abort();
      std::cerr << e.what() << std::endl;
      return simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }
  } else {
    std::string strSql = "INSERT INTO %1.%2 (slug, name) values($1, $2)";
    ReplaceAll2(strSql, "%1", accessory_table.schema());
    ReplaceAll2(strSql, "%2", accessory_table.name());

    pqxx::work txn{DD};
    try {
      txn.exec_params(
              strSql,
              in["slug"].asString(),
              in["name"].asString()
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
save_table(cs_type, "material.cs_type", "name", "$1", "$2", "where id=$1", in["name"].asString())

Json::Value save_clarity(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
  printJson(in);
  auto accessory_table = sqlb::ObjectIdentifier("material", "clarity", "cl");

  if (in["id"].asInt()) {
    std::string strSql =
            "update %1.%2 set "
            "(slug, name)"
            " = ROW($2, $3) where id=$1";
    ReplaceAll2(strSql, "%1", accessory_table.schema());
    ReplaceAll2(strSql, "%2", accessory_table.name());

    pqxx::work txn{DD};
    try {
      txn.exec_params(strSql,
                      in["id"].asInt(),
                      in["slug"].asString(),
                      in["name"].asString()
      );
      txn.commit();
      return simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
      txn.abort();
      std::cerr << e.what() << std::endl;
      return simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }
  } else {
    std::string strSql = "INSERT INTO %1.%2 (slug, name) values($1, $2)";
    ReplaceAll2(strSql, "%1", accessory_table.schema());
    ReplaceAll2(strSql, "%2", accessory_table.name());

    pqxx::work txn{DD};
    try {
      txn.exec_params(
              strSql,
              in["slug"].asString(),
              in["name"].asString()
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

Json::Value save_shape(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
  printJson(in);
  auto accessory_table = sqlb::ObjectIdentifier("material", "shape", "sh");

  if (in["id"].asInt()) {
    std::string strSql =
            "update %1.%2 set "
            "(slug, name)"
            " = ROW($2, $3) where id=$1";
    ReplaceAll2(strSql, "%1", accessory_table.schema());
    ReplaceAll2(strSql, "%2", accessory_table.name());

    pqxx::work txn{DD};
    try {
      txn.exec_params(strSql,
                      in["id"].asInt(),
                      in["slug"].asString(),
                      in["name"].asString()
      );
      txn.commit();
      return simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
      txn.abort();
      std::cerr << e.what() << std::endl;
      return simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }
  } else {
    std::string strSql = "INSERT INTO %1.%2 (slug, name) values($1, $2)";
    ReplaceAll2(strSql, "%1", accessory_table.schema());
    ReplaceAll2(strSql, "%2", accessory_table.name());

    pqxx::work txn{DD};
    try {
      txn.exec_params(
              strSql,
              in["slug"].asString(),
              in["name"].asString()
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

Json::Value save_d_color(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
  printJson(in);
  auto accessory_table = sqlb::ObjectIdentifier("material", "diamond_color", "c");

  if (in["id"].asInt()) {
    std::string strSql =
            "update %1.%2 set "
            "(slug, name)"
            " = ROW($2, $3) where id=$1";
    ReplaceAll2(strSql, "%1", accessory_table.schema());
    ReplaceAll2(strSql, "%2", accessory_table.name());

    pqxx::work txn{DD};
    try {
      txn.exec_params(strSql,
                      in["id"].asInt(),
                      in["slug"].asString(),
                      in["name"].asString()
      );
      txn.commit();
      return simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
      txn.abort();
      std::cerr << e.what() << std::endl;
      return simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }
  } else {
    std::string strSql = "INSERT INTO %1.%2 (slug, name) values($1, $2)";
    ReplaceAll2(strSql, "%1", accessory_table.schema());
    ReplaceAll2(strSql, "%2", accessory_table.name());

    pqxx::work txn{DD};
    try {
      txn.exec_params(
              strSql,
              in["slug"].asString(),
              in["name"].asString()
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

Json::Value save_cs_color(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
  printJson(in);
  auto accessory_table = sqlb::ObjectIdentifier("material", "cs_color", "c");

  if (in["id"].asInt()) {
    std::string strSql =
            "update %1.%2 set "
            "(slug, name)"
            " = ROW($2, $3) where id=$1";
    ReplaceAll2(strSql, "%1", accessory_table.schema());
    ReplaceAll2(strSql, "%2", accessory_table.name());

    pqxx::work txn{DD};
    try {
      txn.exec_params(strSql,
                      in["id"].asInt(),
                      in["slug"].asString(),
                      in["name"].asString()
      );
      txn.commit();
      return simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
      txn.abort();
      std::cerr << e.what() << std::endl;
      return simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }
  } else {
    std::string strSql = "INSERT INTO %1.%2 (slug, name) values($1, $2)";
    ReplaceAll2(strSql, "%1", accessory_table.schema());
    ReplaceAll2(strSql, "%2", accessory_table.name());

    pqxx::work txn{DD};
    try {
      txn.exec_params(
              strSql,
              in["slug"].asString(),
              in["name"].asString()
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

Json::Value save_diamond_size(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
  // also update all the price of products too..
  // also update deleted size price too.



  auto size_table = sqlb::ObjectIdentifier("material", "size", "sh");
  auto size_meta_table = sqlb::ObjectIdentifier("material", "diamond_size_meta", "sm");

  // first insert size then insert on meta ...................
  auto size_name = in["size_name"].asString();
  std::string strSqlSizeSel = "SELECT id, name FROM material.size WHERE name = $1";
  std::string strSqlSizeIns = "INSERT INTO material.size (name) VALUES ($1) RETURNING id";

  std::string strSqlSizeGet = "select dp.diamond_id, dp.clarity_id, ds.pcs, ds.post_id from product.diamond_price dp left join product.post_diamond_size ds on ds.id = dp.diamond_id where ds.shape_id = $1 and ds.color_id = $2 and ds.size_id = $3 and dp.clarity_id = $4;";
  std::string strSqlPriceUpdate = "UPDATE product.diamond_price SET (weight, total_weight, rate, price) = ROW($3, $4, $5, $6) WHERE diamond_id = $1 AND clarity_id = $2";

  auto q = "SELECT  sum(dp.total_weight), sum(dp.price) from product.post_diamond_size ds LEFT JOIN product.diamond_price dp ON (dp.diamond_id = ds.id) where ds.post_id = $1 and dp.clarity_id = $2";
  auto pc = upd("product.post_clarity", "weight, price", "$3, $4", "where post_id = $1 and clarity_id = $2");

  if (in["id"].asInt()) {
    std::string strSql =
            "update %1.%2 set "
            "(clarity_id, shape_id, color_id, size_id, weight, currency_id, rate_on_id, rate)"
            " = ROW($2, $3, $4, $5, $6, $7, $8, $9) where id=$1";
    ReplaceAll2(strSql, "%1", size_meta_table.schema());
    ReplaceAll2(strSql, "%2", size_meta_table.name());

    std::string strSqlSizeId = "SELECT size_id FROM material.diamond_size_meta WHERE id = $1;";
    std::string strSqlSizeCount = "SELECT count(*) FROM material.diamond_size_meta dm WHERE dm.size_id = $1";
    std::string strSqlColorSizeCount = "SELECT count(*) FROM material.color_stone_size_meta cm WHERE cm.size_id = $1";
    std::string strSqlSizeDel = "DELETE FROM material.size WHERE id = $1";


    pqxx::work txn{DD};
    try {
      int size_id;
      auto r = txn.exec_params(strSqlSizeSel, size_name);
      if (r.size() == 0) { // insert
        auto r1 = txn.exec_params(strSqlSizeIns, size_name);
        size_id = r1[0][0].as<int>();
      } else {
        size_id = r[0][0].as<int>();
      }

      auto old_row = txn.exec_params(strSqlSizeId, in["id"].asInt());
      int old_size_id = old_row[0][0].as<int>();

      txn.exec_params(strSql,
                      in["id"].asInt(),
                      in["clarity_id"].asInt(),
                      in["shape_id"].asInt(),
                      in["color_id"].asInt(),
                      size_id,
                      in["weight"].asDouble(),
                      in["currency_id"].asInt(),
                      in["rate_on_id"].asString(),
                      in["rate"].asDouble()
      );
      // If old size count = 0, delete size:
      auto r3 = txn.exec_params(strSqlSizeCount, old_size_id);
      auto r4 = txn.exec_params(strSqlColorSizeCount, old_size_id);
      if (r3[0][0].as<int>() == 0 && r4[0][0].as<int>() == 0) {
        txn.exec_params(strSqlSizeDel, in["shape_id"].asInt(), in["color_id"].asInt(), size_id,
                        in["clarity_id"].asInt());
      }

      // update product weight and price:..
      struct ProductUpdate {
          int postId;
          std::vector<int> clarityId;
      };
      std::vector<ProductUpdate> productUpdate;

      auto s = txn.exec_params(strSqlSizeGet, in["shape_id"].asInt(), in["color_id"].asInt(), size_id,
                               in["clarity_id"].asInt());
      for (auto prow : s) {
        auto w = in["weight"].asDouble();
        auto rate = in["rate"].asDouble();
        auto pcs = prow[2].as<int>();
        txn.exec_params(strSqlPriceUpdate, prow[0].as<int>(), prow[1].as<int>(), w, w * pcs, rate,
                        pcs * w * rate);
        std::vector<ProductUpdate>::iterator it = std::find_if(productUpdate.begin(), productUpdate.end(),
                                                               [&](ProductUpdate t) {
                                                                   return t.postId == prow[3].as<int>();
                                                               });
        if (it == productUpdate.end()) {// Element not Found
          productUpdate.push_back({prow[3].as<int>(), {prow[1].as<int>()}});
        } else {
          it->clarityId.push_back(prow[1].as<int>());
        }
      }

      for (auto p : productUpdate) {
        for (auto c : p.clarityId) {
          auto rsum = txn.exec_params(q, p.postId, c);
          txn.exec_params(pc, p.postId, c, rsum[0][0].as<double>(), rsum[0][1].as<double>());
        }
      }

      txn.commit();
      return simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
      txn.abort();
      std::cerr << e.what() << std::endl;
      return simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }
  } else {
    std::string strSql = "INSERT INTO %1.%2 (clarity_id, shape_id, color_id, size_id, weight, currency_id, rate_on_id, rate) values($1, $2, $3, $4, $5, $6, $7, $8)";
    ReplaceAll2(strSql, "%1", size_meta_table.schema());
    ReplaceAll2(strSql, "%2", size_meta_table.name());


    pqxx::work txn{DD};
    try {
      int size_id;
      auto r = txn.exec_params(strSqlSizeSel, size_name);
      if (r.size() == 0) { // insert
        auto r1 = txn.exec_params(strSqlSizeIns, size_name);
        size_id = r1[0][0].as<int>();
      } else {
        size_id = r[0][0].as<int>();
      }


      txn.exec_params(
              strSql,
              in["clarity_id"].asInt(),
              in["shape_id"].asInt(),
              in["color_id"].asInt(),
              size_id,
              in["weight"].asDouble(),
              in["currency_id"].asInt(),
              in["rate_on_id"].asString(),
              in["rate"].asDouble()
      );

      // copy
      // update product weight and price:..
      struct ProductUpdate {
          int postId;
          std::vector<int> clarityId;
      };
      std::vector<ProductUpdate> productUpdate;

      auto s = txn.exec_params(strSqlSizeGet, in["shape_id"].asInt(), in["color_id"].asInt(), size_id,
                               in["clarity_id"].asInt());
      for (auto prow : s) {
        auto w = in["weight"].asDouble();
        auto rate = in["rate"].asDouble();
        auto pcs = prow[2].as<int>();
        txn.exec_params(strSqlPriceUpdate, prow[0].as<int>(), prow[1].as<int>(), w, w * pcs, rate,
                        pcs * w * rate);
        // Get all post_ids:
        std::vector<ProductUpdate>::iterator it = std::find_if(productUpdate.begin(), productUpdate.end(),
                                                               [&](ProductUpdate t) {
                                                                   return t.postId == prow[3].as<int>();
                                                               });
        if (it == productUpdate.end()) {// Element not Found
          productUpdate.push_back({prow[3].as<int>(), {prow[1].as<int>()}});
        } else {
          it->clarityId.push_back(prow[1].as<int>());
        }
      }

      for (auto p : productUpdate) {
        for (auto c : p.clarityId) {
          auto rsum = txn.exec_params(q, p.postId, c);
          txn.exec_params(pc, p.postId, c, rsum[0][0].as<double>(), rsum[0][1].as<double>());
        }
      }

      txn.commit();
      return simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
      txn.abort();
      std::cerr << e.what() << std::endl;
      return simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }
  }
}

Json::Value delete_diamond_size(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
  pqxx::work txn{DD};
  try {
    auto get_row = "SELECT id, size_id FROM material.diamond_size_meta where id = $1";
    auto r = txn.exec_params(get_row, in[0].asInt());

    txn.exec_params("DELETE FROM " "material.diamond_size_meta" " WHERE id = $1", in[0].asInt());

    auto d_size_count = "SELECT count(*) FROM material.diamond_size_meta where size_id = $1";
    auto cs_size_count = "SELECT count(*) FROM material.color_stone_size_meta where size_id = $1";

    auto size_id = r[0][1].as<int>();
    auto c1 = txn.exec_params(d_size_count, size_id);
    auto c2 = txn.exec_params(cs_size_count, size_id);
    if (c1[0][0].as<int>() == 0 && c2[0][0].as<int>() == 0) {
      txn.exec_params("DELETE FROM " "material.size" " WHERE id = $1", size_id);
    }
    txn.commit();
    return simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
  } catch (const std::exception &e) {
    txn.abort();
    std::cerr << e.what() << std::endl;
    return simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
  }
}

Json::Value save_color_stone_size(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
  auto size_table = sqlb::ObjectIdentifier("material", "size", "sh");
  auto size_meta_table = sqlb::ObjectIdentifier("material", "color_stone_size_meta", "sm");

  // first insert size then insert on meta ...................
  auto size_name = in["size_name"].asString();
  std::string strSqlSizeSel = "SELECT id, name FROM material.size WHERE name = $1";
  std::string strSqlSizeIns = "INSERT INTO material.size (name) VALUES ($1) RETURNING id";

  std::string strSqlSizeGet = "select cp.cs_id, ds.pcs, ds.post_id from product.cs_price cp left join product.post_color_stone_size ds on ds.id = cp.cs_id where ds.cs_type_id = $1 and ds.shape_id = $2 and ds.size_id = $3;";
  std::string strSqlPriceUpdate = "UPDATE product.cs_price SET (weight, total_weight, rate, price) = ROW($2, $3, $4, $5) WHERE cs_id = $1";

  auto q = "SELECT  sum(cp.total_weight), sum(cp.price) from product.post_color_stone_size ds LEFT JOIN product.cs_price cp ON (cp.cs_id = ds.id) where ds.post_id = $1";
  auto pc = upd("product.post_cs_total", "weight, price", "$2, $3", "where post_id = $1");


  if (in["id"].asInt()) {
    std::string strSql =
            "update %1.%2 set "
            "(cs_type_id, shape_id, size_id, weight, currency_id, rate_on_id, rate)"
            " = ROW($2, $3, $4, $5, $6, $7, $8) where id=$1";
    ReplaceAll2(strSql, "%1", size_meta_table.schema());
    ReplaceAll2(strSql, "%2", size_meta_table.name());

    std::string strSqlSizeId = "SELECT size_id FROM material.color_stone_size_meta WHERE id = $1;";
    std::string strSqlSizeCount = "SELECT count(*) FROM material.diamond_size_meta dm WHERE dm.size_id = $1";
    std::string strSqlColorSizeCount = "SELECT count(*) FROM material.color_stone_size_meta cm WHERE cm.size_id = $1";
    std::string strSqlSizeDel = "DELETE FROM material.size WHERE id = $1";

    pqxx::work txn{DD};
    try {
      int size_id;
      auto r = txn.exec_params(strSqlSizeSel, size_name);
      if (r.size() == 0) { // insert
        auto r1 = txn.exec_params(strSqlSizeIns, size_name);
        size_id = r1[0][0].as<int>();
      } else {
        size_id = r[0][0].as<int>();
      }

      auto old_row = txn.exec_params(strSqlSizeId, in["id"].asInt());
      int old_size_id = old_row[0][0].as<int>();

      txn.exec_params(strSql,
                      in["id"].asInt(),
                      in["cs_type_id"].asInt(),
                      in["shape_id"].asInt(),
                      size_id,
                      in["weight"].asDouble(),
                      in["currency_id"].asInt(),
                      in["rate_on_id"].asString(),
                      in["rate"].asDouble()
      );
      // If old size count = 0, delete size:
      auto r3 = txn.exec_params(strSqlSizeCount, old_size_id);
      auto r4 = txn.exec_params(strSqlColorSizeCount, old_size_id);
      if (r3[0][0].as<int>() == 0 && r4[0][0].as<int>() == 0) {
        txn.exec_params(strSqlSizeDel, old_size_id);
      }

      // update product weight and price:..
      struct ProductUpdate {
          int postId;
      };
      std::vector<ProductUpdate> productUpdate;

      auto s = txn.exec_params(strSqlSizeGet, in["cs_type_id"].asInt(), in["shape_id"].asInt(), size_id);
      for (auto prow : s) {
        auto w = in["weight"].asDouble();
        auto rate = in["rate"].asDouble();
        auto pcs = prow[1].as<int>();
        txn.exec_params(strSqlPriceUpdate, prow[0].as<int>(), w, w * pcs, rate, pcs * w * rate);
        // Get all post_ids:
        std::vector<ProductUpdate>::iterator it = std::find_if(productUpdate.begin(), productUpdate.end(),
                                                               [&](ProductUpdate t) {
                                                                   return t.postId == prow[2].as<int>();
                                                               });
        if (it == productUpdate.end()) {// Element not Found
          productUpdate.push_back({prow[2].as<int>()});
        } else {

        }
      }

      for (auto p : productUpdate) {
        auto rsum = txn.exec_params(q, p.postId);
        txn.exec_params(pc, p.postId, rsum[0][0].as<double>(), rsum[0][1].as<double>());
      }

      txn.commit();
      return simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
      txn.abort();
      std::cerr << e.what() << std::endl;
      return simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }
  } else {
    std::string strSql = "INSERT INTO %1.%2 (cs_type_id, shape_id, size_id, weight, currency_id, rate_on_id, rate) values($1, $2, $3, $4, $5, $6, $7)";
    ReplaceAll2(strSql, "%1", size_meta_table.schema());
    ReplaceAll2(strSql, "%2", size_meta_table.name());


    pqxx::work txn{DD};
    try {
      int size_id;
      auto r = txn.exec_params(strSqlSizeSel, size_name);
      if (r.size() == 0) { // insert
        auto r1 = txn.exec_params(strSqlSizeIns, size_name);
        size_id = r1[0][0].as<int>();
      } else {
        size_id = r[0][0].as<int>();
      }


      txn.exec_params(
              strSql,
              in["cs_type_id"].asInt(),
              in["shape_id"].asInt(),
              size_id,
              in["weight"].asDouble(),
              in["currency_id"].asInt(),
              in["rate_on_id"].asString(),
              in["rate"].asDouble()
      );


      //copy
      // update product weight and price:..
      struct ProductUpdate {
          int postId;
      };
      std::vector<ProductUpdate> productUpdate;

      auto s = txn.exec_params(strSqlSizeGet, in["cs_type_id"].asInt(), in["shape_id"].asInt(), size_id);
      for (auto prow : s) {
        auto w = in["weight"].asDouble();
        auto rate = in["rate"].asDouble();
        auto pcs = prow[1].as<int>();
        txn.exec_params(strSqlPriceUpdate, prow[0].as<int>(), w, w * pcs, rate, pcs * w * rate);
        std::vector<ProductUpdate>::iterator it = std::find_if(productUpdate.begin(), productUpdate.end(),
                                                               [&](ProductUpdate t) {
                                                                   return t.postId == prow[2].as<int>();
                                                               });
        if (it == productUpdate.end()) {// Element not Found
          productUpdate.push_back({prow[2].as<int>()});
        } else {

        }
      }

      for (auto p : productUpdate) {
        auto rsum = txn.exec_params(q, p.postId);
        txn.exec_params(pc, p.postId, rsum[0][0].as<double>(), rsum[0][1].as<double>());
      }

      txn.commit();
      return simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
      txn.abort();
      std::cerr << e.what() << std::endl;
      return simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }
  }
}

Json::Value delete_color_stone_size(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
  pqxx::work txn{DD};
  try {
    auto get_row = "SELECT id, size_id FROM material.color_stone_size_meta where id = $1";
    auto r = txn.exec_params(get_row, in[0].asInt());

    txn.exec_params("DELETE FROM " "material.color_stone_size_meta" " WHERE id = $1", in[0].asInt());

    auto d_size_count = "SELECT count(*) FROM material.diamond_size_meta where size_id = $1";
    auto cs_size_count = "SELECT count(*) FROM material.color_stone_size_meta where size_id = $1";

    auto size_id = r[0][1].as<int>();
    auto c1 = txn.exec_params(d_size_count, size_id);
    auto c2 = txn.exec_params(cs_size_count, size_id);
    if (c1[0][0].as<int>() == 0 && c2[0][0].as<int>() == 0) {
      txn.exec_params("DELETE FROM " "material.size" " WHERE id = $1", size_id);
    }
    txn.commit();
    return simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
  } catch (const std::exception &e) {
    txn.abort();
    std::cerr << e.what() << std::endl;
    return simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
  }
}
