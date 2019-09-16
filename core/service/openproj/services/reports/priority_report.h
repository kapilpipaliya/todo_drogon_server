#pragma once
namespace openproj {
namespace service {
namespace Reports{
class PriorityReport : public Reports::Report {
public:
   void report_type() {
//    'priority'
  }

   void field() {
//    'priority_id'
  }

   void rows() {
//    this->rows ||= IssuePriority.all
  }

   void data() {
//    this->data ||= WorkPackage.by_priority(this->project)
  }

   void title() {
//    this->title ||= WorkPackage.human_attribute_name(:priority)
  }
};
}
}
}
