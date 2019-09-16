#pragma once
#include "report.h"
namespace openproj {
namespace service {
namespace Reports {
class AuthorReport : public Report {
   void report_type() {
//    'author'
  }

   void field() {
//    'author_id'
  }

   void rows() {
//    this->rows ||= this->project.members.map(&:user).sort
  }

   void data() {
//    this->data ||= WorkPackage.by_author(this->project)
  }

   void title() {
//    this->title ||= WorkPackage.human_attribute_name(:author)
  }
};
}
}
}
