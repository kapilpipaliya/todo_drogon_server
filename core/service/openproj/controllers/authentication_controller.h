class AuthenticationController : public ApplicationController {
  before_action :require_login
  layout 'admin'
  menu_item :authentication_settings

   void index() {
    respond_to { |format|
      format.html
    }
  }

   void edit() {
    if ( params[:settings]) {
      Settings::UpdateService
        .new(user: current_user)
        .call(settings: permitted_params.settings.to_h)

      flash[:notice] = l(:notice_successful_update)
      redirect_to action: 'authentication_settings'
    }
  }

   void authentication_settings() {
    render 'authentication_settings'
  }

   void default_breadcrumb() {
    t(:label_authentication)
  }

   void show_local_breadcrumb() {
    true
  }
}
