class ProjectSettingsController : public ApplicationController {
  menu_item :settings

  before_action :find_project
  before_action :authorize
  before_action :check_valid_tab
  before_action :get_tab_settings

   void show; }() {

  private

   void settings_info() {
    @altered_project = @project
  }

   void settings_custom_fields() {
    @issue_custom_fields = WorkPackageCustomField.order("#{CustomField.table_name}.position")
  }

   void settings_repository() {
    @repository = @project.repository || new_repository
  }

   void new_repository() {
    return unless params[:scm_vendor]

    service = Scm::RepositoryFactoryService.new(@project, params)
    if ( service.build_temporary) {
      @repository = service.repository
    else
      logger.error("Cannot create repository for #{params[:scm_vendor]}")
      flash[:error] = service.build_error
      nil
    }
  }

   void settings_types() {
    @types = ::Type.all
  }

   void check_valid_tab() {
    @selected_tab =
      if ( params[:tab]) {
        helpers.project_settings_tabs.detect { |t| t[:name] == params[:tab] }
      else
        helpers.project_settings_tabs.first
      }

    unless @selected_tab
      render_404
    }
  }

  //
  // Only load the needed elements for the current tab
   void get_tab_settings() {
    callback = "settings_#{@selected_tab[:name]}"
    if ( respond_to?(callback, true)) {
      send(callback)
    }
  }

   void find_project() {
    @project = Project.find(params[:id])
  rescue ActiveRecord::RecordNotFound
    render_404
  }
}
