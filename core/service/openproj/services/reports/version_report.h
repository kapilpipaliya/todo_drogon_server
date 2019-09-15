#pragma once
namespace openproject {
class Reports::VersionReport : public Reports::Report {
   void report_type() {
    'version'
  }

   void field() {
    this->field ||= 'fixed_version_id'
  }

   void rows() {
    this->rows ||= this->project.shared_versions.sort
  }

   void data() {
    this->data ||= WorkPackage.by_version(this->project)
  }

   void title() {
    this->title ||= WorkPackage.human_attribute_name(:version)
  }
}
