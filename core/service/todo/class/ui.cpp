#include "./ui.h"

#include <utility>
#include "../../../sql/dba.h"

todo::UI::UI(std::shared_ptr<websocket::todo::TodoContext> context_)
    : context(std::move(context_)) {
  setupTable();
}

void todo::UI ::setupTable() {}

nlohmann::json todo::UI::handleEvent(nlohmann::json event, unsigned long next,
                                     nlohmann::json args) {
  auto event_cmp = event[next].get<std::string>();
  if (event_cmp == "menu_data") {
    return {{event, getMenuData()}};
  }
  if (event_cmp == "user_type") {
    return {{event, getUserTypeData()}};
  } else if (event_cmp == "user_title") {
    return {{event, getPageTitle()}};
  } else if (event_cmp == "user_account_type") {
    return {{event, getUserAccountType()}};
  } else if (event_cmp == "catalog_local") {
    return {{event, getCatalogFilterData()}};
  } else if (event_cmp == "ins") {
    return query.ins(event, args);
  } else if (event_cmp == "upd") {
    return query.upd(event, args);
  } else if (event_cmp == "del") {
    return query.del(event, args);
  } else {
    nlohmann::json ret;
    return ret;
  }
}

nlohmann::json todo::UI::getMenuData() {
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

std::string todo::UI::getPageTitle() {
  if (true) {
    return "Admins";
  }
  if (3) {
    return "Executives";
  } else {
    return "";
  }
}

std::string todo::UI::getUserAccountType() {
  if (true) {
    return "Super Admin";
  }
  if (3) {
    return "Admin";
  } else {
    return "Executive";
  }
}

nlohmann::json todo::UI::getUserTypeData() {
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

nlohmann::json todo::UI::getCatalogFilterData() {
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
