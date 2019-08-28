#include "ui.h"
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
            json::array({"Songs","music/browse"}),
            json::array({"Profile", "music/profile"}),
            json::array({"Password Change", "music/update_password"}),
            json::array({"Logout", "music/logout"})
        });
        return j;
    } else if (context->user.type == "admin"){
        json j = json::array({
            json::array({"Dashboard", "music/dashboard"}),
            json::array({"Executives", "music/users"}),
            json::array({"Songs","music/browse"}),
            json::array({"Profile", "music/profile"}),
            json::array({"Password Change", "music/update_password"}),
            json::array({"Logout", "music/logout"})
        }) ;
        return j;
    } else {
        return json::array();
    }
}
