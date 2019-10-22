#pragma once
#include "../../services/base_services/set_attributes.h"
namespace openproj {
namespace service {
namespace TimeEntries {
  class SetAttributesService : public BaseServices::SetAttributes {
    private:

//     void set_attributes(attributes) {
//      super

//      //
//      // Update project context if ( moving time entry) {
//      if ( no_project_or_context_changed?) {
//        model.project = model.work_package&.project
//      }

//      use_project_activity(model)
//    }

//     void set_default_attributes() {
//      set_default_user
//      set_default_activity
//      set_default_hours
//    }

//     void set_default_user() {
//      model.user ||= user
//    }

//     void set_default_activity() {
//      model.activity ||= TimeEntryActivity.default
//    }

//     void set_default_hours() {
//      if ( model.hours&.zero?) { model.hours = nil ;}
//    }

//     void use_project_activity(time_entry) {
//      if ( time_entry.activity&.shared? && time_entry.project) {
//        project_activity = time_entry.project.time_entry_activities.find_by(parent_id: time_entry.activity_id) ||
//                           time_entry.activity

//        time_entry.activity = project_activity
//      }
//    }

//     void no_project_or_context_changed?() {
//      !model.project ||
//        (model.work_package && model.work_package_id_changed? && !model.project_id_changed?)
//    }
  };
}
}
}
