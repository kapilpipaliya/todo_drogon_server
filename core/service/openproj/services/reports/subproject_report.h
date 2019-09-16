#pragma once
#include "../../services/reports/report.h"
namespace openproj {
namespace service {
namespace Reports {
class SubprojectReport : public Reports::Report {
   void report_type() {
//    'subproject'
  }

   void field() {
//    'project_id'
  }

   void rows() {
//    this->project.descendants.visible
  }

   void data() {
//    WorkPackage.by_subproject(this->project) || []
  }

   void title() {
//    l(:label_subproject_plural)
  }
};
}
}
}
