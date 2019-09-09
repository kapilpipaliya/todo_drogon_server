#include "departmenttype.h"

#include <utility>
using namespace jadmin;

DepartmentType::DepartmentType(JAdminContextPtr context_)
    : context(std::move(context_)) {
  getTable().query() =
      sqlb::Query(sqlb::ObjectIdentifier("mfg", "department_type", "m"));
}

void DepartmentType::setupTable() {
  // m_query.setRowIdColumn("id");
  getTable().query().selectedColumns() = {
      sqlb::SelectedColumn({"Id", "id", "", "m", PG_TYPES::INT8, false}),
      sqlb::SelectedColumn({"Name", "name", "", "m", PG_TYPES::TEXT, true}),
      //            sqlb::SelectedColumn({"Created By", "create_user_id", "",
      //            "m", PG_TYPES::INT8, true, 1}),
      //            sqlb::SelectedColumn({"u1_username", "username", "", "u1",
      //            PG_TYPES::TEXT, false, 0, 0, false}),
      //            sqlb::SelectedColumn({"Updated By", "update_user_id", "",
      //            "m", PG_TYPES::INT8, true, 1}),
      //            sqlb::SelectedColumn({"u2_username", "username", "", "u2",
      //            PG_TYPES::TEXT, false, 0, 0, false}),
      sqlb::SelectedColumn({"Create Time", "inserted_at", "", "m",
                            PG_TYPES::TIMESTAMP, true, 0, 0, false}),
      sqlb::SelectedColumn({"Update Time", "updated_at", "", "m",
                            PG_TYPES::TIMESTAMP, true, 0, 0, false}),
  };

  //        auto u1 = sqlb::ObjectIdentifier("entity", "entity_user", "u1");
  //        auto u2 = sqlb::ObjectIdentifier("entity", "entity_user", "u2");

  getTable().query().joins() = {
      //            sqlb::Join("left", u1, "m.create_user_id = u1.id"),
      //            sqlb::Join("left", u2, "m.update_user_id = u2.id"),
  };
}

json DepartmentType::ins(json event, json args) {
  return insBase(event, args, "name", "$1", args[0]["name"].get<std::string>());
}

json DepartmentType::upd(json event, json args) {
  return updBase(event, args, "name", "$1", args[0]["name"].get<std::string>());
}
