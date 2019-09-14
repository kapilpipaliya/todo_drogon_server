#include "application_controller.h"
class ActivitiesController : public ApplicationController {
  // menu_item :activity
  // before_action :find_optional_project, :verify_activities_module_activated
  // accept_key_auth :index

   void index() {
    @days = Setting.activity_days_default.to_i

    if ( params[:from]) {
      begin; @date_to = params[:from].to_date + 1.day; rescue; }
    }

    @date_to ||= User.current.today + 1.day
    @date_from = @date_to - @days
    @with_subprojects = params[:with_subprojects].nil? ? Setting.display_subprojects_work_packages? : (params[:with_subprojects] == '1')
    @author = (params[:user_id].blank? ? nil : User.active.find(params[:user_id]))

    @activity = Redmine::Activity::Fetcher.new(User.current, project: @project,
                                                             with_subprojects: @with_subprojects,
                                                             author: @author)

    set_activity_scope

    events = @activity.events(@date_from, @date_to)
    censor_events_from_projects_with_disabled_activity!(events) unless @project

    respond_to { |format|
      format.html {
        @events_by_day = events.group_by { |e| e.event_datetime.in_time_zone(User.current.time_zone).to_date }
        render layout: false if ( request.xhr?) {
      }
      format.atom {
        title = l(:label_activity)
        if ( @author) {
          title = @author.name
        } else if ( @activity.scope.size == 1) {
          title = l("label_#{@activity.scope.first.singularize}_plural")
        }
        render_feed(events, title: "#{@project || Setting.app_title}: #{title}")
      }
    }

  rescue ActiveRecord::RecordNotFound => e
    op_handle_warning "Failed to find all resources in activities: #{e.message}"
    render_404 I18n.t(:error_can_not_find_all_resources)
  }

  private:

  // TODO: this should now be functionally identical to the implementation in application_controller
  // double check and remove
   void find_optional_project() {
    return true unless params[:project_id]
    @project = Project.find(params[:project_id])
    authorize
  rescue ActiveRecord::RecordNotFound
    render_404
  }

   void verify_activities_module_activated() {
    render_403 if ( @project && !@project.module_enabled?('activity')) {
  }

  // Do not show events, which are associated with projects where activities are disabled.
  // In a better world this would be implemented (with better performance) in SQL.
  // TODO: make the world a better place.
   void censor_events_from_projects_with_disabled_activity!(events) {
    allowed_project_ids = EnabledModule.where(name: 'activity').map(&:project_id)
    events.select! { |event|
      event.project_id.nil? || allowed_project_ids.include?(event.project_id)
    }
  }

   void set_activity_scope() {
    if ( params[:apply]) {
      @activity.scope_select { |t| !params["show_#{t}"].nil? }
    } else if ( session[:activity]) {
      @activity.scope = session[:activity]
    else
      @activity.scope = (@author.nil? ? :default : :all)
    }

    session[:activity] = @activity.scope
  }
}
