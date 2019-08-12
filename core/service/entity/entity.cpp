#include "entity.h"
#include "../../strfns.h"
#include "../../jsonfns.h"


typedef sqlb::SelectedColumn S;
Entity::Entity(const WebSocketConnectionPtr& wsConnPtr): wsConnPtr(wsConnPtr)
{
    t.m_table = sqlb::ObjectIdentifier("entity", "entity", "e");

}

void Entity::setupTable()
{
    t.m_query = sqlb::Query(t.m_table);

    //m_query.setRowIdColumn("id");
    t.m_query.selectedColumns() = {
        S({"id", "id", "", "e", PG_TYPES::INT8}),
        S({"Entity Type", "entity_type_id", "", "e", PG_TYPES::INT8, true, 1, 1}),
        sqlb::SelectedColumn({"et_name", "name", "", "et", PG_TYPES::TEXT, false, 0, 0, false}),
        S({"no", "no", "", "e", PG_TYPES::TEXT}),
        S({"sequence_id", "sequence_id", "", "e", PG_TYPES::INT8, false}),
        S({"Code", "slug", "", "e", PG_TYPES::TEXT}),
        S({"Parent", "parent_id", "", "e", PG_TYPES::INT8}),
        S({"Legal Name", "legal_name", "", "e", PG_TYPES::TEXT}),
        S({"tax_no", "tax_no", "", "e", PG_TYPES::TEXT}),
        S({"First Name", "first_name", "", "e", PG_TYPES::TEXT}),
        S({"Middle Name", "middle_name", "", "e", PG_TYPES::TEXT}),
        S({"Last Name", "last_name", "", "e", PG_TYPES::TEXT}),
        S({"Birth Date", "birth_date", "", "e", PG_TYPES::TIMESTAMP}),
        S({"Start Date", "start_date", "", "e", PG_TYPES::TIMESTAMP}),
        S({"End Date", "end_date", "", "e", PG_TYPES::TIMESTAMP}),
        S({"Salary", "salary", "", "e", PG_TYPES::DOUBLE, false}),
        S({"Rate", "rate", "", "e", PG_TYPES::DOUBLE, false}),
        S({"Active", "active", "", "e", PG_TYPES::BOOL}),
        S({"Pay To Name", "pay_to_name", "", "e", PG_TYPES::TEXT}),
        S({"Threshold", "threshold", "", "e", PG_TYPES::DOUBLE}),
        S({"Credit Limit", "credit_limit", "", "e", PG_TYPES::DOUBLE}),
        S({"Terms", "terms", "", "e", PG_TYPES::INT4}),
        S({"Discount", "discount", "", "e", PG_TYPES::DOUBLE}),
        S({"Discount Terms", "discount_terms", "", "e", PG_TYPES::INT4}),
        S({"discount_account_id", "discount_account_id", "", "e", PG_TYPES::INT8, false}),
        S({"ar_ap_account_id", "ar_ap_account_id", "", "e", PG_TYPES::INT8, false}),
        S({"cash_account_id", "cash_account_id", "", "e", PG_TYPES::INT8, false}),
        S({"currency_id", "currency_id", "", "e", PG_TYPES::INT8, false}),
        S({"price_group_id", "price_group_id", "", "e", PG_TYPES::INT8, false}),
        S({"tax_included", "tax_included", "", "e", PG_TYPES::BOOL, false}),
        S({"Email", "email", "", "e", PG_TYPES::TEXT, true}),
        S({"Password", "password", "", "eu", PG_TYPES::TEXT, true}),


        //S({"Created By", "create_user_id", "", "e", PG_TYPES::INT8, true, 1, 0, false}), S({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
        //S({"Updated By", "update_user_id", "", "e", PG_TYPES::INT8, true, 1, 0, false}), S({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
        //S({"Create Time", "inserted_at", "", "e", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
        //S({"Update Time", "updated_at", "", "e", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
        S({"Addresses", "entity_address",
           "json_agg(distinct jsonb_build_array(ea.id, ea.address_type_id, ea.line1, ea.line2, ea.line3, ea.city, ea.state, ea.country, ea.zipcode, ea.phone, ea.ismain ))",
           "ea", PG_TYPES::PSJSON, true})
    };
    auto entity_type = sqlb::ObjectIdentifier("entity", "entity_type", "et");
    auto entity_address = sqlb::ObjectIdentifier("entity", "entity_address", "ea");
    auto entity_user = sqlb::ObjectIdentifier("entity", "entity_user", "eu");
    auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
    auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

        t.m_query.joins() = {
            sqlb::Join("inner", entity_type, "et.id = e.entity_type_id"),
            sqlb::Join("left", entity_address, "ea.entity_id = e.id"),
            sqlb::Join("left", entity_user, "eu.entity_id = e.id"),
            sqlb::Join("left", u1, "e.create_user_id = u1.id"),
            sqlb::Join("left", u2, "e.update_user_id = u2.id"),
            };
    t.m_query.groupBy() = {
        sqlb::GroupByColumn("et", "id"),
        sqlb::GroupByColumn("e", "id"),
        sqlb::GroupByColumn("eu", "id"),
        };
}

