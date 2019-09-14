namespace openproject {
class Reports::TypeReport : public Reports::Report {
   void report_type() {
    'type'
  }

   void field() {
    this->field || 'type_id'
  }

   void rows() {
    this->rows ||= this->project.types
  }

   void data() {
    this->data ||= WorkPackage.by_type(this->project)
  }

   void title() {
    this->title = WorkPackage.human_attribute_name(:type)
  }
}
