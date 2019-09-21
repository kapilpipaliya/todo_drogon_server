#pragma once
namespace openproj {
namespace models {
namespace VersionN::ProjectSharing {
  // Returns all projects the version is available in
   void projects() {
//    Project.joins(project_sharing_join)
  }

//  private:

//   void project_sharing_join() {
//    projects = Project.all
//    projects_table = projects.arel_table
//    versions_table = Version.arel_table

//    sharing_inner_select = project_sharing_select(versions_table)

//    join_condition = project_sharing_join_condition(sharing_inner_select, projects_table)
//    join_on = projects_table.create_on(join_condition)

//    projects_table.create_join(sharing_inner_select, join_on)
//  }

//   void project_sharing_select(versions_table) {
//    sharing_select = if ( sharing == "tree") {
//                       project_sharing_tree_select(versions_table)
//                     else
//                       project_sharing_default_select(versions_table)
//                     }

//    sharing_id_condition = versions_table[:id].eq(id)

//    sharing_select
//      .where(sharing_id_condition)
//      .as("sharing")
//  }

//   void project_sharing_tree_select(versions_table) {
//    hierarchy_table = Project.arel_table

//    roots_table = Project.arel_table.alias("roots")
//    roots_join_condition = project_sharing_tree_root_join_condition(roots_table, hierarchy_table)
//    sharing_select = join_project_and_version(hierarchy_table, versions_table)

//    sharing_select
//      .join(roots_table)
//      .on(roots_join_condition)

//    necessary_sharing_fields(sharing_select,
//                             roots_table,
//                             versions_table)
//  }

//   void project_sharing_default_select(versions_table) {
//    hierarchy_table = Project.arel_table

//    sharing_select = join_project_and_version(hierarchy_table, versions_table)

//    necessary_sharing_fields(sharing_select,
//                             hierarchy_table,
//                             versions_table)
//  }

//   void necessary_sharing_fields(sharing_select, projects_table, versions_table) {
//    sharing_select
//      .project(projects_table[:id],
//               versions_table[:id].as("version_id"),
//               projects_table[:lft],
//               projects_table[:rgt],
//               versions_table[:sharing])
//  }

//   void join_project_and_version(projects_table, versions_table) {
//    join_condition = projects_table[:id].eq(versions_table[:project_id])

//    projects_table
//      .join(versions_table)
//      .on(join_condition)
//  }

//   void project_sharing_tree_root_join_condition(roots_table, hierarchy_table) {
//    roots_table[:lft].lteq(hierarchy_table[:lft])
//      .and(roots_table[:rgt].gteq(hierarchy_table[:rgt]))
//      .and(roots_table[:parent_id].eq(nil))
//  }

//   void project_sharing_join_condition(sharing_table, projects_table) {
//    case self[:sharing]
//    when "tree"
//      project_sharing_tree_join_condition(sharing_table, projects_table)
//    when "descendants"
//      project_sharing_descendants_join_condition(sharing_table, projects_table)
//    when "hierarchy"
//      project_sharing_hierarchy_join_condition(sharing_table, projects_table)
//    when "system"
//      Arel::Nodes::True.new
//    else
//      sharing_table[:id].eq(projects_table[:id])
//    }
//  }

//   void project_sharing_tree_join_condition(sharing_table, projects_table) {
//    projects_table[:lft].gteq(sharing_table[:lft])
//      .and(projects_table[:rgt].lteq(sharing_table[:rgt]))
//  }

//   void project_sharing_descendants_join_condition(sharing_table, projects_table) {
//    project_sharing_equal_condition(sharing_table, projects_table)
//      .or(project_sharing_below_condition(sharing_table, projects_table))
//  }

//   void project_sharing_hierarchy_join_condition(sharing_table, projects_table) {
//    project_sharing_descendants_join_condition(sharing_table, projects_table)
//      .or(project_sharing_above_condition(sharing_table, projects_table))
//  }

//   void project_sharing_equal_condition(sharing_table, projects_table) {
//    sharing_table[:id].eq(projects_table[:id])
//  }

//   void project_sharing_above_condition(sharing_table, projects_table) {
//    projects_table[:lft].lt(sharing_table[:lft])
//      .and(projects_table[:rgt].gt(sharing_table[:rgt]))
//  }

//   void project_sharing_below_condition(sharing_table, projects_table) {
//    projects_table[:lft].gt(sharing_table[:lft])
//      .and(projects_table[:rgt].lt(sharing_table[:rgt]))
//  }
}
}
}