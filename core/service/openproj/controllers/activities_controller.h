#include "application_controller.h"
class ActivitiesController : public ApplicationController {
public:
  // menu_item :activity
  // before_action :find_optional_project, :verify_activities_module_activated
  // accept_key_auth :index

   void index() {
//    this->days = Setting.activity_days_default.to_i;

//    if ( params[:from]) {
//      begin; this->date_to = params[:from].to_date + 1.day; rescue; }
//    }

//    this->date_to ||= User.current.today + 1.day
//    this->date_from = this->date_to - this->days
//    this->with_subprojects = params[:with_subprojects].nil? ? Setting.display_subprojects_work_packages? : (params[:with_subprojects] == '1')
//    this->author = (params[:user_id].blank? ? nil : User.active.find(params[:user_id]))

//    this->activity = Redmine::Activity::Fetcher.new(User.current, project: this->project,
//                                                             with_subprojects: this->with_subprojects,
//                                                             author: this->author)

//    set_activity_scope

//    events = this->activity.events(this->date_from, this->date_to)
//    censor_events_from_projects_with_disabled_activity!(events) unless this->project

//    respond_to { |format|
//      format.html {
//        this->events_by_day = events.group_by { |e| e.event_datetime.in_time_zone(User.current.time_zone).to_date }
//        render layout: false if ( request.xhr?) {
//      }
//      format.atom {
//        title = l(:label_activity)
//        if ( this->author) {
//          title = this->author.name
//        } else if ( this->activity.scope.size == 1) {
//          title = l("label_#{this->activity.scope.first.singularize}_plural")
//        }
//        render_feed(events, title: "#{this->project || Setting.app_title}: #{title}")
//      }
//    }

//  rescue ActiveRecord::RecordNotFound => e
//    op_handle_warning "Failed to find all resources in activities: #{e.message}"
//    render_404 I18n.t(:error_can_not_find_all_resources)
  }

  private:

  // TODO: this should now be functionally identical to the implementation in application_controller
  // double check and remove
   void find_optional_project() {
//    return true unless params[:project_id]
//    this->project = Project.find(params[:project_id])
//    authorize
//  rescue ActiveRecord::RecordNotFound
//    render_404
  }

   void verify_activities_module_activated() {
//    if ( this->project && !this->project.module_enabled?('activity')) { render_403 ;}
  }

  // Do not show events, which are associated with projects where activities are disabled.
  // In a better world this would be implemented (with better performance) in SQL.
  // TODO: make the world a better place.
//   void censor_events_from_projects_with_disabled_activity!(events) {
//    allowed_project_ids = EnabledModule.where(name: 'activity').map(&:project_id)
//    events.select! { |event|
//      event.project_id.nil? || allowed_project_ids.include?(event.project_id)
//    }
//  }

   void set_activity_scope() {
//    if ( params[:apply]) {
//      this->activity.scope_select { |t| !params["show_#{t}"].nil? }
//    } else if ( session[:activity]) {
//      this->activity.scope = session[:activity]
//    else
//      this->activity.scope = (this->author.nil? ? :default : :all)
//    }

//    session[:activity] = this->activity.scope
  }
};
