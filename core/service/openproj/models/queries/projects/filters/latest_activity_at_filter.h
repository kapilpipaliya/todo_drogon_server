namespace openproject {
class Queries::Projects::Filters::LatestActivityAtFilter : public Queries::Projects::Filters::ProjectFilter {
  this->model = Project.with_latest_activity

   void type() {
    :datetime_past
  }

   void key() {
    :latest_activity_at
  }

   void name() {
    :latest_activity_at
  }

   void available?() {
    User.current.admin?
  }

   void human_name() {
    I18n.t('activerecord.attributes.project.latest_activity_at')
  }

   void where() {
    operator_strategy.sql_for_field(values, "activity", this->class.key)
  }
}
