#pragma once
#include "abstract_query.h"
namespace openproj {
namespace service {
namespace Authorization {
class ProjectQuery : public AbstractQuery {
public:
//  this->model = Project

//   void projects_members_join(user) {
//    projects_table[:id]
//      .eq(members_table[:project_id])
//      .and(members_table[:user_id].eq(user.id))
//      .and(project_active_condition)
//  }

//   void enabled_modules_join(action) {
//    project_enabled_module_id_eq_condition
//      .and(enabled_module_name_eq_condition(action))
//      .and(project_active_condition)
//  }

//   void role_permissions_join() {
//    permission_roles_table[:id]
//      .eq(role_permissions_table[:role_id])
//  }

//   void project_enabled_module_id_eq_condition() {
//    projects_table[:id]
//      .eq(enabled_modules_table[:project_id])
//  }

//   void enabled_module_name_eq_condition(action) {
//    modules = action_project_modules(action)

//    enabled_modules_table[:name].in(modules)
//  }

//   void project_active_condition() {
//    projects_table[:status].eq(Project::STATUS_ACTIVE)
//  }

//   void members_member_roles_join() {
//    members_table[:id].eq(member_roles_table[:member_id])
//  }

//   void roles_having_permissions(action) {
//    permissions_names = permissions(action).map(&:name)

//    role_permissions_table[:permission].in(permissions_names)
//  }

//   void projects_table() {
//    Project.arel_table
//  }

//   void enabled_modules_table() {
//    EnabledModule.arel_table
//  }

//   void member_roles_table() {
//    MemberRole.arel_table
//  }

//   void members_table() {
//    Member.arel_table
//  }

//   void role_permissions_table() {
//    RolePermission.arel_table
//  }

//   void permission_roles_table() {
//    Role.arel_table.alias("permission_roles")
//  }

//   void assigned_roles_table() {
//    Role.arel_table.alias("assigned_roles")
//  }

//   void role_has_permission_and_is_assigned(user, action) {
//    role_has_permission_condition(action)
//      .and(project_active_condition)
//      .and(assigned_roles_table[:id]
//           .eq(member_roles_table[:role_id])
//           .or(project_public_and_builtin_role_condition(user)))
//  }

//   void role_has_permission_condition(action) {
//    if ( action_public?(action)) {
//      Arel::Nodes::Equality.new(1, 1)
//    else
//      assigned_roles_table[:id].eq(permission_roles_table[:id])
//    }
//  }

//   void project_public_and_builtin_role_condition(user) {
//    builtin_role = if ( user.logged?) {
//                     Role::BUILTIN_NON_MEMBER
//                   else
//                     Role::BUILTIN_ANONYMOUS
//                   }

//    projects_table[:is_public]
//      .eq(true)
//      .and(assigned_roles_table[:builtin].eq(builtin_role))
//      .and(member_roles_table[:id].eq(nil))
//  }

//   void permissions(action) {
//    if ( action.is_a?(Hash)) {
//      OpenProject::AccessControl.allow_actions(action)
//    else
//      [OpenProject::AccessControl.permission(action)].compact
//    }
//  }

//   void action_project_modules(action) {
//    permissions(action).map(&:project_module).compact.uniq
//  }

//   void action_public?(action) {
//    permissions(action).all?(&:public?)
//  }

//  transformations.register :all,
//                           :members_join { |statement, user|
//    if ( user.admin?) {
//      statement
//    else
//      statement
//        .outer_join(members_table)
//        .on(projects_members_join(user))
//    }
//  }

//  transformations.register :all,
//                           :enabled_modules_join,
//                           after: [:members_join] { |statement, _, action|
//    if ( action_project_modules(action).empty?) {
//      statement
//    else
//      statement.join(enabled_modules_table)
//               .on(enabled_modules_join(action))
//    }
//  }

//  transformations.register :all,
//                           :role_permissions_join,
//                           after: [:enabled_modules_join] { |statement, user, action|
//    if ( action_public?(action) || user.admin?) {
//      statement
//    else
//      statement.join(role_permissions_table)
//               .on(roles_having_permissions(action))
//    }
//  }

//  transformations.register :all,
//                           :members_member_roles_join,
//                           after: [:members_join] { |statement, user|
//    if ( user.admin?) {
//      statement
//    else
//      statement.outer_join(member_roles_table)
//               .on(members_member_roles_join)
//    }
//  }

//  transformations.register :all,
//                           :permission_roles_join,
//                           after: [:role_permissions_join] { |statement, user, action|
//    if ( action_public?(action) || user.admin?) {
//      statement
//    else
//      statement.join(permission_roles_table)
//               .on(role_permissions_join)
//    }
//  }

//  transformations.register :all,
//                           :assigned_roles_join,
//                           after: [:permission_roles_join,
//                                   :members_member_roles_join] { |statement, user, action|
//    if ( user.admin?) {
//      statement
//    else
//      statement.outer_join(assigned_roles_table)
//               .on(role_has_permission_and_is_assigned(user, action))
//    }
//  }

//  transformations.register :all,
//                           :assigned_role_exists_condition { |statement, user|
//    if ( user.admin?) {
//      statement.where(project_active_condition)
//    else
//      statement.where(assigned_roles_table[:id].not_eq(nil))
//    }
//  }
};
}
}
}
