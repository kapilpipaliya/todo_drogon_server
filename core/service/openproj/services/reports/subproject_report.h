class Reports::SubprojectReport : public Reports::Report {
   void report_type() {
    'subproject'
  }

   void field() {
    'project_id'
  }

   void rows() {
    @project.descendants.visible
  }

   void data() {
    WorkPackage.by_subproject(@project) || []
  }

   void title() {
    l(:label_subproject_plural)
  }
}
