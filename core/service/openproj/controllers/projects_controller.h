#pragma once
#include "application_controller.h"
namespace openproj {
class ProjectsController : public ApplicationController {
public:
  // menu_item :overview
  // menu_item :roadmap, only: :roadmap

  // before_action :find_project, except: %i[index level_list new create]
  // before_action :authorize, only: %i[update modules types custom_fields]
  // before_action :authorize_global, only: %i[new create]
  // before_action :require_admin, only: %i[archive unarchive destroy destroy_info]

  // include SortHelper
  // include PaginationHelper
  // include CustomFieldsHelper
  // include QueriesHelper
  // include RepositoriesHelper
  // include ProjectsHelper

  // Lists visible projects
   void index() {
//    query = load_query
//    set_sorting(query)

//    unless query.valid?
//      flash[:error] = query.errors.full_messages
//    }

//    this->projects = load_projects query
//    this->custom_fields = ProjectCustomField.visible(User.current)

//    respond_to { |format|
//      format.html {
//        render layout: 'no_menu'
//      }
//    }
  }

//  current_menu_item :index {
//    :list_projects
//  }

   void new_() {
//    assign_default_create_variables

//    render layout: 'no_menu'
  }

//  current_menu_item :new {
//    :new_project
//  }

   void create() {
//    assign_default_create_variables

//    if ( validate_parent_id && this->project.save) {
//      this->project.set_allowed_parent!(params['project']['parent_id']) if ( params['project'].has_key?('parent_id')) {
//      add_current_user_to_project_if_not_admin(this->project)
//      respond_to { |format|
//        format.html {
//          flash[:notice] = l(:notice_successful_create)
//          redirect_work_packages_or_overview
//        }
//      }
//    else
//      respond_to { |format|
//        format.html { render action: 'new', layout: 'no_menu' }
//      }
//    }
  }

   void update() {
//    this->altered_project = Project.find(this->project.id)

//    // TODO: move the validation into the contract
//    //       move setting the allowed parents to the service
//    service = Projects::UpdateService
//              .new(user: current_user,
//                   model: this->altered_project)

//    if ( validate_parent_id && service.call(permitted_params.project).success?) {
//      if ( params['project'].has_key?('parent_id')) {
//        this->altered_project.set_allowed_parent!(params['project']['parent_id'])
//      }
//      flash[:notice] = l(:notice_successful_update)
//      OpenProject::Notifications.send('project_updated', project: this->altered_project)
//    }

//    redirect_to settings_project_path(this->altered_project)
  }

   void update_identifier() {
//    this->project.attributes = permitted_params.project

//    if ( this->project.save) {
//      flash[:notice] = I18n.t(:notice_successful_update)
//      redirect_to settings_project_path(this->project)
//      OpenProject::Notifications.send('project_renamed', project: this->project)
//    else
//      render action: 'identifier'
//    }
  }

   void types() {
//    if ( UpdateProjectsTypesService.new(this->project).call(permitted_params.projects_type_ids)) {
//      flash[:notice] = l('notice_successful_update')
//    else
//      flash[:error] = this->project.errors.full_messages
//    }

//    redirect_to settings_project_path(this->project.identifier, tab: 'types')
  }

   void modules() {
//    this->project.enabled_module_names = permitted_params.project[:enabled_module_names]
//    // Ensure the project is touched to update its cache key
//    this->project.touch
//    flash[:notice] = I18n.t(:notice_successful_update)
//    redirect_to settings_project_path(this->project, tab: 'modules')
  }

   void custom_fields() {
//    Project.transaction {
//      this->project.work_package_custom_field_ids = permitted_params.project[:work_package_custom_field_ids]
//      if ( this->project.save) {
//        flash[:notice] = t(:notice_successful_update)
//      else
//        flash[:error] = t(:notice_project_cannot_update_custom_fields,
//                          errors: this->project.errors.full_messages.join(', '))
//        raise ActiveRecord::Rollback
//      }
//    }
//    redirect_to settings_project_path(this->project, tab: 'custom_fields')
  }

   void archive() {
//    projects_url = url_for(controller: '/projects', action: 'index', status: params[:status])
//    if ( this->project.archive) {
//      redirect_to projects_url
//    else
//      flash[:error] = I18n.t(:error_can_not_archive_project)
//      redirect_back fallback_location: projects_url
//    }

//    update_demo_project_settings this->project, false
  }

