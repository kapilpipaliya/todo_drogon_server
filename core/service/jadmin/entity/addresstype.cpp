#include "addresstype.h"

#include <utility>
using namespace jadmin;

AddressType::AddressType(JAdminContextPtr context_)
    : context(std::move(context_)) {
  getQuery() =
      sqlb::Query(sqlb::ObjectIdentifier("entity", "address_type", "a"));
}

void AddressType::setupTable() {
  // m_query.setRowIdColumn("id");
  getQuery().setSelectedColumns({
      sqlb::SelectedColumn({"Id", "id", "", "a", PG_TYPES::INT8, true}),
      sqlb::SelectedColumn({"Name", "name", "", "a", PG_TYPES::TEXT, true}),
      sqlb::SelectedColumn({"Create Time", "inserted_at", "", "a",
                            PG_TYPES::TIMESTAMP, true, 0, 0, false}),
      sqlb::SelectedColumn({"Update Time", "updated_at", "", "a",
                            PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  });
}

nlohmann::json AddressType::ins(nlohmann::json event, nlohmann::json args) {
  return insBase(event, args, "name", "$1", args[0]["name"].get<std::string>());
}

nlohmann::json AddressType::upd(nlohmann::json event, nlohmann::json args) {
  return updBase(event, args, "name", "$1", args[0]["name"].get<std::string>());
}
