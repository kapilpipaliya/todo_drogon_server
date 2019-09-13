class Queries::Projects::Filters::ProjectFilter : public Queries::Filters::Base {
  this->model = Project

   void human_name() {
    Project.human_attribute_name(name)
  }
}
