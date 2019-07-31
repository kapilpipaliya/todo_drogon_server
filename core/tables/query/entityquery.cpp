#include "entityquery.h"

void query_address_type(Table &t) {
  t.m_table = sqlb::ObjectIdentifier("entity", "address_type", "a");
  t.m_query = sqlb::Query(t.m_table);
  //m_query.setRowIdColumn("id");
  t.m_query.selectedColumns() = {
          sqlb::SelectedColumn({"Id", "id", "", "a", PG_TYPES::INT8, true}),
          sqlb::SelectedColumn({"Name", "name", "", "a", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Create Time", "inserted_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
          sqlb::SelectedColumn({"Update Time", "updated_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  };
}

void query_contact_type(Table &t) {
  t.m_table = sqlb::ObjectIdentifier("entity", "contact_type", "a");
  t.m_query = sqlb::Query(t.m_table);
  //m_query.setRowIdColumn("id");
  t.m_query.selectedColumns() = {
          sqlb::SelectedColumn({"Id", "id", "", "a", PG_TYPES::INT8, true}),
          sqlb::SelectedColumn({"Name", "name", "", "a", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Create Time", "inserted_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
          sqlb::SelectedColumn({"Update Time", "updated_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  };
}

void query_entity_type(Table &t) {
  t.m_table = sqlb::ObjectIdentifier("entity", "entity_type", "a");
  t.m_query = sqlb::Query(t.m_table);
  //m_query.setRowIdColumn("id");
  t.m_query.selectedColumns() = {
          sqlb::SelectedColumn({"Id", "id", "", "a", PG_TYPES::INT8, true}),
          sqlb::SelectedColumn({"Name", "name", "", "a", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Create Time", "inserted_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
          sqlb::SelectedColumn({"Update Time", "updated_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  };
}

typedef sqlb::SelectedColumn S;

void query_entity(Table &t) {
  t.m_table = sqlb::ObjectIdentifier("entity", "entity", "e");
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
