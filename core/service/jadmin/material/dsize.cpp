#include "dsize.h"

#include <utility>
#include "../../../strfns.h"
#include "../../dba.h"
using namespace jadmin;

DSize::DSize(JAdminContextPtr context_) : context(std::move(context_)) {
  getTable().query() = sqlb::Query(
      sqlb::ObjectIdentifier("material", "diamond_size_meta", "sm"));
}

void DSize::setupTable() {
  // m_query.setRowIdColumn("id");
  getTable().query().selectedColumns() = {
      sqlb::SelectedColumn({"Id", "id", "", "sm", PG_TYPES::INT8, false}),
      sqlb::SelectedColumn(
          {"Clarity", "clarity_id", "", "sm", PG_TYPES::INT8, true, 2, 2}),
      sqlb::SelectedColumn({"clarity_slug", "slug", "", "clarity",
                            PG_TYPES::TEXT, false, 0, 0, false}),
      sqlb::SelectedColumn({"clarity_name", "name", "", "clarity",
                            PG_TYPES::TEXT, false, 0, 0, false}),
      sqlb::SelectedColumn(
          {"Shape", "shape_id", "", "sm", PG_TYPES::INT8, true, 2, 2}),
      sqlb::SelectedColumn({"shape_slug", "slug", "", "shape", PG_TYPES::TEXT,
                            false, 0, 0, false}),
      sqlb::SelectedColumn({"shape_name", "name", "", "shape", PG_TYPES::TEXT,
                            false, 0, 0, false}),
      sqlb::SelectedColumn(
          {"Color", "color_id", "", "sm", PG_TYPES::INT8, true, 2, 2}),
      sqlb::SelectedColumn({"color_slug", "slug", "", "color", PG_TYPES::TEXT,
                            false, 0, 0, false}),
      sqlb::SelectedColumn({"color_name", "name", "", "color", PG_TYPES::TEXT,
                            false, 0, 0, false}),
      // sqlb::SelectedColumn({"Rank", "rank", "", "sm", PG_TYPES::INT4,
      // false}), sqlb::SelectedColumn({"Code", "slug", "", "sm",
      // PG_TYPES::TEXT, true}),
      sqlb::SelectedColumn(
          {"Size", "size_id", "", "sm", PG_TYPES::INT8, true, 1, 1}),
      sqlb::SelectedColumn({"Name", "name", "", "size", PG_TYPES::TEXT, false}),
      sqlb::SelectedColumn(
          {"Weight", "weight", "", "sm", PG_TYPES::DOUBLE, true}),
      sqlb::SelectedColumn(
          {"Currency", "currency_id", "", "sm", PG_TYPES::INT8, true, 1, 2}),
      sqlb::SelectedColumn({"currency_slug", "slug", "", "currency",
                            PG_TYPES::TEXT, false, 0, 0, false}),
      sqlb::SelectedColumn({"currency_name", "name", "", "currency",
                            PG_TYPES::TEXT, false, 0, 0, false}),
      sqlb::SelectedColumn(
          {"Rate_On", "rate_on_id", "", "sm", PG_TYPES::ENUM, true}),
      sqlb::SelectedColumn({"Rate", "rate", "", "sm", PG_TYPES::DOUBLE, true}),
      sqlb::SelectedColumn({"Created By", "create_user_id", "", "sm",
                            PG_TYPES::INT8, true, 1, 0, false}),
      sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT,
                            false, 0, 0, false}),
      sqlb::SelectedColumn({"Updated By", "update_user_id", "", "sm",
                            PG_TYPES::INT8, true, 1, 0, false}),
      sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT,
                            false, 0, 0, false}),
      sqlb::SelectedColumn({"Create Time", "inserted_at", "", "sm",
                            PG_TYPES::TIMESTAMP, true, 0, 0, false}),
      sqlb::SelectedColumn({"Update Time", "updated_at", "", "sm",
                            PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  };

  auto size = sqlb::ObjectIdentifier("material", "size", "size");
  auto clarity = sqlb::ObjectIdentifier("material", "clarity", "clarity");
  auto shape = sqlb::ObjectIdentifier("material", "shape", "shape");
  auto color = sqlb::ObjectIdentifier("material", "diamond_color", "color");
  auto currency = sqlb::ObjectIdentifier("setting", "currency", "currency");
  auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
  auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

  getTable().query().joins() = {
      sqlb::Join("left", size, "size.id = sm.size_id"),
      sqlb::Join("left", clarity, "clarity.id = sm.clarity_id"),
      sqlb::Join("left", shape, "shape.id = sm.shape_id"),
      sqlb::Join("left", color, "color.id = sm.color_id"),
      sqlb::Join("left", currency, "currency.id = sm.currency_id"),
      sqlb::Join("left", u1, "sm.create_user_id = u1.id"),
      sqlb::Join("left", u2, "sm.update_user_id = u2.id"),
  };
}

