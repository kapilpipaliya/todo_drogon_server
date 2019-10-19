#include "menubase.h"
using namespace dgraph::orm;
timeservice::MenuBase::MenuBase() {}

void timeservice::MenuBase::seed_init_data() {
  if (get_menu_count() > 0) return;

  // top_menu
  using A = dgraph::orm::Attributes;
  auto m = A{};
  {
    m.n("menu", "_:m1",
        A{}.s("menu_name", "top_menu")
            .s("name", "Work Packages")
            .s("path", "/work_packages")
            .i("level", 0))  // if cond
        .n("menu", "_:m2",
           A{}.s("menu_name", "top_menu")
               .s("name", "News")
               .s("path", "/news")
               .i("level", 0))  // if cond
        .n("menu", "_:m3",
           A{}.s("menu_name", "top_menu")
               .s("name", "Time sheet")
               .s("path", "/timelog")
               .i("level", 0))  // if cond
        .n("menu", "_:m4",
           A{}.s("menu_name", "top_menu")
               .s("name", "Help")
               .s("path", "/help")
               .s("icon", "icon5 icon-help")
               .i("level", 0));  // if cond
    // create_menu(m);
  }
  {
    m.n("menu", "_:m5",
        A{}.s("menu_name", "account_menu")
            .s("name", "My Page")
            .s("path", "/my/page")
            .i("level", 0))  // if cond
        .n("menu", "_:m6",
           A{}.s("menu_name", "account_menu")
               .s("name", "My Account")
               .s("path", "/my/account")
               .i("level", 0))  // if cond
        .n("menu", "_:m7",
           A{}.s("menu_name", "account_menu")
               .s("name", "Administration")
               .s("path", "/admin")
               .i("level", 0))  // if cond
        .n("menu", "_:m8",
           A{}.s("menu_name", "account_menu")
               .s("name", "Sign Out")
               .s("path", "//logout")
               .s("icon", "icon5 icon-help")
               .i("level", 0));  // if cond
  }
  // application_menu
  {
    m.n("menu", "_:m9",
        A{}.s("menu_name", "application_menu")
            .s("name", "Work packages")
            .s("path", "/work_packages")
            .i("level", 0));  // if cond

    // my_menu
    {
      m.n("menu", "_:m10",
          A{}.s("menu_name", "my_menu")
              .s("name", "Profile")
              .s("path", "/my/account")
              .s("icon", "icon2 icon-user")
              .i("level", 0))  // if cond
          .n("menu", "_:m11",
             A{}.s("menu_name", "my_menu")
                 .s("name", "Settings")
                 .s("path", "/my/settings")
                 .s("icon", "icon2 icon-settings2")
                 .i("level", 0))  // if cond
          .n("menu", "_:m12",
             A{}.s("menu_name", "my_menu")
                 .s("name", "Change password")
                 .s("path", "/my/password")
                 .s("icon", "icon2 icon-locked")
                 .i("level", 0))  // if cond
          .n("menu", "_:m13",
             A{}.s("menu_name", "my_menu")
                 .s("name", "Access token")
                 .s("path", "/my/access_token")
                 .s("icon", "icon5 icon-key")
                 .i("level", 0))

          .n("menu", "_:m14",
             A{}.s("menu_name", "my_menu")
                 .s("name", "Email notifications")
                 .s("path", "/my/mail_notifications")
                 .s("icon", "icon5 icon-news")
                 .i("level", 0))

          .n("menu", "_:m15",
             A{}.s("menu_name", "my_menu")
                 .s("name", "Delete Accoun")
                 .s("path", "/my/delete")
                 .s("icon", "icon5 icon-delete")
                 .i("level", 0))
          .n("menu", "_:m16",
             A{}.s("menu_name", "my_menu")
                 .s("name", "Avatar")
                 .s("path", "/my/avatar")
                 .s("icon", "icon5 icon-avatar")
                 .i("level", 0)

          );  // if cond
    }
    // admin_menu
    {
      m.n("menu", "_:m17",
          A{}.s("menu_name", "admin_menu")
              .s("name", "Overview")
              .s("path", "/admin")
              .s("icon", "icon2 icon-home")
              .i("level", 0))
          .n("menu", "_:m18",
             A{}.s("menu_name", "admin_menu")
                 .s("name", "Users & Permissions")
                 .s("path", "/users")
                 .s("icon", "icon5 icon-group")
                 .i("level", 0)
                 .n("children", "menu", "_:m19",
                    A{}.s("menu_name", "admin_menu")
                        .s("name", "Settings")
                        .s("path", "/users_settings")
                        .i("level", 1))
                 .n("children", "menu", "_:m20",
                    A{}.s("menu_name", "admin_menu")
                        .s("name", "Users")
                        .s("path", "/users")
                        .i("level", 1))
                 .n("children", "menu", "_:m21",
                    A{}.s("menu_name", "admin_menu")
                        .s("name", "Groups")
                        .s("path", "/groups")
                        .i("level", 1))
                 .n("children", "menu", "_:m22",
                    A{}.s("menu_name", "admin_menu")
                        .s("name", "Roles and permissions")
                        .s("path", "/roles")
                        .i("level", 1))
                 .n("children", "menu", "_:m23",
                    A{}.s("menu_name", "admin_menu")
                        .s("name", "Avatars")
                        .s("path", "/avatars")
                        .i("level", 1)))

          .n("menu", "_:m24",
             A{}.s("menu_name", "admin_menu")
                 .s("name", "Work packages")
                 .s("path", "/work_packages/settings")
                 .s("icon", "icon5 icon-home")
                 .i("level", 0)
                 .n("children", "menu", "_:m25",
                    A{}.s("menu_name", "admin_menu")
                        .s("name", "Settings")
                        .s("path", "/work_packages/settings")
                        .i("level", 1))
                 .n("children", "menu", "_:m26",
                    A{}.s("menu_name", "admin_menu")
                        .s("name", "Types")
                        .s("path", "/statuses")
                        .i("level", 1))
                 .n("children", "menu", "_:m27",
                    A{}.s("menu_name", "admin_menu")
                        .s("name", "Status")
                        .s("path", "/workflows")
                        .i("level", 1))
                 .n("children", "menu", "_:m28",
                    A{}.s("menu_name", "admin_menu")
                        .s("name", "Workflow")
                        .s("path", "/custom_fields")
                        .i("level", 1))
                 .n("children", "menu", "_:m29",
                    A{}.s("menu_name", "admin_menu")
                        .s("name", "Custom actions")
                        .s("path", "/custom_action")
                        .i("level", 1))
             //                   .n("children","menu", "_:m30",
             //                      A{}.s("menu_name", "admin_menu")
             //                          .s("name", "Overview")
             //              .s("path", "/attribute_help_texts").i("level", 1)//
             //                          enterprise
             //                      )
             )

          .n("menu", "_:m31",
             A{}.s("menu_name", "admin_menu")
                 .s("name", "Custom fields")
                 .s("path", "/custom_fields")
                 .s("icon", "icon5 icon-custom-fields")
                 .i("level", 0))
          .n("menu", "_:m32",
             A{}.s("menu_name", "admin_menu")
                 .s("name", "Enumerations")
                 .s("path", "/admin/enumerations")
                 .s("icon", "icon5 icon-enumerations")
                 .i("level", 0))
          .n("menu", "_:m33",
             A{}.s("menu_name", "admin_menu")
                 .s("name", "System settings")
                 .s("path", "/settings")
                 .s("icon", "icon5 icon-settings2")
                 .i("level", 0))
          .n("menu", "_:m34",
             A{}.s("menu_name", "admin_menu")
                 .s("name", "Authentication")
                 .s("path", "/authentication_settings")
                 .s("icon", "icon2 icon-two-factor-authentication")
                 .i("level", 0)
                 .n("children", "menu", "_:m35",
                    A{}.s("menu_name", "admin_menu")
                        .s("name", "Settings")
                        .s("path", "/authentication_settings")
                        .i("level", 1))
             //                   .n("menu", "_:m36",
             //                      A{}.s("menu_name", "admin_menu")
             //                          .s("name", "OAuth applications")
             //                          .s("path",
             //                          "/oauth/applications").i("level", 0))
             //                   .n("menu", "_:m37",
             //                      A{}.s("menu_name", "admin_menu")
             //                          .s("name", "LDAP authentication")
             //                          .s("path",
             //                          "/ldap_auth_sources").i("level", 0))
             )
          .n("menu", "_:m38",
             A{}.s("menu_name", "admin_menu")
                 .s("name", "Announcement")
                 .s("path", "/admin/announcements")
                 .s("icon", "icon5 icon-news")
                 .i("level", 0))
          .n("menu", "_:m39",
             A{}.s("menu_name", "admin_menu")
                 .s("name", "Design")
                 .s("path", "/admin/design")
                 .s("icon", "icon5 icon-design")
                 .i("level", 0))
          //            .n("menu", "_:m40",
          //               A{}.s("menu_name", "admin_menu")
          //                   .s("name", "Overview")
          //                   .s("path", "/custom_styles/show")
          //                   .s("icon", "icon5 icon-custom-fields").i("level",
          //                   0))
          .n("menu", "_:m41",
             A{}.s("menu_name", "admin_menu")
                 .s("name", "Colors")
                 .s("path", "/colors")
                 .s("icon", "icon2 icon-status")
                 .i("level", 0))
          .n("menu", "_:m42",
             A{}.s("menu_name", "admin_menu")
                 .s("name", "Enterprise Edition")
                 .s("path", "/admin/enterprises")
                 .s("icon", "icon5 icon-headset")
                 .i("level", 0))
          //            .n("menu", "_:m43",
          //               A{}.s("menu_name", "admin_menu")
          //                   .s("name", "Bdgets")
          //                   .s("path", "/admin/enterprises")
          //                   .s("icon", "icon5 icon-budget").i("level", 0)) //
          //                   add nested

          //            .n("menu", "_:m44",
          //               A{}.s("menu_name", "admin_menu")
          //                   .s("name", "Backlogs")
          //                   .s("path", "/admin/enterprises")
          //                   .s("icon", "icon5 icon-backlog").i("level", 0))
          //                   // add nested
          .n("menu", "_:m45",
             A{}.s("menu_name", "admin_menu")
                 .s("name", "Plugins")
                 .s("path", "/admin/plugins")
                 .s("icon", "icon5 icon-plugins")
                 .i("level", 0))

          .n("menu", "_:m46",
             A{}.s("menu_name", "admin_menu")
                 .s("name", "Webhooks")
                 .s("path", "/admin/webhooks")
                 .s("icon", "icon5 icon-relations")
                 .i("level", 0))
          .n("menu", "_:m47",
             A{}.s("menu_name", "admin_menu")
                 .s("name", "Information")
                 .s("path", "/admin/info")
                 .s("icon", "icon5 icon-info1")
                 .i("level", 0));
    }
    // project_menu
    {
      m.n("menu", "_:p1",
          A{}.s("menu_name", "admin_menu")
              .s("name", "Overview")
              .s("path", "/activities")
              .s("icon", "icon2 icon-home")
              .i("level", 0))

          .n("menu", "_:p2",
             A{}.s("menu_name", "admin_menu")
                 .s("name", "Overview")
                 .s("path", "/versions")
                 .s("icon", "icon5 icon-relations")
                 .i("level", 0))
          .n("menu", "_:p3",
             A{}.s("menu_name", "admin_menu")
                 .s("name", "Overview")
                 .s("path", "/work_packages")
                 .s("icon", "icon5 icon-relations")
                 .i("level", 0))
          .n("menu", "_:p4",
             A{}.s("menu_name", "admin_menu")
                 .s("name", "Overview")
                 .s("path", "/work_packages")
                 .s("icon", "icon5 icon-relations")
                 .i("level", 0))
          .n("menu", "_:p5",
             A{}.s("menu_name", "admin_menu")
                 .s("name", "Overview")
                 .s("path", "/work_packages/calendars")
                 .s("icon", "icon5 icon-relations")
                 .i("level", 0))
          .n("menu", "_:p6",
             A{}.s("menu_name", "admin_menu")
                 .s("name", "Overview")
                 .s("path", "/news")
                 .s("icon", "icon5 icon-relations")
                 .i("level", 0))
          .n("menu", "_:p7",
             A{}.s("menu_name", "admin_menu")
                 .s("name", "Overview")
                 .s("path", "/forums")
                 .s("icon", "icon5 icon-relations")
                 .i("level", 0))
          .n("menu", "_:p8",
             A{}.s("menu_name", "admin_menu")
                 .s("name", "Overview")
                 .s("path", "/repositories")
                 .s("icon", "icon5 icon-relations")
                 .i("level", 0))
          .n("menu", "_:p9",
             A{}.s("menu_name", "admin_menu")
                 .s("name", "Overview")
                 .s("path", "/timelog")
                 .s("icon", "icon5 icon-relations")
                 .i("level", 0))
          .n("menu", "_:p10",
             A{}.s("menu_name", "admin_menu")
                 .s("name", "Overview")
                 .s("path", "/members")
                 .s("icon", "icon5 icon-relations")
                 .i("level", 0))
          .n("menu", "_:p11",
             A{}.s("menu_name", "admin_menu")
                 .s("name", "Overview")
                 .s("path", "/project_settings")
                 .s("icon", "icon5 icon-relations")
                 .i("level", 0));
    }
  }
  create_menu(m);
}

