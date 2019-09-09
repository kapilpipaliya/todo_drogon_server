#include "contacttype.h"

#include <utility>
using namespace jadmin;

ContactType::ContactType(JAdminContextPtr context_)
    : context(std::move(context_)) {
  getTable().query() =
      sqlb::Query(sqlb::ObjectIdentifier("entity", "contact_type", "a"));
}

void ContactType::setupTable() {
  // m_query.setRowIdColumn("id");
  getTable().query().selectedColumns() = {
      sqlb::SelectedColumn({"Id", "id", "", "a", PG_TYPES::INT8, true}),
      sqlb::SelectedColumn({"Name", "name", "", "a", PG_TYPES::TEXT, true}),
      sqlb::SelectedColumn({"Create Time", "inserted_at", "", "a",
                            PG_TYPES::TIMESTAMP, true, 0, 0, false}),
      sqlb::SelectedColumn({"Update Time", "updated_at", "", "a",
                            PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  };
}

json ContactType::ins(json event, json args) {
  return insBase(event, args, "name", "$1", args[0]["name"].get<std::string>());
}

json ContactType::upd(json event, json args) {
  return updBase(event, args, "name", "$1", args[0]["name"].get<std::string>());
}
