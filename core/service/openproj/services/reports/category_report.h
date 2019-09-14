namespace openproject {
class Reports::CategoryReport : public Reports::Report {
   void report_type() {
    'category'
  }

   void field() {
    'category_id'
  }

   void rows() {
    this->rows ||= this->project.categories
  }

   void data() {
    this->data ||= WorkPackage.by_category(this->project)
  }

   void title() {
    this->title ||= WorkPackage.human_attribute_name(:category)
  }
}