HANDLEEVENT(Entity)

HEADERDATA(Entity)
ALLDATA(Entity)

void save_Entity_Address(Json::Value &args,
                             pqxx::work &txn,
                             int entity_id) {
    std::string strSqlPostCategories = "SELECT id FROM entity.entity_address where entity_id = $1";
    std::string strSqlPostCategorySimpleFind = "SELECT address_type_id, line1, line2, line3, city, state, country, zipcode, phone, ismain FROM entity.entity_address WHERE id = $1";
    std::string strSqlPostCategoryDel = "DELETE FROM entity.entity_address WHERE id = $1";
    std::string strSqlPostCategoryInsert = "INSERT INTO entity.entity_address (	entity_id, address_type_id, line1, line2, line3, city, state, country, zipcode, phone, ismain) VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11);";
    std::string strSqlPostCategoryUpdateAtt = "UPDATE entity.entity_address SET ( address_type_id, line1, line2, line3, city, state, country, zipcode, phone, ismain) = ROW($2, $3, $4, $5, $6, $7, $8, $9, $10, $11) WHERE id = $1";

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
        bool ismain;
    };
    std::vector<EntityAddress> inVector;
    for (auto i : args["ea_entity_address"]) {    // ea.id, ea.address_type_id, ea.line1, ea.line2, ea.line3, ea.city, ea.state, ea.country, ea.zipcode, ea.phone
        if (!i[1].isNull())
            inVector.push_back(
                {i[0].asInt(), i[1].asInt(), i[2].asString(), i[3].asString(), i[4].asString(), i[5].asString(),
                 i[6].asString(), i[7].asString(), i[8].asString(), i[9].asString(), i[10].asBool()});
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
        if (y.size() == 0) {
            txn.exec_params(strSqlPostCategoryInsert, entity_id, r.addess_type_id, r.line1, r.line2, r.line3, r.city,
                            r.state, r.country, r.zipcode, r.phone, r.ismain);
        } else { // update
            //if(y[0][0].as<int>() != r.addess_type_id || y[0][2].as<int>() != r.pcs || y[0][3].as<double>() != r.weight || y[0][4].as<double>() != r.price || y[0][5].as<bool>() != r.ismain) {
            txn.exec_params(strSqlPostCategoryUpdateAtt, r.id, r.addess_type_id, r.line1, r.line2, r.line3, r.city,
                            r.state, r.country, r.zipcode, r.phone, r.ismain);
            //}
        }
    }
}
Json::Value Entity::save( Json::Value event, Json::Value args) {
    if (args["id"].asInt()) {
        std::string strSql = "update entity.entity set (  entity_type_id, no, sequence_id, slug, parent_id, legal_name, tax_no, first_name, middle_name, last_name, birth_date, start_date, end_date, salary, rate, active, pay_to_name, threshold, credit_limit, terms, discount, discount_terms, discount_account_id, ar_ap_account_id, cash_account_id, currency_id, price_group_id, tax_included, email)"
                             " = ROW($2, $3, NULLIF($4, 0), $5, NULLIF($6, 0), $7, $8, $9, $10, $11, $12, NULLIF($13, '')::date, NULLIF($14, '')::date, $15, $16, $17, $18, $19, $20, $21, $22, $23, NULLIF($24, 0), NULLIF($25, 0), NULLIF($26, 0), NULLIF($27, 0), NULLIF($28, 0), $29, $30) where id=$1";
        pqxx::work txn{DD};
        try {
            txn.exec_params(strSql,
                            args["id"].asInt(),
                            args["entity_type_id"].asInt(),
                            args["no"].asString(),
                            args["sequence_id"].asInt(),
                            args["slug"].asString(),
                            args["parent_id"].asInt(),
                            args["legal_name"].asString(),
                            args["tax_no"].asString(),
                            args["first_name"].asString(),
                            args["middle_name"].asString(),
                            args["last_name"].asString(),
                            args["birth_date"].asString(),
                            args["start_date"].asString(),
                            args["end_date"].asString(),
                            args["salary"].asDouble(),
                            args["rate"].asDouble(),
                            args["active"].asBool(),
                            args["pay_to_name"].asString(),
                            args["threshold"].asDouble(),
                            args["credit_limit"].asDouble(),
                            args["terms"].asInt(),
                            args["discount"].asInt(),
                            args["discount_terms"].asInt(),
                            args["discount_account_id"].asInt(),
                            args["ar_ap_account_id"].asInt(),
                            args["cash_account_id"].asInt(),
                            args["currency_id"].asInt(),
                            args["price_group_id"].asInt(),
                            args["tax_included"].asBool(),
                            args["email"].asString()
                            //                            args["create_user_id"].asInt(),
                            //                            args["update_user_id"].asInt(),
                            //                            args["inserted_at"]          timestamp,
                            //                            args["updated_at"]           timestamp,
                            );
            auto entity_id = args["id"].asInt();
            std::string strSqlUser = "UPDATE entity.entity_user set (username, password, password_hash) = ROW($2, $3, $4) where entity_id = $1";
            txn.exec_params(strSqlUser, entity_id, args["email"].asString(), args["eu_password"].asString(),
                            args["eu_password"].asString());
            save_Entity_Address(args, txn, entity_id);

            txn.commit();
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
        }
        } else {
        std::string strSql = "INSERT INTO entity.entity (  entity_type_id, no, sequence_id, slug, parent_id, legal_name, tax_no, first_name, middle_name, last_name, birth_date, start_date, end_date, salary, rate, active, pay_to_name, threshold, credit_limit, terms, discount, discount_terms, discount_account_id, ar_ap_account_id, cash_account_id, currency_id, price_group_id, tax_included, email) "
                             "values($1, $2, NULLIF($3, 0), $4, NULLIF($5, 0), $6, $7, $8, $9, $10, $11, NULLIF($12, '')::date, NULLIF($13, '')::date, $14, $15, $16, $17, $18, $19, $20, $21, $22, NULLIF($23, 0), NULLIF($24, 0), NULLIF($25, 0), NULLIF($26, 0), NULLIF($27, 0), $28, $29) returning id";
        pqxx::work txn{DD};
        try {
            auto x = txn.exec_params(strSql,
                                     args["entity_type_id"].asInt(),
                                     args["no"].asString(),
                                     args["sequence_id"].asInt(),
                                     args["slug"].asString(),
                                     args["parent_id"].asInt(),
                                     args["legal_name"].asString(),
                                     args["tax_no"].asString(),
                                     args["first_name"].asString(),
                                     args["middle_name"].asString(),
                                     args["last_name"].asString(),
                                     args["birth_date"].asString(),
                                     args["start_date"].asString(),
                                     args["end_date"].asString(),
                                     args["salary"].asDouble(),
                                     args["rate"].asDouble(),
                                     args["active"].asBool(),
                                     args["pay_to_name"].asString(),
                                     args["threshold"].asDouble(),
                                     args["credit_limit"].asDouble(),
                                     args["terms"].asInt(),
                                     args["discount"].asInt(),
                                     args["discount_terms"].asInt(),
                                     args["discount_account_id"].asInt(),
                                     args["ar_ap_account_id"].asInt(),
                                     args["cash_account_id"].asInt(),
                                     args["currency_id"].asInt(),
                                     args["price_group_id"].asInt(),
                                     args["tax_included"].asBool(),
                                     args["email"].asString()
                                     //                            args["create_user_id"].asInt(),
                                     //                            args["update_user_id"].asInt(),
                                     //                            args["inserted_at"]          timestamp,
                                     //                            args["updated_at"]           timestamp,
                                     );
            auto entity_id = x[0][0].as<int>();
            std::string strSqlUser = "INSERT INTO entity.entity_user (entity_id, username, password, password_hash) VALUES ($1, $2, $3, $4)";
            txn.exec_params(strSqlUser, entity_id, args["email"].asString(), args["eu_password"].asString(),
                            args["eu_password"].asString());
            save_Entity_Address(args, txn, entity_id);


            txn.commit();
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
        } catch (const std::exception &e) {
            txn.abort();
            std::cerr << e.what() << std::endl;
            Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
        }
    }
}
Json::Value Entity::del( Json::Value event, Json::Value args) {
    pqxx::work txn{DD};
    try {
        auto entity_id = args[0].asInt();
        txn.exec_params(dele("setting.notification", "where from_entity_id = $1"), entity_id);
        txn.exec_params(dele("setting.notification", "where to_entity_id = $1"), entity_id);

        txn.exec_params(dele("entity.entity_bank_account", "where entity_id = $1"), entity_id);
        txn.exec_params(dele("entity.entity_contact", "where entity_id = $1"), entity_id);
        txn.exec_params(dele("entity.entity_file", "where entity_id = $1"), entity_id);
        txn.exec_params(dele("entity.entity_image", "where entity_id = $1"), entity_id);
        txn.exec_params(dele("entity.entity_note", "where entity_id = $1"), entity_id);
        txn.exec_params(dele("entity.entity_address", "where entity_id = $1"), entity_id);
        txn.exec_params("delete from user1.session where value->>'value' = $1;", args[0].asString());
        txn.exec_params(dele("entity.entity_user", "where entity_id = $1"),
                        entity_id);   // This cant be deleted easily, set the table where it used null values or deleted user... 2. Also it is used in same entity table too.!
        txn.exec_params(dele("entity.entity", "where id = $1"), entity_id);
        txn.commit();
        Json::Value ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
    } catch (const std::exception &e) {
        txn.abort();
        std::cerr << e.what() << std::endl;
        Json::Value ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
    }
}
