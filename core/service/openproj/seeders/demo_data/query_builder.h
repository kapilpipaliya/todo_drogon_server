#pragma once
#include "../seeder.h"
namespace openproj {
namespace seeder {
namespace DemoData {
  class QueryBuilder : public Seeder {
  public:
//    attr_reader :config
//    attr_reader :project

//     QueryBuilder(config, project) {
//      this->config = config
//      this->project = project
//    }

     void create() {
//      if ( valid?) { create_query ;}
    }

    private:

    //
    // Don"t seed queries specific to the backlogs plugin.
//     void valid?() {
//      backlogs_present? || !columns.include?("story_points")
//    }

//     void base_attributes() {
//      {
//        name: config[:name],
//        user: User.admin.first,
//        is_public: config[:is_public] != false,
//        hidden: config[:hidden] == true,
//        show_hierarchies: config[:hierarchy] == true,
//        timeline_visible: config[:timeline] == true
//      }
//    }

//     void create_query() {
//      attr = base_attributes

//      set_project! attr
//      set_columns! attr
//      set_sort_by! attr
//      set_group_by! attr
//      set_filters! attr
//      set_display_representation! attr

//      query = Query.create! attr

//      create_menu_item query

//      query
//    }

//     void create_menu_item(query) {
//      MenuItems::QueryMenuItem.create!(
//        navigatable_id: query.id,
//        name: SecureRandom.uuid,
//        title: query.name
//      )
//    }

//     void set_project!(attr) {
//      attr[:project] = project unless project.nil?
//    }

//     void set_display_representation!(attr) {
//      attr[:display_representation] = config[:display_representation] unless config[:display_representation].nil?
//    }

//     void set_columns!(attr) {
//      attr[:column_names] = columns unless columns.empty?
//    }

//     void columns() {
//      this->columns ||= Array(config[:columns]).map(&:to_s)
//    }

//     void set_sort_by!(attr) {
//      sort_by = config[:sort_by]

//      if ( sort_by) { attr[:sort_criteria] = [[sort_by, "asc"]] ;}
//    }

//     void set_group_by!(attr) {
//      group_by = config[:group_by]

//      if ( group_by) { attr[:group_by] = group_by ;}
//    }

//     void set_filters!(query_attr) {
//      fs = filters

//      query_attr[:filters] = [fs] unless fs.empty?
//    }

//     void filters() {
//      filters = {}

//      set_status_filter! filters
//      set_version_filter! filters
//      set_type_filter! filters
//      set_parent_filter! filters

//      filters
//    }

//     void set_status_filter!(filters) {
//      status = String(config[:status])

//      if ( status == "open") { filters[:status_id] = { operator: "o" } ;}
//    }

//     void set_version_filter!(filters) {
//      if ( version = config[:version].presence) {
//        filters[:fixed_version_id] = {
//          operator: "=",
//          values: [Version.find_by(name: version).id]
//        }
//      }
//    }

//     void set_type_filter!(filters) {
//      types = Array(config[:type]).map { |name|
//        Type.find_by(name: translate_with_base_url(name))
//      }

//      if ( !types.empty?) {
//        filters[:type_id] = {
//          operator: "=",
//          values: types.map(&:id).map(&:to_s)
//        }
//      }
//    }

//     void set_parent_filter!(filters) {
//      if ( parent_filter_value = config[:parent].presence) {
//        filters[:parent] = {
//          operator: "=",
//          values: [parent_filter_value]
//        }
//      }
//    }

//     void backlogs_present?() {
//      if ( this->backlogs_present.nil?) { this->backlogs_present = defined? OpenProject::Backlogs ;}

//      this->backlogs_present
//    }
  };
}
}
}
