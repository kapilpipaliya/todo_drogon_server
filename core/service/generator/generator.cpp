#include "generator.h"

#include <utility>

namespace generator {
namespace service {
Generator::Generator() {
  query = sql::Query(sql::ObjectIdentifier("public", "generator", "g"));
  setupTable();
}

nlohmann::json Generator::handleEvent(nlohmann::json event, unsigned long next,
                                      nlohmann::json args) {
  auto event_cmp = event[next].get<int>();
  if (event_cmp == 1) {
    return query.allData(event, args);
  }
  if (event_cmp == 0) {
    return query.headerData(event, args);
  } else if (event_cmp == 2) {
    return query.ins(event, args);
  } else if (event_cmp == 3) {
    return query.upd(event, args);
  } else if (event_cmp == 4) {
    return query.del(event, args);
  } else {
    nlohmann::json ret;
    return ret;
  }
}

void Generator::setupTable() {
  // m_query.setRowIdColumn("id");
  query.setSelectedColumns(
      {sql::SelectedColumn({"Id", "id", "", "g", sql::PG_TYPES::INT8, true}),
       sql::SelectedColumn(
           {"Language", "language", "", "g", sql::PG_TYPES::TEXT, true}),
       sql::SelectedColumn(
           {"Project", "project", "", "g", sql::PG_TYPES::TEXT, true}),
       sql::SelectedColumn(
           {"name", "name", "", "g", sql::PG_TYPES::TEXT, true}),
       sql::SelectedColumn(
           {"Template", "template", "", "g", sql::PG_TYPES::TEXT, true}),
       sql::SelectedColumn(
           {"Result", "result", "", "g", sql::PG_TYPES::TEXT, true})});

  query.setPrimaryKey({{"g", "id", sql::PG_TYPES::INT8}});
}
}  // namespace service
}  // namespace generator
