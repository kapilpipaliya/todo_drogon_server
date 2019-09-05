#include "entity.h"
using namespace  jadmin;


typedef sqlb::SelectedColumn S;
Entity::Entity(const JAdminContextPtr &context_): context(context_)
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

void save_Entity_Address(json &args,
                             std::shared_ptr<Transaction> transPtr,
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
    for (auto i : args[0]["ea_entity_address"]) {    // ea.id, ea.address_type_id, ea.line1, ea.line2, ea.line3, ea.city, ea.state, ea.country, ea.zipcode, ea.phone
        if (!i[1].is_null())
            inVector.push_back(
                {i[0].get<int>(), i[1].get<int>(), i[2].get<std::string>(), i[3].get<std::string>(), i[4].get<std::string>(), i[5].get<std::string>(),
                 i[6].get<std::string>(), i[7].get<std::string>(), i[8].get<std::string>(), i[9].get<std::string>(), i[10].get<bool>()});
    }

    auto all_ct = transPtr->execSqlSync(strSqlPostCategories, entity_id);
    // For each saved tones, If saved tone not exist in new tones, delete it.
    for (auto r : all_ct) {
        std::vector<EntityAddress>::iterator it = std::find_if(inVector.begin(), inVector.end(), [&](EntityAddress t) {
            return t.id == r["id"].as<int>();
        });
        if (it == inVector.end()) {// Element not Found
            transPtr->execSqlSync(strSqlPostCategoryDel, r["id"].as<int>());
        }
    }
    // For each new tones, insert it if it not already exist.
    for (auto r : inVector) {
        auto y = transPtr->execSqlSync(strSqlPostCategorySimpleFind, r.id);
        if (y.size() == 0) {
            transPtr->execSqlSync(strSqlPostCategoryInsert, entity_id, r.addess_type_id, r.line1, r.line2, r.line3, r.city,
                            r.state, r.country, r.zipcode, r.phone, r.ismain);
        } else { // update
            //if(y[0][0].as<int>() != r.addess_type_id || y[0][2].as<int>() != r.pcs || y[0][3].as<double>() != r.weight || y[0][4].as<double>() != r.price || y[0][5].as<bool>() != r.ismain) {
            transPtr->execSqlSync(strSqlPostCategoryUpdateAtt, r.id, r.addess_type_id, r.line1, r.line2, r.line3, r.city,
                            r.state, r.country, r.zipcode, r.phone, r.ismain);
            //}
        }
    }
}
json Entity::ins( json event, json args) {
    std::string strSql = "INSERT INTO entity.entity (  entity_type_id, no, sequence_id, slug, parent_id, legal_name, tax_no, first_name, middle_name, last_name, birth_date, start_date, end_date, salary, rate, active, pay_to_name, threshold, credit_limit, terms, discount, discount_terms, discount_account_id, ar_ap_account_id, cash_account_id, currency_id, price_group_id, tax_included, email) "
                         "values($1, $2, NULLIF($3, 0), $4, NULLIF($5, 0), $6, $7, $8, $9, $10, $11, NULLIF($12, '')::date, NULLIF($13, '')::date, $14, $15, $16, $17, $18, $19, $20, $21, $22, NULLIF($23, 0), NULLIF($24, 0), NULLIF($25, 0), NULLIF($26, 0), NULLIF($27, 0), $28, $29) returning id";
    auto clientPtr = drogon::app().getDbClient("sce");
    auto transPtr = clientPtr->newTransaction();
    try {
        auto x = transPtr->execSqlSync(strSql,
                                 args[0]["entity_type_id"].get<int>(),
                                 args[0]["no"].get<std::string>(),
                                 args[0]["sequence_id"].get<int>(),
                                 args[0]["slug"].get<std::string>(),
                                 args[0]["parent_id"].get<long>(),
                                 args[0]["legal_name"].get<std::string>(),
                                 args[0]["tax_no"].get<std::string>(),
                                 args[0]["first_name"].get<std::string>(),
                                 args[0]["middle_name"].get<std::string>(),
                                 args[0]["last_name"].get<std::string>(),
                                 args[0]["birth_date"].get<std::string>(),
                                 args[0]["start_date"].get<std::string>(),
                                 args[0]["end_date"].get<std::string>(),
                                 args[0]["salary"].get<float>(),
                                 args[0]["rate"].get<float>(),
                                 args[0]["active"].get<bool>(),
                                 args[0]["pay_to_name"].get<std::string>(),
                                 args[0]["threshold"].get<float>(),
                                 args[0]["credit_limit"].get<float>(),
                                 args[0]["terms"].get<int>(),
                                 args[0]["discount"].get<int>(),
                                 args[0]["discount_terms"].get<int>(),
                                 args[0]["discount_account_id"].get<int>(),
                                 args[0]["ar_ap_account_id"].get<int>(),
                                 args[0]["cash_account_id"].get<int>(),
                                 args[0]["currency_id"].get<int>(),
                                 args[0]["price_group_id"].get<int>(),
                                 args[0]["tax_included"].get<bool>(),
                                 args[0]["email"].get<std::string>()
                                 //                            args[0]["create_user_id"].get<int>(),
                                 //                            args[0]["update_user_id"].get<int>(),
                                 //                            args[0]["inserted_at"]          timestamp,
                                 //                            args[0]["updated_at"]           timestamp,
                                 );
        auto entity_id = x[0]["id"].as<int>();
        std::string strSqlUser = "INSERT INTO entity.entity_user (entity_id, username, password, password_hash) VALUES ($1, $2, $3, $4)";
        transPtr->execSqlSync(strSqlUser, entity_id, args[0]["email"].get<std::string>(), args[0]["eu_password"].get<std::string>(),
                        args[0]["eu_password"].get<std::string>());
        save_Entity_Address(args, transPtr, entity_id);


        json ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
    } catch (const std::exception &e) {
       SPDLOG_TRACE(e.what());
        json ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
    }
}
json Entity::upd( json event, json args_) {
    auto args = args_[1];
    if (args[0]["id"].get<long>()) {
        std::string strSql = "update entity.entity set (  entity_type_id, no, sequence_id, slug, parent_id, legal_name, tax_no, first_name, middle_name, last_name, birth_date, start_date, end_date, salary, rate, active, pay_to_name, threshold, credit_limit, terms, discount, discount_terms, discount_account_id, ar_ap_account_id, cash_account_id, currency_id, price_group_id, tax_included, email)"
                             " = ROW($2, $3, NULLIF($4, 0), $5, NULLIF($6, 0), $7, $8, $9, $10, $11, $12, NULLIF($13, '')::date, NULLIF($14, '')::date, $15, $16, $17, $18, $19, $20, $21, $22, $23, NULLIF($24, 0), NULLIF($25, 0), NULLIF($26, 0), NULLIF($27, 0), NULLIF($28, 0), $29, $30) where id=$1";
        auto clientPtr = drogon::app().getDbClient("sce");
        auto transPtr = clientPtr->newTransaction();
        try {
            transPtr->execSqlSync(strSql,
                            args[0]["id"].get<long>(),
                    args[0]["entity_type_id"].get<int>(),
                    args[0]["no"].get<std::string>(),
                    args[0]["sequence_id"].get<int>(),
                    args[0]["slug"].get<std::string>(),
                    args[0]["parent_id"].get<long>(),
                    args[0]["legal_name"].get<std::string>(),
                    args[0]["tax_no"].get<std::string>(),
                    args[0]["first_name"].get<std::string>(),
                    args[0]["middle_name"].get<std::string>(),
                    args[0]["last_name"].get<std::string>(),
                    args[0]["birth_date"].get<std::string>(),
                    args[0]["start_date"].get<std::string>(),
                    args[0]["end_date"].get<std::string>(),
                    args[0]["salary"].get<float>(),
                    args[0]["rate"].get<float>(),
                    args[0]["active"].get<bool>(),
                    args[0]["pay_to_name"].get<std::string>(),
                    args[0]["threshold"].get<float>(),
                    args[0]["credit_limit"].get<float>(),
                    args[0]["terms"].get<int>(),
                    args[0]["discount"].get<int>(),
                    args[0]["discount_terms"].get<int>(),
                    args[0]["discount_account_id"].get<int>(),
                    args[0]["ar_ap_account_id"].get<int>(),
                    args[0]["cash_account_id"].get<int>(),
                    args[0]["currency_id"].get<int>(),
                    args[0]["price_group_id"].get<int>(),
                    args[0]["tax_included"].get<bool>(),
                    args[0]["email"].get<std::string>()
                    //                            args[0]["create_user_id"].get<int>(),
                    //                            args[0]["update_user_id"].get<int>(),
                    //                            args[0]["inserted_at"]          timestamp,
                    //                            args[0]["updated_at"]           timestamp,
                    );
            auto entity_id = args[0]["id"].get<long>();
            std::string strSqlUser = "UPDATE entity.entity_user set (username, password, password_hash) = ROW($2, $3, $4) where entity_id = $1";
            transPtr->execSqlSync(strSqlUser, entity_id, args[0]["email"].get<std::string>(), args[0]["eu_password"].get<std::string>(),
                    args[0]["eu_password"].get<std::string>());
            save_Entity_Address(args, transPtr, entity_id);


            json ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
        } catch (const std::exception &e) {

           SPDLOG_TRACE(e.what());
            json ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
        }
    }
}
json Entity::del( json event, json args) {
     // to support global filter, get first all ids b selected filter and for each id delete.
    auto clientPtr = drogon::app().getDbClient("sce");
    auto transPtr = clientPtr->newTransaction();
    try {
        auto entity_id = args[0][0].get<int>();
        transPtr->execSqlSync(dele_("setting.notification", "where from_entity_id = $1"), entity_id);
        transPtr->execSqlSync(dele_("setting.notification", "where to_entity_id = $1"), entity_id);

        transPtr->execSqlSync(dele_("entity.entity_bank_account", "where entity_id = $1"), entity_id);
        transPtr->execSqlSync(dele_("entity.entity_contact", "where entity_id = $1"), entity_id);
        transPtr->execSqlSync(dele_("entity.entity_file", "where entity_id = $1"), entity_id);
        transPtr->execSqlSync(dele_("entity.entity_image", "where entity_id = $1"), entity_id);
        transPtr->execSqlSync(dele_("entity.entity_note", "where entity_id = $1"), entity_id);
        transPtr->execSqlSync(dele_("entity.entity_address", "where entity_id = $1"), entity_id);
        transPtr->execSqlSync("delete from user1.session where value->>'value' = $1;", entity_id);
        transPtr->execSqlSync(dele_("entity.entity_user", "where entity_id = $1"),
                        entity_id);   // This cant be deleted easily, set the table where it used null values or deleted user... 2. Also it is used in same entity table too.!
        transPtr->execSqlSync(dele_("entity.entity", "where id = $1"), entity_id);

        json ret; ret[0] = simpleJsonSaveResult(event, true, "Done"); return ret;
    } catch (const std::exception &e) {

       SPDLOG_TRACE(e.what());
        json ret; ret[0] = simpleJsonSaveResult(event, false, e.what()); return ret;
    }
}
