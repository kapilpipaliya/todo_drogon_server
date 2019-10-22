#pragma once
#include "application_controller.h"
namespace openproj {
namespace controller {
class ColorsController : public ApplicationController {
public:
  // before_action :require_admin_unless_readonly_api_request

  // layout "admin"

  // menu_item :colors

   void index() {
//    this->colors = Color.all
//    respond_to { |format|
//      format.html
//    }
  }

   void show() {
//    this->color = Color.find(params[:id])
//    respond_to { |_format|
//    }
  }

   void new_() {
//    this->color = Color.new
//    respond_to { |format|
//      format.html
//    }
  }

   void create() {
//    this->color = Color.new(permitted_params.color)

//    if ( this->color.save) {
//      flash[:notice] = l(:notice_successful_create)
//      redirect_to colors_path
//    else
//      flash.now[:error] = l("timelines.color_could_not_be_saved")
//      render action: "new"
//    }
  }

   void edit() {
//    this->color = Color.find(params[:id])
//    respond_to { |format|
//      format.html
//    }
  }

   void update() {
//    this->color = Color.find(params[:id])

//    if ( this->color.update_attributes(permitted_params.color)) {
//      flash[:notice] = l(:notice_successful_update)
//      redirect_to colors_path
//    else
//      flash.now[:error] = l("timelines.color_could_not_be_saved")
//      render action: "edit"
//    }
  }

   void confirm_destroy() {
//    this->color = Color.find(params[:id])
//    respond_to { |format|
//      format.html
//    }
  }

   void destroy() {
//    this->color = Color.find(params[:id])
//    this->color.destroy

//    flash[:notice] = l(:notice_successful_delete)
//    redirect_to colors_path
  }

  protected:

   void default_breadcrumb() {
//    if ( action_name == "index") {
//      t("timelines.admin_menu.colors")
//    else
//      ActionController::Base.helpers.link_to(t("timelines.admin_menu.colors"), colors_path)
//    }
  }

   bool show_local_breadcrumb() {
    return true;
  }

   void require_admin_unless_readonly_api_request() {
//    require_admin unless %w[index show].include? params[:action] and
//                         api_request?
  }
};
}
}
