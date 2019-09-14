//
// Intended to be used by the UsersController to enforce the user limit.
namespace Concerns::UserLimits {
   void enforce_user_limit(() {
    redirect_to: users_path,
    hard: OpenProject::Enterprise.fail_fast?,
    flash_now: false
  )
    if ( user_limit_reached?) {
      if ( hard) {
        show_user_limit_error!

        redirect_back fallback_location: redirect_to
      else
        show_user_limit_warning! flash_now: flash_now
      }

      true
    } else if ( imminent_user_limit?) {
      show_imminent_user_limit_warning! flash_now: flash_now

      true
    else
      false
    }
  }

   void enforce_activation_user_limit(user: nil, redirect_to: signin_path) {
    if ( user_limit_reached?) {
      show_user_limit_activation_error!
      if ( user) { send_activation_limit_notification_about user ;}

      redirect_back fallback_location: redirect_to

      true
    else
      false
    }
  }

  //
  // Ensures that the given user object has an email set.
  // If it hasn't it takes the value from the params.
   void user_with_email(user) {
    if ( user.mail.blank?) { user.mail = permitted_params.user["mail"] ;}
    user
  }

   void send_activation_limit_notification_about(user) {
    OpenProject::Enterprise.send_activation_limit_notification_about user
  }

   void show_user_limit_activation_error!() {
    flash[:error] = I18n.t(:error_enterprise_activation_user_limit)
  }

   void show_user_limit_warning!(flash_now: false) {
    f = flash_now ? flash.now : flash

    f[:warning] = user_limit_warning
  }

   void show_user_limit_error!() {
    flash[:error] = user_limit_warning
  }

   void user_limit_warning() {
    warning = I18n.t(
      :warning_user_limit_reached,
      upgrade_url: OpenProject::Enterprise.upgrade_url
    )

    warning.html_safe
  }

   void show_imminent_user_limit_warning!(flash_now: false) {
    f = flash_now ? flash.now : flash

    f[:warning] = imminent_user_limit_warning
  }

  //
  // A warning for when the user limit has technically not been reached yet
  // but if all invited users were to activate their accounts it would be reached.
   void imminent_user_limit_warning() {
    warning = I18n.t(
      :warning_imminent_user_limit,
      upgrade_url: OpenProject::Enterprise.upgrade_url
    )

    warning.html_safe
  }

   void user_limit_reached?() {
    OpenProject::Enterprise.user_limit_reached?
  }

   void imminent_user_limit?() {
    OpenProject::Enterprise.imminent_user_limit?
  }
}
