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
            .i("level", 0)
            .i("position", 1))  // if cond
        .n("menu", "_:m2",
           A{}.s("menu_name", "top_menu")
               .s("name", "News")
               .s("path", "/news")
               .i("level", 0)
               .i("position", 2))  // if cond
        .n("menu", "_:m3",
           A{}.s("menu_name", "top_menu")
               .s("name", "Time sheet")
               .s("path", "/timelog")
               .i("level", 0)
               .i("position", 3))  // if cond
        .n("menu", "_:m4",
           A{}.s("menu_name", "top_menu")
               .s("name", "Help")
               .s("path", "/help")
               .s("icon", "mif-help")
               .i("level", 0)
               .i("position", 4));  // if cond
    // create_menu(m);
  }
  {
    m.n("menu", "_:m5",
        A{}.s("menu_name", "account_menu")
            .s("name", "My Page")
            .s("path", "/my/page")
            .i("level", 0)
            .i("position", 1))  // if cond
        .n("menu", "_:m6",
           A{}.s("menu_name", "account_menu")
               .s("name", "My Account")
               .s("path", "/my/account")
               .i("level", 0)
               .i("position", 2))  // if cond
        .n("menu", "_:m7",
           A{}.s("menu_name", "account_menu")
               .s("name", "Administration")
               .s("path", "/admin")
               .i("level", 0)
               .i("position", 3))  // if cond
        .n("menu", "_:m8",
           A{}.s("menu_name", "account_menu")
               .s("name", "Sign Out")
               .s("path", "//logout")
               .s("icon", "mif-help")
               .i("level", 0)
               .i("position", 4));  // if cond
  }
  // application_menu
  {
    m.n("menu", "_:m9",
        A{}.s("menu_name", "application_menu")
            .s("name", "Work packages")
            .s("path", "/work_packages")
            .i("level", 0)
            .i("position", 1));  // if cond

    // my_menu
    {
      m.n("menu", "_:m10",
          A{}.s("menu_name", "my_menu")
              .s("name", "Profile")
              .s("path", "/my/account")
              .s("icon", "mif-user")
              .i("level", 0)
              .i("position", 1))  // if cond
          .n("menu", "_:m11",
             A{}.s("menu_name", "my_menu")
                 .s("name", "Settings")
                 .s("path", "/my/settings")
                 .s("icon", "mif-my-location")
                 .i("level", 0)
                 .i("position", 2))  // if cond
          .n("menu", "_:m12",
             A{}.s("menu_name", "my_menu")
                 .s("name", "Change password")
                 .s("path", "/my/password")
                 .s("icon", "mif-lock")
                 .i("level", 0)
                 .i("position", 3))  // if cond
          .n("menu", "_:m13",
             A{}.s("menu_name", "my_menu")
                 .s("name", "Access token")
                 .s("path", "/my/access_token")
                 .s("icon", "mif-key")
                 .i("level", 0)
                 .i("position", 4))

          .n("menu", "_:m14",
             A{}.s("menu_name", "my_menu")
                 .s("name", "Email notifications")
                 .s("path", "/my/mail_notifications")
                 .s("icon", "mif-news")
                 .i("level", 0)
                 .i("position", 5))

          .n("menu", "_:m15",
             A{}.s("menu_name", "my_menu")
                 .s("name", "Delete Account")
                 .s("path", "/my/delete")
                 .s("icon", "mif-user-minus")
                 .i("level", 0)
                 .i("position", 6))
          .n("menu", "_:m16",
             A{}.s("menu_name", "my_menu")
                 .s("name", "Avatar")
                 .s("path", "/my/avatar")
                 .s("icon", "mif-image")
                 .i("level", 0)
                 .i("position", 7)

          );  // if cond
    }
    // admin_menu
    {
      m.n("menu", "_:m17",
          A{}.s("menu_name", "admin_menu")
              .s("name", "Overview")
              .s("path", "/admin")
              .s("icon", "mif-meter")
              .i("level", 0)
              .i("position", 1))
          .n("menu", "_:m18",
             A{}.s("menu_name", "admin_menu")
                 .s("name", "Users & Permissions")
                 .s("path", "/admin/users")
                 .s("icon", "mif-users")
                 .i("level", 0)
                 .i("position", 2)
                 .n("children", "menu", "_:m19",
                    A{}.s("menu_name", "admin_menu")
                        .s("name", "Settings")
                        .s("path", "/admin/users/users_settings")
                        .i("level", 1)
                        .i("position", 1))
                 .n("children", "menu", "_:m20",
                    A{}.s("menu_name", "admin_menu")
                        .s("name", "Users")
                        .s("path", "/admin/users/users")
                        .i("level", 1)
                        .i("position", 2))
                 .n("children", "menu", "_:m21",
                    A{}.s("menu_name", "admin_menu")
                        .s("name", "Groups")
                        .s("path", "/admin/users/groups")
                        .i("level", 1)
                        .i("position", 3))
                 .n("children", "menu", "_:m22",
                    A{}.s("menu_name", "admin_menu")
                        .s("name", "Roles and permissions")
                        .s("path", "/admin/users/roles")
                        .i("level", 1)
                        .i("position", 4))
                 .n("children", "menu", "_:m23",
                    A{}.s("menu_name", "admin_menu")
                        .s("name", "Avatars")
                        .s("path", "/admin/users/avatars")
                        .i("level", 1)
                        .i("position", 5)))

          .n("menu", "_:m24",
             A{}.s("menu_name", "admin_menu")
                 .s("name", "Work packages")
                 .s("path", "/admin/work_packages/settings")
                 .s("icon", "mif-assignment")
                 .i("level", 0)
                 .i("position", 3)
                 .n("children", "menu", "_:m25",
                    A{}.s("menu_name", "admin_menu")
                        .s("name", "Settings")
                        .s("path", "/admin/work_packages/settings")
                        .i("level", 1)
                        .i("position", 1))
                 .n("children", "menu", "_:m26",
                    A{}.s("menu_name", "admin_menu")
                        .s("name", "Types")
                        .s("path", "/admin/work_packages/statuses")
                        .i("level", 1)
                        .i("position", 2))
                 .n("children", "menu", "_:m27",
                    A{}.s("menu_name", "admin_menu")
                        .s("name", "Status")
                        .s("path", "/admin/work_packages/workflows")
                        .i("level", 1)
                        .i("position", 3))
                 .n("children", "menu", "_:m28",
                    A{}.s("menu_name", "admin_menu")
                        .s("name", "Workflow")
                        .s("path", "/admin/work_packages/custom_fields")
                        .i("level", 1)
                        .i("position", 4))
                 .n("children", "menu", "_:m29",
                    A{}.s("menu_name", "admin_menu")
                        .s("name", "Custom actions")
                        .s("path", "/admin/work_packages/custom_action")
                        .i("level", 1)
                        .i("position", 5))
             //                   .n("children","menu", "_:m30",
             //                      A{}.s("menu_name", "admin_menu")
             //                          .s("name", "Overview")
             //              .s("path", "/attribute_help_texts").i("level",
             //              1).i("position", 6)//
             //                          enterprise
             //                      )
             )

          .n("menu", "_:m31",
             A{}.s("menu_name", "admin_menu")
                 .s("name", "Custom fields")
                 .s("path", "/admin/custom_fields")
                 .s("icon", "mif-battery-empty")
                 .i("level", 0)
                 .i("position", 4))
          .n("menu", "_:m32",
             A{}.s("menu_name", "admin_menu")
                 .s("name", "Enumerations")
                 .s("path", "/admin/enumerations")
                 .s("icon", "mif-equalizer-v")
                 .i("level", 0)
                 .i("position", 5))
          .n("menu", "_:m33",
             A{}.s("menu_name", "admin_menu")
                 .s("name", "System settings")
                 .s("path", "/admin/settings")
                 .s("icon", "mif-hammer")
                 .i("level", 0)
                 .i("position", 6))
          .n("menu", "_:m34",
             A{}.s("menu_name", "admin_menu")
                 .s("name", "Authentication")
                 .s("path", "/admin/authentication/settings")
                 .s("icon", "mif-lock")
                 .i("level", 0)
                 .i("position", 7)
                 .n("children", "menu", "_:m35",
                    A{}.s("menu_name", "admin_menu")
                        .s("name", "Settings")
                        .s("path", "/admin/authentication/settings")
                        .i("level", 1)
                        .i("position", 1))
             //                   .n("menu", "_:m36",
             //                      A{}.s("menu_name", "admin_menu")
             //                          .s("name", "OAuth applications")
             //                          .s("path",
             //                          "/oauth/applications").i("level",
             //                          0).i("position", 2))
             //                   .n("menu", "_:m37",
             //                      A{}.s("menu_name", "admin_menu")
             //                          .s("name", "LDAP authentication")
             //                          .s("path",
             //                          "/ldap_auth_sources").i("level",
             //                          0).i("position", 3))
             )
          .n("menu", "_:m38",
             A{}.s("menu_name", "admin_menu")
                 .s("name", "Announcement")
                 .s("path", "/admin/announcements")
                 .s("icon", "mif-news")
                 .i("level", 0)
                 .i("position", 8))
          .n("menu", "_:m39",
             A{}.s("menu_name", "admin_menu")
                 .s("name", "Design")
                 .s("path", "/admin/design")
                 .s("icon", "mif-pencil")
                 .i("level", 0)
                 .i("position", 9))
          //            .n("menu", "_:m40",
          //               A{}.s("menu_name", "admin_menu")
          //                   .s("name", "Overview")
          //                   .s("path", "/admin/custom_styles/show")
          //                   .s("icon", "icon5 icon-custom-fields").i("level",
          //                   0).i("position", 1))
          .n("menu", "_:m41",
             A{}.s("menu_name", "admin_menu")
                 .s("name", "Colors")
                 .s("path", "/admin/colors")
                 .s("icon", "mif-pencil")
                 .i("level", 0)
                 .i("position", 10))
          .n("menu", "_:m42",
             A{}.s("menu_name", "admin_menu")
                 .s("name", "Enterprise Edition")
                 .s("path", "/admin/enterprises")
                 .s("icon", "mif-shopping-basket")
                 .i("level", 0)
                 .i("position", 11))
          //            .n("menu", "_:m43",
          //               A{}.s("menu_name", "admin_menu")
          //                   .s("name", "Bdgets")
          //                   .s("path", "/admin/enterprises")
          //                   .s("icon", "mif-balance-scale").i("level",
          //                   0).i("position", 1)) // add nested

          //            .n("menu", "_:m44",
          //               A{}.s("menu_name", "admin_menu")
          //                   .s("name", "Backlogs")
          //                   .s("path", "/admin/enterprises")
          //                   .s("icon", "mif-backlog").i("level",
          //                   0).i("position", 2))
          //                   // add nested
          .n("menu", "_:m45",
             A{}.s("menu_name", "admin_menu")
                 .s("name", "Plugins")
                 .s("path", "/admin/plugins")
                 .s("icon", "mif-power-cord")
                 .i("level", 0)
                 .i("position", 12))

          .n("menu", "_:m46",
             A{}.s("menu_name", "admin_menu")
                 .s("name", "Webhooks")
                 .s("path", "/admin/webhooks")
                 .s("icon", "mif-flow-parallel")
                 .i("level", 0)
                 .i("position", 13))
          .n("menu", "_:m47",
             A{}.s("menu_name", "admin_menu")
                 .s("name", "Information")
                 .s("path", "/admin/info")
                 .s("icon", "mif-info")
                 .i("level", 0)
                 .i("position", 14));
    }
    // project_menu
    {
      m.n("menu", "_:p1",
          A{}.s("menu_name", "project_menu")
              .s("name", "Overview")
              .s("path", "/projects/slug/")
              .s("icon", "mif-info")
              .i("level", 0)
              .i("position", 1))

          .n("menu", "_:p2",
             A{}.s("menu_name", "project_menu")
                 .s("name", "Activity")
                 .s("path", "/projects/slug/activity")
                 .s("icon", "mif-checkmark")
                 .i("level", 0)
                 .i("position", 2))

          .n("menu", "_:p3",
             A{}.s("menu_name", "project_menu")
                 .s("name", "Roadmap")
                 .s("path", "/projects/slug/roadmap")
                 .s("icon", "mif-compass")
                 .i("level", 0)
                 .i("position", 3))

          .n("menu", "_:p4",
             A{}.s("menu_name", "project_menu")
                 .s("name", "Work packages")
                 .s("path", "/projects/slug/work_packages")
                 .s("icon", "mif-clipboard")
                 .i("level", 0)
                 .i("position", 4))
          .n("menu", "_:p5",
             A{}.s("menu_name", "project_menu")
                 .s("name", "Boards")
                 .s("path", "/projects/slug/boards")
                 .s("icon", "mif-chart-bars2")
                 .i("level", 0)
                 .i("position", 5))

          .n("menu", "_:p6",
             A{}.s("menu_name", "project_menu")
                 .s("name", "Backlogs")
                 .s("path", "/projects/slug/backlogs")
                 .s("icon", "mif-copy")
                 .i("level", 0)
                 .i("position", 6))
          .n("menu", "_:p7",
             A{}.s("menu_name", "project_menu")
                 .s("name", "Calender")
                 .s("path", "/projects/slug/work_packages/calendar")
                 .s("icon", "mif-calendar")
                 .i("level", 0)
                 .i("position", 7))
          .n("menu", "_:p8",
             A{}.s("menu_name", "project_menu")
                 .s("name", "News")
                 .s("path", "/projects/slug/news")
                 .s("icon", "mif-volume-high")
                 .i("level", 0)
                 .i("position", 8))
          .n("menu", "_:p9",
             A{}.s("menu_name", "project_menu")
                 .s("name", "Forum")
                 .s("path", "/projects/slug/forum")
                 .s("icon", "mif-stack")
                 .i("level", 0)
                 .i("position", 9))
          .n("menu", "_:p10",
             A{}.s("menu_name", "project_menu")
                 .s("name", "Wiki")
                 .s("path", "/projects/slug/wiki/wiki")
                 .s("icon", "mif-leanpub")
                 .i("level", 0)
                 .i("position", 10))
          .n("menu", "_:p11",
             A{}.s("menu_name", "project_menu")
                 .s("name", "Cost reports")
                 .s("path", "/projects/slug/cost_reports")
                 .s("icon", "mif-equalizer2")
                 .i("level", 0)
                 .i("position", 11))
          .n("menu", "_:p12",
             A{}.s("menu_name", "project_menu")
                 .s("name", "Members")
                 .s("path", "/projects/slug/members")
                 .s("icon", "mif-users")
                 .i("level", 0)
                 .i("position", 12))
          .n("menu", "_:p13",
             A{}.s("menu_name", "project_menu")
                 .s("name", "Budgets")
                 .s("path", "/projects/slug/cost_objects")
                 .s("icon", "mif-calculator")
                 .i("level", 0)
                 .i("position", 13))
          .n("menu", "_:p14",
             A{}.s("menu_name", "project_menu")
                 .s("name", "Meetings")
                 .s("path", "/projects/slug/meetings")
                 .s("icon", "mif-bubbles")
                 .i("level", 0)
                 .i("position", 14))
          .n("menu", "_:p15",
             A{}.s("menu_name", "project_menu")
                 .s("name", "Project settings")
                 .s("path", "/projects/slug/settings")
                 .s("icon", "mif-wrench")
                 .i("level", 0)
                 .i("position", 15));
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
