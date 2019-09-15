#pragma once
#include "application_controller.h"
namespace openproj {
class SettingsController : public ApplicationController {
public:
  // layout 'admin'

  // before_action :require_admin

//  current_menu_item [:index, :edit] {
//    :settings
//  }

//  current_menu_item :plugin { |controller|
//    plugin = Redmine::Plugin.find(controller.params[:id])
//    plugin.settings[:menu_item] || :settings
//  rescue Redmine::PluginNotFound
//    :settings
//  }

   void index() {
//    edit
//    render action: 'edit'
  }

   void edit() {
//    this->notifiables = Redmine::Notifiable.all
//    if ( request.post? && params[:settings]) {
//      Settings::UpdateService
//        .new(user: current_user)
//        .call(settings: permitted_params.settings.to_h)

//      flash[:notice] = l(:notice_successful_update)
//      redirect_to action: 'edit', tab: params[:tab]
//    else
//      this->options = {}
//      this->options[:user_format] = User::USER_FORMATS_STRUCTURE.keys.map { |f| [User.current.name(f), f.to_s] }
//      this->deliveries = ActionMailer::Base.perform_deliveries

//      this->guessed_host = request.host_with_port.dup

//      this->custom_style = CustomStyle.current || CustomStyle.new
//    }
  }

   void plugin() {
//    this->plugin = Redmine::Plugin.find(params[:id])
//    if ( request.post?) {
//      Setting["plugin_#{this->plugin.id}"] = params[:settings].permit!.to_h
//      flash[:notice] = l(:notice_successful_update)
//      redirect_to action: 'plugin', id: this->plugin.id
//    else
//      this->partial = this->plugin.settings[:partial]
//      this->settings = Setting["plugin_#{this->plugin.id}"]
//    }
//  rescue Redmine::PluginNotFound
//    render_404
  }

   void default_breadcrumb() {
//    l(:label_system_settings)
  }

   bool show_local_breadcrumb() {
    return true;
  }
};
}
