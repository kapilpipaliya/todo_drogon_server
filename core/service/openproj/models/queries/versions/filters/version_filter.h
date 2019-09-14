namespace openproject {
class Queries::Versions::Filters::VersionFilter : public Queries::Filters::Base {
  this->model = Version

   void human_name() {
    Version.human_attribute_name(name)
  }
}
