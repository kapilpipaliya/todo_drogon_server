namespace openproj {
class Queries::Principals::Filters::PrincipalFilter : public Queries::Filters::Base {
  this->model = Principal

   void human_name() {
    Principal.human_attribute_name(name)
  }
}
