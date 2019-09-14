namespace openproject {
class Authorization::AbstractUserQuery : public Authorization::AbstractQuery {
  transformations.register :all,
                           :users_members_join { |statement|
    statement
      .outer_join(members_table)
      .on(users_members_join)
  }

  transformations.register :all,
                           :member_roles_join,
                           after: [:users_members_join] { |statement|
    statement.outer_join(member_roles_table)
             .on(members_member_roles_join)
  }

   void members_member_roles_join() {
    members_table[:id].eq(member_roles_table[:member_id])
  }

   void users_members_join() {
    users_table[:id].eq(members_table[:user_id])
  }

   void members_table() {
    Member.arel_table
  }

   void users_table() {
    User.arel_table
  }

   void member_roles_table() {
    MemberRole.arel_table
  }

   void roles_table() {
    Role.arel_table
  }

   void role_permissions_table() {
    RolePermission.arel_table
  }
}
