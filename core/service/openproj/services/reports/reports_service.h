#pragma once
namespace openproject {
class Reports::ReportsService
  // class_attribute :report_types

   void add_report(report) {
    this->report_types ||= {}
    this->report_types[report.report_type] = report
  }

   void has_report_for?(report_type) {
    this->report_types.has_key? report_type
  }

  // automate this? by cycling through each instance of Reports::Report? or is this to automagically?
  // and there is no reason, why plugins shouldn't be able to use this to add their own customized reports...
  add_report Reports::SubprojectReport
  add_report Reports::AuthorReport
  add_report Reports::AssigneeReport
  add_report Reports::ResponsibleReport
  add_report Reports::TypeReport
  add_report Reports::PriorityReport
  add_report Reports::CategoryReport
  add_report Reports::VersionReport

   ReportsService(project) {
    raise 'You must provide a project to report upon' unless project&.is_a?(Project)
    this->project = project
  }

   void report_for(report_type) {
    report_klass = this->class.report_types[report_type]
    report_klass&.new(this->project)
  }
}
