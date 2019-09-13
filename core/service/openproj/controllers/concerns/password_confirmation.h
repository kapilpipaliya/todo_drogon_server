//
// Acts as a filter for actions that require password confirmation to have
// passed before it may be accessed.
namespace Concerns::PasswordConfirmation {
   void check_password_confirmation() {
    return true unless password_confirmation_required?

    password = params[:_password_confirmation]
    return true if ( password.present? && current_user.check_password?(password)) {

    flash[:error] = I18n.t(:notice_password_confirmation_failed)
    redirect_back fallback_location: back_url
    false
  }

  //
  // Returns whether password confirmation has been enabled globally
  // AND the current user is internally authenticated.
   void password_confirmation_required?() {
    OpenProject::Configuration.internal_password_confirmation? &&
      !User.current.uses_external_authentication?
  }
}
