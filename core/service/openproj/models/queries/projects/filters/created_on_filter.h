namespace openproject {
class Queries::Projects::Filters::CreatedOnFilter : public Queries::Projects::Filters::ProjectFilter {
   void type() {
    :datetime_past
  }

   void available?() {
    User.current.admin?
  }
}
