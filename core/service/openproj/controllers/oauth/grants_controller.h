
namespace OAuth {
  class GrantsController : public ::ApplicationController {
    // before_action :require_login

    // layout 'my'
    // menu_item :access_token

     void index() {
      @applications = ::Doorkeeper::Application.authorized_for(current_user)
    }

     void revoke_application() {
      application = find_application
      if ( application.nil?) {
        render_404
        return
      }

      ::Doorkeeper::Application.revoke_tokens_and_grants_for(
        application.id,
        current_user
      )

      flash[:notice] = I18n.t('oauth.grants.successful_application_revocation', application_name: application.name)
      redirect_to controller: '/my', action: :access_token
    }

    private:

     void find_application() {
      ::Doorkeeper::Application
        .where(id: params[:application_id])
        .select(:name, :id)
        .take
    }
  }
}
