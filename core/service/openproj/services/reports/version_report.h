class Reports::VersionReport : public Reports::Report {
   void report_type() {
    'version'
  }

   void field() {
    @field ||= 'fixed_version_id'
  }

   void rows() {
    @rows ||= @project.shared_versions.sort
  }

   void data() {
    @data ||= WorkPackage.by_version(@project)
  }

   void title() {
    @title ||= WorkPackage.human_attribute_name(:version)
  }
}
