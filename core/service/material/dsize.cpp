#include "dsize.h"
#include "../../strfns.h"
#include "../../jsonfns.h"

DSize::DSize(const WebSocketConnectionPtr& wsConnPtr_): BaseService(wsConnPtr_)
{
    t.m_table = sqlb::ObjectIdentifier("material", "diamond_size_meta", "sm");

}

void DSize::setupTable()
{
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

Json::Value DSize::ins( Json::Value event, Json::Value args) {
    // also update all the price of products too..
    // also update deleted size price too.

    auto size_table = sqlb::ObjectIdentifier("material", "size", "sh");
    auto size_meta_table = sqlb::ObjectIdentifier("material", "diamond_size_meta", "sm");

    // first insert size then insert on meta ...................
    auto size_name = args["size_name"].asString();
    std::string strSqlSizeSel = "SELECT id, name FROM material.size WHERE name = $1";
    std::string strSqlSizeIns = "INSERT INTO material.size (name) VALUES ($1) RETURNING id";

    std::string strSqlSizeGet = "select dp.diamond_id, dp.clarity_id, ds.pcs, ds.post_id from product.diamond_price dp left join product.post_diamond_size ds on ds.id = dp.diamond_id where ds.shape_id = $1 and ds.color_id = $2 and ds.size_id = $3 and dp.clarity_id = $4;";
    std::string strSqlPriceUpdate = "UPDATE product.diamond_price SET (weight, total_weight, rate, price) = ROW($3, $4, $5, $6) WHERE diamond_id = $1 AND clarity_id = $2";

    auto q = "SELECT  sum(dp.total_weight), sum(dp.price) from product.post_diamond_size ds LEFT JOIN product.diamond_price dp ON (dp.diamond_id = ds.id) where ds.post_id = $1 and dp.clarity_id = $2";
    auto pc = upd_("product.post_clarity", "weight, price", "$3, $4", "where post_id = $1 and clarity_id = $2");

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
            args["clarity_id"].asInt(),
            args["shape_id"].asInt(),
            args["color_id"].asInt(),
            size_id,
            args["weight"].asDouble(),
            args["currency_id"].asInt(),
            args["rate_on_id"].asString(),
            args["rate"].asDouble()
            );

        // copy
        // update product weight and price:..
        struct ProductUpdate {
            int postId;
            std::vector<int> clarityId;
        };
        std::vector<ProductUpdate> productUpdate;

        auto s = txn.exec_params(strSqlSizeGet, args["shape_id"].asInt(), args["color_id"].asInt(), size_id,
                                 args["clarity_id"].asInt());
        for (auto prow : s) {
            auto w = args["weight"].asDouble();
            auto rate = args["rate"].asDouble();
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
        Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
    } catch (const std::exception &e) {
        txn.abort();
        std::cerr << e.what() << std::endl;
        Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
    }
}
Json::Value DSize::upd( Json::Value event, Json::Value args) {
    // also update all the price of products too..
    // also update deleted size price too.



    auto size_table = sqlb::ObjectIdentifier("material", "size", "sh");
    auto size_meta_table = sqlb::ObjectIdentifier("material", "diamond_size_meta", "sm");

    // first insert size then insert on meta ...................
    auto size_name = args["size_name"].asString();
    std::string strSqlSizeSel = "SELECT id, name FROM material.size WHERE name = $1";
    std::string strSqlSizeIns = "INSERT INTO material.size (name) VALUES ($1) RETURNING id";

    std::string strSqlSizeGet = "select dp.diamond_id, dp.clarity_id, ds.pcs, ds.post_id from product.diamond_price dp left join product.post_diamond_size ds on ds.id = dp.diamond_id where ds.shape_id = $1 and ds.color_id = $2 and ds.size_id = $3 and dp.clarity_id = $4;";
    std::string strSqlPriceUpdate = "UPDATE product.diamond_price SET (weight, total_weight, rate, price) = ROW($3, $4, $5, $6) WHERE diamond_id = $1 AND clarity_id = $2";

    auto q = "SELECT  sum(dp.total_weight), sum(dp.price) from product.post_diamond_size ds LEFT JOIN product.diamond_price dp ON (dp.diamond_id = ds.id) where ds.post_id = $1 and dp.clarity_id = $2";
    auto pc = upd_("product.post_clarity", "weight, price", "$3, $4", "where post_id = $1 and clarity_id = $2");

    if (args["id"].asInt()) {
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

            auto old_row = txn.exec_params(strSqlSizeId, args["id"].asInt());
            int old_size_id = old_row[0][0].as<int>();

            txn.exec_params(strSql,
                            args["id"].asInt64(),
                    args["clarity_id"].asInt(),
                    args["shape_id"].asInt(),
                    args["color_id"].asInt(),
                    size_id,
                    args["weight"].asDouble(),
                    args["currency_id"].asInt(),
                    args["rate_on_id"].asString(),
                    args["rate"].asDouble()
                    );
            // If old size count = 0, delete size:
            auto r3 = txn.exec_params(strSqlSizeCount, old_size_id);
            auto r4 = txn.exec_params(strSqlColorSizeCount, old_size_id);
            if (r3[0][0].as<int>() == 0 && r4[0][0].as<int>() == 0) {
                txn.exec_params(strSqlSizeDel, args["shape_id"].asInt(), args["color_id"].asInt(), size_id,
                        args["clarity_id"].asInt());
            }

            // update product weight and price:..
            struct ProductUpdate {
                int postId;
                std::vector<int> clarityId;
            };
            std::vector<ProductUpdate> productUpdate;

            auto s = txn.exec_params(strSqlSizeGet, args["shape_id"].asInt(), args["color_id"].asInt(), size_id,
                    args["clarity_id"].asInt());
            for (auto prow : s) {
                auto w = args["weight"].asDouble();
                auto rate = args["rate"].asDouble();
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
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
        }
    }
}

Json::Value DSize::del( Json::Value event, Json::Value args) {
    pqxx::work txn{DD};
    try {
        auto get_row = "SELECT id, size_id FROM material.diamond_size_meta where id = $1";
        auto r = txn.exec_params(get_row, args[0].asInt());

        txn.exec_params("DELETE FROM " "material.diamond_size_meta" " WHERE id = $1", args[0].asInt());

        auto d_size_count = "SELECT count(*) FROM material.diamond_size_meta where size_id = $1";
        auto cs_size_count = "SELECT count(*) FROM material.color_stone_size_meta where size_id = $1";

        auto size_id = r[0][1].as<int>();
        auto c1 = txn.exec_params(d_size_count, size_id);
        auto c2 = txn.exec_params(cs_size_count, size_id);
        if (c1[0][0].as<int>() == 0 && c2[0][0].as<int>() == 0) {
            txn.exec_params("DELETE FROM " "material.size" " WHERE id = $1", size_id);
        }
        txn.commit();
        Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
    } catch (const std::exception &e) {
        txn.abort();
        std::cerr << e.what() << std::endl;
        Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
    }
}
