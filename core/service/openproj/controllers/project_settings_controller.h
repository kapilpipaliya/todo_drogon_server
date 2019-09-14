#pragma once
#include "application_controller.h"
namespace openproject {
class ProjectSettingsController : public ApplicationController {
public:
  // menu_item :settings

  // before_action :find_project
  // before_action :authorize
  // before_action :check_valid_tab
  // before_action :get_tab_settings

   void show() {}

  private:

   void settings_info() {
//    this->altered_project = this->project
  }

   void settings_custom_fields() {
//    this->issue_custom_fields = WorkPackageCustomField.order("#{CustomField.table_name}.position")
  }

   void settings_repository() {
//    this->repository = this->project.repository || new_repository
  }

   void new_repository() {
//    return unless params[:scm_vendor]

//    service = Scm::RepositoryFactoryService.new(this->project, params)
//    if ( service.build_temporary) {
//      this->repository = service.repository
//    else
//      logger.error("Cannot create repository for #{params[:scm_vendor]}")
//      flash[:error] = service.build_error
//      nil
//    }
  }

   void settings_types() {
//    this->types = ::Type.all
  }

   void check_valid_tab() {
//    this->selected_tab =
//      if ( params[:tab]) {
//        helpers.project_settings_tabs.detect { |t| t[:name] == params[:tab] }
//      } else {
//        helpers.project_settings_tabs.first
//      }

//    unless this->selected_tab {
//      render_404
//    }
  }

  //
  // Only load the needed elements for the current tab
   void get_tab_settings() {
//    callback = "settings_#{this->selected_tab[:name]}"
//    if ( respond_to?(callback, true)) {
//      send(callback)
//    }
  }

   void find_project() {
//    this->project = Project.find(params[:id])
//  rescue ActiveRecord::RecordNotFound
//    render_404
  }
};
}
