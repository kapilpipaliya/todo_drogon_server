#include "savefunctions.h"

#include "core/tables/Table.h"
#include "core/tables/functions.h"
#include <iostream>
#include <range/v3/all.hpp>
#include <regex>
#include <iostream>
#include <fstream>
#include <vector>
#include <boost/filesystem.hpp>

#define i(t, c, v) "INSERT INTO " t " (" c ") VALUES (" v ")"
#define u(t, c, v, w) "UPDATE " t " SET (" c ") = ROW (" v ")" w
#define s(t, c, w) "SELECT " c " FROM " t " " w

#define de(t, w) "DELETE FROM " t " " w

void printJson(Json::Value & in)
{
    fprintf(stdout, "%s\n", in.toStyledString().c_str());
    fflush(stdout);
}

void simpleJsonResult(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, bool ok, const std::string & error)
{
    Json::Value out;
    out[0]=event_name;

    Json::Value ret;
    ret["ok"]=ok;
    if (!ok) {
        ret["error"]=error;
    }
    out[1]=ret;
    wsConnPtr->send(out.toStyledString());
}
void sendAJson(const WebSocketConnectionPtr& wsConnPtr, Json::Value out)
{
    wsConnPtr->send(out.toStyledString());
}
#define ids2(s)\
std::string ids = "{";\
for (auto i : s) { ids += std::to_string(i[0].as<int>()) + ","; }\
if(s.size() > 0) ids.pop_back();\
ids += "}";


// ---------
void saveImageMeta(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in)
{
    auto c = std::any_cast<int>(wsConnPtr->getContext());
    auto strSql = i("setting.temp_image", "session_id, event_name, name, size, type", "$1, $2, $3, $4, $5");
    pqxx::work txn{DD};
    try {
        auto r = txn.exec_params(strSql, c,  in[0].asString(), in[1].asString(), in[2].asInt64(), in[3].asString());
        txn.commit();
        simpleJsonResult(event_name, wsConnPtr, true, "done");
    } catch (const std::exception &e) {
        txn.abort();
        std::cerr << e.what() << std::endl;
        simpleJsonResult(event_name, wsConnPtr, false, "Error");
    }


}

#define delFn(s, s1)\
void delete_##s(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in)\
{\
    pqxx::work txn{DD};\
    try {\
        txn.exec_params("DELETE FROM " s1 " WHERE id = $1", in[0].asInt());\
        txn.commit();\
        simpleJsonResult(event_name, wsConnPtr, true, "Done");\
    } catch (const std::exception &e) {\
        txn.abort();\
        std::cerr << e.what() << std::endl;\
        simpleJsonResult(event_name, wsConnPtr, false, e.what());\
    }\
}
delFn(metal, "material.metal");

//delFn(purity, "material.purity");
delFn(tone, "material.tone");
delFn(accessory, "material.accessory");

delFn(clarity, "material.clarity");
delFn(shape, "material.shape");
delFn(d_color, "material.diamond_color");
delFn(cs_color, "material.cs_color");
//delFn(diamond_size, "material.diamond_size_meta");
//delFn(color_stone_size, "material.color_stone_size_meta");
// Entity
delFn(address_type, "entity.address_type");
delFn(contact_type, "entity.contact_type");
delFn(entity_type, "entity.entity_type");
//delFn(entity, "entity.entity");
// product:
delFn(category, "product.category");
//delFn(product, "product.product");
delFn(post, "product.post");

delFn(tag, "product.tag");
delFn(shipping_class, "product.shipping_class");
delFn(setting_type, "product.setting_type");
delFn(certified_by, "product.certified_by");

delFn(currency, "setting.currency");

//-----------
void save_metal(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in)
{
    printJson(in);
    auto metal_table = sqlb::ObjectIdentifier("material", "metal", "m");

    if(in["id"].asInt()) {
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

            ids2(pr);
            auto pr_update2 = R"(
update material.purity p
set (price) = row((select SUM(pm.price)
             FROM material.purity_metal pm
             WHERE p.id = pm.purity_id))
where
p.id = ANY($1::bigint[])
)";
            auto pr2 = txn.exec_params(pr_update2, ids);

            auto pr_update3 = R"(
update product.product p
set (volume) = row(
            p.weight / (select SUM(pm.purity * m.specific_density / 100)
             FROM material.purity_metal pm left join material.metal m on m.id = pm.metal_id
             WHERE pm.purity_id = p.purity_id)
             )
where
p.purity_id = ANY($1::bigint[])
)";
            auto pr3 = txn.exec_params(pr_update3, ids);

            auto pr_update4 = R"(
UPDATE product.post_purity pp
SET (weight, price) = row(pr.volume * sub_q.sum_val, pr.volume * sub_q.sum_vaL * p.price)
FROM
    (
        select pm.purity_id, SUM(pm.purity * m.specific_density / 100) as sum_val
             FROM material.purity_metal pm left join material.metal m on m.id = pm.metal_id
            group by pm.purity_id
    ) AS sub_q, product.product pr, material.purity p
where sub_q.purity_id = pp.purity_id
and pr.post_id = pp.post_id -- to get volume from pr
and p.id = pp.purity_id -- to get price from p
and pp.purity_id = ANY($1::bigint[])
--returning pp.post_id, pp.purity_id, pp.weight, pp.price
)";
            auto pr4 = txn.exec_params(pr_update4, ids);
/*
 *             auto s = R"(
update product.post_purity pp set
  (price) = row (pp.weight * p.purity * $2 / 100)
from  material.purity p
where p.id = pp.purity_id
and p.metal_id = $1
)";


            auto pr = txn.exec_params(s, in["id"].asInt(), in["price"].asDouble());
*/
            
            txn.commit();
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
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
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
        }
    }
}
void save_purity_metal(sqlb::ObjectIdentifier purity_metal_table,
                            Json::Value &in,
                            pqxx::work &txn,
                            int purity_id)
{
    std::string strSqlPostCategories = "SELECT metal_id FROM %1.%2 where purity_id = $1";
    ReplaceAll2(strSqlPostCategories, "%1", purity_metal_table.schema());
    ReplaceAll2(strSqlPostCategories, "%2", purity_metal_table.name());

    std::string strSqlPostCategorySimpleFind = "SELECT purity_id, metal_id, purity, price, ismain FROM %1.%2 WHERE purity_id = $1 and metal_id = $2";
    ReplaceAll2(strSqlPostCategorySimpleFind, "%1", purity_metal_table.schema());
    ReplaceAll2(strSqlPostCategorySimpleFind, "%2", purity_metal_table.name());


    std::string strSqlPostCategoryDel = "DELETE FROM %1.%2 WHERE purity_id = $1 and metal_id = $2";
    ReplaceAll2(strSqlPostCategoryDel, "%1", purity_metal_table.schema());
    ReplaceAll2(strSqlPostCategoryDel, "%2", purity_metal_table.name());

    std::string strSqlPostCategoryInsert = "INSERT INTO %1.%2 (purity_id, metal_id, purity, price, ismain) VALUES ($1, $2, $3, $4, $5);";
    ReplaceAll2(strSqlPostCategoryInsert, "%1", purity_metal_table.schema());
    ReplaceAll2(strSqlPostCategoryInsert, "%2", purity_metal_table.name());

    std::string strSqlPostCategoryUpdateAtt = "UPDATE material.purity_metal SET (purity, price, ismain) = ROW($3, $4, $5) WHERE purity_id = $1 and metal_id = $2";

    struct PriceMetal {
        int metal_id;
        double purity;
        double price;
        bool ismain;
    };
    std::vector<PriceMetal>inVector;
    for (auto i : in["mp_metal_purity"]) { // purity_id, weight, price
        if (!i[0].isNull()) inVector.push_back({i[0].asInt(), i[1].asDouble(), i[2].asDouble(), i[3].asBool()});
    }

    pqxx::result all_ct = txn.exec_params(strSqlPostCategories, purity_id);
    // For each saved tones, If saved tone not exist in new tones, delete it.
    for (auto r : all_ct) {
        std::vector<PriceMetal>::iterator it = std::find_if(inVector.begin(), inVector.end(), [&](PriceMetal t) {
            return t.metal_id == r[0].as<int>();
        });
        if (it == inVector.end()) {// Element not Found
            txn.exec_params(strSqlPostCategoryDel, purity_id, r[0].as<int>());
        }
    }
    // For each new tones, insert it if it not already exist.
    for (auto r : inVector) {
        pqxx::result y = txn.exec_params(strSqlPostCategorySimpleFind, purity_id, r.metal_id);
        if(y.size() == 0) {
            txn.exec_params(strSqlPostCategoryInsert, purity_id, r.metal_id, r.purity, r.price, r.ismain);
        } else { // update
            if(y[0][1].as<int>() != r.metal_id || y[0][2].as<double>() != r.purity || y[0][3].as<double>() != r.price || y[0][4].as<bool>() != r.ismain) {
                txn.exec_params(strSqlPostCategoryUpdateAtt, purity_id, r.metal_id, r.purity, r.price, r.ismain);
            }
        }
    }
}
void save_purity(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in)
{
    printJson(in);
    auto metal_purity_table = sqlb::ObjectIdentifier("material", "purity", "p");
    auto purity_metal_table = sqlb::ObjectIdentifier("material", "purity_metal", "mp");


    if(in["id"].asInt()) {
        std::string strSql =
            "update %1.%2 set (slug, name, price, description) = ROW($2, $3, $4, $5) where id=$1";
        ReplaceAll2(strSql, "%1", metal_purity_table.schema());
        ReplaceAll2(strSql, "%2", metal_purity_table.name());

        pqxx::work txn{DD};
        try {
            txn.exec_params(strSql,
                            in["id"].asInt(),
                            in["slug"].asString(),
                            in["name"].asString(),
                            in["price"].asDouble(),
                            in["description"].asString()
                           );
            auto purity_id = in["id"].asInt();
            save_purity_metal(purity_metal_table, in, txn, purity_id);

            auto pr_update3 = R"(
update product.product p
set (volume) = row(
            p.weight / (select SUM(pm.purity * m.specific_density / 100)
             FROM material.purity_metal pm left join material.metal m on m.id = pm.metal_id
             WHERE pm.purity_id = p.purity_id)
             )
where
p.purity_id = $1 returning p.post_id
)";
            auto product_update = txn.exec_params(pr_update3, in["id"].asInt());
            ids2(product_update);
            auto pr_update4 = R"(
UPDATE product.post_purity pp
SET (weight, price) = row(pr.volume * sub_q.sum_val, pr.volume * sub_q.sum_vaL * p.price)
FROM
    (
        select pm.purity_id, SUM(pm.purity * m.specific_density / 100) as sum_val
             FROM material.purity_metal pm left join material.metal m on m.id = pm.metal_id
            group by pm.purity_id
    ) AS sub_q, product.product pr, material.purity p
where sub_q.purity_id = pp.purity_id
and pr.post_id = pp.post_id -- to get volume from pr
and p.id = pp.purity_id -- to get price from p
and (pp.purity_id = $1 or pp.post_id = ANY($2::bigint[]) )
--returning pp.post_id, pp.purity_id, pp.weight, pp.price
)";
            auto pr = txn.exec_params(pr_update4, purity_id, ids);

            txn.commit();
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
        }
    } else {
        std::string strSql = "INSERT INTO %1.%2 (slug, name, price, description) values($1, $2, $3, $4) returning id";
        ReplaceAll2(strSql, "%1", metal_purity_table.schema());
        ReplaceAll2(strSql, "%2", metal_purity_table.name());

        pqxx::work txn{DD};
        try {
            pqxx::result x = txn.exec_params(
                strSql,
                in["slug"].asString(),
                in["name"].asString(),
                in["price"].asDouble(),
                in["description"].asString()
            );
            auto  purity_id = x[0]["id"].as<int>();
            save_purity_metal(purity_metal_table, in, txn, purity_id);
            txn.commit();
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
        }
    }
}void delete_purity(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in)
{
    pqxx::work txn{DD};
    try {
        txn.exec_params("DELETE FROM " "material.purity_metal" " WHERE purity_id = $1", in[0].asInt());
        txn.exec_params("DELETE FROM " "material.purity" " WHERE id = $1", in[0].asInt());
        txn.commit();
        simpleJsonResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
        txn.abort();
        std::cerr << e.what() << std::endl;
        simpleJsonResult(event_name, wsConnPtr, false, e.what());
    }
}

