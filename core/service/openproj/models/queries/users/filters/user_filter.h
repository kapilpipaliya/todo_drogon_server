namespace openproj {
class Queries::Users::Filters::UserFilter : public Queries::Filters::Base {
  this->model = User

   void human_name() {
    User.human_attribute_name(name)
  }
}
