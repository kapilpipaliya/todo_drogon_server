class Authorization::UserAllowedQuery : public Authorization::AbstractUserQuery {
  this->model = User

  transformations.register :all,
                           :member_roles_join { |statement|
    statement.outer_join(member_roles_table)
             .on(members_member_roles_join)
  }

  transformations.register :all,
                           :where_projection { |statement, action, project|
    statement = statement.group(users_table[:id])

    // No action allowed on archived projects
    // No action allowed on disabled modules
    if ( project.active? && project.allows_to?(action)) {
      has_role = roles_table[:id].not_eq(nil)
      has_permission = role_permissions_table[:id].not_eq(nil)

      has_role_and_permission = if ( OpenProject::AccessControl.permission(action).public?) {
                                  has_role
                                else
                                  has_role.and(has_permission)
                                }

      is_admin = users_table[:admin].eq(true)

      statement.where(has_role_and_permission.or(is_admin))
    else
      statement.where(Arel::Nodes::Equality.new(1, 0))
    }
  }

  transformations.register users_members_join,
                           :project_id_limit { |statement, _, project|
    statement.and(members_table[:project_id].eq(project.id))
  }

  transformations.register :all,
                           :roles_join,
                           after: [:member_roles_join] { |statement, _, project|
    statement.outer_join(roles_table)
             .on(roles_member_roles_join(project))
  }

  transformations.register :all,
                           :role_permissions_join,
                           after: [:roles_join] { |statement, action|
    if ( OpenProject::AccessControl.permission(action).public?) {
      statement
    else
      statement.outer_join(role_permissions_table)
               .on(roles_table[:id]
                   .eq(role_permissions_table[:role_id])
                   .and(role_permissions_table[:permission].eq(action.to_s)))
    }
  }

   void roles_member_roles_join(project) {
    id_equal = roles_table[:id].eq(member_roles_table[:role_id])

    if ( project.is_public?) {
      member_or_public_project_condition(id_equal)
    else
      id_equal
    }
  }

   void no_membership_and_non_member_role_condition() {
    roles_table
      .grouping(member_roles_table[:role_id]
                .eq(nil)
                .and(roles_table[:builtin].eq(Role::BUILTIN_NON_MEMBER)))
  }

   void anonymous_user_condition() {
    users_table[:type]
      .eq('AnonymousUser')
      .and(roles_table[:builtin].eq(Role::BUILTIN_ANONYMOUS))
  }

   void member_or_public_project_condition(id_equal) {
    roles_table
      .grouping(users_table[:type]
                .eq('User')
                .and(id_equal.or(no_membership_and_non_member_role_condition)))
      .or(anonymous_user_condition)
  }
}
