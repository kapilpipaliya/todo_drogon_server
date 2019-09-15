#pragma once
namespace openproject {
class Authorization::UserProjectRolesQuery : public Authorization::UserRolesQuery {
  transformations.register :all, :project_where_projection { |statement, user, _|
    statement.where(users_table[:id].eq(user.id))
  }

  transformations.register users_members_join, :project_id_limit { |statement, _, project|
    statement.and(members_table[:project_id].eq(project.id))
  }

  transformations.register roles_member_roles_join, :builtin_role { |statement, user, project|
    if ( project.is_public?) {
      builtin_role = if ( user.logged?) {
                       Role::BUILTIN_NON_MEMBER
                     else
                       Role::BUILTIN_ANONYMOUS
                     }

      builtin_role_condition = members_table[:id]
                               .eq(nil)
                               .and(roles_table[:builtin]
                                    .eq(builtin_role))

      statement = statement.or(builtin_role_condition)
    }

    statement
  }
}
