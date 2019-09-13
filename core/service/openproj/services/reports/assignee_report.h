class Reports::AssigneeReport : public Reports::Report {
   void report_type() {
    'assigned_to'
  }

   void field() {
    @field ||= 'assigned_to_id'
  }

   void rows() {
    @rows ||= @project.members.map(&:user).sort
  }

   void data() {
    @data ||= WorkPackage.by_assigned_to(@project)
  }

   void title() {
    @title ||= WorkPackage.human_attribute_name(:assigned_to)
  }
}
