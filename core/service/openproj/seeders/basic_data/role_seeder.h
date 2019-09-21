#pragma once
#include <drogon/drogon.h>
#include <vector>
//#include "../../models/role.h"
#include "../seeder.h"
#include "models/RolePermissions.h"
#include "models/Roles.h"

namespace openproj {
namespace seeder {
namespace BasicData {
class RoleSeeder : public Seeder {
  struct row {
    std::string name;
    int position;
    int builtin;
    std::vector<std::string> role_permissions;
  };
  std::vector<row> data_;

 public:
  void seed_data() {
    //      Role.transaction {
    //        roles.each { |attributes|
    //          Role.create!(attributes)
    //        }

    //        builtin_roles.each { |attributes|
    //          Role.find_by!(name:
    //          attributes[:name]).update_attributes(attributes)
    //        }
    //      }
    createandAddPermissions("Role", roles(), true);
    createandAddPermissions("GlobalRole", globalrole(), false);

    auto clientPtr = drogon::app().getDbClient("sce");
    findRoladAndAddPermissions(builtin_roles());

    findRoladAndAddPermissions(extra_member());
    findRoladAndAddPermissions(extra_reader());
  }
  void createandAddPermissions(std::string type, std::vector<row> roles_,
                               bool isassignable) {
    auto clientPtr = drogon::app().getDbClient("sce");
    for (auto &it : roles_) {
      drogon::orm::Mapper<drogon_model::openproject6::Roles> mapper(clientPtr);

      drogon_model::openproject6::Roles roles;
      roles.setName(it.name);
      roles.setBuiltin(it.builtin);
      roles.setPosition(it.position);
      roles.setType(type);
      roles.setAssignable(isassignable);
      mapper.insert(roles);
      auto id = roles.getId();

      for (auto it_ : it.role_permissions) {
        drogon::orm::Mapper<drogon_model::openproject6::RolePermissions>
            mapper_role_perm(clientPtr);
        drogon_model::openproject6::RolePermissions role_permission;
        role_permission.setPermission(it_);
        role_permission.setRoleId(*id);
        role_permission.setCreatedAt(trantor::Date::now());
        role_permission.setUpdatedAt(trantor::Date::now());
        mapper_role_perm.insert(role_permission);
      }
    }
  }

  void findRoladAndAddPermissions(std::vector<row> role) {
    auto clientPtr = drogon::app().getDbClient("sce");
    for (auto &it : role) {
      drogon::orm::Mapper<drogon_model::openproject6::Roles> mapper(clientPtr);
      auto r =
          mapper.findBy(Criteria(drogon_model::openproject6::Roles::Cols::_name,
                                 CompareOperator::EQ, it.name));

      if (!r.empty()) {
        auto id = *r.at(0).getId();
        for (auto it_ : it.role_permissions) {
          drogon::orm::Mapper<drogon_model::openproject6::RolePermissions>
              mapper_role_perm(clientPtr);
          drogon_model::openproject6::RolePermissions role_permission;
          role_permission.setPermission(it_);
          role_permission.setRoleId(id);
          role_permission.setCreatedAt(trantor::Date::now());
          role_permission.setUpdatedAt(trantor::Date::now());
          mapper_role_perm.insert(role_permission);
        }
      }
    }
  }
  bool applicable() {
    //      Role.where(builtin: false).empty?
  }
  void not_applicable_message() {
    //      'Skipping roles as there are already some configured'
  }
  std::vector<row> roles() {
    //      [project_admin, member, reader]
    data_.erase(data_.begin(), data_.end());
    data_.push_back(project_admin());
    data_.push_back(member());
    data_.push_back(reader());
    return data_;
  }
  std::vector<row> builtin_roles() {
    //      [non_member, anonymous]
    data_.erase(data_.begin(), data_.end());
    data_.push_back(non_member());
    data_.push_back(anonymous());
    return data_;
  }

