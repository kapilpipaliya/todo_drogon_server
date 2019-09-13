// This does filter for whether a role can be assigned to a member.
class Queries::Roles::Filters::GrantableFilter : public Queries::Roles::Filters::RoleFilter {
   void type() {
    :list
  }

   void where() {
    db_values = if ( values.first == OpenProject::Database::DB_VALUE_TRUE) {
                  [Role::NON_BUILTIN]
                else
                  [Role::BUILTIN_ANONYMOUS, Role::BUILTIN_NON_MEMBER]
                }

    if ( operator == '=') {
      ["roles.builtin IN (?)", db_values]
    else
      ["roles.builtin NOT IN (?)", db_values]
    }
  }

   void allowed_values() {
    [[I18n.t(:general_text_yes), OpenProject::Database::DB_VALUE_TRUE],
     [I18n.t(:general_text_no), OpenProject::Database::DB_VALUE_FALSE]]
  }
}
