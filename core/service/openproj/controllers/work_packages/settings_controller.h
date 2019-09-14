#pragma once
#include "../application_controller.h"
namespace WorkPackages {

class SettingsController : public ApplicationController {
  // layout 'admin'
//  current_menu_item :index {
//    :work_packages_setting
//  }

   void index() {
//    render 'work_packages/settings/work_package_tracking'
  }

   void edit() {
//    if ( params[:settings]) {
//      Settings::UpdateService
//        .new(user: current_user)
//        .call(settings: permitted_params.settings.to_h)

//      flash[:notice] = l(:notice_successful_update)
//      redirect_to action: 'index'
//    }
  }

   void default_breadcrumb() {
//    t(:label_work_package_tracking)
  }

  bool show_local_breadcrumb() {
    return true;
  }
};
}
