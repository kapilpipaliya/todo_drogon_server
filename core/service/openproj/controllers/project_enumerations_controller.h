#pragma once
#include "application_controller.h"
class ProjectEnumerationsController : public ApplicationController {
  // before_action :find_project_by_project_id
  // before_action :authorize
public:
   void update() {
//    if ( permitted_params.enumerations.present?) {
//      Project.transaction {
//        permitted_params.enumerations.each { |id, activity|
//          this->project.update_or_create_time_entry_activity(id, activity)
//        }
//      }
//      flash[:notice] = l(:notice_successful_update)
//    }

//    redirect_to settings_project_path(id: this->project, tab: 'activities')
  }

   void destroy() {
//    TimeEntryActivity.bulk_destroy(this->project.time_entry_activities)

//    flash[:notice] = l(:notice_successful_update)

//    redirect_to settings_project_path(id: this->project, tab: 'activities')
  }
};
