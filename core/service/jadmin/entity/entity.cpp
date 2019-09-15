#include "entity.h"

#include <utility>
#include "../../../sql/dba.h"

namespace jadmin {
namespace service {
Entity::Entity(std::shared_ptr<websocket::jadmin::JAdminContext> context_)
    : context(std::move(context_)) {
  query = sql::Query(sql::ObjectIdentifier("entity", "entity", "e"));
  setupTable();
}

nlohmann::json Entity::handleEvent(nlohmann::json event, unsigned long next,
                                   nlohmann::json args) {
  auto event_cmp = event[next].get<std::string>();
  if (event_cmp == "data") {
    return query.allData(event, args);
  }
  if (event_cmp == "header") {
    return query.headerData(event, args);
  } else if (event_cmp == "ins") {
    return ins(event, args);
  } else if (event_cmp == "upd") {
    return upd(event, args);
  } else if (event_cmp == "del") {
    return del(event, args);
  } else {
    nlohmann::json ret;
    return ret;
  }
}

void Entity::setupTable() {
  // m_query.setRowIdColumn("id");
  query.setSelectedColumns(
      {sql::SelectedColumn({"id", "id", "", "e", sql::PG_TYPES::INT8}),
       sql::SelectedColumn({"Entity Type", "entity_type_id", "", "e",
                            sql::PG_TYPES::INT8, true, 1, 1}),
       sql::SelectedColumn({"et_name", "name", "", "et", sql::PG_TYPES::TEXT,
                            false, 0, 0, false}),
       sql::SelectedColumn({"no", "no", "", "e", sql::PG_TYPES::TEXT}),
       sql::SelectedColumn(
           {"sequence_id", "sequence_id", "", "e", sql::PG_TYPES::INT8, false}),
       sql::SelectedColumn({"Code", "slug", "", "e", sql::PG_TYPES::TEXT}),
       sql::SelectedColumn(
           {"Parent", "parent_id", "", "e", sql::PG_TYPES::INT8}),
       sql::SelectedColumn(
           {"Legal Name", "legal_name", "", "e", sql::PG_TYPES::TEXT}),
       sql::SelectedColumn(
           {"tax_no", "tax_no", "", "e", sql::PG_TYPES::TEXT, false}),
       sql::SelectedColumn(
           {"First Name", "first_name", "", "e", sql::PG_TYPES::TEXT}),
       sql::SelectedColumn(
           {"Middle Name", "middle_name", "", "e", sql::PG_TYPES::TEXT}),
       sql::SelectedColumn(
           {"Last Name", "last_name", "", "e", sql::PG_TYPES::TEXT}),
       sql::SelectedColumn(
           {"Email", "email", "", "e", sql::PG_TYPES::TEXT, true}),
       sql::SelectedColumn(
           {"Password", "password", "", "eu", sql::PG_TYPES::TEXT, true}),
       sql::SelectedColumn({"Birth Date", "birth_date", "", "e",
                            sql::PG_TYPES::TIMESTAMP, false}),
       sql::SelectedColumn(
           {"Start Date", "start_date", "", "e", sql::PG_TYPES::TIMESTAMP}),
       sql::SelectedColumn(
           {"End Date", "end_date", "", "e", sql::PG_TYPES::TIMESTAMP}),
       sql::SelectedColumn(
           {"Salary", "salary", "", "e", sql::PG_TYPES::DOUBLE, false}),
       sql::SelectedColumn(
           {"Rate", "rate", "", "e", sql::PG_TYPES::DOUBLE, false}),
       sql::SelectedColumn(
           {"Active", "active", "", "e", sql::PG_TYPES::BOOL, false}),
       sql::SelectedColumn(
           {"Pay To Name", "pay_to_name", "", "e", sql::PG_TYPES::TEXT, false}),
       sql::SelectedColumn(
           {"Threshold", "threshold", "", "e", sql::PG_TYPES::DOUBLE, false}),
       sql::SelectedColumn({"Credit Limit", "credit_limit", "", "e",
                            sql::PG_TYPES::DOUBLE, false}),
       sql::SelectedColumn(
           {"Terms", "terms", "", "e", sql::PG_TYPES::INT4, false}),
       sql::SelectedColumn(
           {"Discount", "discount", "", "e", sql::PG_TYPES::DOUBLE, false}),
       sql::SelectedColumn({"Discount Terms", "discount_terms", "", "e",
                            sql::PG_TYPES::INT4, false}),
       sql::SelectedColumn({"discount_account_id", "discount_account_id", "",
                            "e", sql::PG_TYPES::INT8, false}),
       sql::SelectedColumn({"ar_ap_account_id", "ar_ap_account_id", "", "e",
                            sql::PG_TYPES::INT8, false}),
       sql::SelectedColumn({"cash_account_id", "cash_account_id", "", "e",
                            sql::PG_TYPES::INT8, false}),
       sql::SelectedColumn(
           {"currency_id", "currency_id", "", "e", sql::PG_TYPES::INT8, false}),
       sql::SelectedColumn({"price_group_id", "price_group_id", "", "e",
                            sql::PG_TYPES::INT8, false}),
       sql::SelectedColumn({"tax_included", "tax_included", "", "e",
                            sql::PG_TYPES::BOOL, false}),

       // sql::SelectedColumn({"Created By", "create_user_id", "", "e",
       // sql::PG_TYPES::INT8, true, 1, 0, false}),
       // sql::SelectedColumn({"u1_username", "username", "", "u1",
       // sql::PG_TYPES::TEXT, false, 0, 0, false}),
       // sql::SelectedColumn({"Updated By", "update_user_id", "", "e",
       // sql::PG_TYPES::INT8, true, 1, 0, false}),
       // sql::SelectedColumn({"u2_username", "username", "", "u2",
       // sql::PG_TYPES::TEXT, false, 0, 0, false}),
       // sql::SelectedColumn({"Create Time", "inserted_at", "", "e",
       // sql::PG_TYPES::TIMESTAMP, true, 0, 0, false}),
       // sql::SelectedColumn({"Update Time", "updated_at", "", "e",
       // sql::PG_TYPES::TIMESTAMP, true, 0, 0, false}),
       sql::SelectedColumn(
           {"Addresses", "entity_address",
            "json_agg(distinct jsonb_build_array(ea.id, ea.address_type_id, "
            "ea.line1, ea.line2, ea.line3, ea.city, ea.state, ea.country, "
            "ea.zipcode, ea.phone, ea.ismain ))",
            "ea", sql::PG_TYPES::PSJSON, false})});
  auto entity_type = sql::ObjectIdentifier("entity", "entity_type", "et");
  auto entity_address = sql::ObjectIdentifier("entity", "entity_address", "ea");
  auto entity_user = sql::ObjectIdentifier("entity", "entity_user", "eu");
  auto u1 = sql::ObjectIdentifier("entity", "entity_user", "u1");
  auto u2 = sql::ObjectIdentifier("entity", "entity_user", "u2");

  query.setJoins({
      sql::Join("inner", entity_type, "et.id = e.entity_type_id"),
      sql::Join("left", entity_address, "ea.entity_id = e.id"),
      sql::Join("left", entity_user, "eu.entity_id = e.id"),
      sql::Join("left", u1, "e.create_user_id = u1.id"),
      sql::Join("left", u2, "e.update_user_id = u2.id"),
  });
  query.setGroupBy({
      sql::GroupByColumn("et", "id"),
      sql::GroupByColumn("e", "id"),
      sql::GroupByColumn("eu", "id"),
  });
}

void save_Entity_Address(
    nlohmann::json &args,
    const std::shared_ptr<drogon::orm::Transaction> &transPtr, long entity_id) {
  std::string strSqlPostCategories =
      "SELECT id FROM entity.entity_address where entity_id = $1";
  std::string strSqlPostCategorySimpleFind =
      "SELECT address_type_id, line1, line2, line3, city, state, country, "
      "zipcode, phone, ismain FROM entity.entity_address WHERE id = $1";
  std::string strSqlPostCategoryDel =
      "DELETE FROM entity.entity_address WHERE id = $1";
  std::string strSqlPostCategoryInsert =
      "INSERT INTO entity.entity_address (	entity_id, address_type_id, "
      "line1, line2, line3, city, state, country, zipcode, phone, ismain) "
      "VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10, $11);";
  std::string strSqlPostCategoryUpdateAtt =
      "UPDATE entity.entity_address SET ( address_type_id, line1, line2, "
      "line3, city, state, country, zipcode, phone, ismain) = ROW($2, $3, $4, "
      "$5, $6, $7, $8, $9, $10, $11) WHERE id = $1";

  struct EntityAddress {
    long id;
    long addess_type_id;
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
  for (auto i :
       args[0]
           ["ea_entity_address"]) {  // ea.id, ea.address_type_id, ea.line1,
                                     // ea.line2, ea.line3, ea.city, ea.state,
                                     // ea.country, ea.zipcode, ea.phone
    if (!i[1].is_null())
      inVector.push_back({i[0].get<long>(), i[1].get<long>(),
                          i[2].get<std::string>(), i[3].get<std::string>(),
                          i[4].get<std::string>(), i[5].get<std::string>(),
                          i[6].get<std::string>(), i[7].get<std::string>(),
                          i[8].get<std::string>(), i[9].get<std::string>(),
                          i[10].get<bool>()});
  }

  auto all_ct =
      sql::Dba::writeInTrans(transPtr, strSqlPostCategories, entity_id);
  // For each saved tones, If saved tone not exist in new tones, delete it.
  for (auto r : all_ct) {
    auto it = std::find_if(
        inVector.begin(), inVector.end(),
        [&](const EntityAddress &t) { return t.id == r["id"].as<long>(); });
    if (it == inVector.end()) {  // Element not Found
      sql::Dba::writeInTrans(transPtr, strSqlPostCategoryDel,
                             r["id"].as<long>());
    }
  }
  // For each new tones, insert it if it not already exist.
  for (const auto &r : inVector) {
    auto y =
        sql::Dba::writeInTrans(transPtr, strSqlPostCategorySimpleFind, r.id);
    if (y.empty()) {
      sql::Dba::writeInTrans(transPtr, strSqlPostCategoryInsert, entity_id,
                             r.addess_type_id, r.line1, r.line2, r.line3,
                             r.city, r.state, r.country, r.zipcode, r.phone,
                             r.ismain);
    } else {  // update
      // if(y[0][0].as<long>() != r.addess_type_id || y[0][2].as<int>() != r.pcs
      // || y[0][3].as<double>() != r.weight || y[0][4].as<double>() != r.price
      // || y[0][5].as<bool>() != r.ismain) {
      sql::Dba::writeInTrans(transPtr, strSqlPostCategoryUpdateAtt, r.id,
                             r.addess_type_id, r.line1, r.line2, r.line3,
                             r.city, r.state, r.country, r.zipcode, r.phone,
                             r.ismain);
      //}
    }
  }
}
nlohmann::json Entity::ins(nlohmann::json event, nlohmann::json args) {
  std::string strSql =
      "INSERT INTO entity.entity (  entity_type_id, no, sequence_id, slug, "
      "parent_id, legal_name, tax_no, first_name, middle_name, last_name, "
      "birth_date, start_date, end_date, salary, rate, active, pay_to_name, "
      "threshold, credit_limit, terms, discount, discount_terms, "
      "discount_account_id, ar_ap_account_id, cash_account_id, currency_id, "
      "price_group_id, email) "
      "values($1, $2, NULLIF($3, 0::bigint), $4, NULLIF($5, 0::bigint), $6, "
      "$7, $8, $9, $10, $11, NULLIF($12, '')::date, NULLIF($13, '')::date, "
      "$14, $15, $16, $17, $18, $19, $20, $21, $22, NULLIF($23, 0::bigint), "
      "NULLIF($24, 0::bigint), NULLIF($25, 0::bigint), NULLIF($26, 0::bigint), "
      "NULLIF($27, 0::bigint), $28) returning id";
  auto clientPtr = drogon::app().getDbClient("sce");
  auto transPtr = clientPtr->newTransaction();
  try {
    auto x = sql::Dba::writeInTrans(
        transPtr, strSql, args[0]["entity_type_id"].get<long>(),
        args[0]["no"].get<std::string>(),
        args[0]["sequence_id"].is_null() ? 0L
                                         : args[0]["sequence_id"].get<long>(),
        args[0]["slug"].get<std::string>(),
        args[0]["parent_id"].is_null() ? 0L : args[0]["parent_id"].get<long>(),
        args[0]["legal_name"].get<std::string>(),
        args[0]["tax_no"].get<std::string>(),
        args[0]["first_name"].get<std::string>(),
        args[0]["middle_name"].get<std::string>(),
        args[0]["last_name"].get<std::string>(),
        args[0]["birth_date"].get<std::string>(),
        args[0]["start_date"].get<std::string>(),
        args[0]["end_date"].is_null() ? ""
                                      : args[0]["end_date"].get<std::string>(),
        args[0]["salary"].get<float>(), args[0]["rate"].get<float>(),
        args[0]["active"].get<bool>(),
        args[0]["pay_to_name"].get<std::string>(),
        args[0]["threshold"].get<float>(), args[0]["credit_limit"].get<float>(),
        args[0]["terms"].get<int>(), args[0]["discount"].get<double>(),
        args[0]["discount_terms"].get<int>(),
        args[0]["discount_account_id"].is_null()
            ? 0L
            : args[0]["discount_account_id"].get<long>(),
        args[0]["ar_ap_account_id"].is_null()
            ? 0L
            : args[0]["ar_ap_account_id"].get<long>(),
        args[0]["cash_account_id"].is_null()
            ? 0L
            : args[0]["cash_account_id"].get<long>(),
        args[0]["currency_id"].is_null() ? 0L
                                         : args[0]["currency_id"].get<long>(),
        args[0]["price_group_id"].is_null()
            ? 0L
            : args[0]["price_group_id"].get<long>(),
        args[0]["email"].get<std::string>()
        //                            args[0]["create_user_id"].get<long>(),
        //                            args[0]["update_user_id"].get<long>(),
        //                            args[0]["inserted_at"]          timestamp,
        //                            args[0]["updated_at"]           timestamp,
    );
    auto entity_id = x[0]["id"].as<long>();
    std::string strSqlUser =
        "INSERT INTO entity.entity_user (entity_id, username, password, "
        "password_hash) VALUES ($1, $2, $3, $4)";
    sql::Dba::writeInTrans(transPtr, strSqlUser, entity_id,
                           args[0]["email"].get<std::string>(),
                           args[0]["eu_password"].get<std::string>(),
                           args[0]["eu_password"].get<std::string>());
    save_Entity_Address(args, transPtr, entity_id);

    nlohmann::json ret;
    ret[0] = websocket::WsFns::successJsonObject(event, true, "Done");
    return ret;
  } catch (const std::exception &e) {
    SPDLOG_TRACE(e.what());
    nlohmann::json ret;
    ret[0] = websocket::WsFns::successJsonObject(event, false, e.what());
    return ret;
  }
}
nlohmann::json Entity::upd(nlohmann::json event, nlohmann::json args) {
  if (args[0]["id"].get<long>()) {
    std::string strSql =
        "update entity.entity set (  entity_type_id, no, sequence_id, slug, "
        "parent_id, legal_name, tax_no, first_name, middle_name, last_name, "
        "birth_date, start_date, end_date, salary, rate, active, pay_to_name, "
        "threshold, credit_limit, terms, discount, discount_terms, "
        "discount_account_id, ar_ap_account_id, cash_account_id, currency_id, "
        "price_group_id,  email)"
        " = ROW($2, $3, NULLIF($4, 0::bigint), $5, NULLIF($6, 0::bigint), $7, "
        "$8, $9, $10, $11, $12, NULLIF($13, '')::date, NULLIF($14, '')::date, "
        "$15, $16, $17, $18, $19, $20, $21, $22, $23, NULLIF($24, 0::bigint), "
        "NULLIF($25, 0::bigint), NULLIF($26, 0::bigint), NULLIF($27, "
        "0::bigint), NULLIF($28, 0::bigint), $29) where id=$1";
    auto clientPtr = drogon::app().getDbClient("sce");
    auto transPtr = clientPtr->newTransaction();
    try {
      sql::Dba::writeInTrans(
          transPtr, strSql, args[0]["id"].get<long>(),
          args[0]["entity_type_id"].get<long>(),
          args[0]["no"].get<std::string>(),
          args[0]["sequence_id"].is_null() ? 0L
                                           : args[0]["sequence_id"].get<long>(),
          args[0]["slug"].get<std::string>(),
          args[0]["parent_id"].is_null() ? 0L
                                         : args[0]["parent_id"].get<long>(),
          args[0]["legal_name"].get<std::string>(),
          args[0]["tax_no"].get<std::string>(),
          args[0]["first_name"].get<std::string>(),
          args[0]["middle_name"].get<std::string>(),
          args[0]["last_name"].get<std::string>(),
          args[0]["birth_date"].get<std::string>(),
          args[0]["start_date"].get<std::string>(),
          args[0]["end_date"].is_null()
              ? ""
              : args[0]["end_date"].get<std::string>(),
          args[0]["salary"].get<float>(), args[0]["rate"].get<float>(),
          args[0]["active"].get<bool>(),
          args[0]["pay_to_name"].get<std::string>(),
          args[0]["threshold"].get<float>(),
          args[0]["credit_limit"].get<float>(), args[0]["terms"].get<int>(),
          args[0]["discount"].get<double>(),
          args[0]["discount_terms"].get<int>(),
          args[0]["discount_account_id"].is_null()
              ? 0L
              : args[0]["discount_account_id"].get<long>(),
          args[0]["ar_ap_account_id"].is_null()
              ? 0L
              : args[0]["ar_ap_account_id"].get<long>(),
          args[0]["cash_account_id"].is_null()
              ? 0L
              : args[0]["cash_account_id"].get<long>(),
          args[0]["currency_id"].is_null() ? 0L
                                           : args[0]["currency_id"].get<long>(),
          args[0]["price_group_id"].is_null()
              ? 0L
              : args[0]["price_group_id"].get<long>(),
          args[0]["email"].get<std::string>()
          //                            args[0]["create_user_id"].get<long>(),
          //                            args[0]["update_user_id"].get<long>(),
          //                            args[0]["inserted_at"] timestamp,
          //                            args[0]["updated_at"] timestamp,
      );
      auto entity_id = args[0]["id"].get<long>();
      std::string strSqlUser =
          "UPDATE entity.entity_user set (username, password, password_hash) = "
          "ROW($2, $3, $4) where entity_id = $1";
      sql::Dba::writeInTrans(transPtr, strSqlUser, entity_id,
                             args[0]["email"].get<std::string>(),
                             args[0]["eu_password"].get<std::string>(),
                             args[0]["eu_password"].get<std::string>());
      save_Entity_Address(args, transPtr, entity_id);

      nlohmann::json ret;
      ret[0] = websocket::WsFns::successJsonObject(event, true, "Done");
      return ret;
    } catch (const std::exception &e) {
      SPDLOG_TRACE(e.what());
      nlohmann::json ret;
      ret[0] = websocket::WsFns::successJsonObject(event, false, e.what());
      return ret;
    }
  }
  nlohmann::json ret;
  ret[0] =
      websocket::WsFns::successJsonObject(event, false, "Not Valid Structure");
  return ret;
}
nlohmann::json Entity::del(nlohmann::json event, nlohmann::json args) {
  // to support global filter, get first all ids b selected filter and for each
  // id delete.
  auto clientPtr = drogon::app().getDbClient("sce");
  auto transPtr = clientPtr->newTransaction();
  try {
    auto entity_id = args[0][0].get<long>();
    sql::Dba::writeInTrans(transPtr,
                           sql::CRUDHelper::dele_("entity.notification",
                                                  "where from_entity_id = $1"),
                           entity_id);
    sql::Dba::writeInTrans(transPtr,
                           sql::CRUDHelper::dele_("entity.notification",
                                                  "where to_entity_id = $1"),
                           entity_id);

    sql::Dba::writeInTrans(transPtr,
                           sql::CRUDHelper::dele_("entity.entity_bank_account",
                                                  "where entity_id = $1"),
                           entity_id);
    sql::Dba::writeInTrans(
        transPtr,
        sql::CRUDHelper::dele_("entity.entity_contact", "where entity_id = $1"),
        entity_id);
    sql::Dba::writeInTrans(
        transPtr,
        sql::CRUDHelper::dele_("entity.entity_file", "where entity_id = $1"),
        entity_id);
    sql::Dba::writeInTrans(
        transPtr,
        sql::CRUDHelper::dele_("entity.entity_image", "where entity_id = $1"),
        entity_id);
    sql::Dba::writeInTrans(
        transPtr,
        sql::CRUDHelper::dele_("entity.entity_note", "where entity_id = $1"),
        entity_id);
    sql::Dba::writeInTrans(
        transPtr,
        sql::CRUDHelper::dele_("entity.entity_address", "where entity_id = $1"),
        entity_id);
    // sql::Dba::writeInTrans(transPtr, "delete from entity.session where
    // value->>'value' = $1;", entity_id);
    sql::Dba::writeInTrans(transPtr,
                           "delete from entity.session where entity_id = $1;",
                           entity_id);
    sql::Dba::writeInTrans(
        transPtr,
        sql::CRUDHelper::dele_("entity.entity_user", "where entity_id = $1"),
        entity_id);  // This cant be deleted easily, set the table where it used
                     // null values or deleted user... 2. Also it is used in
                     // same entity table too.!
    sql::Dba::writeInTrans(
        transPtr, sql::CRUDHelper::dele_("entity.entity", "where id = $1"),
        entity_id);

    nlohmann::json ret;
    ret[0] = websocket::WsFns::successJsonObject(event, true, "Done");
    return ret;
  } catch (const std::exception &e) {
    SPDLOG_TRACE(e.what());
    nlohmann::json ret;
    ret[0] = websocket::WsFns::successJsonObject(event, false, e.what());
    return ret;
  }
}
}  // namespace service
}  // namespace jadmin
