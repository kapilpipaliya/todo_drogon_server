#include "ui.h"
#include "dba.h"
using namespace  madmin;
UI::UI(const MAdminContextPtr &context_): BaseService(context_)
{

}

void UI::setupTable()
{

}

nlohmann::json UI::handleEvent(nlohmann::json event, unsigned long next, nlohmann::json args)
{
    auto event_cmp = event[next].get<std::string>();
    if (event_cmp == "menu_data") {
        return {{event, getMenuData()}};
    } else if (event_cmp  == "user_type") {
        return {{event, getUserTypeData()}};
    } else if (event_cmp  == "user_title") {
        return {{event, getPageTitle()}};
    } else if (event_cmp  == "user_account_type") {
        return {{event, getUserAccountType()}};
    } else if (event_cmp  == "catalog_local") {
        return {{event, getCatalogFilterData()}};
    } else if (event_cmp  == "ins") {
        return ins(event, args);
    } else if (event_cmp  == "ins") {
        return ins(event, args);
    } else if (event_cmp  == "upd") {
        return upd(event, args);
    } else if (event_cmp  == "del") {
        return del(event, args);
    } else {
        return Json::nullValue;
    }
}

nlohmann::json UI::getMenuData()
{
    if(context->user.type == "super admin"){
        json j = json::array({
            json::array({"Dashboard", "music/dashboard"}),
            json::array({"Admins","music/users"}),
            json::array({"Catalogs","music/catalogs"}),
            json::array({"Songs","music/browse"}),
//            json::array({"Profile", "music/profile"}),
            json::array({"Password Change", "music/update_password"}),
            json::array({"Logout", "music/logout"})
        });
        return j;
    } else if (context->user.type == "admin"){
        json j = json::array({
            json::array({"Dashboard", "music/dashboard"}),
            json::array({"Executives", "music/users"}),
//            json::array({"Songs","music/browse"}),
//            json::array({"Profile", "music/profile"}),
            json::array({"Password Change", "music/update_password"}),
            json::array({"Logout", "music/logout"})
        });
        return j;
    } else if (context->user.type == "executive"){
        json j = json::array({
                                 json::array({"Dashboard", "music/dashboard"}),
//                                 json::array({"Songs","music/browse"}),
//                                 json::array({"Profile", "music/profile"}),
                                 json::array({"Password Change", "music/update_password"}),
                                 json::array({"Logout", "music/logout"})
                             }) ;
        return j;
    } else {
        return json::array();
    }
}

std::string UI::getPageTitle()
{
    if(context->user.type == "super admin"){
        return "Admins";
    } else if (context->user.type == "admin"){
       return "Executives";
    } else {
        return "";
    }
}

std::string UI::getUserAccountType()
{
    if(context->user.type == "super admin"){
        return "Super Admin";
    } else if (context->user.type == "admin"){
       return "Admin";
    } else {
        return "Executive";
    }
}

nlohmann::json UI::getUserTypeData()
{
    if(context->user.type == "super admin"){
        json j = json::array({
                                 json::array({"All", nullptr}),
                                    json::array({"Super Admin", "super admin"}),
                                    json::array({"Admins","admin"}),
                                    json::array({"Executives","executive"}),
        });
        return j;
    } else if (context->user.type == "admin"){
        json j = json::array({
                                  json::array({"All", nullptr}),
                                 json::array({"Executives","executive"}),
        }) ;
        return j;
    } else {
        return json::array();
    }
}

nlohmann::json UI::getCatalogFilterData()
{
    std::string sql = "select id, name from music.catalog order by id";
    auto r = Dba::read(sql);
    json out = json::array({
                    json::array({"All", nullptr})
                });
    for (auto i : r) {
        auto id = i["id"].as<long>();
        auto name = i["name"].as<std::string>();
        out.push_back(json::array({name, id}));
    }

    return out;
}
