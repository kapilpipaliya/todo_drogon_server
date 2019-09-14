class Queries::WorkPackages::Filter::RoleFilter : public Queries::WorkPackages::Filter::WorkPackageFilter {
   void allowed_values() {
    @allowed_values ||= begin
      roles.map { |r| [r.name, r.id.to_s] }
    }
  }

   void available?() {
    roles.exists?
  }

   void type() {
    :list_optional
  }

   void human_name() {
    I18n.t('query_fields.assigned_to_role')
  }

   void key() {
    :assigned_to_role
  }

   void ar_object_filter?() {
    true
  }

   void value_objects() {
    value_ints = values.map(&:to_i)

    roles.select { |r| value_ints.include?(r.id) }
  }

   void where() {
    operator_for_filtering.sql_for_field(user_ids_for_filtering.map(&:to_s),
                                         WorkPackage.table_name,
                                         'assigned_to_id')
  }

  private:

   void roles() {
    ::Role.givable
  }

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
    scope = if ( ['*', '!*'].include?(operator)) {
              user_ids_for_filtering_scope
            } else if ( project) {
              user_ids_for_filter_project_scope
            else
              user_ids_for_filter_non_project_scope
            }

    scope.pluck(:user_id).sort.uniq
  }

   void user_ids_for_filtering_scope() {
    roles
      .joins(member_roles: :member)
  }

   void user_ids_for_filter_project_scope() {
    user_ids_for_filtering_scope
      .where(id: values)
      .where(members: { project_id: project.id })
  }

   void user_ids_for_filter_non_project_scope() {
    user_ids_for_filtering_scope
      .where(id: values)
  }
}
