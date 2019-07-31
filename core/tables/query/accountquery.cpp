#include "accountquery.h"

void query_account_type(Table &t) {

  t.m_table = sqlb::ObjectIdentifier("account", "account_type", "a");
  t.m_query = sqlb::Query(t.m_table);

  //m_query.setRowIdColumn("id");
  t.m_query.selectedColumns() = {
          sqlb::SelectedColumn({"Id", "id", "", "a", PG_TYPES::INT8, false}),
          sqlb::SelectedColumn({"Name", "name", "", "a", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Created By", "create_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}),
          sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
          sqlb::SelectedColumn({"Updated By", "update_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}),
          sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
          sqlb::SelectedColumn({"Create Time", "inserted_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
          sqlb::SelectedColumn({"Update Time", "updated_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  };

  auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
  auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

  t.m_query.joins() = {
          sqlb::Join("left", u1, "a.create_user_id = u1.id"),
          sqlb::Join("left", u2, "a.update_user_id = u2.id"),
  };
}

void query_account(Table &t) {

  t.m_table = sqlb::ObjectIdentifier("account", "account", "a");
  t.m_query = sqlb::Query(t.m_table);

  //m_query.setRowIdColumn("id");
  t.m_query.selectedColumns() = {
          sqlb::SelectedColumn({"Id", "id", "", "a", PG_TYPES::INT8, false}),
          sqlb::SelectedColumn({"Material", "material_id", "", "a", PG_TYPES::INT8, true, 1, 2}),
          sqlb::SelectedColumn({"m_slug", "slug", "", "m", PG_TYPES::TEXT, false}),
          sqlb::SelectedColumn({"m_name", "name", "", "m", PG_TYPES::TEXT, false}),
          sqlb::SelectedColumn({"Rank", "rank", "", "a", PG_TYPES::INT4, false}),
          sqlb::SelectedColumn({"Code", "slug", "", "a", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Name", "name", "", "a", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Created By", "create_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}),
          sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
          sqlb::SelectedColumn({"Updated By", "update_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}),
          sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
          sqlb::SelectedColumn({"Create Time", "inserted_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
          sqlb::SelectedColumn({"Update Time", "updated_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  };

  auto m = sqlb::ObjectIdentifier("material", "metal", "m");
  auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
  auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

  t.m_query.joins() = {
          sqlb::Join("left", m, "a.material_id = m.id"),
          sqlb::Join("left", u1, "a.create_user_id = u1.id"),
          sqlb::Join("left", u2, "a.update_user_id = u2.id"),
  };
}

void query_account_heading(Table &t) {

  t.m_table = sqlb::ObjectIdentifier("account", "account_heading", "p");
  t.m_query = sqlb::Query(t.m_table);

  //m_query.setRowIdColumn("id");
  t.m_query.selectedColumns() = {
          sqlb::SelectedColumn({"Id", "id", "", "p", PG_TYPES::INT8, false}),

  };

  //auto pg = sqlb::ObjectIdentifier("part", "part_category", "pg");
  //auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
  //auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

  t.m_query.joins() = {
          //sqlb::Join("left", c, "p.color_id = c.id"),
          //sqlb::Join("left", pg, "p.part_group_id = pg.id"),
          //sqlb::Join("left", u1, "gt.create_user_id = u1.id"),
          //sqlb::Join("left", u2, "a.update_user_id = u2.id"),
  };
}

void query_journal_type(Table &t) {

  t.m_table = sqlb::ObjectIdentifier("account", "journal_type", "a");
  t.m_query = sqlb::Query(t.m_table);

  //m_query.setRowIdColumn("id");
  t.m_query.selectedColumns() = {
          sqlb::SelectedColumn({"Id", "id", "", "a", PG_TYPES::INT8, true}),
          sqlb::SelectedColumn({"Rank", "rank", "", "a", PG_TYPES::INT4, false}),
          sqlb::SelectedColumn({"Name", "name", "", "a", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Description", "description", "", "a", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Created By", "create_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}),
          sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
          sqlb::SelectedColumn({"Updated By", "update_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}),
          sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
          sqlb::SelectedColumn({"Create Time", "inserted_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
          sqlb::SelectedColumn({"Update Time", "updated_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  };

  auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
  auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

  t.m_query.joins() = {
          sqlb::Join("left", u1, "a.create_user_id = u1.id"),
          sqlb::Join("left", u2, "a.update_user_id = u2.id"),
  };
}


void query_txn(Table &t) {

  t.m_table = sqlb::ObjectIdentifier("account", "txn", "a");
  t.m_query = sqlb::Query(t.m_table);

  //m_query.setRowIdColumn("id");
  t.m_query.selectedColumns() = {
          sqlb::SelectedColumn({"id", "id", "", "a", PG_TYPES::INT8}),
          sqlb::SelectedColumn({"Journal Type", "journal_type_id", "", "a", PG_TYPES::INT8, true, 1, 1}),
          sqlb::SelectedColumn({"jt_name", "name", "", "jt", PG_TYPES::TEXT, false, 0, 0, false}),
          sqlb::SelectedColumn({"Party", "party_id", "", "a", PG_TYPES::INT8, true, 1, 1}),
          sqlb::SelectedColumn({"party_slug", "slug", "", "party", PG_TYPES::TEXT, false, 0, 0, false}),
          sqlb::SelectedColumn({"no", "no", "", "a", PG_TYPES::TEXT}),
          sqlb::SelectedColumn({"sequence_id", "sequence_id", "", "a", PG_TYPES::INT8}),
          sqlb::SelectedColumn({"Date", "date", "", "a", PG_TYPES::TIMESTAMP}),
          sqlb::SelectedColumn({"entity_id", "entity_id", "", "a", PG_TYPES::INT8}),
          sqlb::SelectedColumn({"account_id", "account_id", "", "a", PG_TYPES::INT8}),
          sqlb::SelectedColumn({"tax_included", "tax_included", "", "a", PG_TYPES::BOOL}),
          sqlb::SelectedColumn({"due_date", "due_date", "", "a", PG_TYPES::TIMESTAMP}),
          sqlb::SelectedColumn({"till", "till", "", "a", PG_TYPES::TEXT}),
          sqlb::SelectedColumn({"order_number", "order_number", "", "a", PG_TYPES::TEXT}),
          sqlb::SelectedColumn({"quo_number", "quo_number", "", "a", PG_TYPES::TEXT}),
          sqlb::SelectedColumn({"Currency", "currency_id", "", "a", PG_TYPES::INT8}),
          sqlb::SelectedColumn({"invoice", "invoice", "", "a", PG_TYPES::BOOL}),
          sqlb::SelectedColumn({"amount_bc", "amount_bc", "", "a", PG_TYPES::DOUBLE}),
          sqlb::SelectedColumn({"amount_tc", "amount_tc", "", "a", PG_TYPES::DOUBLE}),
          sqlb::SelectedColumn({"net_amount_bc", "net_amount_bc", "", "a", PG_TYPES::DOUBLE}),
          sqlb::SelectedColumn({"net_amount_tc", "net_amount_tc", "", "a", PG_TYPES::DOUBLE}),
          sqlb::SelectedColumn({"notes", "notes", "", "a", PG_TYPES::TEXT}),
          sqlb::SelectedColumn({"internal_notes", "internal_notes", "", "a", PG_TYPES::TEXT}),
          sqlb::SelectedColumn({"description", "description", "", "a", PG_TYPES::TEXT}),
          sqlb::SelectedColumn({"status_id", "status_id", "", "a", PG_TYPES::TEXT}),
          sqlb::SelectedColumn({"branch_id", "branch_id", "", "a", PG_TYPES::INT8}),
          sqlb::SelectedColumn({"ship_via", "ship_via", "", "a", PG_TYPES::TEXT}),
          sqlb::SelectedColumn({"language_code", "language_code", "", "a", PG_TYPES::TEXT}),
          sqlb::SelectedColumn({"po_number", "po_number", "", "a", PG_TYPES::TEXT}),
          sqlb::SelectedColumn({"shipping_point", "shipping_point", "", "a", PG_TYPES::TEXT}),
          sqlb::SelectedColumn({"on_hold", "on_hold", "", "a", PG_TYPES::BOOL}),
          sqlb::SelectedColumn({"force_closed", "force_closed", "", "a", PG_TYPES::BOOL}),
          sqlb::SelectedColumn({"reverse", "reverse", "", "a", PG_TYPES::BOOL}),
          sqlb::SelectedColumn({"terms", "terms", "", "a", PG_TYPES::INT4}),
          sqlb::SelectedColumn({"is_return", "is_return", "", "a", PG_TYPES::BOOL}),
          // sqlb::SelectedColumn({"created_date", "created_date", "", "a", PG_TYPES::date}),
          sqlb::SelectedColumn({"is_approved", "is_approved", "", "a", PG_TYPES::BOOL}),
          sqlb::SelectedColumn({"approved_by_id", "approved_by_id", "", "a", PG_TYPES::INT8}),
          sqlb::SelectedColumn({"approved_at", "approved_at", "", "a", PG_TYPES::TIMESTAMP}),
          sqlb::SelectedColumn({"order_item", "order_item",
                                "json_agg( distinct jsonb_build_array(o_i.id, o_i.post_id, o_i.pcs, o_i.purity_id, o_i.tone_id, o_i.clarity_id, o_i.price, o_i.instruction))",
                                "o_i", PG_TYPES::PSJSON, false}),

          sqlb::SelectedColumn({"Created By", "create_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}),
          sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
          sqlb::SelectedColumn({"Updated By", "update_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}),
          sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
          sqlb::SelectedColumn({"Create Time", "inserted_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
          sqlb::SelectedColumn({"Update Time", "updated_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  };

  auto jt = sqlb::ObjectIdentifier("account", "journal_type", "jt");
  auto party = sqlb::ObjectIdentifier("entity", "entity", "party");
  auto order_item = sqlb::ObjectIdentifier("order1", "order_item", "o_i");
  auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
  auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

  t.m_query.joins() = {
          sqlb::Join("left", jt, "jt.id = a.journal_type_id"),
          sqlb::Join("left", party, "party.id = a.party_id"),
          sqlb::Join("left", order_item, "o_i.txn_id = a.id"),
          sqlb::Join("left", u1, "a.create_user_id = u1.id"),
          sqlb::Join("left", u2, "a.update_user_id = u2.id"),
  };
  t.m_query.groupBy() = {
          sqlb::GroupByColumn("a", "id"),
          sqlb::GroupByColumn("jt", "id"),
          sqlb::GroupByColumn("party", "id"),
          sqlb::GroupByColumn("u1", "id"),
          sqlb::GroupByColumn("u2", "id"),
  };
}

void query_priority(Table &t) {

  t.m_table = sqlb::ObjectIdentifier("account", "priority", "a");
  t.m_query = sqlb::Query(t.m_table);

  //m_query.setRowIdColumn("id");
  t.m_query.selectedColumns() = {
          sqlb::SelectedColumn({"Id", "id", "", "a", PG_TYPES::INT8, false}),
          sqlb::SelectedColumn({"Rank", "rank", "", "a", PG_TYPES::INT4, false}),
          sqlb::SelectedColumn({"Code", "slug", "", "a", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Name", "name", "", "a", PG_TYPES::TEXT, true}),
//            sqlb::SelectedColumn({"Description", "description", "", "a", PG_TYPES::TEXT, true}),
          sqlb::SelectedColumn({"Created By", "create_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}),
          sqlb::SelectedColumn({"u1_username", "username", "", "u1", PG_TYPES::TEXT, false, 0, 0, false}),
          sqlb::SelectedColumn({"Updated By", "update_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}),
          sqlb::SelectedColumn({"u2_username", "username", "", "u2", PG_TYPES::TEXT, false, 0, 0, false}),
          sqlb::SelectedColumn({"Create Time", "inserted_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
          sqlb::SelectedColumn({"Update Time", "updated_at", "", "a", PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  };

  auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
  auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

  t.m_query.joins() = {
          sqlb::Join("left", u1, "a.create_user_id = u1.id"),
          sqlb::Join("left", u2, "a.update_user_id = u2.id"),
  };
}
