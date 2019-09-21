#pragma once
#include "../seeder.h"
namespace openproj {
namespace seeder {
namespace DemoData {
  class WorkPackageBoardSeeder : public Seeder {
  public:
    // attr_accessor :project, :key

    // include ::DemoData::References

//     WorkPackageBoardSeeder(project, key) {
//      this->project = project
//      this->key = key
//    }

     void seed_data() {
//      // Seed only for those projects that provide a `kanban` key, i.e. "demo-project" in standard edition.
//      if ( project_has_data_for?(key, "boards.kanban")) {
//        LOG_DEBUG << "    ↳ Creating demo status board"
//        seed_kanban_board
//        puts
//      }

//      if ( project_has_data_for?(key, "boards.basic")) {
//        LOG_DEBUG << "    ↳ Creating demo basic board"
//        seed_basic_board
//        puts
//      }
    }

    private:

     void seed_kanban_board() {
//      board = ::Boards::Grid.new project: project

//      board.name = project_data_for(key, "boards.kanban.name")
//      board.options = { "type" => "action", "attribute" => "status", "highlightingMode" => "priority" }

//      board.widgets = seed_kanban_board_queries.each_with_index.map { |query, i|
//        Grids::Widget.new start_row: 1, end_row: 2,
//                          start_column: i + 1, end_column: i + 2,
//                          options: { query_id: query.id,
//                                     filters: [{ status: { operator: "=", values: query.filters[0].values } }] },
//                          identifier: "work_package_query"
//      }

//      board.column_count = board.widgets.count
//      board.row_count = 1

//      board.save!

//      Setting.boards_demo_data_available = "true"
    }

     void seed_kanban_board_queries() {
//      admin = User.admin.first

//      status_names = ["New", "In progress", "Closed", "Rejected"]
//      statuses = Status.where(name: status_names).to_a

//      if ( statuses.size < status_names.size) {
//        raise StandardError.new "Not all statuses needed for seeding a KANBAN board are present. Check that they get seeded."
//      }

//      statuses.to_a.map { |status|
//        Query.new_default(project: project, user: admin).tap { |query|
//          // Hide the query in the main menu
//          query.hidden = true

//          // Make it public so that new members can see it too
//          query.is_public = true

//          query.name = status.name
//          // Set filter by this status
//          query.add_filter("status_id", "=", [status.id])

//          // Set manual sort filter
//          query.sort_criteria = [[:manual_sorting, "asc"]]

//          query.save!
//        }
//      }
    }

     void seed_basic_board() {
//      board = ::Boards::Grid.new project: project
//      board.name = project_data_for(key, "boards.basic.name")
//      board.options = { "highlightingMode" => "priority" }

//      board.widgets = seed_basic_board_queries.each_with_index.map { |query, i|
//        Grids::Widget.new start_row: 1, end_row: 2,
//                          start_column: i + 1, end_column: i + 2,
//                          options: { query_id: query.id,
//                                     filters: [{ manualSort: { operator: "ow", values: [] } }] },
//                          identifier: "work_package_query"
//      }

//      board.column_count = board.widgets.count
//      board.row_count = 1

//      board.save!
    }

     void seed_basic_board_queries() {
//      admin = User.admin.first

//      if ( project.name === "Scrum project") { wps = ;}
//              scrum_query_work_packages
//            else
//              basic_query_work_packages
//            }

//      lists = [{ name: "Today", wps: wps[0] },
//               { name: "Tomorrow", wps: wps[1] },
//               { name: "Later", wps: wps[2] },
//               { name: "Never", wps: wps[3] }]

//      lists.map { |list|
//        Query.new(project: project, user: admin).tap { |query|
//          // Hide the query in the main menu
//          query.hidden = true

//          // Make it public so that new members can see it too
//          query.is_public = true

//          query.name = list[:name]

//          // Set manual sort filter
//          query.add_filter("manual_sort", "ow", [])
//          query.sort_criteria = [[:manual_sorting, "asc"]]

//          list[:wps].each_with_index { |wp_id, i|
//            query.ordered_work_packages.build(work_package_id: wp_id, position: i)
//          }

//          query.save!
//        }
//      }

    }

     void scrum_query_work_packages() {
//      [
//        [WorkPackage.find_by(subject: "New website").id,
//         WorkPackage.find_by(subject: "SSL certificate").id,
//         WorkPackage.find_by(subject: "Choose a content management system").id],
//        [WorkPackage.find_by(subject: "New login screen").id],
//        [WorkPackage.find_by(subject: "Set-up Staging environment").id],
//        [WorkPackage.find_by(subject: "Wrong hover color").id]
//      ]
    }

     void basic_query_work_packages() {
//      [
//        [WorkPackage.find_by(subject: "Create a new project").id,
//         WorkPackage.find_by(subject: "Edit a work package").id,
//         WorkPackage.find_by(subject: "Create work packages").id,
//         WorkPackage.find_by(subject: "Activate further modules").id],
//        [WorkPackage.find_by(subject: "Create a project plan").id],
//        [WorkPackage.find_by(subject: "Invite new team members").id],
//        [WorkPackage.find_by(subject: "Customize project overview page").id]
//      ]
    }
  };
}
}
}
