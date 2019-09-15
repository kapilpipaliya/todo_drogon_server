#pragma once
#include "application_controller.h"
namespace openproj {
class EnterprisesController : public ApplicationController {
public:
  // layout 'admin'
  // menu_item :enterprise

  // before_action :require_admin
  // before_action :check_user_limit, only: [:show]

   void show() {
//    this->current_token = EnterpriseToken.current
//    this->token = this->current_token || EnterpriseToken.new
  }

   void create() {
//    this->token = EnterpriseToken.current || EnterpriseToken.new
//    this->token.encoded_token = params[:enterprise_token][:encoded_token]

//    if ( this->token.save) {
//      flash[:notice] = t(:notice_successful_update)
//      redirect_to action: :show
//    else
//      render action: :show
//    }
  }

   void destroy() {
//    token = EnterpriseToken.current
//    if ( token) {
//      token.destroy
//      flash[:notice] = t(:notice_successful_delete)
//      redirect_to action: :show
//    else
//      render_404
//    }
  }

  private:

   void default_breadcrumb() {
//    t(:label_enterprise)
  }

   bool show_local_breadcrumb() {
    return true;
  }

   void check_user_limit() {
//    if ( OpenProject::Enterprise.user_limit_reached?) {
//      flash.now[:warning] = I18n.t(
//        "warning_user_limit_reached_instructions",
//        current: OpenProject::Enterprise.active_user_count,
//        max: OpenProject::Enterprise.user_limit
//      )
//    }
  }
};
}
