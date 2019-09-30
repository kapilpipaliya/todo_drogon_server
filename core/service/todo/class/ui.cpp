#include "./ui.h"

#include <utility>
#include "../../../sql/dba.h"
namespace todo {
namespace service {
UI::UI(std::shared_ptr<websocket::todo::TodoContext> context_)
    : context(std::move(context_)) {
  query = sql::Query(sql::ObjectIdentifier("public", "ui", "u"));
  setupTable();
}

void UI ::setupTable() {
  // m_query.setRowIdColumn("id");
  query.setSelectedColumns(
      {sql::SelectedColumn({"Id", "id", "", "u", sql::PG_TYPES::INT8, true}),
       sql::SelectedColumn({"Key", "key", "", "u", sql::PG_TYPES::TEXT, true}),
       sql::SelectedColumn(
           {"Purpose", "purpose", "", "u", sql::PG_TYPES::TEXT, true}),
       sql::SelectedColumn(
           {"Description", "description", "", "u", sql::PG_TYPES::TEXT, true}),
       sql::SelectedColumn(
           {"Parent", "parent_id", "", "u", sql::PG_TYPES::INT8, true, 1, 1}),
       sql::SelectedColumn({"Key", "",
                            "u1.id || ' ' || u1.key || ' ' || u1.description",
                            "u1", sql::PG_TYPES::TEXT, false, 0, 0, false})});

  query.setPrimaryKey({{"u", "id", sql::PG_TYPES::INT8}});
  auto u = sql::ObjectIdentifier("public", "ui", "u1");
  query.setJoins({sql::Join("left", u, "u1.id = u.parent_id")});
}

nlohmann::json UI::handleEvent(nlohmann::json event, unsigned long next,
                               nlohmann::json args) {
  auto event_cmp = event[next].get<int>();
  //  if (event_cmp == "menu_data") {
  //    return {{event, getMenuData()}};
  //  }
  //  if (event_cmp == "user_type") {
  //    return {{event, getUserTypeData()}};
  //  } else if (event_cmp == "user_title") {
  //    return {{event, getPageTitle()}};
  //  } else if (event_cmp == "user_account_type") {
  //    return {{event, getUserAccountType()}};
  //  } else if (event_cmp == "catalog_local") {
  //    return {{event, getCatalogFilterData()}};
  //  } else
  if (event_cmp == header) {
    return query.headerData(event, args);
  } else if (event_cmp == all) {
    return query.allData(event, args);
  } else if (event_cmp == insert) {
    return query.ins(event, args);
  } else if (event_cmp == update) {
    return query.upd(event, args);
  } else if (event_cmp == delete_) {
    return query.del(event, args);
  } else if (event_cmp == count) {
    return query.count(event, args);
  } else if (event_cmp == key) {
    auto new_event = event;
    new_event.erase(0);
    auto i = new_event.size();
    unsigned long l = 1;
    long key = 0;
    while (l < i) {
      std::string key2;
      if (new_event[l].is_string()) {
        key2 = new_event[l].get<std::string>();
      } else if (new_event[l].is_number()) {
        key2 = std::to_string(new_event[l].get<int>());
      }
      std::string sql;
      if (i == 0) {
        sql =
            "select id, key, description from public.ui where u1.key = $1 and "
            "u1.parent_id is null";
      } else {
        sql =
            "select id, key, description from public.ui where u1.key = $1 and "
            "parent_id = $2";
      }
      auto result = sql::Dba::write(sql, key);
      l++;
      std::string next_key;
      if (new_event[l].is_string()) {
        next_key = new_event[l].get<std::string>();
      } else if (new_event[l].is_number()) {
        next_key = std::to_string(new_event[l].get<int>());
      }
      //      auto it =
      //          std::find_if(result.begin(), result.end(),
      //                       [next_key](const drogon::orm::Row& value) {
      //                         return value["key"].as<std::string>() ==
      //                         next_key;
      //                       });
      //      l++;
      //      if (it != result.end()) {
      //        // return it["description"].as<std::string>();
      //        return key;
      //        // it["key"].as<std::string>();
      //      }
    }

    return query.count(event, args);
  } else {
    nlohmann::json ret;
    return ret;
  }
}

nlohmann::json UI::getValueData() {}

nlohmann::json UI::getMenuData() {
  if (1) {
    nlohmann::json j = nlohmann::json::array(
        {nlohmann::json::array({"Dashboard", "todo/dashboard"}),
         nlohmann::json::array({"Admins", "todo/users"}),
         nlohmann::json::array({"Catalogs", "todo/catalogs"}),
         nlohmann::json::array({"todo", "todo/browse"}),
         //            nlohmann::json::array({"Profile", "todo/profile"}),
         nlohmann::json::array({"Password Change", "todo/update_password"}),
         nlohmann::json::array({"Logout", "todo/logout"})});
    return j;
  }
  if (2) {
    nlohmann::json j = nlohmann::json::array(
        {nlohmann::json::array({"Dashboard", "todo/dashboard"}),
         nlohmann::json::array({"Executives", "todo/users"}),
         //            nlohmann::json::array({"Songs","todo/browse"}),
         //            nlohmann::json::array({"Profile", "todo/profile"}),
         nlohmann::json::array({"Password Change", "todo/update_password"}),
         nlohmann::json::array({"Logout", "todo/logout"})});
    return j;
  } else if (3) {
    nlohmann::json j = nlohmann::json::array(
        {nlohmann::json::array({"Dashboard", "todo/dashboard"}),
         //                                 nlohmann::json::array({"Songs","todo/browse"}),
         //                                 nlohmann::json::array({"Profile",
         //                                 "todo/profile"}),
         nlohmann::json::array({"Password Change", "todo/update_password"}),
         nlohmann::json::array({"Logout", "todo/logout"})});
    return j;
  } else {
    return nlohmann::json::array();
  }
}

std::string UI::getPageTitle() {
  if (true) {
    return "Admins";
  }
  if (3) {
    return "Executives";
  } else {
    return "";
  }
}

std::string UI::getUserAccountType() {
  if (true) {
    return "Super Admin";
  }
  if (3) {
    return "Admin";
  } else {
    return "Executive";
  }
}

nlohmann::json UI::getUserTypeData() {
  if (true) {
    nlohmann::json j = nlohmann::json::array({
        nlohmann::json::array({"All", nullptr}),
        nlohmann::json::array({"Super Admin", "super admin"}),
        nlohmann::json::array({"Admins", "admin"}),
        nlohmann::json::array({"Executives", "executive"}),
    });
    return j;
  }
  if (true) {
    nlohmann::json j = nlohmann::json::array({
        nlohmann::json::array({"All", nullptr}),
        nlohmann::json::array({"Executives", "executive"}),
    });
    return j;
  } else {
    return nlohmann::json::array();
  }
}

nlohmann::json UI::getCatalogFilterData() {
  std::string sql = "select id, name from music.catalog order by id";
  auto r = sql::Dba::read(sql);
  nlohmann::json out =
      nlohmann::json::array({nlohmann::json::array({"All", nullptr})});
  for (const auto& i : r) {
    auto id = i["id"].as<long>();
    auto name = i["name"].as<std::string>();
    out.push_back(nlohmann::json::array({name, id}));
  }

  return out;
}
}  // namespace service
}  // namespace todo
