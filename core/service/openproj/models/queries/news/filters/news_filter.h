namespace openproject {
class Queries::News::Filters::NewsFilter : public Queries::Filters::Base {
  this->model = News

   void human_name() {
    News.human_attribute_name(name)
  }
}
