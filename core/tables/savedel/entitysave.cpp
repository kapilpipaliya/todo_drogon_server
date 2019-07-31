#include "entitysave.h"

delFn(address_type, "entity.address_type");

delFn(contact_type, "entity.contact_type");

delFn(entity_type, "entity.entity_type");
//delFn(entity, "entity.entity");

void save_address_type(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
  if (in["id"].asInt()) {
    std::string strSql = "update entity.address_type set (name) = ROW($2) where id=$1";
    pqxx::work txn{DD};
    try {
      txn.exec_params(strSql, in["id"].asInt(), in["name"].asString());
      txn.commit();
      simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
      txn.abort();
      std::cerr << e.what() << std::endl;
      simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }
  } else {
    std::string strSql = "INSERT INTO entity.address_type (name) values($1)";
    pqxx::work txn{DD};
    try {
      txn.exec_params(strSql, in["name"].asString());
      txn.commit();
      simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
      txn.abort();
      std::cerr << e.what() << std::endl;
      simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }
  }
}

void save_contact_type(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
  if (in["id"].asInt()) {
    std::string strSql = "update entity.contact_type set (name) = ROW($2) where id=$1";
    pqxx::work txn{DD};
    try {
      txn.exec_params(strSql, in["id"].asInt(), in["name"].asString());
      txn.commit();
      simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
      txn.abort();
      std::cerr << e.what() << std::endl;
      simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }
  } else {
    std::string strSql = "INSERT INTO entity.contact_type (name) values($1)";
    pqxx::work txn{DD};
    try {
      txn.exec_params(strSql, in["name"].asString());
      txn.commit();
      simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
      txn.abort();
      std::cerr << e.what() << std::endl;
      simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }
  }
}

void save_entity_type(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
  if (in["id"].asInt()) {
    std::string strSql = "update entity.entity_type set (name) = ROW($2) where id=$1";
    pqxx::work txn{DD};
    try {
      txn.exec_params(strSql, in["id"].asInt(), in["name"].asString());
      txn.commit();
      simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
      txn.abort();
      std::cerr << e.what() << std::endl;
      simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }
  } else {
    std::string strSql = "INSERT INTO entity.entity_type (name) values($1)";
    pqxx::work txn{DD};
    try {
      txn.exec_params(strSql, in["name"].asString());
      txn.commit();
      simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
      txn.abort();
      std::cerr << e.what() << std::endl;
      simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }
  }
}

void save_Entity_Address(Json::Value &in,
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
  for (auto i : in["ea_entity_address"]) {    // ea.id, ea.address_type_id, ea.line1, ea.line2, ea.line3, ea.city, ea.state, ea.country, ea.zipcode, ea.phone
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

void save_entity(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
  if (in["id"].asInt()) {
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
      txn.exec_params(strSqlUser, entity_id, in["email"].asString(), in["eu_password"].asString(),
                      in["eu_password"].asString());
      save_Entity_Address(in, txn, entity_id);

      txn.commit();
      simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
      txn.abort();
      std::cerr << e.what() << std::endl;
      simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
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
      std::string strSqlUser = "INSERT INTO entity.entity_user (entity_id, username, password, password_hash) VALUES ($1, $2, $3, $4)";
      txn.exec_params(strSqlUser, entity_id, in["email"].asString(), in["eu_password"].asString(),
                      in["eu_password"].asString());
      save_Entity_Address(in, txn, entity_id);


      txn.commit();
      simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
    } catch (const std::exception &e) {
      txn.abort();
      std::cerr << e.what() << std::endl;
      simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
    }
  }
}

void delete_entity(const std::string &event_name, const WebSocketConnectionPtr &wsConnPtr, Json::Value in) {
  pqxx::work txn{DD};
  try {
    auto entity_id = in[0].asInt();
    txn.exec_params(dele("setting.notification", "where from_entity_id = $1"), entity_id);
    txn.exec_params(dele("setting.notification", "where to_entity_id = $1"), entity_id);

    txn.exec_params(dele("entity.entity_bank_account", "where entity_id = $1"), entity_id);
    txn.exec_params(dele("entity.entity_contact", "where entity_id = $1"), entity_id);
    txn.exec_params(dele("entity.entity_file", "where entity_id = $1"), entity_id);
    txn.exec_params(dele("entity.entity_image", "where entity_id = $1"), entity_id);
    txn.exec_params(dele("entity.entity_note", "where entity_id = $1"), entity_id);
    txn.exec_params(dele("entity.entity_address", "where entity_id = $1"), entity_id);
    txn.exec_params(dele("entity.entity_user", "where entity_id = $1"),
                    entity_id);   // This cant be deleted easily, set the table where it used null values or deleted user... 2. Also it is used in same entity table too.!
    txn.exec_params(dele("entity.entity", "where id = $1"), entity_id);
    txn.commit();
    simpleJsonSaveResult(event_name, wsConnPtr, true, "Done");
  } catch (const std::exception &e) {
    txn.abort();
    std::cerr << e.what() << std::endl;
    simpleJsonSaveResult(event_name, wsConnPtr, false, e.what());
  }
}
