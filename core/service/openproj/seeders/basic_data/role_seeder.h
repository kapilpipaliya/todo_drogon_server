#pragma once
#include "../seeder.h"
namespace openproj {
namespace seeder {
namespace BasicData {
  class RoleSeeder : public Seeder {
  public:
     void seed_data() {
//      Role.transaction {
//        roles.each { |attributes|
//          Role.create!(attributes)
//        }

//        builtin_roles.each { |attributes|
//          Role.find_by!(name: attributes[:name]).update_attributes(attributes)
//        }
//      }
    }

     bool applicable() {
//      Role.where(builtin: false).empty?
    }

     void not_applicable_message() {
//      'Skipping roles as there are already some configured'
    }

     void roles() {
//      [project_admin, member, reader]
    }

     void builtin_roles() {
//      [non_member, anonymous]
    }

     void member() {
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
    }

     void reader() {
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
    }

     void project_admin() {
//      {
//        name: I18n.t(:default_role_project_admin),
//        position: 5,
//        permissions: Roles::CreateContract.new(Role.new, nil).assignable_permissions.map(&:name)
//      }
    }

     void non_member() {
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
    }

     void anonymous() {
//      {
//        name: I18n.t(:default_role_anonymous),
//        permissions: %i[
//          view_work_packages
//          browse_repository
//          view_changesets
//          view_wiki_pages
//        ]
//      }
    }
  };
}
}
}
