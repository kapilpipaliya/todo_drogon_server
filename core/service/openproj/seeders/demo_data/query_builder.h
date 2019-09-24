#pragma once
#include <yaml-cpp/yaml.h>
#include "../../models/menu_items/query_menu_item.h"
#include "../seeder.h"
namespace openproj {
namespace seeder {
namespace DemoData {
class QueryBuilder : public Seeder {
 public:
  //    attr_reader :config
  //    attr_reader :project

  YAML::Node config;
  long project_id;
  YAML::Node version_node;
  QueryBuilder(YAML::Node &config, long project) {
    this->config = config;
    this->project_id = project;
  }
  void create() {
    if (valid()) {
      create_query();
    }
  }
  void seed_data(){};

 private:
  //
  // Don"t seed queries specific to the backlogs plugin.
  bool valid() {
    //      backlogs_present? || !columns.include?("story_points")
    return true;
  }

  void base_attributes() {
    //      {
    //        name: config[:name],
    //        user: User.admin.first,
    //        is_public: config[:is_public] != false,
    //        hidden: config[:hidden] == true,
    //        show_hierarchies: config[:hierarchy] == true,
    //        timeline_visible: config[:timeline] == true
    //      }
  }

  void create_query() {
    //      attr = base_attributes

    //      set_project! attr
    //      set_columns! attr
    //      set_sort_by! attr
    //      set_group_by! attr
    //      set_filters! attr
    //      set_display_representation! attr

    //      query = Query.create! attr

    //      create_menu_item(query)

    //      MenuItems::QueryMenuItem.create!(
    //        navigatable_id: query.id,
    //        name: SecureRandom.uuid,
    //        title: query.name
    //      )

    auto name = config["name"].as<std::string>();
    // user: User.admin.first,
    bool is_public = true;
    bool hidden = false;
    // auto show_hierarchies = config["hierarchy"].as<bool>();
    // auto timeline_visible = config["timeline"].as<bool>();
    // auto type = config["type"].as<std::string>();
    // auto sort_by = config["sort_by"].as<std::string>();

    // attr[:project] = project_id;
    auto column_names = config["columns"];
    auto sort_criteria = config["sort_by"];  // asc
    auto group_by = config["group_by"];

    // auto filters_ = filters();

    // auto query_attr[filters] = [filters_] unless fs.empty;
    // auto display_representation = config[:display_representation];
    // when wiki or wikipage is created it create default menu_item WikiMenuItem automatically
    openproj::models::MenuItems::QueryMenuItem menu_items;
    menu_items.setName("uuid");  // character_varying  ;
    menu_items.setTitle(name);   // character_varying  ;
    // menu_items.setParentId(); //integer  ;
    menu_items.setOptions("");       // text  ; // get yaml
    menu_items.setNavigatableId(1);  // integer  ;
    menu_items.save();
  }

  void columns() {
    //      this->columns ||= Array(config[:columns]).map(&:to_s)
  }

  void filters() {
    /*
//      filters = {}

//      set_status_filter! filters
//      set_version_filter! filters
//      set_type_filter! filters
//      set_parent_filter! filters

//      filters
auto status = config["status"].as<std::string>();
   if ( status == "open") { filters[:status_id] = { operator: "o" } ;}
   if ( config["version"]) {
//        filters[:fixed_version_id] = {
//          operator: "=",
//          values: [Version.find_by(name: version).id]
     }
   }
//      types = Array(config[:type]).map { |name|
//        Type.find_by(name: translate_with_base_url(name))
//      }

//      if ( !types.empty?) {
//        filters[:type_id] = {
//          operator: "=",
//          values: types.map(&:id).map(&:to_s)
//        }
//      }
//      if ( parent_filter_value = config[:parent].presence) {
//        filters[:parent] = {
//          operator: "=",
//          values: [parent_filter_value]
//        }
//      }
*/
  }

  bool backlogs_present() {
    //      if ( this->backlogs_present.nil?) { this->backlogs_present =
    //      defined? OpenProject::Backlogs ;}

    //      this->backlogs_present
  }
};
}  // namespace DemoData
}  // namespace seeder
}  // namespace openproj
