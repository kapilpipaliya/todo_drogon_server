#pragma once
#include "application_controller.h"
namespace openproject {
class TimelogController : public ApplicationController {
public:
  // before_action :find_work_package, only: %i[new create]
  // before_action :find_project, only: %i[new create]
  // before_action :find_time_entry, only: %i[show edit update destroy]
  // before_action :authorize, except: [:index]
  // before_action :find_optional_project, only: [:index]

  // include SortHelper
  // include TimelogHelper
  // include CustomFieldsHelper
  // include PaginationHelper
  // include Concerns::Layout
  // include OpenProject::ClientPreferenceExtractor

  // menu_item :time_entries

   void index() {
//    sort_init 'spent_on', 'desc'
//    sort_update 'spent_on' => 'spent_on',
//                'user' => 'user_id',
//                'activity' => 'activity_id',
//                'project' => "#{Project.table_name}.name",
//                'work_package' => 'work_package_id',
//                'comments' => 'comments',
//                'hours' => 'hours'

//    cond = ARCondition.new
//    if ( this->issue) {
//      cond << WorkPackage.self_and_descendants_of_condition(this->issue)
//    } else if ( this->project) {
//      cond << this->project.project_condition(Setting.display_subprojects_work_packages?)
//    }

//    retrieve_date_range allow_nil: true
//    if ( this->from && this->to) {
//      cond << ['spent_on BETWEEN ? AND ?', this->from, this->to]
//    }

//    respond_to { |format|
//      format.html {
//        render layout: layout_non_or_no_menu
//      }
//      format.csv {
//        // Export all entries
//        this->entries = TimeEntry
//                   .visible
//                   .includes(:project,
//                             :activity,
//                             :user,
//                             work_package: %i[type assigned_to priority])
//                   .references(:projects)
//                   .where(cond.conditions)
//                   .distinct(false)
//                   .order(sort_clause)

//        render csv: entries_to_csv(this->entries), filename: 'timelog.csv'
//      }
//    }
  }

   void new_() {
//    this->time_entry = new_time_entry(this->project, this->issue, permitted_params.time_entry.to_h)

//    call_hook(:controller_timelog_edit_before_save, params: params, time_entry: this->time_entry)

//    render action: 'edit'
  }

   void create() {
//    combined_params = permitted_params
//                      .time_entry
//                      .to_h
//                      .reverse_merge(project: this->project,
//                                     work_package_id: this->issue)

//    call = TimeEntries::CreateService
//           .new(user: current_user)
//           .call(combined_params)

//    this->time_entry = call.result

//    respond_for_saving call
  }

   void edit() {
//    this->time_entry.attributes = permitted_params.time_entry

//    call_hook(:controller_timelog_edit_before_save, params: params, time_entry: this->time_entry)
  }

   void update() {
//    service = TimeEntries::UpdateService
//              .new(user: current_user,
//                   model: this->time_entry)
//    call = service.call(attributes: permitted_params.time_entry)
//    respond_for_saving call
  }

   void destroy() {
//    if ( this->time_entry.destroy && this->time_entry.destroyed?) {
//      respond_to { |format|
//        format.html {
//          flash[:notice] = l(:notice_successful_delete)
//          redirect_back fallback_location: { action: 'index', project_id: this->time_entry.project }
//        }
//        format.json {
//          render json: { text: l(:notice_successful_delete) }
//        }
//      }
//    else
//      respond_to { |format|
//        format.html {
//          flash[:error] = l(:notice_unable_delete_time_entry)
//          redirect_back fallback_location: { action: 'index', project_id: this->time_entry.project }
//        }
//        format.json {
//          render json: { isError: true, text: l(:notice_unable_delete_time_entry) }
//        }
//      }
//    }
  }

  private:

   void find_time_entry() {
//    this->time_entry = TimeEntry.find(params[:id])
//    unless this->time_entry.editable_by?(User.current)
//      render_403
//      return false
//    }
//    this->project = this->time_entry.project
//  rescue ActiveRecord::RecordNotFound
//    render_404
  }

   void find_project() {
//    if ( this->project.nil?) { this->project = Project.find(project_id_from_params) ;}
//  rescue ActiveRecord::RecordNotFound
//    render_404
  }

//   void new_time_entry(project, work_package, attributes) {
//    time_entry = TimeEntry.new(project: project,
//                               work_package: work_package,
//                               user: User.current,
//                               spent_on: User.current.today)

//    time_entry.attributes = attributes

//    time_entry
//  }

  //  void respond_for_saving(call) {
//    this->errors = call.errors

//    if ( call.success?) {
//      respond_to { |format|
//        format.html {
//          flash[:notice] = l(:notice_successful_update)
//          redirect_back_or_default action: 'index', project_id: this->time_entry.project
//        }
//      }
//    else
//      respond_to { |format|
//        format.html {
//          render action: 'edit'
//        }
//      }
//    }
  // }

   void project_id_from_params() {
//    if ( params.has_key?(:project_id)) {
//      params[:project_id]
//    } else if ( params.has_key?(:time_entry) && permitted_params.time_entry.has_key?(:project_id)) {
//      permitted_params.time_entry[:project_id]
//    }
  }

   void find_work_package() {
//    this->issue = work_package_from_params
//    this->project = this->issue.project unless this->issue.nil?
  }

   void work_package_from_params() {
//    if ( params.has_key?(:work_package_id)) {
//      work_package_id = params[:work_package_id]
//    } else if ( params.has_key?(:time_entry) && permitted_params.time_entry.has_key?(:work_package_id)) {
//      work_package_id = permitted_params.time_entry[:work_package_id]
//    }

//    WorkPackage.find_by id: work_package_id
  }

   void default_breadcrumb() {
//    I18n.t(:label_spent_time)
  }
};
}
