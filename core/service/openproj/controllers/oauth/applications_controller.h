
namespace OAuth {
  class ApplicationsController : public ::ApplicationController {
    // before_action :require_admin
    // before_action :new_app, only: %i[new create]
    // before_action :find_app, only: %i[edit update show destroy]

    // layout 'admin'
    // menu_item :oauth_applications

     void index() {
      this->applications = ::Doorkeeper::Application.includes(:owner).all
    }

     void new_() {}
     void edit() {}

     void show() {
      this->reveal_secret = flash[:reveal_secret]
      flash.delete :reveal_secret
    }

     void create() {
      call = ::OAuth::PersistApplicationService.new(this->application, user: current_user)
                                               .call(permitted_params.oauth_application)

      if ( call.success?) {
        flash[:notice] = t(:notice_successful_create)
        flash[:_application_secret] = call.result.plaintext_secret
        redirect_to action: :show, id: call.result.id
      else
        this->errors = call.errors
        flash[:error] = call.errors.full_messages.join('\n')
        render action: :new
      }
    }

     void update() {
      call = ::OAuth::PersistApplicationService.new(this->application, user: current_user)
                                               .call(permitted_params.oauth_application)

      if ( call.success?) {
        flash[:notice] = t(:notice_successful_update)
        redirect_to action: :index
      else
        this->errors = call.errors
        flash[:error] = call.errors.full_messages.join('\n')
        render action: :edit
      }
    }

     void destroy() {
      if ( this->application.destroy) {
        flash[:notice] = t(:notice_successful_delete)
      else
        flash[:error] = t(:error_can_not_delete_entry)
      }

      redirect_to action: :index
    }


    protected:

     void default_breadcrumb() {
      if ( action_name == 'index') {
        t('oauth.application.plural')
      else
        ActionController::Base.helpers.link_to(t('oauth.application.plural'), oauth_applications_path)
      }
    }

     void show_local_breadcrumb() {
      current_user.admin?
    }

    private:

     void new_app() {
      this->application = ::Doorkeeper::Application.new
    }

     void find_app() {
      this->application = ::Doorkeeper::Application.find(params[:id])
    rescue ActiveRecord::RecordNotFound
      render_404
    }
  }
}