void save_tone(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in)
{
    printJson(in);
    auto product_table = sqlb::ObjectIdentifier("material", "tone", "t");

    if(in["id"].asInt()) {
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
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
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
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
        }
    }
}

void save_accessory(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in)
{
    printJson(in);
    auto accessory_table = sqlb::ObjectIdentifier("material", "accessory", "t");

    if(in["id"].asInt()) {
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
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
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
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
        }
    }
}

void save_clarity(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in)
{
    printJson(in);
    auto accessory_table = sqlb::ObjectIdentifier("material", "clarity", "cl");

    if(in["id"].asInt()) {
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
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
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
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
        }
    }
}

void save_shape(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in)
{
    printJson(in);
    auto accessory_table = sqlb::ObjectIdentifier("material", "shape", "sh");

    if(in["id"].asInt()) {
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
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
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
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
        }
    }
}

void save_d_color(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in)
{
    printJson(in);
    auto accessory_table = sqlb::ObjectIdentifier("material", "diamond_color", "c");

    if(in["id"].asInt()) {
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
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
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
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
        }
    }
}
void save_cs_color(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in)
{
    printJson(in);
    auto accessory_table = sqlb::ObjectIdentifier("material", "cs_color", "c");

    if(in["id"].asInt()) {
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
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
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
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
        }
    }
}
void save_diamond_size(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in)
{
    // also update all the price of products too..
    // also update deleted size price too.



    auto size_table = sqlb::ObjectIdentifier("material", "size", "sh");
    auto size_meta_table = sqlb::ObjectIdentifier("material", "diamond_size_meta", "sm");

    // first insert size then insert on meta ...................
    auto size_name =  in["size_name"].asString();
    std::string strSqlSizeSel = "SELECT id, name FROM material.size WHERE name = $1";
    std::string strSqlSizeIns = "INSERT INTO material.size (name) VALUES ($1) RETURNING id";

    std::string strSqlSizeGet = "select dp.diamond_id, dp.clarity_id, ds.pcs, ds.post_id from product.diamond_price dp left join product.post_diamond_size ds on ds.id = dp.diamond_id where ds.shape_id = $1 and ds.color_id = $2 and ds.size_id = $3 and dp.clarity_id = $4;";
    std::string strSqlPriceUpdate = "UPDATE product.diamond_price SET (weight, total_weight, rate, price) = ROW($3, $4, $5, $6) WHERE diamond_id = $1 AND clarity_id = $2";

    auto q = "SELECT  sum(dp.total_weight), sum(dp.price) from product.post_diamond_size ds LEFT JOIN product.diamond_price dp ON (dp.diamond_id = ds.id) where ds.post_id = $1 and dp.clarity_id = $2";
    auto pc = u("product.post_clarity", "weight, price", "$3, $4", "where post_id = $1 and clarity_id = $2");

    if(in["id"].asInt()) {
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
            if(r.size() == 0) { // insert
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
            if(r3[0][0].as<int>() == 0 && r4[0][0].as<int>() == 0) {
                txn.exec_params(strSqlSizeDel, in["shape_id"].asInt(), in["color_id"].asInt(), size_id, in["clarity_id"].asInt());
            }

            // todo: if size_name is changed rename size.
            // update product weight and price:..
            struct ProductUpdate{
                int postId;
                std::vector<int> clarityId;
            };
            std::vector<ProductUpdate>productUpdate;

            auto s = txn.exec_params(strSqlSizeGet, in["shape_id"].asInt(), in["color_id"].asInt(), size_id, in["clarity_id"].asInt());
            for (auto prow : s) {
                auto w = in["weight"].asDouble();
                auto rate = in["rate"].asDouble();
                auto pcs = prow[2].as<int>();
                txn.exec_params(strSqlPriceUpdate, prow[0].as<int>(), prow[1].as<int>(), w, w * pcs, rate, pcs * w * rate);
                std::vector<ProductUpdate>::iterator it = std::find_if(productUpdate.begin(), productUpdate.end(), [&](ProductUpdate t) {
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
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
        }
    } else {
        std::string strSql = "INSERT INTO %1.%2 (clarity_id, shape_id, color_id, size_id, weight, currency_id, rate_on_id, rate) values($1, $2, $3, $4, $5, $6, $7, $8)";
        ReplaceAll2(strSql, "%1", size_meta_table.schema());
        ReplaceAll2(strSql, "%2", size_meta_table.name());


        pqxx::work txn{DD};
        try {
            int size_id;
            auto r = txn.exec_params(strSqlSizeSel, size_name);
            if(r.size() == 0) { // insert
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

            // todo: if size_name is changed rename size.
            // update product weight and price:..
            struct ProductUpdate{
                int postId;
                std::vector<int> clarityId;
            };
            std::vector<ProductUpdate>productUpdate;

            auto s = txn.exec_params(strSqlSizeGet, in["shape_id"].asInt(), in["color_id"].asInt(), size_id, in["clarity_id"].asInt());
            for (auto prow : s) {
                auto w = in["weight"].asDouble();
                auto rate = in["rate"].asDouble();
                auto pcs = prow[2].as<int>();
                txn.exec_params(strSqlPriceUpdate, prow[0].as<int>(), prow[1].as<int>(), w, w * pcs, rate, pcs * w * rate);
                std::vector<ProductUpdate>::iterator it = std::find_if(productUpdate.begin(), productUpdate.end(), [&](ProductUpdate t) {
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
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
        }
    }
}
void delete_diamond_size(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in)
{
    pqxx::work txn{DD};
    try {
        auto get_row = "SELECT id, size_id FROM material.diamond_size_meta where id = $1";
        auto r = txn.exec_params(get_row, in[0].asInt());

        txn.exec_params("DELETE FROM " "material.diamond_size_meta" " WHERE id = $1", in[0].asInt());

        auto d_size_count = "SELECT count(*) FROM material.diamond_size_meta where size_id = $1";
        auto cs_size_count = "SELECT count(*) FROM material.color_stone_size_meta where size_id = $1";

        auto size_id  = r[0][1].as<int>();
        auto c1 = txn.exec_params(d_size_count, size_id);
        auto c2 = txn.exec_params(cs_size_count, size_id);
        if(c1[0][0].as<int>() == 0 && c2[0][0].as<int>() == 0) {
            txn.exec_params("DELETE FROM " "material.size" " WHERE id = $1", size_id);
        }
        txn.commit();
        simpleJsonResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
        txn.abort();
        std::cerr << e.what() << std::endl;
        simpleJsonResult(event_name, wsConnPtr, false, e.what());
    }
}
void save_color_stone_size(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in)
{
    auto size_table = sqlb::ObjectIdentifier("material", "size", "sh");
    auto size_meta_table = sqlb::ObjectIdentifier("material", "color_stone_size_meta", "sm");

    // first insert size then insert on meta ...................
    auto size_name =  in["size_name"].asString();
    std::string strSqlSizeSel = "SELECT id, name FROM material.size WHERE name = $1";
    std::string strSqlSizeIns = "INSERT INTO material.size (name) VALUES ($1) RETURNING id";



    if(in["id"].asInt()) {
        std::string strSql =
            "update %1.%2 set "
            "(shape_id, size_id, weight, currency_id, rate_on_id, rate)"
            " = ROW($2, $3, $4, $5, $6, $7) where id=$1";
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
            if(r.size() == 0) { // insert
                auto r1 = txn.exec_params(strSqlSizeIns, size_name);
                size_id = r1[0][0].as<int>();
            } else {
                size_id = r[0][0].as<int>();
            }

            auto r2 = txn.exec_params(strSqlSizeId, in["id"].asInt());
            int old_size_id = r2[0][0].as<int>();

            txn.exec_params(strSql,
                            in["id"].asInt(),
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
            if(r3[0][0].as<int>() == 0 && r4[0][0].as<int>() == 0) {
                txn.exec_params(strSqlSizeDel, old_size_id);
            }

            txn.commit();
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
        }
    } else {
        std::string strSql = "INSERT INTO %1.%2 (shape_id, size_id, weight, currency_id, rate_on_id, rate) values($1, $2, $3, $4, $5, $6)";
        ReplaceAll2(strSql, "%1", size_meta_table.schema());
        ReplaceAll2(strSql, "%2", size_meta_table.name());


        pqxx::work txn{DD};
        try {
            int size_id;
            auto r = txn.exec_params(strSqlSizeSel, size_name);
            if(r.size() == 0) { // insert
                auto r1 = txn.exec_params(strSqlSizeIns, size_name);
                size_id = r1[0][0].as<int>();
            } else {
                size_id = r[0][0].as<int>();
            }


            txn.exec_params(
                strSql,
                in["shape_id"].asInt(),
                size_id,
                in["weight"].asDouble(),
                in["currency_id"].asInt(),
                in["rate_on_id"].asString(),
                in["rate"].asDouble()
            );


            txn.commit();
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
        }
    }
}
void delete_color_stone_size(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in)
{
    pqxx::work txn{DD};
    try {
        auto get_row = "SELECT id, size_id FROM material.color_stone_size_meta where id = $1";
        auto r = txn.exec_params(get_row, in[0].asInt());

        txn.exec_params("DELETE FROM " "material.color_stone_size_meta" " WHERE id = $1", in[0].asInt());

        auto d_size_count = "SELECT count(*) FROM material.diamond_size_meta where size_id = $1";
        auto cs_size_count = "SELECT count(*) FROM material.color_stone_size_meta where size_id = $1";

        auto size_id  = r[0][1].as<int>();
        auto c1 = txn.exec_params(d_size_count, size_id);
        auto c2 = txn.exec_params(cs_size_count, size_id);
        if(c1[0][0].as<int>() == 0 && c2[0][0].as<int>() == 0) {
            txn.exec_params("DELETE FROM " "material.size" " WHERE id = $1", size_id);
        }
        txn.commit();
        simpleJsonResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
        txn.abort();
        std::cerr << e.what() << std::endl;
        simpleJsonResult(event_name, wsConnPtr, false, e.what());
    }
}
void product_tags_process(sqlb::ObjectIdentifier tags_table,
                          sqlb::ObjectIdentifier post_tag_table,
                          Json::Value &in,
                          pqxx::work &txn,
                          int post_id
                         )
{
    std::string strSqlTag = "select id, name FROM %1.%2 where name = $1";
    ReplaceAll2(strSqlTag, "%1", tags_table.schema());
    ReplaceAll2(strSqlTag, "%2", tags_table.name());

    std::string strSqlTagInsert = "INSERT INTO product.tag (name, slug, description) VALUES ($1, $2, $3)";
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

    auto inNewTags = in["tags_tags_id"].asString();
    std::vector<std::string> inNewTagsVector;
    std::stringstream ss{inNewTags};
    std::string tag;
    // 1.find a tag, if not exist then insert.
    while (ss >> tag) {
        inNewTagsVector.push_back(tag);
        pqxx::result x = txn.exec_params(strSqlTag, tag);
        if(x.size() == 0) {
            txn.exec_params(strSqlTagInsert, tag, tag, tag);
        }
    }
    pqxx::result all_pt = txn.exec_params(strSqlPostTags, post_id);
    // For each saved tags, If saved tag not exist in new tags, delete it.
    for (auto r : all_pt) {
        if(inNewTags.find(r[2].c_str()) == std::string::npos) {
            txn.exec_params(strSqlPostTagsDel, r[0].as<int>(), r[1].as<int>());
        }
    }
    // For each new tags, insert it if it not already exist.
    for (auto r : inNewTagsVector) {
        pqxx::result x = txn.exec_params(strSqlTag, r);

        pqxx::result y = txn.exec_params(strSqlPostTagSimpleFind, post_id, x[0]["id"].as<int>());
        if(y.size() == 0) {
            txn.exec_params(strSqlPostTagsInsert, post_id, x[0][0].as<int>());
        }
    }
}

void save_product_categories(sqlb::ObjectIdentifier post_category_table,
                             Json::Value &in,
                             pqxx::work &txn,
                             int post_id)
{
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

    std::vector<int>inNewCategories;
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
        if(y.size() == 0) {
            txn.exec_params(strSqlPostCategoryInsert, post_id, x);
            //auto it = std::find(inNewCategories.begin(), inNewCategories.end(), x);
            //if (it == inNewCategories.end()) updatedCategories.push_back(x);
        }
    }
}
#define purejoinTableSave(f, t, inKey, id1, id2)\
void save_product_##f(Json::Value &in, pqxx::work &txn, int idv1){\
    std::string strSqlPostCategories = "SELECT " id1 ", " id2 " FROM " t " where " id1 " = $1";\
    std::string strSqlPostCategorySimpleFind = "SELECT * FROM " t " WHERE " id1 " = $1 and " id2 " = $2";\
    std::string strSqlPostCategoryDel = "DELETE FROM " t " WHERE " id1 " = $1 and " id2 " = $2";\
    std::string strSqlPostCategoryInsert = "INSERT INTO " t " (" id1 ", " id2 ") VALUES ($1, $2);";\
    std::vector<int>inNewTones;\
    for (auto i : in[ inKey ]) {\
        if (!i.isNull()) inNewTones.push_back(i.asInt());\
    }\
    \
    pqxx::result all_ct = txn.exec_params(strSqlPostCategories, idv1);\
    /* For each saved tones, If saved tone not exist in new tones, delete it.*/\
    for (auto r : all_ct) {\
        std::vector<int>::iterator it = std::find(inNewTones.begin(), inNewTones.end(), r[1].as<int>());\
        if (it == inNewTones.end()) {/* Element not Found*/\
            txn.exec_params(strSqlPostCategoryDel, r[0].as<int>(), r[1].as<int>());\
        }\
    }\
    /* For each new tones, insert it if it not already exist.*/\
    for (auto x : inNewTones) {\
        pqxx::result y = txn.exec_params(strSqlPostCategorySimpleFind, idv1, x);\
        if(y.size() == 0) {\
            txn.exec_params(strSqlPostCategoryInsert, idv1, x);\
        }\
    }\
}

purejoinTableSave(tones, "product.post_tone", "p_tones_tone_id", "post_id", "tone_id" );
purejoinTableSave(certified_by, "product.post_certified_by", "p_certified_by_certified_by", "post_id", "certified_by_id" );

void save_product_clarities(sqlb::ObjectIdentifier post_clarity_table,
                            Json::Value &in,
                            pqxx::work &txn,
                            int post_id)
{
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
    std::vector<PostClarity>inVector;
    for (auto i : in["p_clarity_clarity_id"]) { // purity_id, weight, price
        if (!i[0].isNull()) inVector.push_back({i[0].asInt(), i[1].asInt(), i[2].asDouble(), i[3].asDouble(), i[4].asBool()});
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
        if(y.size() == 0) {
            txn.exec_params(strSqlPostCategoryInsert, post_id, r.clarity_id, r.pcs, r.weight, r.price, r.ismain);
        } else { // update
            if(y[0][1].as<int>() != r.clarity_id || y[0][2].as<int>() != r.pcs || y[0][3].as<double>() != r.weight || y[0][4].as<double>() != r.price || y[0][5].as<bool>() != r.ismain) {
                txn.exec_params(strSqlPostCategoryUpdateAtt, post_id, r.clarity_id, r.pcs, r.weight, r.price, r.ismain);
            }
        }
    }
}
void save_purity_tone_(Json::Value &in, pqxx::work &txn, int post_id, int purity_id)
{
    std::string strSqlPostCategories = s("product.purity_tone", "post_id, purity_id, tone_id", "where post_id = $1 and purity_id = $2");
    std::string strSqlPostCategorySimpleFind = s("product.purity_tone", "post_id, purity_id, tone_id", "where post_id = $1 and purity_id = $2 and tone_id = $3");
    std::string strSqlPostCategoryDel = de("product.purity_tone", "where post_id = $1 and purity_id = $2 and tone_id = $3");
    std::string strSqlPostCategoryInsert = i("product.purity_tone", "post_id, purity_id, tone_id", "$1, $2, $3");
    //std::string strSqlPostCategoryUpdateAtt = u("product.purity_tone", "post_id, purity_id, tone_id", "$1, $2, $3", "where  post_id = $1 and purity_id = $2 and tone_id = $3");

    struct PurityTone {
        int post_id;
        int purity_id;
        int tone_id;
    };
    std::vector<PurityTone>inNewPrice; // post_id, purity_id, tone_id
    for (auto i : in) {
        if(!i.isNull()) { // to pass null row
            inNewPrice.push_back({post_id, purity_id, i.asInt()});
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
        if(y.size() == 0) { // insert
            txn.exec_params(strSqlPostCategoryInsert, post_id, r.purity_id, r.tone_id);
        } else { // no update needed
            //if(y[0][1].as<int>() != r.shape_id || y[0][2].as<int>() != r.color_id || y[0][3].c_str() != r.dsize || y[0][4].as<int>() != r.pcs || y[0][5].as<double>() != r.price) {
            //txn.exec_params(strSqlPostCategoryUpdateAtt, post_id, r.weight, r.total_weight, r.rate, r.price);
            //}
        }
    }
}
void save_product_purities(sqlb::ObjectIdentifier post_purity_table,
                           Json::Value &in,
                           pqxx::work &txn,
                           int post_id)
{
    std::string strSqlPostCategories = "SELECT purity_id FROM %1.%2 where post_id = $1";
    ReplaceAll2(strSqlPostCategories, "%1", post_purity_table.schema());
    ReplaceAll2(strSqlPostCategories, "%2", post_purity_table.name());

    std::string strSqlPostCategorySimpleFind = "SELECT purity_id, weight, price FROM %1.%2 WHERE post_id = $1 and purity_id = $2";
    ReplaceAll2(strSqlPostCategorySimpleFind, "%1", post_purity_table.schema());
    ReplaceAll2(strSqlPostCategorySimpleFind, "%2", post_purity_table.name());


    std::string strSqlPostCategoryDel = "DELETE FROM %1.%2 WHERE post_id = $1 and purity_id = $2";
    ReplaceAll2(strSqlPostCategoryDel, "%1", post_purity_table.schema());
    ReplaceAll2(strSqlPostCategoryDel, "%2", post_purity_table.name());

    std::string strSqlPostCategoryInsert = "INSERT INTO %1.%2 (post_id, purity_id, weight, price) VALUES ($1, $2, $3, $4);";
    ReplaceAll2(strSqlPostCategoryInsert, "%1", post_purity_table.schema());
    ReplaceAll2(strSqlPostCategoryInsert, "%2", post_purity_table.name());

    std::string strSqlPostCategoryUpdateAtt = "UPDATE product.post_purity SET (weight, price) = ROW($3, $4) WHERE post_id = $1 and purity_id = $2";


    struct PostPurity {
        int purity_id;
        double weight;
        double price;
        Json::Value tones;
    };

    std::vector<PostPurity>inVector;
    for (auto i : in["p_purities_purity_id"]) { // purity_id, weight, price, tones
        if (!i[0].isNull()) inVector.push_back({i[0].asInt(), i[1].asDouble(), i[2].asDouble(), i[3]});
    }

    pqxx::result all_ct = txn.exec_params(strSqlPostCategories, post_id);
    // For each saved tones, If saved tone not exist in new tones, delete it.
    for (auto r : all_ct) {
        std::vector<PostPurity>::iterator it = std::find_if(inVector.begin(), inVector.end(), [&](PostPurity t) {
            return t.purity_id == r[0].as<int>();
        });
        if (it == inVector.end()) {// Element not Found
            txn.exec_params("DELETE FROM product.purity_tone WHERE post_id = $1 and purity_id = $2", post_id, r[0].as<int>());
            txn.exec_params(strSqlPostCategoryDel, post_id, r[0].as<int>());
        }
    }
    // For each new tones, insert it if it not already exist.
    for (auto r : inVector) {
        pqxx::result y = txn.exec_params(strSqlPostCategorySimpleFind, post_id, r.purity_id);
        if(y.size() == 0) {
            txn.exec_params(strSqlPostCategoryInsert, post_id, r.purity_id, r.weight, r.price);
            save_purity_tone_(r.tones, txn, post_id, r.purity_id);
        } else { // update
            if(y[0][0].as<int>() != r.purity_id || y[0][1].as<double>() != r.weight || y[0][2].as<double>() != r.price) {
                txn.exec_params(strSqlPostCategoryUpdateAtt, post_id, r.purity_id, r.weight, r.price);
            }
            save_purity_tone_(r.tones, txn, post_id, r.purity_id);
        }
    }
}
void save_diamond_price(Json::Value &in, pqxx::work &txn, int diamond_id)
{
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
    std::vector<DiamondPrice>inNewPrice;
    for (auto i : in) {
        if(!i[0].isNull()) { // to pass null row
            inNewPrice.push_back({diamond_id, i[0].asInt(), i[2].asDouble(), i[3].asDouble(), i[4].asDouble(), i[5].asDouble()});
        }
    }

    pqxx::result all_ct = txn.exec_params(strSqlPostCategories, diamond_id);
    // For each saved attachments, If it not exist in new attachments, delete it.
    for (auto r : all_ct) {
        std::vector<DiamondPrice>::iterator it = std::find_if(inNewPrice.begin(), inNewPrice.end(), [&](DiamondPrice t) {
            return t.diamond_id == r[0].as<int>() && t.clarity_id == r[1].as<int>();
        });
        if (it == inNewPrice.end()) {// Element not Found
            txn.exec_params(strSqlPostCategoryDel, diamond_id, r[1].as<int>());
        }
    }
    // For each new attachments, insert it if it not already exist.
    for (auto r : inNewPrice) {
        pqxx::result y = txn.exec_params(strSqlPostCategorySimpleFind, r.diamond_id, r.clarity_id);
        if(y.size() == 0) { // insert
            txn.exec_params(strSqlPostCategoryInsert, diamond_id, r.clarity_id, r.weight, r.total_weight, r.rate, r.price);
        } else { // update
            //if(y[0][1].as<int>() != r.shape_id || y[0][2].as<int>() != r.color_id || y[0][3].c_str() != r.dsize || y[0][4].as<int>() != r.pcs || y[0][5].as<double>() != r.price) {
                txn.exec_params(strSqlPostCategoryUpdateAtt, diamond_id, r.clarity_id, r.weight, r.total_weight, r.rate, r.price);
            //}
        }
    }
}
void save_product_diamond_sizes(sqlb::ObjectIdentifier post_diamond_sizes_table,
                                Json::Value &in,
                                pqxx::work &txn,
                                int post_id)
{
    std::string strSqlPostCategories = "SELECT id, post_id, shape_id, color_id, size_id, pcs FROM product.post_diamond_size where post_id = $1";
    std::string strSqlPostCategorySimpleFind = "SELECT id, post_id, shape_id, color_id, size_id, pcs FROM product.post_diamond_size WHERE id = $1";
    std::string strSqlPostCategoryDel = "DELETE FROM product.post_diamond_size WHERE id = $1";
    std::string strSqlPostCategoryInsert = "INSERT INTO product.post_diamond_size (post_id, shape_id, color_id, size_id, pcs) VALUES ($1, $2, $3, $4, $5) RETURNING id;";
    std::string strSqlPostCategoryUpdateAtt = "UPDATE product.post_diamond_size SET (post_id, shape_id, color_id, size_id, pcs) = ROW($2, $3, $4, $5, $6) WHERE id = $1;";

    struct PostDiamondSize {
        int id;
        int shape_id;
        int color_id;
        int pcs;
        std::string dsize;
        Json::Value clarity_price;
    };
    std::vector<PostDiamondSize>inNewAttachments; // id Shape	Color	Size	Pcs
    for (auto i : in["p_d_size_diamond_size_id"]) {
        if(!i[1].isNull()) { // to pass null row
            inNewAttachments.push_back({i[0].asInt(), i[1].asInt(), i[2].asInt(), i[4].asInt(), i[3].asString(), i[5]});
        }
    }

    pqxx::result all_ct = txn.exec_params(strSqlPostCategories, post_id);
    // For each saved attachments, If it not exist in new attachments, delete it.
    for (auto r : all_ct) {
        std::vector<PostDiamondSize>::iterator it = std::find_if(inNewAttachments.begin(), inNewAttachments.end(), [&](PostDiamondSize t) {
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
        if(y.size() == 0) { // insert
            auto i = txn.exec_params(strSqlPostCategoryInsert, post_id, r.shape_id, r.color_id, r.dsize, r.pcs);
            save_diamond_price(r.clarity_price, txn, i[0][0].as<int>());
        } else { // update
            if(y[0][2].as<int>() != r.shape_id || y[0][3].as<int>() != r.color_id || y[0][4].c_str() != r.dsize || y[0][5].as<int>() != r.pcs) {
                txn.exec_params(strSqlPostCategoryUpdateAtt, r.id, post_id, r.shape_id, r.color_id, r.dsize, r.pcs);
            }
            save_diamond_price(r.clarity_price, txn, y[0][0].as<int>());
        }
    }
}
void save_cs_price(Json::Value &in, pqxx::work &txn, int cs_id)
{
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
    std::vector<DiamondPrice>inNewPrice;
    for (auto i : in) {
        if(!i[0].isNull()) { // to pass null row
            inNewPrice.push_back({cs_id, i[2].asDouble(), i[3].asDouble(), i[4].asDouble(), i[5].asDouble()});
        }
    }

    pqxx::result all_ct = txn.exec_params(strSqlPostCategories, cs_id);
    // For each saved attachments, If it not exist in new attachments, delete it.
    for (auto r : all_ct) {
        std::vector<DiamondPrice>::iterator it = std::find_if(inNewPrice.begin(), inNewPrice.end(), [&](DiamondPrice t) {
            return t.cs_id == r[0].as<int>();
        });
        if (it == inNewPrice.end()) {// Element not Found
            txn.exec_params(strSqlPostCategoryDel, cs_id, r[1].as<int>());
        }
    }
    // For each new attachments, insert it if it not already exist.
    for (auto r : inNewPrice) {
        pqxx::result y = txn.exec_params(strSqlPostCategorySimpleFind, r.cs_id);
        if(y.size() == 0) { // insert
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
                           int post_id)
{
    std::string strSqlPostCategories = "SELECT id, post_id, shape_id, color_id, size_id, pcs FROM product.post_color_stone_size where post_id = $1";
    std::string strSqlPostCategorySimpleFind = "SELECT id, post_id, shape_id, color_id, size_id, pcs FROM product.post_color_stone_size WHERE id = $1";
    std::string strSqlPostCategoryDel = "DELETE FROM product.post_color_stone_size WHERE id = $1";
    std::string strSqlPostCategoryInsert = "INSERT INTO product.post_color_stone_size (post_id, shape_id, color_id, size_id, pcs) VALUES ($1, $2, $3, $4, $5) RETURNING id;";
    std::string strSqlPostCategoryUpdateAtt = "UPDATE product.post_color_stone_size SET (post_id, shape_id, color_id, size_id, pcs) = ROW($2, $3, $4, $5, $6) WHERE id = $1;";

    struct PostDiamondSize {
        int id;
        int shape_id;
        int color_id;
        int pcs;
        std::string dsize;
        Json::Value clarity_price;
    };
    std::vector<PostDiamondSize>inNewAttachments; // id Shape	Color	Size	Pcs
    for (auto i : in["p_cs_size_cs_size_id"]) {
        if(!i[1].isNull()) { // to pass null row
            inNewAttachments.push_back({i[0].asInt(), i[1].asInt(), i[2].asInt(), i[4].asInt(), i[3].asString(), i[5]});
        }
    }

    pqxx::result all_ct = txn.exec_params(strSqlPostCategories, post_id);
    // For each saved attachments, If it not exist in new attachments, delete it.
    for (auto r : all_ct) {
        std::vector<PostDiamondSize>::iterator it = std::find_if(inNewAttachments.begin(), inNewAttachments.end(), [&](PostDiamondSize t) {
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
        if(y.size() == 0) { // insert
            auto i = txn.exec_params(strSqlPostCategoryInsert, post_id, r.shape_id, r.color_id, r.dsize, r.pcs);
            save_cs_price(r.clarity_price, txn, i[0][0].as<int>());
        } else { // update
            if(y[0][2].as<int>() != r.shape_id || y[0][3].as<int>() != r.color_id || y[0][4].c_str() != r.dsize || y[0][5].as<int>() != r.pcs) {
                txn.exec_params(strSqlPostCategoryUpdateAtt, r.id, post_id, r.shape_id, r.color_id, r.dsize, r.pcs);
            }
            save_cs_price(r.clarity_price, txn, y[0][0].as<int>());
        }
    }
}
void save_product_cs_total(sqlb::ObjectIdentifier post_cs_total_table,
                           Json::Value &in,
                           pqxx::work &txn,
                           int post_id)
{
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
    std::vector<PostCSTotal>inNewAttachments; // id Shape	Color	Size	Pcs
    for (auto i : in["p_cs_total_p_cs_total"]) {
        if(!i[1].isNull()) { // to pass null row
            inNewAttachments.push_back({post_id, i[0].asInt(), i[1].asDouble(), i[2].asDouble()});
        }
    }

    pqxx::result all_ct = txn.exec_params(strSqlPostCategories, post_id);
    // For each saved attachments, If it not exist in new attachments, delete it.
    for (auto r : all_ct) {
        std::vector<PostCSTotal>::iterator it = std::find_if(inNewAttachments.begin(), inNewAttachments.end(), [&](PostCSTotal t) {
            return t.post_id == r[0].as<int>();
        });
        if (it == inNewAttachments.end()) {// Element not Found
            txn.exec_params(strSqlPostCategoryDel, r[0].as<int>());
        }
    }
    // For each new attachments, insert it if it not already exist.
    for (auto r : inNewAttachments) {
        pqxx::result y = txn.exec_params(strSqlPostCategorySimpleFind, r.post_id);
        if(y.size() == 0) { // insert
            auto i = txn.exec_params(strSqlPostCategoryInsert, post_id, r.pcs, r.weight, r.price);
        } else { // update
            if(y[0][0].as<int>() != r.post_id || y[0][1].as<int>() != r.pcs || y[0][2].as<double>() != r.weight || y[0][3].as<double>() != r.price) {
                txn.exec_params(strSqlPostCategoryUpdateAtt, r.post_id, r.pcs, r.weight, r.price);
            }
        }
    }
}

void save_product_Attachments(sqlb::ObjectIdentifier post_attachment_table,
                              Json::Value &in,
                              pqxx::work &txn,
                              int post_id)
{
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

    std::string strSqlTempImage= "SELECT name, size, type FROM product.temp_image WHERE id = $1";
    std::string strSqlTempImageDel= "DELETE FROM product.temp_image WHERE id = $1";

    struct Attachment {
        int id;
        int tone_id;
        int temp_id;
        bool main_image;
    };
    std::vector<Attachment>inNewAttachments; // tone_id, temp_id
    for (auto i : in["p_attachments_attachement_id"]) {
        if(i[1].asInt() == 0) {
            continue;
        }
        inNewAttachments.push_back({i[0].asInt(), i[1].asInt(), i[2].asInt(), i[3].asBool()});
    }

    pqxx::result all_ct = txn.exec_params(strSqlPostCategories, post_id);
    // For each saved attachments, If it not exist in new attachments, delete it.
    for (auto r : all_ct) {
        std::vector<Attachment>::iterator it = std::find_if(inNewAttachments.begin(), inNewAttachments.end(), [&](Attachment t) {
            return t.id == r[0].as<int>();
        });
        if (it == inNewAttachments.end()) {// Element not Found
            txn.exec_params(strSqlPostCategoryDel, r[0].as<int>());
        }
    }
    // For each new attachments, insert it if it not already exist.
    for (auto r : inNewAttachments) {
        pqxx::result y = txn.exec_params(strSqlPostCategorySimpleFind, r.id);
        if(y.size() == 0) { // insert
            auto temp_id = r.temp_id;
            if (temp_id != 0) {
                pqxx::result z = txn.exec_params(strSqlTempImage, temp_id);
                if(z.size() == 1) {
                    txn.exec_params(strSqlPostCategoryInsert, post_id, r.tone_id, z[0][0].c_str(), z[0][1].as<int>(), z[0][2].c_str(), r.main_image);
                    txn.exec_params(strSqlTempImageDel, temp_id);
                }
            }
        } else { // update
            if(y[0][2].as<int>() != r.tone_id || y[0][3].as<bool>() != r.main_image || r.temp_id != 0) { // can also update image
                auto temp_id = r.temp_id;
                if (temp_id != 0) {
                    pqxx::result z = txn.exec_params(strSqlTempImage, temp_id);
                    if(z.size() == 1) {
                        txn.exec_params(strSqlPostCategoryUpdateAtt, y[0][0].as<int>(), r.tone_id, z[0][0].c_str(), z[0][1].as<int>(), z[0][2].c_str(), r.main_image);
                        txn.exec_params(strSqlTempImageDel, temp_id);
                    }
                } else {
                    txn.exec_params(strSqlPostCategoryUpdate, r.id, r.tone_id, r.main_image);
                }

            }
        }
    }
}

void save_product(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in)
{
    printJson(in);
    auto product_table = sqlb::ObjectIdentifier("product", "product", "p");
    auto post_table = sqlb::ObjectIdentifier("product", "post", "p");
    auto tags_table = sqlb::ObjectIdentifier("product", "tag", "t");
    auto post_tag_table = sqlb::ObjectIdentifier("product", "post_tag", "pt");
    auto post_category_table = sqlb::ObjectIdentifier("product", "post_category", "pt");
    auto post_tone_table = sqlb::ObjectIdentifier("product", "post_tone", "p_tones");
    auto post_clarity_table = sqlb::ObjectIdentifier("product", "post_clarity", "p_clarity");
    auto post_purity_table = sqlb::ObjectIdentifier("product", "post_purity", "p_purities");
    auto post_attachment_table = sqlb::ObjectIdentifier("product", "post_attachment", "p_attachments");
    auto post_diamond_sizes_table = sqlb::ObjectIdentifier("product", "post_diamond_size", "post_diamond_sizes");
    auto post_cs_total_table = sqlb::ObjectIdentifier("product", "post_cs_total", "post_cs_total");
    auto post_certified_by = sqlb::ObjectIdentifier("product", "post_certified_by", "p_certified_by");

    if(in["id"].asInt()) {
        std::string strSqlPost =
            "update %1.%2 set "
            "(comment_status, menu_order, post_excerpt, post_content, post_title, post_name, post_password, post_status, post_date, post_type, visibility)"
            " = ROW($2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12) where id=$1";
        ReplaceAll2(strSqlPost, "%1", post_table.schema());
        ReplaceAll2(strSqlPost, "%2", post_table.name());

        std::string strSqlProduct =
            "update %1.%2 set "
            "(post_id, sku, min_price, max_price, weight, length, width, height, manage_stock, featured, stock_quantity, shipping_class_id, catalog_visibility, product_type, backorders, stock_status, virtual, downloadable, purchase_note, low_stock_amount, sold_individually, setting_type_id, making_charges, discount_per, volume, purity_id)"
            " = ROW($2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12, NULLIF($13, 0), $14, $15, $16, $17, $18, $19, $20, $21, $22, NULLIF($23, 0), $24, $25, $26, $27) where id=$1";
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
                            in["p_setting_type_id"].asInt(),
                            in["p_making_charges"].asDouble(),
                            in["p_discount_per"].asDouble(),
                            in["p_volume"].asDouble(),
                            in["p_purity_id"].asDouble()
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

            txn.commit();
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
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
                                    "(post_id, sku, min_price, max_price, weight, length, width, height, manage_stock, featured, stock_quantity, shipping_class_id, catalog_visibility, product_type, backorders, stock_status, virtual, downloadable, purchase_note, low_stock_amount, sold_individually, setting_type_id, making_charges, discount_per, volume, purity_id)"
                                    " VALUES($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11, NULLIF($12, 0), $13, $14, $15, $16, $17, $18, $19, $20, $21, NULLIF($22, 0), $23, $24, $25, $26)";
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
            auto  post_id = x[0]["id"].as<int>();

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
                in["p_setting_type_id"].asInt(),
                in["p_making_charges"].asDouble(),
                in["p_discount_per"].asDouble(),
                in["p_volume"].asDouble(),
                in["p_purity_id"].asDouble()
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
            txn.commit();
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
        }
    }
}
void delete_product(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in)
{
    printJson(in);

    pqxx::work txn{DD};
    try {
        auto post_del = "DELETE FROM product.post WHERE id = $1";
        auto product_del = "DELETE FROM product.product WHERE post_id = $1";
        //auto tags_del = "DELETE FROM product.tag  WHERE post_id = $1"; // Fix This. If Tag is not used in any product delete it
        auto post_tag_del = "DELETE FROM product.post_tag  WHERE post_id = $1";
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
        simpleJsonResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
        txn.abort();
        std::cerr << e.what() << std::endl;
        simpleJsonResult(event_name, wsConnPtr, false, e.what());
    }
}
void save_post(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in)
{
    auto post_table = sqlb::ObjectIdentifier("product", "post", "p");

    if(in["id"].asInt()) {
        std::string strSqlPost =
            "update %1.%2 set "
            "(comment_status, menu_order, post_excerpt, post_content, post_title, post_name, post_password, post_status, post_date, post_type, visibility)"
            " = ROW($2, $3, $4, $5, $6, $7, $8, $9, $10, $11, $12) where id=$1";
        ReplaceAll2(strSqlPost, "%1", post_table.schema());
        ReplaceAll2(strSqlPost, "%2", post_table.name());

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

            //product_tags_process(tags_table, post_tag_table, in, txn, post_id);
            //save_product_categories(post_category_table, in, txn, post_id);

            txn.commit();
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
        }
    } else {
        std::string strSqlPost =
            "INSERT INTO %1.%2 "
            "(comment_status, menu_order, post_excerpt, post_content, post_title, post_name, post_password, post_status, post_date, post_type, visibility)"
            " VALUES($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11)"
            "RETURNING id";
        ReplaceAll2(strSqlPost, "%1", post_table.schema());
        ReplaceAll2(strSqlPost, "%2", post_table.name());

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
            auto  post_id = x[0]["id"].as<int>();

            //product_tags_process(tags_table, post_tag_table, in, txn, post_id);
            //save_product_categories(post_category_table, in, txn, post_id);

            txn.commit();
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
        }
    }
}
void save_category(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in)
{
    printJson(in);
    auto product_table = sqlb::ObjectIdentifier("product", "category", "p");

    if(in["id"].asInt()) {
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
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
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
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
        }
    }
}

void save_tag(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in)
{
    printJson(in);
    auto product_table = sqlb::ObjectIdentifier("product", "tag", "t");

    if(in["id"].asInt()) {
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
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
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
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
        }
    }
}


void save_shipping_class(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in)
{
    printJson(in);
    auto product_table = sqlb::ObjectIdentifier("product", "shipping_class", "s");

    if(in["id"].asInt()) {
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
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
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
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
        }
    }
}

void save_setting_type(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in)
{
    printJson(in);
    auto setting_type_table = sqlb::ObjectIdentifier("product", "setting_type", "s");

    if(in["id"].asInt()) {
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
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
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
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
        }
    }
}
void save_certified_by(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in)
{
    auto setting_type_table = sqlb::ObjectIdentifier("product", "certified_by", "s");

    if(in["id"].asInt()) {
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
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
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
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
        }
    }
}

void save_product_attachment(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, std::string &message)
{
    auto session_id = std::any_cast<int>(wsConnPtr->getContext());
    auto strSql = s("setting.temp_image", "event_name, name, size, type", "where session_id = $1");
    pqxx::work txn{DD};
    try {
        auto r = txn.exec_params(strSql, session_id );
        txn.exec_params(de("setting.temp_image", "where session_id = $1"), session_id );

        // check if file exist else rename a file
        auto event_name_meta = r[0][0].c_str();

        namespace fs = boost::filesystem;
        auto home = fs::path(getenv("HOME"));

        auto name = home.string() + "/fileuploads/" + r[0][1].c_str();
        auto size = r[0][2].as<int>();
        auto type = r[0][3].c_str();


        fprintf(stdout, "%s %d %s\n", name.c_str(), size, type);
        fflush(stdout);

        // basic file operations

        std::string new_name = name;
        auto path = boost::filesystem::path(new_name);
        int i = 1;
        while(true) {
            if(boost::filesystem::exists(new_name)) {
                new_name = path.parent_path().string() + "/" + path.stem().string() + std::to_string(i) + path.extension().string();
            } else {
                break;
            }
            i++;
        }
        name = new_name;


        std::ofstream myfile;
        myfile.open (name);
        myfile << message;
        myfile.close();

        // Insert Image
        auto temp_image_table = sqlb::ObjectIdentifier("product", "temp_image", "pa");
        std::string strSql = "INSERT INTO %1.%2 (name, size, type) VALUES ($1, $2, $3) RETURNING id";
        ReplaceAll2(strSql, "%1", temp_image_table.schema());
        ReplaceAll2(strSql, "%2", temp_image_table.name());

        Json::Value jresult;
        jresult[0]=event_name_meta;
        pqxx::result insert_result = txn.exec_params(strSql, name, size, type );
        jresult[1] = insert_result[0][0].as<int>();
        //jresult[1] = e.what();
        wsConnPtr->send(jresult.toStyledString());
        txn.commit();

    } catch (const std::exception &e) {
        txn.abort();
        std::cerr << e.what() << std::endl;
    }




}
// https://wandbox.org/permlink/ESIFJiztM76Q8KvP
// https://wandbox.org/permlink/33rgXrc1TGmNeYya
std::string read_all(std::ifstream& in)
{
    in.seekg (0, std::ios::beg);
    return {std::istreambuf_iterator<char>{in}, std::istreambuf_iterator<char>{}};
}


void save_currency(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in)
{
    printJson(in);
    auto metal_purity_table = sqlb::ObjectIdentifier("setting", "currency", "c");

    if(in["id"].asInt()) {
        std::string strSql =
            "update %1.%2 set (slug, name, symbol, rounding, active) = ROW($2, $3, $4, $5, $6) where id=$1";
        ReplaceAll2(strSql, "%1", metal_purity_table.schema());
        ReplaceAll2(strSql, "%2", metal_purity_table.name());

        pqxx::work txn{DD};
        try {
            txn.exec_params(strSql,
                            in["id"].asInt(),
                            in["slug"].asString(),
                            in["name"].asString(),
                            in["symbol"].asString(),
                            in["rounding"].asDouble(),
                            in["active"].asBool()
                           );
            txn.commit();
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
        }
    } else {
        std::string strSql = "INSERT INTO %1.%2 (slug, name, symbol, rounding, active) values($1, $2, $3, $4, $5)";
        ReplaceAll2(strSql, "%1", metal_purity_table.schema());
        ReplaceAll2(strSql, "%2", metal_purity_table.name());

        pqxx::work txn{DD};
        try {
            txn.exec_params(
                strSql,
                in["slug"].asString(),
                in["name"].asString(),
                in["symbol"].asString(),
                in["rounding"].asDouble(),
                in["active"].asBool()
            );
            txn.commit();
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
        }
    }
}

void get_product_attachment(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in)
{
    // send meta_data
    Json::Value ret;
    ret[0] = "take_image_meta";
    Json::Value data;
    data[0] = event_name;
    data[1] = 0;
    ret[1] = data;
    sendAJson(wsConnPtr, ret);

    pqxx::work txn{DD};
    try {
        auto sql = "SELECT name FROM product.post_attachment WHERE id = $1";
        pqxx::result x = txn.exec_params(sql, in.asInt());
        txn.commit();
        if(x.size() == 1) {
            std::streampos size;
            // http://www.cplusplus.com/doc/tutorial/files/
            // What is the best way to read an entire file into a std::string in C++?
            // https://stackoverflow.com/questions/116038/what-is-the-best-way-to-read-an-entire-file-into-a-stdstring-in-c/116220#116220
            std::ifstream file (x[0][0].c_str(), std::ios::in|std::ios::binary|std::ios::ate);
            if (file.is_open()) {
                auto memblock = read_all(file);
                file.close();

                //std::cout << "the entire file content is in memory";
                wsConnPtr->send(memblock, WebSocketMessageType::Binary);
                //delete[] memblock;
            }
        } else {
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        }

    } catch (const std::exception &e) {
        txn.abort();
        std::cerr << e.what() << std::endl;
        //simpleJsonResult(event_name, wsConnPtr, false, e.what());
    }

    //get binary data and send.
    //wsConnPtr->send();
}

void get_diamond_price(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in)
{
    printJson(in);
    Json::Value jresult;
    jresult[0] = event_name;

    auto shape = in[1].asInt();
    auto color = in[2].asInt();
    auto size = in[3].asInt();
    auto pcs = in[4].asInt();

    fprintf(stdout, "%d %d %d\n", shape, color, size);
    fflush(stdout);

    std::string s = "{"; // clarity
    for (auto i : in[5]) {
        s += std::to_string(i[0].asInt()) + ",";
    }
    if(in[5].size() > 0) s.pop_back();
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
        //simpleJsonResult(event_name, wsConnPtr, false, e.what());
    }

    //get binary data and send.
    //wsConnPtr->send();
}
void get_cs_price(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in)
{
    Json::Value jresult;
    jresult[0] = event_name;

    auto shape = in[1].asInt();
    auto color = in[2].asInt();
    auto size = in[3].asInt();
    auto pcs = in[4].asInt();

    pqxx::work txn{DD};
    try {
        // You can't use IN (...) with arrays. You need to use an operator (ex: =, >, <, etc) and ANY/ALL
        auto sql = "SELECT weight, rate FROM material.color_stone_size_meta WHERE shape_id = $1 AND size_id = $2";
        pqxx::result x = txn.exec_params(sql, shape, size);

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
        //simpleJsonResult(event_name, wsConnPtr, false, e.what());
    }

    //get binary data and send.
    //wsConnPtr->send();
}
void get_product_category_tree_data(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in)
{
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
        //simpleJsonResult(event_name, wsConnPtr, false, e.what());
    }

    //get binary data and send.
    //wsConnPtr->send();
}
void save_address_type(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in)
{
    if(in["id"].asInt()) {
        std::string strSql = "update entity.address_type set (name) = ROW($2) where id=$1";
        pqxx::work txn{DD};
        try {
            txn.exec_params(strSql,in["id"].asInt(),in["name"].asString());
            txn.commit();
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
        }
    } else {
        std::string strSql = "INSERT INTO entity.address_type (name) values($1)";
        pqxx::work txn{DD};
        try {
            txn.exec_params(strSql,in["name"].asString());
            txn.commit();
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
        }
    }
}
void save_contact_type(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in)
{
    if(in["id"].asInt()) {
        std::string strSql = "update entity.contact_type set (name) = ROW($2) where id=$1";
        pqxx::work txn{DD};
        try {
            txn.exec_params(strSql,in["id"].asInt(),in["name"].asString());
            txn.commit();
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
        }
    } else {
        std::string strSql = "INSERT INTO entity.contact_type (name) values($1)";
        pqxx::work txn{DD};
        try {
            txn.exec_params(strSql,in["name"].asString());
            txn.commit();
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
        }
    }
}
void save_entity_type(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in)
{
    if(in["id"].asInt()) {
        std::string strSql = "update entity.entity_type set (name) = ROW($2) where id=$1";
        pqxx::work txn{DD};
        try {
            txn.exec_params(strSql,in["id"].asInt(),in["name"].asString());
            txn.commit();
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
        }
    } else {
        std::string strSql = "INSERT INTO entity.entity_type (name) values($1)";
        pqxx::work txn{DD};
        try {
            txn.exec_params(strSql,in["name"].asString());
            txn.commit();
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
        }
    }
}
void save_Entity_Address(Json::Value &in,
                            pqxx::work &txn,
                            int entity_id)
{
    std::string strSqlPostCategories = "SELECT id FROM entity.entity_address where entity_id = $1";
    std::string strSqlPostCategorySimpleFind = "SELECT address_type_id, line1, line2, line3, city, state, country, zipcode, phone FROM entity.entity_address WHERE id = $1";
    std::string strSqlPostCategoryDel = "DELETE FROM entity.entity_address WHERE id = $1";
    std::string strSqlPostCategoryInsert = "INSERT INTO entity.entity_address (	entity_id, address_type_id, line1, line2, line3, city, state, country, zipcode, phone) VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10);";
    std::string strSqlPostCategoryUpdateAtt = "UPDATE entity.entity_address SET ( address_type_id, line1, line2, line3, city, state, country, zipcode, phone) = ROW($2, $3, $4, $5, $6, $7, $8, $9, $10) WHERE id = $1";

    struct EntityAddress {
        int id;
        int addess_type_id;
        std::string line1;
        std::string line2;
        std::string line3;
        std::string city;
        std::string state;
        std::string country;
        std::string zipcode;
        std::string phone;
    };
    std::vector<EntityAddress>inVector;
    for (auto i : in["ea_entity_address"]) { 	// ea.id, ea.address_type_id, ea.line1, ea.line2, ea.line3, ea.city, ea.state, ea.country, ea.zipcode, ea.phone
        if (!i[1].isNull()) inVector.push_back({i[0].asInt(), i[1].asInt(), i[2].asString(), i[3].asString(), i[4].asString(), i[5].asString(), i[6].asString(), i[7].asString(), i[8].asString(), i[9].asString()});
    }

    pqxx::result all_ct = txn.exec_params(strSqlPostCategories, entity_id);
    // For each saved tones, If saved tone not exist in new tones, delete it.
    for (auto r : all_ct) {
        std::vector<EntityAddress>::iterator it = std::find_if(inVector.begin(), inVector.end(), [&](EntityAddress t) {
            return t.id == r[0].as<int>();
        });
        if (it == inVector.end()) {// Element not Found
            txn.exec_params(strSqlPostCategoryDel, r[0].as<int>());
        }
    }
    // For each new tones, insert it if it not already exist.
    for (auto r : inVector) {
        pqxx::result y = txn.exec_params(strSqlPostCategorySimpleFind, r.id);
        if(y.size() == 0) {
            txn.exec_params(strSqlPostCategoryInsert, entity_id, r.addess_type_id, r.line1, r.line2, r.line3, r.city, r.state, r.country, r.zipcode, r.phone );
        } else { // update
            //if(y[0][0].as<int>() != r.addess_type_id || y[0][2].as<int>() != r.pcs || y[0][3].as<double>() != r.weight || y[0][4].as<double>() != r.price || y[0][5].as<bool>() != r.ismain) {
                txn.exec_params(strSqlPostCategoryUpdateAtt, r.id, r.addess_type_id, r.line1, r.line2, r.line3, r.city, r.state, r.country, r.zipcode, r.phone );
            //}
        }
    }
}

void save_entity(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in)
{
    if(in["id"].asInt()) {
        std::string strSql = "update entity.entity set (  entity_type_id, no, sequence_id, slug, parent_id, legal_name, tax_no, first_name, middle_name, last_name, birth_date, start_date, end_date, salary, rate, active, pay_to_name, threshold, credit_limit, terms, discount, discount_terms, discount_account_id, ar_ap_account_id, cash_account_id, currency_id, price_group_id, tax_included, email)"
                             " = ROW($2, $3, NULLIF($4, 0), $5, NULLIF($6, 0), $7, $8, $9, $10, $11, $12, NULLIF($13, '')::date, NULLIF($14, '')::date, $15, $16, $17, $18, $19, $20, $21, $22, $23, NULLIF($24, 0), NULLIF($25, 0), NULLIF($26, 0), NULLIF($27, 0), NULLIF($28, 0), $29, $30) where id=$1";
        pqxx::work txn{DD};
        try {
            txn.exec_params(strSql,
                            in["id"].asInt(),
                            in["entity_type_id"].asInt(),
                            in["no"].asString(),
                            in["sequence_id"].asInt(),
                            in["slug"].asString(),
                            in["parent_id"].asInt(),
                            in["legal_name"].asString(),
                            in["tax_no"].asString(),
                            in["first_name"].asString(),
                            in["middle_name"].asString(),
                            in["last_name"].asString(),
                            in["birth_date"].asString(),
                            in["start_date"].asString(),
                            in["end_date"].asString(),
                            in["salary"].asDouble(),
                            in["rate"].asDouble(),
                            in["active"].asBool(),
                            in["pay_to_name"].asString(),
                            in["threshold"].asDouble(),
                            in["credit_limit"].asDouble(),
                            in["terms"].asInt(),
                            in["discount"].asInt(),
                            in["discount_terms"].asInt(),
                            in["discount_account_id"].asInt(),
                            in["ar_ap_account_id"].asInt(),
                            in["cash_account_id"].asInt(),
                            in["currency_id"].asInt(),
                            in["price_group_id"].asInt(),
                            in["tax_included"].asBool(),
                            in["email"].asString()
//                            in["create_user_id"].asInt(),
//                            in["update_user_id"].asInt(),
//                            in["inserted_at"]          timestamp,
//                            in["updated_at"]           timestamp,
                            );
            auto entity_id = in["id"].asInt();
            std::string strSqlUser = "UPDATE entity.entity_user set (username, password, password_hash) = ROW($2, $3, $4) where entity_id = $1";
            txn.exec_params(strSqlUser, entity_id, in["email"].asString(), in["eu_password"].asString(), in["eu_password"].asString());
            save_Entity_Address(in, txn, entity_id);

            txn.commit();
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
        }
    } else {
        std::string strSql = "INSERT INTO entity.entity (  entity_type_id, no, sequence_id, slug, parent_id, legal_name, tax_no, first_name, middle_name, last_name, birth_date, start_date, end_date, salary, rate, active, pay_to_name, threshold, credit_limit, terms, discount, discount_terms, discount_account_id, ar_ap_account_id, cash_account_id, currency_id, price_group_id, tax_included, email) "
                             "values($1, $2, NULLIF($3, 0), $4, NULLIF($5, 0), $6, $7, $8, $9, $10, $11, NULLIF($12, '')::date, NULLIF($13, '')::date, $14, $15, $16, $17, $18, $19, $20, $21, $22, NULLIF($23, 0), NULLIF($24, 0), NULLIF($25, 0), NULLIF($26, 0), NULLIF($27, 0), $28, $29) returning id";
        pqxx::work txn{DD};
        try {
            auto x = txn.exec_params(strSql,
                            in["entity_type_id"].asInt(),
                            in["no"].asString(),
                            in["sequence_id"].asInt(),
                            in["slug"].asString(),
                            in["parent_id"].asInt(),
                            in["legal_name"].asString(),
                            in["tax_no"].asString(),
                            in["first_name"].asString(),
                            in["middle_name"].asString(),
                            in["last_name"].asString(),
                            in["birth_date"].asString(),
                            in["start_date"].asString(),
                            in["end_date"].asString(),
                            in["salary"].asDouble(),
                            in["rate"].asDouble(),
                            in["active"].asBool(),
                            in["pay_to_name"].asString(),
                            in["threshold"].asDouble(),
                            in["credit_limit"].asDouble(),
                            in["terms"].asInt(),
                            in["discount"].asInt(),
                            in["discount_terms"].asInt(),
                            in["discount_account_id"].asInt(),
                            in["ar_ap_account_id"].asInt(),
                            in["cash_account_id"].asInt(),
                            in["currency_id"].asInt(),
                            in["price_group_id"].asInt(),
                            in["tax_included"].asBool(),
                            in["email"].asString()
                            //                            in["create_user_id"].asInt(),
                            //                            in["update_user_id"].asInt(),
                            //                            in["inserted_at"]          timestamp,
                            //                            in["updated_at"]           timestamp,
                            );
            auto entity_id = x[0][0].as<int>();
            std::string strSqlUser = "INSERT INTO entity.entity_user (entity_id, username, password, password_hash) = ROW($1, $2, $3, $4)";
            txn.exec_params(strSqlUser, entity_id, in["email"].asString(), in["eu_password"].asString(), in["eu_password"].asString());
            save_Entity_Address(in, txn, entity_id);


            txn.commit();
            simpleJsonResult(event_name, wsConnPtr, true, "Done");
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            simpleJsonResult(event_name, wsConnPtr, false, e.what());
        }
    }
}
void delete_entity(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in)
{
    pqxx::work txn{DD};
    try {
        auto entity_id = in[0].asInt();
        txn.exec_params(de("setting.notification", "where from_entity_id = $1"), entity_id);
        txn.exec_params(de("setting.notification", "where to_entity_id = $1"), entity_id);

        txn.exec_params(de("entity.entity_bank_account", "where entity_id = $1"), entity_id);
        txn.exec_params(de("entity.entity_contact", "where entity_id = $1"), entity_id);
        txn.exec_params(de("entity.entity_file", "where entity_id = $1"), entity_id);
        txn.exec_params(de("entity.entity_image", "where entity_id = $1"), entity_id);
        txn.exec_params(de("entity.entity_note", "where entity_id = $1"), entity_id);
        txn.exec_params(de("entity.entity_address", "where entity_id = $1"), entity_id);
        txn.exec_params(de("entity.entity_user", "where entity_id = $1"), entity_id);   // This cant be deleted easily, set the table where it used null values or deleted user... 2. Also it is used in same entity table too.!
        txn.exec_params(de("entity.entity", "where id = $1"), entity_id);
        txn.commit();
        simpleJsonResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
        txn.abort();
        std::cerr << e.what() << std::endl;
        simpleJsonResult(event_name, wsConnPtr, false, e.what());
    }
}
int get_serial_no(){
    pqxx::work txn{DD};
    try {
        auto sql = "select nextval('setting.session_id_seq')";
        pqxx::result x = txn.exec_params(sql);
        txn.commit();
        return x[0][0].as<int>();
    } catch (const std::exception &e) {
        txn.abort();
        std::cerr << e.what() << std::endl;
        return 0;
        //simpleJsonResult(event_name, wsConnPtr, false, e.what());
    }
}
void admin_login(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in)
{
//    Json::Value jresult;
//    jresult[0] = event_name;

    auto sql = "select e.id from entity.entity e left join entity.entity_user as u on u.entity_id = e.id where e.email = $1 and u.password = $2";
    pqxx::work txn{DD};
    try {
        auto r = txn.exec_params( sql, in["email"].asString(), in["pass"].asString() );

        if(r.size() == 1){

            Json::Value j;
            j["value"] = r[0][0].as<int>();
            auto sqlSession = "INSERT INTO setting.session (key, value) VALUES ($1, $2) returning id";
            // To serialize the Json::Value into a Json document, you should use a Json writer, or Json::Value::toStyledString().
            LOG_INFO << j.toStyledString();
            auto rs = txn.exec_params( sqlSession, "admin",  j.toStyledString());
            simpleJsonResult(event_name, wsConnPtr, true, "Done");

            // ask to save cookie
            Json::Value jresult;
            jresult[0]="set_cookie";
            Json::Value cookie_value;
            //auto s = get_serial_no();
            cookie_value["admin"]=rs[0][0].as<int>();
            jresult[1]=cookie_value;
            wsConnPtr->send(jresult.toStyledString());

            wsConnPtr->setContext(rs[0][0].as<int>());

        } else {
            simpleJsonResult(event_name, wsConnPtr, false, "Error");
        }
        txn.commit();
    } catch (const std::exception &e) {
        txn.abort();
        std::cerr << e.what() << std::endl;
        simpleJsonResult(event_name, wsConnPtr, false, e.what());
    }
}
void admin_logout(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in)
{
    deleteSession(wsConnPtr);
    simpleJsonResult(event_name, wsConnPtr, true, "Done");


}
void is_admin_auth(const std::string &event_name, const WebSocketConnectionPtr& wsConnPtr, Json::Value in)
{
    Json::Value jresult;
    jresult[0] = event_name;
    auto c = std::any_cast<int>(wsConnPtr->getContext());
    if(c != 0){jresult[1] = true;} else {jresult[1] = false;}
    wsConnPtr->send(jresult.toStyledString());
}
