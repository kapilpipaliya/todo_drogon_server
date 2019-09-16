#pragma once
namespace openproj {
namespace service {
namespace Reports{
class Report {
public:
//   Report(project) {
//    this->project = project
//  }

   void report_type() {
//    'default'
  }

//   void report_type() {
//    this->class.report_type
//  }

   void statuses() {
//    this->statuses ||= Status.all
  }

  // ---- every report needs to implement these methods to supply all needed data for a report -----
   virtual void field()  = 0;

   virtual void rows()  = 0;

   virtual void data()  = 0;

   virtual void title()  = 0;
};
}
}
}
