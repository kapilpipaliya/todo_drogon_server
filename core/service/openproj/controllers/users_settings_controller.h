#pragma once
#include "application_controller.h"
namespace openproj {
namespace controller {
class UsersSettingsController : public ApplicationController {
  // layout 'admin'
  // menu_item :user_settings
public:
   void index() {
//    render 'users/users_settings'
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
//    t(:label_user_settings)
  }

   bool show_local_breadcrumb() {
    return true;
  }
};
}
}
