#include "cssize.h"
#include "../../strfns.h"
#include "../../jsonfns.h"

CSSize::CSSize(const WebSocketConnectionPtr& wsConnPtr_): BaseService(wsConnPtr_)
{
    t.m_table = sqlb::ObjectIdentifier("material", "color_stone_size_meta", "sm");

}

void CSSize::setupTable()
{
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

Json::Value CSSize::ins( Json::Value event, Json::Value args) {
    auto size_table = sqlb::ObjectIdentifier("material", "size", "sh");
    auto size_meta_table = sqlb::ObjectIdentifier("material", "color_stone_size_meta", "sm");

    // first insert size then insert on meta ...................
    auto size_name = args["size_name"].asString();
    std::string strSqlSizeSel = "SELECT id, name FROM material.size WHERE name = $1";
    std::string strSqlSizeIns = "INSERT INTO material.size (name) VALUES ($1) RETURNING id";

    std::string strSqlSizeGet = "select cp.cs_id, ds.pcs, ds.post_id from product.cs_price cp left join product.post_color_stone_size ds on ds.id = cp.cs_id where ds.cs_type_id = $1 and ds.shape_id = $2 and ds.size_id = $3;";
    std::string strSqlPriceUpdate = "UPDATE product.cs_price SET (weight, total_weight, rate, price) = ROW($2, $3, $4, $5) WHERE cs_id = $1";

    auto q = "SELECT  sum(cp.total_weight) as sum_weight, sum(cp.price) as sum_price from product.post_color_stone_size ds LEFT JOIN product.cs_price cp ON (cp.cs_id = ds.id) where ds.post_id = $1";
    auto pc = upd_("product.post_cs_total", "weight, price", "$2, $3", "where post_id = $1");

    std::string strSql = "INSERT INTO %1.%2 (cs_type_id, shape_id, size_id, weight, currency_id, rate_on_id, rate) values($1, $2, $3, $4, $5, $6, $7)";
    ReplaceAll2(strSql, "%1", size_meta_table.schema());
    ReplaceAll2(strSql, "%2", size_meta_table.name());

    try {
        auto transPtr = clientPtr->newTransaction();
        int size_id;
        auto r = transPtr->execSqlSync(strSqlSizeSel, size_name);
        if (r.size() == 0) { // insert
            auto r1 = transPtr->execSqlSync(strSqlSizeIns, size_name);
            size_id = r1[0]["id"].as<int>();
        } else {
            size_id = r[0]["id"].as<int>();
        }


        transPtr->execSqlSync(
            strSql,
            args["cs_type_id"].asInt(),
            args["shape_id"].asInt(),
            size_id,
            args["weight"].asDouble(),
            args["currency_id"].asInt(),
            args["rate_on_id"].asString(),
            args["rate"].asDouble()
            );


        //copy
        // update product weight and price:..
        struct ProductUpdate {
            int postId;
        };
        std::vector<ProductUpdate> productUpdate;

        auto s = transPtr->execSqlSync(strSqlSizeGet, args["cs_type_id"].asInt(), args["shape_id"].asInt(), size_id);
        for (auto prow : s) {
            auto w = args["weight"].asDouble();
            auto rate = args["rate"].asDouble();
            auto pcs = prow[1].as<int>();
            transPtr->execSqlSync(strSqlPriceUpdate, prow["cs_id"].as<int>(), w, w * pcs, rate, pcs * w * rate);
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
            auto rsum = transPtr->execSqlSync(q, p.postId);
            transPtr->execSqlSync(pc, p.postId, rsum[0]["sum_weight"].as<double>(), rsum[0]["sum_price"].as<double>());
        }

        
        Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
    } catch (const std::exception &e) {
        
        std::cerr << e.what() << std::endl;
        Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
    }
}

Json::Value CSSize::upd( Json::Value event, Json::Value args) {
    auto size_table = sqlb::ObjectIdentifier("material", "size", "sh");
    auto size_meta_table = sqlb::ObjectIdentifier("material", "color_stone_size_meta", "sm");

    // first insert size then insert on meta ...................
    auto size_name = args["size_name"].asString();
    std::string strSqlSizeSel = "SELECT id, name FROM material.size WHERE name = $1";
    std::string strSqlSizeIns = "INSERT INTO material.size (name) VALUES ($1) RETURNING id";

    std::string strSqlSizeGet = "select cp.cs_id, ds.pcs, ds.post_id from product.cs_price cp left join product.post_color_stone_size ds on ds.id = cp.cs_id where ds.cs_type_id = $1 and ds.shape_id = $2 and ds.size_id = $3;";
    std::string strSqlPriceUpdate = "UPDATE product.cs_price SET (weight, total_weight, rate, price) = ROW($2, $3, $4, $5) WHERE cs_id = $1";

    auto q = "SELECT  sum(cp.total_weight) as sum_weight, sum(cp.price) as sum_price from product.post_color_stone_size ds LEFT JOIN product.cs_price cp ON (cp.cs_id = ds.id) where ds.post_id = $1";
    auto pc = upd_("product.post_cs_total", "weight, price", "$2, $3", "where post_id = $1");


    if (args["id"].asInt()) {
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

        auto transPtr = clientPtr->newTransaction();
        try {
            int size_id;
            auto r = transPtr->execSqlSync(strSqlSizeSel, size_name);
            if (r.size() == 0) { // insert
                auto r1 = transPtr->execSqlSync(strSqlSizeIns, size_name);
                size_id = r1[0]["id"].as<int>();
            } else {
                size_id = r[0]["id"].as<int>();
            }

            auto old_row = transPtr->execSqlSync(strSqlSizeId, args["id"].asInt());
            int old_size_id = old_row[0]["id"].as<int>();

            transPtr->execSqlSync(strSql,
                            args["id"].asInt64(),
                    args["cs_type_id"].asInt(),
                    args["shape_id"].asInt(),
                    size_id,
                    args["weight"].asDouble(),
                    args["currency_id"].asInt(),
                    args["rate_on_id"].asString(),
                    args["rate"].asDouble()
                    );
            // If old size count = 0, delete size:
            auto r3 = transPtr->execSqlSync(strSqlSizeCount, old_size_id);
            auto r4 = transPtr->execSqlSync(strSqlColorSizeCount, old_size_id);
            if (r3[0]["count"].as<int>() == 0 && r4[0]["count"].as<int>() == 0) {
                transPtr->execSqlSync(strSqlSizeDel, old_size_id);
            }

            // update product weight and price:..
            struct ProductUpdate {
                int postId;
            };
            std::vector<ProductUpdate> productUpdate;

            auto s = transPtr->execSqlSync(strSqlSizeGet, args["cs_type_id"].asInt(), args["shape_id"].asInt(), size_id);
            for (auto prow : s) {
                auto w = args["weight"].asDouble();
                auto rate = args["rate"].asDouble();
                auto pcs = prow[1].as<int>();
                transPtr->execSqlSync(strSqlPriceUpdate, prow["cs_id"].as<int>(), w, w * pcs, rate, pcs * w * rate);
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
                auto rsum = transPtr->execSqlSync(q, p.postId);
                transPtr->execSqlSync(pc, p.postId, rsum[0]["sum_weight"].as<double>(), rsum[0]["sum_price"].as<double>());
            }

            
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
        } catch (const std::exception &e) {
            
            std::cerr << e.what() << std::endl;
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
        }
    }
}

Json::Value CSSize::del( Json::Value event, Json::Value args) {
    auto transPtr = clientPtr->newTransaction();
    try {
        auto get_row = "SELECT id, size_id FROM material.color_stone_size_meta where id = $1";
        auto r = transPtr->execSqlSync(get_row, args[0].asInt());

        transPtr->execSqlSync("DELETE FROM " "material.color_stone_size_meta" " WHERE id = $1", args[0].asInt());

        auto d_size_count = "SELECT count(*) FROM material.diamond_size_meta where size_id = $1";
        auto cs_size_count = "SELECT count(*) FROM material.color_stone_size_meta where size_id = $1";

        auto size_id = r[0][1].as<int>();
        auto c1 = transPtr->execSqlSync(d_size_count, size_id);
        auto c2 = transPtr->execSqlSync(cs_size_count, size_id);
        if (c1[0]["count"].as<int>() == 0 && c2[0]["count"].as<int>() == 0) {
            transPtr->execSqlSync("DELETE FROM " "material.size" " WHERE id = $1", size_id);
        }
        
        Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
    } catch (const std::exception &e) {
        
        std::cerr << e.what() << std::endl;
        Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
    }
}
