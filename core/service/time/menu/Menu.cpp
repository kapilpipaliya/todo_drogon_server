#include "./Menu.h"
timeservice::Menu::Menu(int event1_, int event2_,
                        const drogon::WebSocketConnectionPtr &wsConnPtr_,
                        std::shared_ptr<websocket::todo::TodoContext> context_,
                        std::string &&message_)
    : TimeServiceBase(event1_, event2_, wsConnPtr_, context_,
                      std::move(message_))
/*inh*/
/*inh_end*/
{}
void timeservice::Menu::run() {
  // run
  {
    create_menu("top_menu", "Work Packages", "/work_packages");   // if cond
    create_menu("top_menu", "news", "/news");                     // add if cond
    create_menu("top_menu", "Time sheet", "/timelog");            // add if cond
    create_menu("top_menu", "Help", "/help", "icon5 icon-help");  // add html
  }
  {
    create_menu("account_menu", "My Page", "/my/page");        // add if cond
    create_menu("account_menu", "My Account", "/my/account");  // add if cond
    create_menu("account_menu", "Administration", "/admin");   // add if cond
    create_menu("account_menu", "Sign Out", "/logout");        // add if cond
  }
  { create_menu("application_menu", "Work packages", "/work_packages"); }
  {
    create_menu("my_menu", "Profile", "/my/account", "icon2 icon-user");
    create_menu("my_menu", "Settings", "/my/settings", "icon2 icon-settings2");
    create_menu("my_menu", "Change password", "/my/password",
                "icon2 icon-locked");
    create_menu("my_menu", "Access token", "/my/access_token",
                "icon2 icon-key");
    create_menu("my_menu", "Email notifications", "/my/mail_notifications",
                "icon2 icon-news");
    // create_menu("my_menu", "Delete Account", "/my/delete", "icon2
    // icon-user"); // add if cond
    create_menu("my_menu", "Avatar", "/my/avatar", "icon2 icon-delete");
  }
  {
    create_menu("admin_menu", "Overview", "/admin", "icon2 icon-home");
    create_menu("admin_menu", "Users & Permissions", "/users",
                "icon2 icon-group");
    {
      create_menu("admin_menu", "Settings", "/users_settings");
      create_menu("admin_menu", "Users", "/users");
      create_menu("admin_menu", "Groups", "/groups");
      create_menu("admin_menu", "Roles and permissions", "/roles");
      create_menu("admin_menu", "Avatars", "/avatars");
    }
    create_menu("admin_menu", "Work packages", "/work_packages/settings",
                "icon2 icon-home");
    {
      create_menu("admin_menu", "Settings", "/work_packages/settings");
      create_menu("admin_menu", "Types", "/statuses");
      create_menu("admin_menu", "Status", "/workflows");
      create_menu("admin_menu", "Workflow", "/custom_fields");
      create_menu("admin_menu", "Custom actions", "/custom_action");
      // create_menu("admin_menu", "Overview", "/attribute_help_texts");
      // enterprise
    }
    create_menu("admin_menu", "Custom fields", "/custom_fields",
                "icon2 icon-custom-fields");

    create_menu("admin_menu", "Enumerations", "/admin/enumerations",
                "icon2 icon-enumerations");
    create_menu("admin_menu", "System settings", "/settings",
                "icon2 icon-settings2");
    create_menu("admin_menu", "Authentication", "/authentication_settings",
                "icon2 icon-two-factor-authentication");
    {
      create_menu("admin_menu", "Settings", "/authentication_settings");
      // create_menu("admin_menu", "OAuth applications", "/oauth/applications");
      // create_menu("admin_menu", "LDAP authentication", "/ldap_auth_sources");
    }
    create_menu("admin_menu", "Announcement", "admin/announcements",
                "icon2 icon-news");
    create_menu("admin_menu", "Design", "/admin/design", "icon2 icon-design");
    // create_menu("admin_menu", "Overview", "/custom_styles/show", "icon2
    // icon-home");
    create_menu("admin_menu", "Colors", "/colors", "icon2 icon-status");
    create_menu("admin_menu", "Enterprise Edition", "/admin/enterprises",
                "icon2 icon-headset");

    // create_menu("admin_menu", "Bdgets", "/settings", "icon2 icon-budget");
    {}
    // create_menu("admin_menu", "Backlogs", "/settings", "icon2 icon-backlog");
    {}
    create_menu("admin_menu", "Plugins", "/admin/plugins",
                "icon2 icon-plugins");
    create_menu("admin_menu", "Webhooks", "/admin/webhooks",
                "icon2 icon-relations");
    create_menu("admin_menu", "Information", "/admin/info", "icon2 icon-info1");
  }
  {
    create_menu("project_menu", "Overview", "/activities", "icon2 icon-home");
    create_menu("project_menu", "Overview", "/versions", "icon2 icon-home");
    create_menu("project_menu", "Overview", "/work_packages",
                "icon2 icon-home");
    create_menu("project_menu", "Overview", "/work_packages",
                "icon2 icon-home");
    create_menu("project_menu", "Overview", "/work_packages/calendars",
                "icon2 icon-home");
    create_menu("project_menu", "Overview", "/news", "icon2 icon-home");
    create_menu("project_menu", "Overview", "/forums", "icon2 icon-home");
    create_menu("project_menu", "Overview", "/repositories", "icon2 icon-home");
  }
  {
    create_menu("time_entries", "Overview", "/timelog", "icon2 icon-home");
    create_menu("time_entries", "Overview", "/members", "icon2 icon-home");
    create_menu("time_entries", "Overview", "/project_settings",
                "icon2 icon-home");
  }

  // run_end
}

void timeservice::Menu::create_menu(std::string type, std::string name,
                                    std::string path, std::string icon) {
  auto dgraphorm = dgraph::DGraphClientManger::getDGraphOrm("1");
  auto menu = dgraphorm->newmodel("menu");
  auto response = new api::Response;
  {
    dgraph::orm::Attributes a;
    a.s("menu_name", type);
    a.s("name", name);
    a.s("path", path);
    if (!icon.empty()) {
      a.s("icon", icon);
    }
    auto status = menu->create(a, response);

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
    delete response;
  }

  delete response;
}
// extend_class
// extend_class_end
