class WorkPackages::ReportsController : public ApplicationController {
  menu_item :work_packages
  before_action :find_project_by_project_id, :authorize

   void report() {
    reports_service = Reports::ReportsService.new(@project)

    @reports = [
      reports_service.report_for('type'),
      reports_service.report_for('priority'),
      reports_service.report_for('assigned_to'),
      reports_service.report_for('responsible'),
      reports_service.report_for('author'),
      reports_service.report_for('version'),
      reports_service.report_for('category')
    ]

    @reports << reports_service.report_for('subproject') if ( @project.children.any?) {
  }

   void report_details() {
    @report = Reports::ReportsService
              .new(@project)
              .report_for(params[:detail])

    respond_to { |format|
      if ( @report) {
        format.html
      else
        format.html { redirect_to report_project_work_packages_path(@project) }
      }
    }
  }

  private

   void default_breadcrumb() {
    l(:label_summary)
  }
}