json DSize::ins(json event, json args) {
  // also update all the price of products too..
  // also update deleted size price too.

  auto size_table = sqlb::ObjectIdentifier("material", "size", "sh");
  auto size_meta_table =
      sqlb::ObjectIdentifier("material", "diamond_size_meta", "sm");

  // first insert size then insert on meta ...................
  auto size_name = args[0]["size_name"].get<std::string>();
  std::string strSqlSizeSel =
      "SELECT id, name FROM material.size WHERE name = $1";
  std::string strSqlSizeIns =
      "INSERT INTO material.size (name) VALUES ($1) RETURNING id";

  std::string strSqlSizeGet =
      "select dp.diamond_id, dp.clarity_id, ds.pcs, ds.post_id from "
      "product.diamond_price dp left join product.post_diamond_size ds on "
      "ds.id = dp.diamond_id where ds.shape_id = $1 and ds.color_id = $2 and "
      "ds.size_id = $3 and dp.clarity_id = $4;";
  std::string strSqlPriceUpdate =
      "UPDATE product.diamond_price SET (weight, total_weight, rate, price) = "
      "ROW($3, $4, $5, $6) WHERE diamond_id = $1 AND clarity_id = $2";

  auto q =
      "SELECT  sum(dp.total_weight) as sum_weight, sum(dp.price) as sum_price "
      "from product.post_diamond_size ds LEFT JOIN product.diamond_price dp ON "
      "(dp.diamond_id = ds.id) where ds.post_id = $1 and dp.clarity_id = $2";
  auto pc = upd_("product.post_clarity", "weight, price", "$3, $4",
                 "where post_id = $1 and clarity_id = $2");

  std::string strSql =
      "INSERT INTO %1.%2 (clarity_id, shape_id, color_id, size_id, weight, "
      "currency_id, rate_on_id, rate) values($1, $2, $3, $4, $5, $6, $7, $8)";
  ReplaceAll2(strSql, "%1", size_meta_table.schema());
  ReplaceAll2(strSql, "%2", size_meta_table.name());

  auto clientPtr = drogon::app().getDbClient("sce");
  auto transPtr = clientPtr->newTransaction();
  try {
    long size_id;
    auto r = Dba::writeInTrans(transPtr, strSqlSizeSel, size_name);
    if (r.empty()) {  // insert
      auto r1 = Dba::writeInTrans(transPtr, strSqlSizeIns, size_name);
      size_id = r1[0]["id"].as<long>();
    } else {
      size_id = r[0]["id"].as<long>();
    }

    Dba::writeInTrans(
        transPtr, strSql, args[0]["clarity_id"].get<long>(),
        args[0]["shape_id"].get<long>(), args[0]["color_id"].get<long>(),
        size_id, args[0]["weight"].get<float>(),
        args[0]["currency_id"].get<long>(),
        args[0]["rate_on_id"].get<std::string>(), args[0]["rate"].get<float>());

    // copy
    // update product weight and price:..
    struct ProductUpdate {
      long postId;
      std::vector<long> clarityId;
    };
    std::vector<ProductUpdate> productUpdate;

    auto s = Dba::writeInTrans(transPtr, strSqlSizeGet,
                               args[0]["shape_id"].get<long>(),
                               args[0]["color_id"].get<long>(), size_id,
                               args[0]["clarity_id"].get<long>());
    for (auto prow : s) {
      auto w = args[0]["weight"].get<float>();
      auto rate = args[0]["rate"].get<float>();
      auto pcs = prow[2].as<int>();
      Dba::writeInTrans(
          transPtr, strSqlPriceUpdate, prow["diamond_id"].as<long>(),
          prow["clarity_id"].as<long>(), w, w * pcs, rate, pcs * w * rate);
      // Get all post_ids:
      auto it = std::find_if(productUpdate.begin(), productUpdate.end(),
                             [&](const ProductUpdate& t) {
                               return t.postId == prow[3].as<long>();
                             });
      if (it == productUpdate.end()) {  // Element not Found
        productUpdate.push_back({prow[3].as<long>(), {prow[1].as<long>()}});
      } else {
        it->clarityId.push_back(prow[1].as<long>());
      }
    }

    for (const auto& p : productUpdate) {
      for (auto c : p.clarityId) {
        auto rsum = Dba::writeInTrans(transPtr, q, p.postId, c);
        Dba::writeInTrans(transPtr, pc, p.postId, c,
                          rsum[0]["sum_weight"].as<double>(),
                          rsum[0]["sum_price"].as<double>());
      }
    }

    json ret;
    ret[0] = simpleJsonSaveResult(event, true, "Done");
    return ret;
  } catch (const std::exception& e) {
    SPDLOG_TRACE(e.what());
    json ret;
    ret[0] = simpleJsonSaveResult(event, false, e.what());
    return ret;
  }
}
json DSize::upd(json event, json args) {
  // also update all the price of products too..
  // also update deleted size price too.

  auto size_table = sqlb::ObjectIdentifier("material", "size", "sh");
  auto size_meta_table =
      sqlb::ObjectIdentifier("material", "diamond_size_meta", "sm");

  // first insert size then insert on meta ...................
  auto size_name = args[0]["size_name"].get<std::string>();
  std::string strSqlSizeSel =
      "SELECT id, name FROM material.size WHERE name = $1";
  std::string strSqlSizeIns =
      "INSERT INTO material.size (name) VALUES ($1) RETURNING id";

  std::string strSqlSizeGet =
      "select dp.diamond_id, dp.clarity_id, ds.pcs, ds.post_id from "
      "product.diamond_price dp left join product.post_diamond_size ds on "
      "ds.id = dp.diamond_id where ds.shape_id = $1 and ds.color_id = $2 and "
      "ds.size_id = $3 and dp.clarity_id = $4;";
  std::string strSqlPriceUpdate =
      "UPDATE product.diamond_price SET (weight, total_weight, rate, price) = "
      "ROW($3, $4, $5, $6) WHERE diamond_id = $1 AND clarity_id = $2";

  auto q =
      "SELECT  sum(dp.total_weight) as sum_weight, sum(dp.price) as sum_price "
      "from product.post_diamond_size ds LEFT JOIN product.diamond_price dp ON "
      "(dp.diamond_id = ds.id) where ds.post_id = $1 and dp.clarity_id = $2";
  auto pc = upd_("product.post_clarity", "weight, price", "$3, $4",
                 "where post_id = $1 and clarity_id = $2");

  if (args[0]["id"].get<long>()) {
    std::string strSql =
        "update %1.%2 set "
        "(clarity_id, shape_id, color_id, size_id, weight, currency_id, "
        "rate_on_id, rate)"
        " = ROW($2, $3, $4, $5, $6, $7, $8, $9) where id=$1";
    ReplaceAll2(strSql, "%1", size_meta_table.schema());
    ReplaceAll2(strSql, "%2", size_meta_table.name());

    std::string strSqlSizeId =
        "SELECT size_id FROM material.diamond_size_meta WHERE id = $1;";
    std::string strSqlSizeCount =
        "SELECT count(*) FROM material.diamond_size_meta dm WHERE dm.size_id = "
        "$1";
    std::string strSqlColorSizeCount =
        "SELECT count(*) FROM material.color_stone_size_meta cm WHERE "
        "cm.size_id = $1";
    std::string strSqlSizeDel = "DELETE FROM material.size WHERE id = $1";

    auto clientPtr = drogon::app().getDbClient("sce");
    auto transPtr = clientPtr->newTransaction();
    try {
      long size_id;
      auto r = Dba::writeInTrans(transPtr, strSqlSizeSel, size_name);
      if (r.empty()) {  // insert
        auto r1 = Dba::writeInTrans(transPtr, strSqlSizeIns, size_name);
        size_id = r1[0]["id"].as<long>();
      } else {
        size_id = r[0]["id"].as<long>();
      }

      auto old_row =
          Dba::writeInTrans(transPtr, strSqlSizeId, args[0]["id"].get<long>());
      long old_size_id = old_row[0]["size_id"].as<long>();

      Dba::writeInTrans(
          transPtr, strSql, args[0]["id"].get<long>(),
          args[0]["clarity_id"].get<long>(), args[0]["shape_id"].get<long>(),
          args[0]["color_id"].get<long>(), size_id,
          args[0]["weight"].get<float>(), args[0]["currency_id"].get<long>(),
          args[0]["rate_on_id"].get<std::string>(),
          args[0]["rate"].get<float>());
      // If old size count = 0, delete size:
      auto r3 = Dba::writeInTrans(transPtr, strSqlSizeCount, old_size_id);
      auto r4 = Dba::writeInTrans(transPtr, strSqlColorSizeCount, old_size_id);
      if (r3[0]["count"].as<long>() == 0 && r4[0]["count"].as<long>() == 0) {
        Dba::writeInTrans(transPtr, strSqlSizeDel,
                          args[0]["shape_id"].get<long>(),
                          args[0]["color_id"].get<long>(), size_id,
                          args[0]["clarity_id"].get<long>());
      }

      // update product weight and price:..
      struct ProductUpdate {
        long postId;
        std::vector<long> clarityId;
      };
      std::vector<ProductUpdate> productUpdate;

      auto s = Dba::writeInTrans(transPtr, strSqlSizeGet,
                                 args[0]["shape_id"].get<long>(),
                                 args[0]["color_id"].get<long>(), size_id,
                                 args[0]["clarity_id"].get<long>());
      for (auto prow : s) {
        auto w = args[0]["weight"].get<float>();
        auto rate = args[0]["rate"].get<float>();
        auto pcs = prow[2].as<int>();
        Dba::writeInTrans(transPtr, strSqlPriceUpdate,
                          prow["diamond_id"].as<long>(), prow[1].as<long>(), w,
                          w * pcs, rate, pcs * w * rate);
        auto it = std::find_if(productUpdate.begin(), productUpdate.end(),
                               [&](const ProductUpdate& t) {
                                 return t.postId == prow[3].as<long>();
                               });
        if (it == productUpdate.end()) {  // Element not Found
          productUpdate.push_back({prow[3].as<long>(), {prow[1].as<long>()}});
        } else {
          it->clarityId.push_back(prow[1].as<long>());
        }
      }

      for (const auto& p : productUpdate) {
        for (auto c : p.clarityId) {
          auto rsum = Dba::writeInTrans(transPtr, q, p.postId, c);
          Dba::writeInTrans(transPtr, pc, p.postId, c,
                            rsum[0]["sum_weight"].as<double>(),
                            rsum[0]["sum_price"].as<double>());
        }
      }

      json ret;
      ret[0] = simpleJsonSaveResult(event, true, "Done");
      return ret;
    } catch (const std::exception& e) {
      SPDLOG_TRACE(e.what());
      json ret;
      ret[0] = simpleJsonSaveResult(event, false, e.what());
      return ret;
    }
  }
  json ret;
  ret[0] = simpleJsonSaveResult(event, false, "Not Valid Structure");
  return ret;
}

