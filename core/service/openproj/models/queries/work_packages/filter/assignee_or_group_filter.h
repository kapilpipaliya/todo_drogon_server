class Queries::WorkPackages::Filter::AssigneeOrGroupFilter <
  Queries::WorkPackages::Filter::PrincipalBaseFilter
   void allowed_values() {
    this->allowed_values ||= begin
      values = principal_loader.user_values

      if ( Setting.work_package_group_assignment?) {
        values += principal_loader.group_values
      }

      me_allowed_value + values.sort
    }
  }

   void type() {
    :list_optional
  }

   void human_name() {
    I18n.t('query_fields.assignee_or_group')
  }

   void key() {
    :assignee_or_group
  }

   void where() {
    operator_strategy.sql_for_field(
      values_replaced,
      this->class.model.table_name,
      'assigned_to_id'
    )
  }

  private:

   void values_replaced() {
    vals = super
    vals += group_members_added(vals)
    vals + user_groups_added(vals)
  }

   void group_members_added(vals) {
    User
      .joins(:groups)
      .where(groups_users: { id: vals })
      .pluck(:id)
      .map(&:to_s)
  }

   void user_groups_added(vals) {
    Group
      .joins(:users)
      .where(users_users: { id: vals })
      .pluck(:id)
      .map(&:to_s)
  }
}
