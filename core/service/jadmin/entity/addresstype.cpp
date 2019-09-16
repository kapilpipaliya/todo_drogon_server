#include "addresstype.h"

#include <utility>

namespace jewel {
namespace service {
AddressType::AddressType(
    std::shared_ptr<websocket::jewel::JAdminContext> context_)
    : context(std::move(context_)) {
  query = sql::Query(sql::ObjectIdentifier("entity", "address_type", "a"));
  setupTable();
}

nlohmann::json AddressType::handleEvent(nlohmann::json event,
                                        unsigned long next,
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
    return query.del(event, args);
  } else {
    nlohmann::json ret;
    return ret;
  }
}

void AddressType::setupTable() {
  // m_query.setRowIdColumn("id");
  query.setSelectedColumns({
      sql::SelectedColumn({"Id", "id", "", "a", sql::PG_TYPES::INT8, true}),
      sql::SelectedColumn({"Name", "name", "", "a", sql::PG_TYPES::TEXT, true}),
      sql::SelectedColumn({"Create Time", "inserted_at", "", "a",
                           sql::PG_TYPES::TIMESTAMP, true, 0, 0, false}),
      sql::SelectedColumn({"Update Time", "updated_at", "", "a",
                           sql::PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  });
}

nlohmann::json AddressType::ins(nlohmann::json event, nlohmann::json args) {
  return query.insBase(event, args, "name", "$1",
                       args[0]["name"].get<std::string>());
}

nlohmann::json AddressType::upd(nlohmann::json event, nlohmann::json args) {
  return query.updBase(event, args, "name", "$1",
                       args[0]["name"].get<std::string>());
}
}  // namespace service
}  // namespace jadmin
