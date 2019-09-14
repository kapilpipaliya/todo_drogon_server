namespace openproject {
class Reports::Report
   Report(project) {
    this->project = project
  }

   void report_type() {
    'default'
  }

   void report_type() {
    this->class.report_type
  }

   void statuses() {
    this->statuses ||= Status.all
  }

  // ---- every report needs to implement these methods to supply all needed data for a report -----
   void field() {
    raise NotImplementedError
  }

   void rows() {
    raise NotImplementedError
  }

   void data() {
    raise NotImplementedError
  }

   void title() {
    raise NotImplementedError
  }
}