json DSize::del(json event, json args) {
  // to support global filter, get first all ids b selected filter and for each
  // id delete.
  auto clientPtr = drogon::app().getDbClient("sce");
  auto transPtr = clientPtr->newTransaction();
  try {
    auto get_row =
        "SELECT id, size_id FROM material.diamond_size_meta where id = $1";
    auto id = args[0][0].get<long>();
    auto r = Dba::writeInTrans(transPtr, get_row, id);

    Dba::writeInTrans(transPtr,
                      "DELETE FROM "
                      "material.diamond_size_meta"
                      " WHERE id = $1",
                      id);

    auto d_size_count =
        "SELECT count(*) FROM material.diamond_size_meta where size_id = $1";
    auto cs_size_count =
        "SELECT count(*) FROM material.color_stone_size_meta where size_id = "
        "$1";

    auto size_id = r[0][1].as<long>();
    auto c1 = Dba::writeInTrans(transPtr, d_size_count, size_id);
    auto c2 = Dba::writeInTrans(transPtr, cs_size_count, size_id);
    if (c1[0]["count"].as<long>() == 0 && c2[0]["count"].as<long>() == 0) {
      Dba::writeInTrans(transPtr,
                        "DELETE FROM "
                        "material.size"
                        " WHERE id = $1",
                        size_id);
    }

    json ret;
    ret[0] = simpleJsonSaveResult(event, true, "Done");
    return ret;
  } catch (const std::exception& e) {
    SPDLOG_TRACE(e.what());
    json ret;
    ret[0] = simpleJsonSaveResult(event, false, e.what());
    return ret;
  }
}
