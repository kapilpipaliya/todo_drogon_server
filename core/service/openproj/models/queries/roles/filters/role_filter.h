namespace openproj {
class Queries::Roles::Filters::RoleFilter : public Queries::Filters::Base {
  this->model = Role

   void human_name() {
    Role.human_attribute_name(name)
  }
}
