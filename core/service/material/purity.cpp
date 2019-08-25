#include "purity.h"
#include "../../strfns.h"
#include "../../jsonfns.h"

Purity::Purity()
{
    t.m_table = sqlb::ObjectIdentifier("material", "purity", "p");

}

void Purity::setupTable()
{
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

void save_purity_metal_(json &args, std::shared_ptr<Transaction> transPtr, int purity_id, int tone_id) {
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
    for (auto i : args) {
        if (!i[0].is_null()) inVector.push_back({i[0].get<int>(), i[1].get<float>(), i[2].get<float>()});
    }

    auto all_ct = transPtr->execSqlSync(strSqlPostCategories, purity_id, tone_id);
    // For each saved tones, If saved tone not exist in new tones, delete it.
    for (auto r : all_ct) {
        std::vector<PriceMetal>::iterator it = std::find_if(inVector.begin(), inVector.end(), [&](PriceMetal t) {
            return t.metal_id == r["metal_id"].as<int>();
        });
        if (it == inVector.end()) {// Element not Found
            transPtr->execSqlSync(strSqlPostCategoryDel, purity_id, tone_id, r["metal_id"].as<int>());
        }
    }
    // For each new tones, insert it if it not already exist.
    for (auto r : inVector) {
        auto y = transPtr->execSqlSync(strSqlPostCategorySimpleFind, purity_id, tone_id, r.metal_id);
        if (y.size() == 0) {
            transPtr->execSqlSync(strSqlPostCategoryInsert, purity_id, tone_id, r.metal_id, r.purity, r.price);
        } else { // update
            if (y[0][2].as<int>() != r.metal_id || y[0]["purity"].as<double>() != r.purity || y[0]["price"].as<double>() != r.price) {
                transPtr->execSqlSync(strSqlPostCategoryUpdateAtt, purity_id, tone_id, r.metal_id, r.purity, r.price);
            }
        }
    }
}
void save_purity_tone_(json &args, std::shared_ptr<Transaction> transPtr, int purity_id) {
    std::string strSqlPostCategories = "SELECT tone_id FROM material.purity_tone where purity_id = $1";
    std::string strSqlPostCategorySimpleFind = "SELECT purity_id, tone_id, price FROM material.purity_tone WHERE purity_id = $1 and tone_id = $2";
    std::string strSqlPostCategoryDel = "DELETE FROM material.purity_tone WHERE purity_id = $1 and tone_id = $2";
    std::string strSqlPostCategoryInsert = "INSERT INTO material.purity_tone (purity_id, tone_id, price) VALUES ($1, $2, $3) returning purity_id, tone_id;";
    std::string strSqlPostCategoryUpdateAtt = "UPDATE material.purity_tone SET (price) = ROW($3) WHERE purity_id = $1 and tone_id = $2";

    struct PurityTone {
        int tone_id;
        double price;
        json j;
    };
    std::vector<PurityTone> inVector;
    for (auto i : args[0]["pt_purity_tone"]) {
        if (!i[0].is_null()) inVector.push_back({i[0].get<int>(), i[2].get<float>(), i[1]});
    }

    auto all_ct = transPtr->execSqlSync(strSqlPostCategories, purity_id);
    // For each saved tones, If saved tone not exist in new tones, delete it.
    for (auto r : all_ct) {
        std::vector<PurityTone>::iterator it = std::find_if(inVector.begin(), inVector.end(), [&](PurityTone t) {
            return t.tone_id == r["tone_id"].as<int>();
        });
        if (it == inVector.end()) {// Element not Found
            // because when tone_id change it actually inserting new entries..
            transPtr->execSqlSync(dele_("material.purity_metal", "where purity_id = $1 and tone_id = $2"), purity_id, r["tone_id"].as<int>());
            transPtr->execSqlSync(strSqlPostCategoryDel, purity_id, r["tone_id"].as<int>());
        }
    }
    // For each new tones, insert it if it not already exist.
    for (auto r : inVector) {
        auto y = transPtr->execSqlSync(strSqlPostCategorySimpleFind, purity_id, r.tone_id);
        if (y.size() == 0) {
            auto z = transPtr->execSqlSync(strSqlPostCategoryInsert, purity_id, r.tone_id, r.price);
            save_purity_metal_(r.j, transPtr, z[0]["purity_id"].as<int>(), z[0]["tone_id"].as<int>());
        } else { // update
            if (y[0]["tone_id"].as<int>() != r.tone_id || y[0]["price"].as<double>() != r.price) {
                transPtr->execSqlSync(strSqlPostCategoryUpdateAtt, purity_id, r.tone_id, r.price);
            }
            save_purity_metal_(r.j, transPtr, purity_id, r.tone_id);
        }
    }
}

json Purity::ins( json event, json args) {
    auto metal_purity_table = sqlb::ObjectIdentifier("material", "purity", "p");
    auto purity_metal_table = sqlb::ObjectIdentifier("material", "purity_metal", "mp");

    std::string strSql = "INSERT INTO %1.%2 (slug, name, metal_id, purity, price, description) values($1, $2, $3, $4, $5, $6) returning id";
    ReplaceAll2(strSql, "%1", metal_purity_table.schema());
    ReplaceAll2(strSql, "%2", metal_purity_table.name());

    auto clientPtr = drogon::app().getDbClient("sce");
    auto transPtr = clientPtr->newTransaction();
    try {
        auto x = transPtr->execSqlSync(
            strSql,
            args[0]["slug"].get<std::string>(),
            args[0]["name"].get<std::string>(),
            args[0]["metal_id"].get<int>(),
            args[0]["purity"].get<float>(),
            args[0]["price"].get<float>(),
            args[0]["description"].get<std::string>()
            );
        auto purity_id = x[0]["id"].as<int>();
        save_purity_tone_(args, transPtr, purity_id);
        
        json ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
    } catch (const std::exception &e) {
        
        spdlog::error(e.what());
        json ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
    }
}
json Purity::upd( json event, json args) {
    auto metal_purity_table = sqlb::ObjectIdentifier("material", "purity", "p");
    auto purity_metal_table = sqlb::ObjectIdentifier("material", "purity_metal", "mp");

    if (args[0]["id"].get<long>()) {
        std::string strSql =
                "update %1.%2 set (slug, name, metal_id, purity, price, description) = ROW($2, $3, $4, $5, $6, $7) where id=$1";
        ReplaceAll2(strSql, "%1", metal_purity_table.schema());
        ReplaceAll2(strSql, "%2", metal_purity_table.name());

        auto clientPtr = drogon::app().getDbClient("sce");
        auto transPtr = clientPtr->newTransaction();
        try {
            transPtr->execSqlSync(strSql,
                    args[0]["id"].get<long>(),
                    args[0]["slug"].get<std::string>(),
                    args[0]["name"].get<std::string>(),
                    args[0]["metal_id"].get<int>(),
                    args[0]["purity"].get<float>(),
                    args[0]["price"].get<float>(),
                    args[0]["description"].get<std::string>()
                    );
            auto purity_id = args[0]["id"].get<long>();
            save_purity_tone_(args, transPtr, purity_id);

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

            auto product_update = transPtr->execSqlSync(pr_update3, args[0]["id"].get<long>());
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

            auto pr = transPtr->execSqlSync(pr_update4, purity_id, ids);

            
            json ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
        } catch (const std::exception &e) {
            
            spdlog::error(e.what());
            json ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
        }
    }
}

json Purity::del( json event, json args) {
     // to support global filter, get first all ids b selected filter and for each id delete.
    auto clientPtr = drogon::app().getDbClient("sce");
    auto transPtr = clientPtr->newTransaction();
    try {
        auto post_id = args[0][0].get<int>();
        transPtr->execSqlSync("DELETE FROM " "material.purity_metal" " WHERE purity_id = $1", post_id);
        transPtr->execSqlSync("DELETE FROM " "material.purity_tone" " WHERE purity_id = $1", post_id);
        transPtr->execSqlSync("DELETE FROM " "material.purity" " WHERE id = $1", post_id);
        
        json ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
    } catch (const std::exception &e) {
        
        spdlog::error(e.what());
        json ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
    }
}