  row member() {
    //      {
    //        name: I18n.t(:default_role_member),
    //        position: 3,
    //        permissions: %i[
    //          view_work_packages
    //          export_work_packages
    //          add_work_packages
    //          move_work_packages
    //          edit_work_packages
    //          assign_versions
    //          add_work_package_notes
    //          edit_own_work_package_notes
    //          manage_work_package_relations
    //          manage_subtasks
    //          manage_public_queries
    //          save_queries
    //          view_work_package_watchers
    //          add_work_package_watchers
    //          delete_work_package_watchers
    //          view_calendar
    //          comment_news
    //          manage_news
    //          log_time
    //          view_time_entries
    //          view_own_time_entries
    //          edit_own_time_entries
    //          view_timelines
    //          edit_timelines
    //          delete_timelines
    //          view_reportings
    //          edit_reportings
    //          delete_reportings
    //          manage_wiki
    //          manage_wiki_menu
    //          rename_wiki_pages
    //          change_wiki_parent_page
    //          delete_wiki_pages
    //          view_wiki_pages
    //          export_wiki_pages
    //          view_wiki_edits
    //          edit_wiki_pages
    //          delete_wiki_pages_attachments
    //          protect_wiki_pages
    //          list_attachments
    //          add_messages
    //          edit_own_messages
    //          delete_own_messages
    //          browse_repository
    //          view_changesets
    //          commit_access
    //          view_commit_author_statistics
    //          view_members
    //          manage_board_views
    //          show_board_views
    //        ]
    //      }
    return {
        std::string("Member"),
        3,
        0,
        {"view_work_packages", "export_work_packages", "add_work_packages",
         "move_work_packages", "edit_work_packages", "assign_versions",
         "add_work_package_notes", "edit_own_work_package_notes",
         "manage_work_package_relations", "manage_subtasks",
         "manage_public_queries", "save_queries", "view_work_package_watchers",
         "add_work_package_watchers", "delete_work_package_watchers",
         "view_calendar", "comment_news", "manage_news", "log_time",
         "view_time_entries", "view_own_time_entries", "edit_own_time_entries",
         "view_timelines", "edit_timelines", "delete_timelines",
         "view_reportings", "edit_reportings", "delete_reportings",
         "manage_wiki", "manage_wiki_menu", "rename_wiki_pages",
         "change_wiki_parent_page", "delete_wiki_pages", "view_wiki_pages",
         "export_wiki_pages", "view_wiki_edits", "edit_wiki_pages",
         "delete_wiki_pages_attachments", "protect_wiki_pages",
         "list_attachments", "add_messages", "edit_own_messages",
         "delete_own_messages", "browse_repository", "view_changesets",
         "commit_access", "view_commit_author_statistics", "view_members",
         "manage_board_views", "show_board_views",

         // documents
         "view_documents", "manage_documents",

         // backlogs
         "view_master_backlog", "view_taskboards",
         // boards
         "show_board_views", "manage_board_views"

        }};
  }
  std::vector<row> extra_member() {
    return {
        {std::string("Member"),
         -1,
         0,
         {// costs default_data.rb
          // member = default_role_member
          "view_own_hourly_rate", "view_cost_rates", "log_own_costs",
          "edit_own_cost_entries", "view_cost_objects", "view_own_cost_entries",

          // reporting default_data.rb
          // project admin = default_role_project_admin
          // The Project Admin role is assigned all possible permission in
          // the core's `roles.rb` seed. Here we remove those permissions
          // which should not be assigned by default.
          //          "save_cost_reports",  // set role_id to null
          //          "save_private_cost_reports",  // set role_id to null
          // metting default_data.rb
          // member = default_role_member
          "create_meetings", "edit_meetings", "delete_meetings",
          "view_meetings", "create_meeting_agendas", "close_meeting_agendas",
          "send_meeting_agendas_notification", "send_meeting_agendas_icalendar",
          "create_meeting_minutes", "send_meeting_minutes_notification"

         }}};
  }

  row reader() {
    //      {
    //        name: I18n.t(:default_role_reader),
    //        position: 4,
    //        permissions: %i[
    //          view_work_packages
    //          add_work_package_notes
    //          edit_own_work_package_notes
    //          save_queries
    //          view_calendar
    //          comment_news
    //          view_timelines
    //          view_reportings
    //          view_wiki_pages
    //          export_wiki_pages
    //          list_attachments
    //          add_messages
    //          edit_own_messages
    //          delete_own_messages
    //          browse_repository
    //          view_changesets
    //          show_board_views
    //        ]
    //      }
    return {std::string("Reader"),
            4,
            0,
            {"view_work_packages", "add_work_package_notes",
             "edit_own_work_package_notes", "save_queries", "view_calendar",
             "comment_news", "view_timelines", "view_reportings",
             "view_wiki_pages", "export_wiki_pages", "list_attachments",
             "add_messages", "edit_own_messages", "delete_own_messages",
             "browse_repository", "view_changesets", "show_board_views",

             // documents
             "view_documents",

             // backlogs
             "view_master_backlog", "view_taskboards",

             // boards
             "show_board_views"}};
  }
  std::vector<row> extra_reader() {
    return {{std::string("Reader"),
             -1,
             0,
             {// metting default_data.rb
              "view_meetings"}}};
  }

