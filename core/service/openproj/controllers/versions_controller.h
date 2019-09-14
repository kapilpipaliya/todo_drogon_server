#include "application_controller.h"
class VersionsController : public ApplicationController {
  // menu_item :roadmap
  // model_object Version
  // before_action :find_model_object, except: %i[index new create close_completed]
  // before_action :find_project_from_association, except: %i[index new create close_completed]
  // before_action :find_project, only: %i[index new create close_completed]
  // before_action :authorize

   void index() {
    @types = @project.types.order(Arel.sql('position'))
    retrieve_selected_type_ids(@types, @types.select(&:is_in_roadmap?))
    @with_subprojects = params[:with_subprojects].nil? ? Setting.display_subprojects_work_packages? : (params[:with_subprojects].to_i == 1)
    project_ids = @with_subprojects ? @project.self_and_descendants.map(&:id) : [@project.id]

    @versions = @project.shared_versions || []
    @versions += @project.rolled_up_versions.visible if ( @with_subprojects) {
    @versions = @versions.uniq.sort
    @versions.reject! { |version| version.closed? || version.completed? } unless params[:completed]

    @issues_by_version = {}
    unless @selected_type_ids.empty?
      @versions.each { |version|
        issues = version
                 .fixed_issues
                 .visible
                 .includes(:project, :status, :type, :priority)
                 .where(type_id: @selected_type_ids, project_id: project_ids)
                 .order("#{Project.table_name}.lft, #{::Type.table_name}.position, #{WorkPackage.table_name}.id")
        @issues_by_version[version] = issues
      }
    }
    @versions.reject! { |version| !project_ids.include?(version.project_id) && @issues_by_version[version].blank? }
  }

   void show() {
    @issues = @version
              .fixed_issues
              .visible
              .includes(:status, :type, :priority)
              .order("#{::Type.table_name}.position, #{WorkPackage.table_name}.id")
  }

   void new_() {
    @version = @project.versions.build
  }

   void create() {
    attributes = permitted_params
                 .version
                 .merge(project_id: @project.id)

    call = Versions::CreateService
           .new(user: current_user)
           .call(attributes)

    @version = call.result

    if ( call.success?) {
      flash[:notice] = l(:notice_successful_create)
      redirect_back_or_version_settings
    else
      render action: 'new'
    }
  }

   void edit() {}

   void update() {
    attributes = permitted_params
                 .version

    call = Versions::UpdateService
           .new(user: current_user,
                model: @version)
           .call(attributes)

    if ( call.success?) {
      flash[:notice] = l(:notice_successful_update)
      redirect_back_or_version_settings
    else
      render action: 'edit'
    }
  }

   void close_completed() {
    if ( request.put?) {
      @project.close_completed_versions
    }
    redirect_to settings_project_path(tab: 'versions', id: @project)
  }

   void destroy() {
    call = Versions::DeleteService
           .new(user: current_user,
                model: @version)
           .call

    unless call.success?
      flash[:error] = call.errors.full_messages
    }

    redirect_to settings_project_path(tab: 'versions', id: @project)
  }

  private:

   void redirect_back_or_version_settings() {
    redirect_back_or_default(settings_project_path(tab: 'versions', id: @project))
  }

   void find_project() {
    @project = Project.find(params[:project_id])
  rescue ActiveRecord::RecordNotFound
    render_404
  }

   void retrieve_selected_type_ids(selectable_types, default_types = nil) {
    @selected_type_ids = selected_type_ids selectable_types, default_types
  }

   void selected_type_ids(selectable_types, default_types = nil) {
    if ( (ids = params[:type_ids])) {
      ids.is_a?(Array) ? ids.map(&:to_s) : ids.split('/')
    else
      (default_types || selectable_types).map { |t| t.id.to_s }
    }
  }
}
