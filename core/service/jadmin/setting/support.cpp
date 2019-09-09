#include "support.h"

#include <utility>
using namespace jadmin;

Support::Support(JAdminContextPtr context_) : context(std::move(context_)) {
  getTable().query() =
      sqlb::Query(sqlb::ObjectIdentifier("setting", "support", "a"));
}

void Support::setupTable() {
  // m_query.setRowIdColumn("id");
  getTable().query().selectedColumns() = {
      sqlb::SelectedColumn({"Id", "id", "", "a", PG_TYPES::INT8, false}),
      sqlb::SelectedColumn({"Name", "name", "", "a", PG_TYPES::TEXT, true}),
      sqlb::SelectedColumn({"Email", "email", "", "a", PG_TYPES::TEXT, true}),
      sqlb::SelectedColumn({"Phone", "phone", "", "a", PG_TYPES::TEXT, true}),
      sqlb::SelectedColumn(
          {"Message", "message", "", "a", PG_TYPES::TEXT, true}),
      // sqlb::SelectedColumn({"Created By", "create_user_id", "", "a",
      // PG_TYPES::INT8, true, 1, 0, false}),
      // sqlb::SelectedColumn({"u1_username", "username", "", "u1",
      // PG_TYPES::TEXT, false, 0, 0, false}), sqlb::SelectedColumn({"Updated
      // By", "update_user_id", "", "a", PG_TYPES::INT8, true, 1, 0, false}),
      // sqlb::SelectedColumn({"u2_username", "username", "", "u2",
      // PG_TYPES::TEXT, false, 0, 0, false}),
      sqlb::SelectedColumn({"Create Time", "inserted_at", "", "a",
                            PG_TYPES::TIMESTAMP, true, 0, 0, false}),
      sqlb::SelectedColumn({"Update Time", "updated_at", "", "a",
                            PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  };

  // auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
  // auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

  getTable().query().joins() = {
      // sqlb::Join("left", u1, "gt.create_user_id = u1.id"),
      // sqlb::Join("left", u2, "a.update_user_id = u2.id"),
  };
}

json Support::ins(json event, json args) {
  return insBase(event, args, "name, email, phone, message", "$1, $2, $3, $4",
                 args[0]["name"].get<std::string>(),
                 args[0]["email"].get<std::string>(),
                 args[0]["phone"].get<std::string>(),
                 args[0]["message"].get<std::string>());
}

json Support::upd(json event, json args) {
  return updBase(event, args, "name, email, phone, message", "$1, $2, $3, $4",
                 args[0]["name"].get<std::string>(),
                 args[0]["email"].get<std::string>(),
                 args[0]["phone"].get<std::string>(),
                 args[0]["message"].get<std::string>());
}