  row project_admin() {
    //      {
    //        name: I18n.t(:default_role_project_admin),
    //        position: 5,
    //        permissions: Roles::CreateContract.new(Role.new,
    //        nil).assignable_permissions.map(&:name)
    //      }
    // pretty hard to find automatically
    return {std::string("Project admin"),
            5,
            0,
            {
                "edit_project",
                "select_project_modules",
                "manage_members",
                "view_members",
                "manage_versions",
                "manage_types",
                "add_subprojects",
                "copy_projects",
                "view_work_packages",
                "add_work_packages",
                "edit_work_packages",
                "move_work_packages",
                "add_work_package_notes",
                "edit_work_package_notes",
                "edit_own_work_package_notes",
                "manage_categories",
                "export_work_packages",
                "delete_work_packages",
                "manage_work_package_relations",
                "manage_subtasks",
                "manage_public_queries",
                "save_queries",
                "view_work_package_watchers",
                "add_work_package_watchers",
                "delete_work_package_watchers",
                "assign_versions",
                "view_time_entries",
                "log_time",
                "edit_time_entries",
                "view_own_time_entries",
                "edit_own_time_entries",
                "manage_project_activities",
                "manage_news",
                "comment_news",
                "view_wiki_pages",
                "list_attachments",
                "manage_wiki",
                "manage_wiki_menu",
                "rename_wiki_pages",
                "change_wiki_parent_page",
                "delete_wiki_pages",
                "export_wiki_pages",
                "view_wiki_edits",
                "edit_wiki_pages",
                "delete_wiki_pages_attachments",
                "protect_wiki_pages",
                "browse_repository",
                "commit_access",
                "manage_repository",
                "view_changesets",
                "view_commit_author_statistics",
                "manage_forums",
                "add_messages",
                "edit_messages",
                "edit_own_messages",
                "delete_messages",
                "delete_own_messages",
                "view_calendar",
                "view_documents",
                "manage_documents",
                "view_own_hourly_rate",
                "view_hourly_rates",
                "edit_own_hourly_rate",
                "edit_hourly_rates",
                "view_cost_rates",
                "log_own_costs",
                "log_costs",
                "edit_own_cost_entries",
                "edit_cost_entries",
                "view_cost_objects",
                "view_cost_entries",
                "view_own_cost_entries",
                "edit_cost_objects",
                "save_cost_reports",
                "save_private_cost_reports",
                "view_meetings",
                "create_meetings",
                "edit_meetings",
                "delete_meetings",
                "meetings_send_invite",
                "create_meeting_agendas",
                "close_meeting_agendas",
                "send_meeting_agendas_notification",
                "send_meeting_agendas_icalendar",
                "create_meeting_minutes",
                "send_meeting_minutes_notification",
                "view_master_backlog",
                "view_taskboards",
                "update_sprints",
                "show_board_views",
                "manage_board_views",
                "manage_overview",

            }};
  }

  row non_member() {
    //      {
    //        name: I18n.t(:default_role_non_member),
    //        permissions: %i[
    //          view_work_packages
    //          view_calendar
    //          comment_news
    //          browse_repository
    //          view_changesets
    //          view_wiki_pages
    //        ]
    //      }
    return {std::string("Non member"),
            -1,
            0,
            {"view_work_packages", "view_calendar", "comment_news",
             "browse_repository", "view_changesets", "view_wiki_pages"}};
  }

  row anonymous() {
    //      {
    //        name: I18n.t(:default_role_anonymous),
    //        permissions: %i[
    //          view_work_packages
    //          browse_repository
    //          view_changesets
    //          view_wiki_pages
    //        ]
    //      }
    return {std::string("Anonymous"),
            -1,
            0,
            {"view_work_packages", "browse_repository", "view_changesets",
             "view_wiki_pages"}};
  }
  std::vector<row> globalrole() {
    // modules/global_roles/lib/open_project/global_roles/patches/role_seeder_patch.rb
    //      def project_creator
    //        { name: I18n.t(:'seeders.default_role_project_creator'),
    //          position: 6,
    //          permissions: [:add_project],
    //          type: 'GlobalRole'
    //        }
    //      end
    return {{std::string("Project creator"), 6, 0, {"add_project"}}};
  }
};
}  // namespace BasicData
}  // namespace seeder
}  // namespace openproj
