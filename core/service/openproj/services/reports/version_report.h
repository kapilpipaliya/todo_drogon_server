#pragma once
#include "report.h"
namespace openproj {
namespace service {
namespace Reports{
class VersionReport : public Reports::Report {
public:
   void report_type() {
//    'version'
  }

   void field() {
//    this->field ||= 'fixed_version_id'
  }

   void rows() {
//    this->rows ||= this->project.shared_versions.sort
  }

   void data() {
//    this->data ||= WorkPackage.by_version(this->project)
  }

   void title() {
//    this->title ||= WorkPackage.human_attribute_name(:version)
  }
};
}
}
}
