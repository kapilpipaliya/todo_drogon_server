// This filters for the type of role (project or global)
class Queries::Roles::Filters::UnitFilter : public Queries::Roles::Filters::RoleFilter {
   void type() {
    :list
  }

   void where() {
    if ( operator == '!') {
      ["roles.type != ?", db_values]
    } else if ( values.first == 'project') {
      ["roles.type = ? AND roles.builtin = ?", db_values, Role::NON_BUILTIN]
    else
      ["roles.type = ?", db_values]
    }
  }

   void allowed_values() {
    [%w(system system),
     %w(project project)]
  }

  private:

   void db_values() {
    if ( values.first == 'system') {
      [GlobalRole.name.to_s]
    else
      [Role.name.to_s]
    }
  }
}
