class Reports::PriorityReport : public Reports::Report {
   void report_type() {
    'priority'
  }

   void field() {
    'priority_id'
  }

   void rows() {
    @rows ||= IssuePriority.all
  }

   void data() {
    @data ||= WorkPackage.by_priority(@project)
  }

   void title() {
    @title ||= WorkPackage.human_attribute_name(:priority)
  }
}
