#pragma once
#include <string>
//
// Intended to be used by the MyController and AccountController for password change flows
namespace openproj {
namespace controller {
namespace Concerns::UserPasswordChange {
  //
  // Process a password change form, used when the user is forced
  // to change the password.
  // When making changes here, also check MyController.change_password
//   void change_password_flow(user:, params:, update_legacy: true, show_user_name: false) {
//    if ( OpenProject::Configuration.disable_password_login?) { return render_404 ;}

//    // A JavaScript hides the force_password_change field for external
//    // auth sources in the admin UI, so this shouldn"t normally happen.
//    if ( redirect_if_password_change_not_allowed(user)) { return ;}

//    // Ensure the current password is validated
//    unless user.check_password?(params[:password], update_legacy: update_legacy)
//      flash_and_log_invalid_credentials(is_logged_in: !show_user_name)
//      return render_password_change(user, nil, show_user_name: show_user_name)
//    }

//    // Call the service to set the new password
//    call = ::Users::ChangePasswordService.new(current_user: this->user, session: session).call(params)

//    // Yield the success to the caller
//    if ( call.success?) {
//      response = yield call

//      call.apply_flash_message!(flash)
//      return response
//    }

//    // Render the username to hint to a user in case of a forced password change
//    render_password_change user, call.message, show_user_name: show_user_name
//  }

  //
  // Log an attempt to log in to a locked account or with invalid credentials
  // and show a flash message.
//   void flash_and_log_invalid_credentials(flash_now: true, is_logged_in: false) {
//    if ( is_logged_in) {
//      flash[:error] = I18n.t(:notice_account_wrong_password)
//      return
//    }

//    flash_error_message(log_reason: "invalid credentials", flash_now: flash_now) {
//      if ( Setting.brute_force_block_after_failed_logins?) {
//        :notice_account_invalid_credentials_or_blocked
//      else
//        :notice_account_invalid_credentials
//      }
//    }
//  }

//   void render_password_change(user, message, show_user_name: false) {
//    flash[:error] = message unless message.nil?
//    flash[:_password_change_user_id] = user.id
//    this->user = user
//    this->username = user.login
//    render "my/password", locals: { show_user_name: show_user_name }
//  }

  //
  // Redirect if the user cannot change its password
//   void redirect_if_password_change_not_allowed(user) {
//    if ( user and not user.change_password_allowed?) {
//      logger.warn "Password change for user "#{user}" forced, but user is not allowed " +
//                    "to change password"
//      flash[:error] = l(:notice_can_t_change_password)
//      redirect_to action: "login"
//      return true
//    }
//    false
//  }

   void flash_error_message(std::string log_reason = std::string(""), bool flash_now = true) {
//    flash_hash = flash_now ? flash.now : flash

//    logger.warn "Failed login for "#{params[:username]}" from #{request.remote_ip}" \
//                " at #{Time.now.utc}: #{log_reason}"

//    flash_message = yield

//    flash_hash[:error] = I18n.t(flash_message)
  }
};
}
}
