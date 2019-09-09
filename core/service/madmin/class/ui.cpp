#include "ui.h"

#include <utility>
#include "../../dba.h"

madmin::UI::UI(MAdminContextPtr context_) : context(std::move(context_)) {
  setupTable();
}

void madmin::UI ::setupTable() {}

nlohmann::json madmin::UI::handleEvent(nlohmann::json event, unsigned long next,
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

nlohmann::json madmin::UI::getMenuData() {
  if (context->getUser().type == "super admin") {
    nlohmann::json j = nlohmann::json::array(
        {nlohmann::json::array({"Dashboard", "music/dashboard"}),
         nlohmann::json::array({"Admins", "music/users"}),
         nlohmann::json::array({"Catalogs", "music/catalogs"}),
         nlohmann::json::array({"Music", "music/browse"}),
         //            nlohmann::json::array({"Profile", "music/profile"}),
         nlohmann::json::array({"Password Change", "music/update_password"}),
         nlohmann::json::array({"Logout", "music/logout"})});
    return j;
  }
  if (context->getUser().type == "admin") {
    nlohmann::json j = nlohmann::json::array(
        {nlohmann::json::array({"Dashboard", "music/dashboard"}),
         nlohmann::json::array({"Executives", "music/users"}),
         //            nlohmann::json::array({"Songs","music/browse"}),
         //            nlohmann::json::array({"Profile", "music/profile"}),
         nlohmann::json::array({"Password Change", "music/update_password"}),
         nlohmann::json::array({"Logout", "music/logout"})});
    return j;
  } else if (context->getUser().type == "executive") {
    nlohmann::json j = nlohmann::json::array(
        {nlohmann::json::array({"Dashboard", "music/dashboard"}),
         //                                 nlohmann::json::array({"Songs","music/browse"}),
         //                                 nlohmann::json::array({"Profile",
         //                                 "music/profile"}),
         nlohmann::json::array({"Password Change", "music/update_password"}),
         nlohmann::json::array({"Logout", "music/logout"})});
    return j;
  } else {
    return nlohmann::json::array();
  }
}

std::string madmin::UI::getPageTitle() {
  if (context->getUser().type == "super admin") {
    return "Admins";
  }
  if (context->getUser().type == "admin") {
    return "Executives";
  } else {
    return "";
  }
}

std::string madmin::UI::getUserAccountType() {
  if (context->getUser().type == "super admin") {
    return "Super Admin";
  }
  if (context->getUser().type == "admin") {
    return "Admin";
  } else {
    return "Executive";
  }
}

nlohmann::json madmin::UI::getUserTypeData() {
  if (context->getUser().type == "super admin") {
    nlohmann::json j = nlohmann::json::array({
        nlohmann::json::array({"All", nullptr}),
        nlohmann::json::array({"Super Admin", "super admin"}),
        nlohmann::json::array({"Admins", "admin"}),
        nlohmann::json::array({"Executives", "executive"}),
    });
    return j;
  }
  if (context->getUser().type == "admin") {
    nlohmann::json j = nlohmann::json::array({
        nlohmann::json::array({"All", nullptr}),
        nlohmann::json::array({"Executives", "executive"}),
    });
    return j;
  } else {
    return nlohmann::json::array();
  }
}

nlohmann::json madmin::UI::getCatalogFilterData() {
  std::string sql = "select id, name from music.catalog order by id";
  auto r = Dba::read(sql);
  nlohmann::json out =
      nlohmann::json::array({nlohmann::json::array({"All", nullptr})});
  for (const auto& i : r) {
    auto id = i["id"].as<long>();
    auto name = i["name"].as<std::string>();
    out.push_back(nlohmann::json::array({name, id}));
  }

  return out;
}