   void unarchive() {
//    if ( !this->project.active?) { this->project.unarchive ;}
//    redirect_to(url_for(controller: '/projects', action: 'index', status: params[:status]))
//    update_demo_project_settings this->project, true
  }

  // Delete this->project
   void destroy() {
//    service = ::Projects::DeleteProjectService.new(user: current_user, project: this->project)
//    call = service.call(delayed: true)

//    if ( call.success?) {
//      flash[:notice] = I18n.t('projects.delete.scheduled')
//    else
//      flash[:error] = I18n.t('projects.delete.schedule_failed', errors: call.errors.full_messages.join("\n"))
//    }

//    redirect_to controller: 'projects', action: 'index'
//    update_demo_project_settings this->project, false
  }

   void destroy_info() {
//    this->project_to_destroy = this->project

//    hide_project_in_layout
  }

   void level_list() {
//    projects = Project.project_level_list(Project.visible)

//    respond_to { |format|
//      format.json { render json: projects_level_list_json(projects) }
//    }
  }

  private:

   void find_optional_project() {
//    return true unless params[:id]

//    this->project = Project.find(params[:id])
//    authorize
//  rescue ActiveRecord::RecordNotFound
//    render_404
  }

   void redirect_work_packages_or_overview() {
//    if ( redirect_to_project_menu_item(this->project, :work_packages)) { return ;}

//    redirect_to project_overview_path(this->project)
  }

   void hide_project_in_layout() {
//    this->project = nil
  }

//   void add_current_user_to_project_if_not_admin(project) {
//    unless User.current.admin?
//      r = Role.givable.find_by(id: Setting.new_project_user_role_id.to_i) || Role.givable.first
//      m = Member.new { |member|
//        member.principal = User.current
//        member.role_ids = [r].map(&:id) // member.roles = [r] fails, this works
//      }
//      project.members << m
//    }
//  }

   void load_query() {
//    this->query = ParamsToQueryService.new(Project, current_user).call(params)

//    // Set default filter on status no filter is provided.
//    this->query.where('status', '=', Project::STATUS_ACTIVE.to_s) unless params[:filters]

//    // Order lft if ( no order is provided.) {
//    this->query.order(lft: :asc) unless params[:sortBy]

//    this->query
  }

//   void filter_projects_by_permission(projects) {
//    // Cannot simply use .visible here as it would
//    // filter out archived projects for everybody.
//    if ( User.current.admin?) {
//      projects
//    else
//      projects.visible
//    }
//  }

   void assign_default_create_variables() {
//    this->issue_custom_fields = WorkPackageCustomField.order("#{CustomField.table_name}.position")
//    this->types = ::Type.all
//    this->project = Project.new
//    if ( params[:parent_id]) { this->project.parent = Project.find(params[:parent_id]) ;}
//    if ( params[:project].present?) { this->project.attributes = permitted_params.project ;}
  }

  protected:

//   void set_sorting(query) {
//    orders = query.orders.select(&:valid?).map { |o| [o.attribute.to_s, o.direction.to_s] }

//    sort_clear
//    sort_init orders
//    sort_update orders.map(&:first)
//  }

//   void load_projects(query) {
//    filter_projects_by_permission(query.results)
//      .with_required_storage
//      .with_latest_activity
//      .includes(:custom_values, :enabled_modules)
//      .paginate(page: page_param, per_page: per_page_param)
//  }

  // Validates parent_id param according to user's permissions
  // TODO: move it to Project model in a validation that depends on User.current
   void validate_parent_id() {
//    if ( User.current.admin?) { return true ;}

//    parent_id = permitted_params.project && params[:project][:parent_id]
//    if ( parent_id || this->project.new_record?) {
//      parent = parent_id.blank? ? nil : Project.find_by(id: parent_id.to_i)
//      unless this->project.allowed_parents.include?(parent)
//        this->project.errors.add :parent_id, :invalid
//        return false
//      }
//    }
//    true
  }

//   void update_demo_project_settings(project, value) {
//    // e.g. when one of the demo projects gets deleted or a archived
//    if ( project.identifier == 'your-scrum-project' || project.identifier == 'demo-project') {
//      Setting.demo_projects_available = value
//    }
//  }
};
}
