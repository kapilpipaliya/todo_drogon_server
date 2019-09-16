#pragma once
#include "../application_controller.h"
namespace openproj {
namespace controller {
namespace WorkPackages {

class ReportsController : public ApplicationController {
  // menu_item :work_packages
  // before_action :find_project_by_project_id, :authorize

   void report() {
//    reports_service = Reports::ReportsService.new(this->project)

//    this->reports = [
//      reports_service.report_for('type'),
//      reports_service.report_for('priority'),
//      reports_service.report_for('assigned_to'),
//      reports_service.report_for('responsible'),
//      reports_service.report_for('author'),
//      reports_service.report_for('version'),
//      reports_service.report_for('category')
//    ]

//    if ( this->project.children.any?) { this->reports << reports_service.report_for('subproject') ;}
  }

   void report_details() {
//    this->report = Reports::ReportsService
//              .new(this->project)
//              .report_for(params[:detail])

//    respond_to { |format|
//      if ( this->report) {
//        format.html
//      else
//        format.html { redirect_to report_project_work_packages_path(this->project) }
//      }
//    }
  }

  private:

   void default_breadcrumb() {
//    l(:label_summary)
  }
};
}
}
}
