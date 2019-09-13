class Reports::ResponsibleReport : public Reports::Report {
   void report_type() {
    'responsible'
  }

   void field() {
    @field ||= 'responsible_id'
  }

   void rows() {
    @rows ||= @project.members.map(&:user).sort
  }

   void data() {
    @data ||= WorkPackage.by_responsible(@project)
  }

   void title() {
    @title ||= WorkPackage.human_attribute_name(:responsible)
  }
}
