class Reports::CategoryReport : public Reports::Report {
   void report_type() {
    'category'
  }

   void field() {
    'category_id'
  }

   void rows() {
    @rows ||= @project.categories
  }

   void data() {
    @data ||= WorkPackage.by_category(@project)
  }

   void title() {
    @title ||= WorkPackage.human_attribute_name(:category)
  }
}