void timeservice::MenuBase::create_menu(dgraph::orm::Attributes& attributes) {
  auto dgraphorm = dgraph::DGraphClientManger::getDGraphOrm("1");
  auto menu = dgraphorm->newmodel("menu");
  auto response = new api::Response;
  {
    auto status = menu->create(attributes, response);

    switch (status) {
      case dgraph::orm::success: {
        auto j = nlohmann::json::parse(response->json());
        auto uid = j["menu"][0]["uid"].get<std::string>();
        break;
      }
      case dgraph::orm::unique_error:
        break;
      default:
        break;
    }
  }
  delete response;
}

int timeservice::MenuBase::get_menu_count() {
  auto dgraphorm = dgraph::DGraphClientManger::getDGraphOrm("1");
  auto menu = dgraphorm->newmodel("menu");
  auto response = new api::Response;
  menu->method(dgraph::orm::MethodsType::type, "menu", "",
               dgraph::orm::Params::builder{}
                   .attributes(dgraph::orm::Attributes{}.no(true))
                   .inc(dgraph::orm::IncludeBase::builder{}
                            .name("uid")
                            //.as("user_count")
                            .count(true)
                            .build())
                   .build_shared(),
               response);
  auto j = nlohmann::json::parse(response->json());
  return j["menu"][0]["count"].get<int>();
}
