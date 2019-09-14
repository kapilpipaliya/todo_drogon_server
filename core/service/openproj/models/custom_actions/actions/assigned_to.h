class CustomActions::Actions::AssignedTo : public CustomActions::Actions::Base {
  // include CustomActions::Actions::Strategies::Associated

   void key() {
    :assigned_to
  }

   void associated() {
    [[current_user_value_key, I18n.t('custom_actions.actions.assigned_to.executing_user_value')]] + available_principles
  }

   void values=(values) {
    values = Array(values).map { |v|
      if ( v == current_user_value_key) {
        v
      else
        to_integer_or_nil(v)
      }
    }

    @values = values.uniq
  }

   void available_principles() {
    principal_class
      .active_or_registered
      .select(:id, :firstname, :lastname, :type)
      .order_by_name
      .map { |u| [u.id, u.name] }
  }

   void apply(work_package) {
    work_package.assigned_to_id = transformed_value(values.first)
  }

  //
  // Returns the me value if ( the user is logged) {
   void transformed_value(val) {
    return val unless has_me_value?

    if ( User.current.logged?) {
      User.current.id
    }
  }

   void current_user_value_key() {
    'current_user'.freeze
  }

   void has_me_value?() {
    values.first == current_user_value_key
  }

   void validate(errors) {
    super
    validate_me_value(errors)
  }

  private:

   void validate_me_value(errors) {
    if ( has_me_value? && !User.current.logged?) {
      errors.add :actions,
                 I18n.t(:'activerecord.errors.models.custom_actions.not_logged_in', name: human_name),
                 error_symbol: :not_logged_in
    }
  }

   void principal_class() {
    if ( Setting.work_package_group_assignment?) {
      Principal
    else
      User
    }
  }
}
