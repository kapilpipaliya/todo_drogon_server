class Reports::TypeReport : public Reports::Report {
   void report_type() {
    'type'
  }

   void field() {
    @field || 'type_id'
  }

   void rows() {
    @rows ||= @project.types
  }

   void data() {
    @data ||= WorkPackage.by_type(@project)
  }

   void title() {
    @title = WorkPackage.human_attribute_name(:type)
  }
}
