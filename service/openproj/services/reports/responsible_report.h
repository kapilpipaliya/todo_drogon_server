#pragma once
#include "../../services/reports/report.h"
namespace openproj {
namespace service {
namespace Reports{
class ResponsibleReport : public Reports::Report {
public:
   void report_type() {
//    "responsible"
  }

   void field() {
//    this->field ||= "responsible_id"
  }

   void rows() {
//    this->rows ||= this->project.members.map(&:user).sort
  }

   void data() {
//    this->data ||= WorkPackage.by_responsible(this->project)
  }

   void title() {
//    this->title ||= WorkPackage.human_attribute_name(:responsible)
  }
};
}
}
}
