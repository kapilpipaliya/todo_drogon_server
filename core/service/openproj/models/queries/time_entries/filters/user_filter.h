namespace openproj {
class Queries::TimeEntries::Filters::UserFilter : public Queries::TimeEntries::Filters::TimeEntryFilter {
  // include Queries::Filters::Shared::MeValueFilter

   void allowed_values() {
    this->allowed_values ||= begin
      // We don't care for the first value as we do not display the values visibly
      me_allowed_value + ::Principal
                         .in_visible_project
                         .pluck(:id)
                         .map { |id| [id, id.to_s] }
    }
  }

   void where() {
    operator_strategy.sql_for_field(values_replaced, this->class.model.table_name, this->class.key)
  }

   void type() {
    :list_optional
  }

   void key() {
    :user_id
  }
}
