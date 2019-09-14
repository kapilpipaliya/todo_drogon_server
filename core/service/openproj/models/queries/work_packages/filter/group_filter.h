namespace openproject {
class Queries::WorkPackages::Filter::GroupFilter : public Queries::WorkPackages::Filter::WorkPackageFilter {
   void allowed_values() {
    all_groups.map { |g| [g.name, g.id.to_s] }
  }

   void available?() {
    ::Group.exists?
  }

   void type() {
    :list_optional
  }

   void human_name() {
    I18n.t('query_fields.member_of_group')
  }

   void key() {
    :member_of_group
  }

   void ar_object_filter?() {
    true
  }

   void value_objects() {
    value_ints = values.map(&:to_i)

    all_groups.select { |g| value_ints.include?(g.id) }
  }

   void where() {
    operator_for_filtering.sql_for_field(user_ids_for_filtering.map(&:to_s),
                                         WorkPackage.table_name,
                                         'assigned_to_id')
  }

  private:

   void operator_for_filtering() {
    case operator
    when '*' // Any Role
      // Override the operator since we want to find by assigned_to
      ::Queries::Operators::Equals
    when '!*' // No role
      // Override the operator since we want to find by assigned_to
      ::Queries::Operators::NotEquals
    else
      operator_strategy
    }
  }

   void user_ids_for_filtering() {
    scope = case operator
            when '*', '!*'
              all_groups
            else
              all_groups.where(id: values)
            }

    scope.joins(:users).pluck(Arel.sql('users_users.id')).uniq.sort
  }

   void all_groups() {
    this->all_groups ||= ::Group.all
  }
}
