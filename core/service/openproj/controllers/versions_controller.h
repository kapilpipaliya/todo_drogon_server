#include "application_controller.h"
class VersionsController : public ApplicationController {
public:
  // menu_item :roadmap
  // model_object Version
  // before_action :find_model_object, except: %i[index new create close_completed]
  // before_action :find_project_from_association, except: %i[index new create close_completed]
  // before_action :find_project, only: %i[index new create close_completed]
  // before_action :authorize
   void index() {
//    this->types = this->project.types.order(Arel.sql('position'))
//    retrieve_selected_type_ids(this->types, this->types.select(&:is_in_roadmap?))
//    this->with_subprojects = params[:with_subprojects].nil? ? Setting.display_subprojects_work_packages? : (params[:with_subprojects].to_i == 1)
//    project_ids = this->with_subprojects ? this->project.self_and_descendants.map(&:id) : [this->project.id]

//    this->versions = this->project.shared_versions || []
//    if ( this->with_subprojects) { this->versions += this->project.rolled_up_versions.visible ;}
//    this->versions = this->versions.uniq.sort
//    this->versions.reject! { |version| version.closed? || version.completed? } unless params[:completed]

//    this->issues_by_version = {}
//    unless this->selected_type_ids.empty?
//      this->versions.each { |version|
//        issues = version
//                 .fixed_issues
//                 .visible
//                 .includes(:project, :status, :type, :priority)
//                 .where(type_id: this->selected_type_ids, project_id: project_ids)
//                 .order("#{Project.table_name}.lft, #{::Type.table_name}.position, #{WorkPackage.table_name}.id")
//        this->issues_by_version[version] = issues
//      }
//    }
//    this->versions.reject! { |version| !project_ids.include?(version.project_id) && this->issues_by_version[version].blank? }
  }

   void show() {
//    this->issues = this->version
//              .fixed_issues
//              .visible
//              .includes(:status, :type, :priority)
//              .order("#{::Type.table_name}.position, #{WorkPackage.table_name}.id")
  }

   void new_() {
//    this->version = this->project.versions.build
  }

   void create() {
//    attributes = permitted_params
//                 .version
//                 .merge(project_id: this->project.id)

//    call = Versions::CreateService
//           .new(user: current_user)
//           .call(attributes)

//    this->version = call.result

//    if ( call.success?) {
//      flash[:notice] = l(:notice_successful_create)
//      redirect_back_or_version_settings
//    else
//      render action: 'new'
//    }
  }

   void edit() {}

   void update() {
//    attributes = permitted_params
//                 .version

//    call = Versions::UpdateService
//           .new(user: current_user,
//                model: this->version)
//           .call(attributes)

//    if ( call.success?) {
//      flash[:notice] = l(:notice_successful_update)
//      redirect_back_or_version_settings
//    else
//      render action: 'edit'
//    }
  }

   void close_completed() {
//    if ( request.put?) {
//      this->project.close_completed_versions
//    }
//    redirect_to settings_project_path(tab: 'versions', id: this->project)
  }

   void destroy() {
//    call = Versions::DeleteService
//           .new(user: current_user,
//                model: this->version)
//           .call

//    unless call.success?
//      flash[:error] = call.errors.full_messages
//    }

//    redirect_to settings_project_path(tab: 'versions', id: this->project)
  }

  private:

   void redirect_back_or_version_settings() {
//    redirect_back_or_default(settings_project_path(tab: 'versions', id: this->project))
  }

   void find_project() {
//    this->project = Project.find(params[:project_id])
//  rescue ActiveRecord::RecordNotFound
//    render_404
  }

//   void retrieve_selected_type_ids(selectable_types, default_types = nil) {
//    this->selected_type_ids = selected_type_ids selectable_types, default_types
//  }

//   void selected_type_ids(selectable_types, default_types = nil) {
//    if ( (ids = params[:type_ids])) {
//      ids.is_a?(Array) ? ids.map(&:to_s) : ids.split('/')
//    else
//      (default_types || selectable_types).map { |t| t.id.to_s }
//    }
//  }
};
