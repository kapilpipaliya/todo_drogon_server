#pragma once
namespace openproj {
class Reports::ResponsibleReport : public Reports::Report {
   void report_type() {
    'responsible'
  }

   void field() {
    this->field ||= 'responsible_id'
  }

   void rows() {
    this->rows ||= this->project.members.map(&:user).sort
  }

   void data() {
    this->data ||= WorkPackage.by_responsible(this->project)
  }

   void title() {
    this->title ||= WorkPackage.human_attribute_name(:responsible)
  }
}
