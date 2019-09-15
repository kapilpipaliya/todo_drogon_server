#pragma once
namespace openproject {
class Authorization::UserRolesQuery : public Authorization::AbstractUserQuery {
  this->model = Role
  this->base_table = users_table

   void query(*args) {
    arel = transformed_query(*args)

    model.where(roles_table[:id].in(arel))
  }

  transformations.register :all, :roles_join { |statement|
    statement.outer_join(roles_table)
             .on(roles_member_roles_join)
  }

  transformations.register :all, :project { |statement|
    statement.project(roles_table[:id])
  }

   void roles_member_roles_join() {
    roles_table[:id].eq(member_roles_table[:role_id])
  }
}
