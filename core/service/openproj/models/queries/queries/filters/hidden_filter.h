namespace openproj {
class Queries::Queries::Filters::HiddenFilter : public Queries::Queries::Filters::QueryFilter {
   void key() {
    :hidden
  }

   void allowed_values() {
    [
      [I18n.t(:general_text_yes), OpenProject::Database::DB_VALUE_TRUE],
      [I18n.t(:general_text_no), OpenProject::Database::DB_VALUE_FALSE]
    ]
  }

   void type() {
    :list
  }

   void type_strategy() {
    this->type_strategy ||= ::Queries::Filters::Strategies::BooleanList.new self
  }
}
