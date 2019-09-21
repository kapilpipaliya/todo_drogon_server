#pragma once
#include "application_controller.h"
namespace openproj {
namespace controller {
class CustomStylesController : public ApplicationController {
public:
  // layout "admin"
  // menu_item :custom_style

  // before_action :require_admin, except: [:logo_download, :favicon_download, :touch_icon_download]
  // before_action :require_ee_token, except: [:upsale, :logo_download, :favicon_download, :touch_icon_download]
  // skip_before_action :check_if_login_required, only: [:logo_download, :favicon_download, :touch_icon_download]

   void show() {
//    this->custom_style = CustomStyle.current || CustomStyle.new
  }

   void upsale() {}

   void create() {
//    this->custom_style = CustomStyle.create(custom_style_params)
//    if ( this->custom_style.valid?) {
//      redirect_to custom_style_path
//    else
//      flash[:error] = this->custom_style.errors.full_messages
//      render action: :show
//    }
  }

   void update() {
//    this->custom_style = CustomStyle.current
//    if ( this->custom_style.update_attributes(custom_style_params)) {
//      redirect_to custom_style_path
//    else
//      flash[:error] = this->custom_style.errors.full_messages
//      render action: :show
//    }
  }

   void logo_download() {
//    file_download(:logo_path)
  }

   void favicon_download() {
//    file_download(:favicon_path)
  }

   void touch_icon_download() {
//    file_download(:touch_icon_path)
  }

   void logo_delete() {
//    file_delete(:remove_logo!)
  }

   void favicon_delete() {
//    file_delete(:remove_favicon!)
  }

   void touch_icon_delete() {
//    file_delete(:remove_touch_icon!)
  }

   void update_colors() {
//    variable_params = params[:design_colors].first

//    variable_params.each { |param_variable, param_hexcode|
//      if ( design_color = DesignColor.find_by(variable: param_variable)) {
//        if ( param_hexcode.blank?) {
//          design_color.destroy
//        } else if ( design_color.hexcode != param_hexcode) {
//          design_color.hexcode = param_hexcode
//          design_color.save
//        }
//      else
//        // create that design_color
//        design_color = DesignColor.new variable: param_variable, hexcode: param_hexcode
//        design_color.save
//      }
//    }

//    redirect_to action: :show
  }

   bool show_local_breadcrumb() {
    return true;
  }

  private:

   void require_ee_token() {
//    unless EnterpriseToken.allows_to?(:define_custom_style)
//      redirect_to custom_style_upsale_path
//    }
  }

   void custom_style_params() {
//    params.require(:custom_style).permit(:logo, :remove_logo, :favicon, :remove_favicon, :touch_icon, :remove_touch_icon)
  }

//   void file_download(path_method) {
//    this->custom_style = CustomStyle.current
//    if ( this->custom_style && this->custom_style.send(path_method)) {
//      expires_in 1.years, public: true, must_revalidate: false
//      send_file(this->custom_style.send(path_method))
//    else
//      head :not_found
//    }
//  }

//   void file_delete(remove_method) {
//    this->custom_style = CustomStyle.current
//    if ( this->custom_style.nil?) {
//      return render_404
//    }

//    this->custom_style.send(remove_method)
//    this->custom_style.save
//    redirect_to custom_style_path
//  }
};
}
}
