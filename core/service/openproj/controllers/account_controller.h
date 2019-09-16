#pragma once
#include "application_controller.h"
namespace openproj {
namespace controller {
class AccountController : public ApplicationController {
public:
  // include CustomFieldsHelper
  // include OmniauthHelper
  // include Concerns::OmniauthLogin
  // include Concerns::RedirectAfterLogin
  // include Concerns::AuthenticationStages
  // include Concerns::UserConsent
  // include Concerns::UserLimits
  // include Concerns::UserPasswordChange

  // prevents login action to be filtered by check_if_login_required application scope filter
  // skip_before_action :check_if_login_required

  // before_action :disable_api
  // before_action :check_auth_source_sso_failure, only: :auth_source_sso_failed

  // layout 'no_menu'

  // Login request and validation
  void login() {
//    user = User.current;

//    if ( user.logged?) {
//      redirect_after_login(user);
//    } else if ( omniauth_direct_login?) {
//      direct_login(user);
//    } else if ( request.post?) {
//      authenticate_user();
//    }
  }

  // Log out current user and redirect to welcome page
  void logout() {
//    logout_user();
//    if ( Setting.login_required? && omniauth_direct_login?) {
//      flash.now[:notice] = I18n.t : notice_logged_out render : exit, locals : {
//      instructions: :after_logout
//      }
//      else redirect_to home_url
//    }
  }

  // Enable user to choose a new password
  void lost_password() {
//    return redirect_to(home_url) unless allow_lost_password_recovery ?

//                                                                     if (params[:token]) {
//      this->token = ::Token::Recovery
//                   .find_by_plaintext_value(params[:token]) redirect_to(home_url)&& return unless
//               this->token and !this->token.expired
//          ? this->user = this->token.user if (request.post ?) {
//        call = ::Users::ChangePasswordService.new(current_user: this->user, session: session).call(params)
//        call.apply_flash_message!(flash)

//        if ( call.success?) {
//          this->token.destroy redirect_to action : 'login' return
//        }
//      }

//      render template : 'account/password_recovery'
//    } else if ( request.post?) {
//      mail = params[:mail]
//      user = User.find_by_mail(mail) if ( mail.present?) {

//      // Ensure the same request is sent regardless of which email is entered
//      // to avoid detecability of mails
//      flash[:notice] = l(:notice_account_lost_email_sent)

//      unless user
//        // user not found in db
//        Rails.logger.error "Lost password unknown email input: #{mail}"
//        return
//      }

//      unless user.change_password_allowed?
//        // user uses an external authentification
//        Rails.logger.error "Password cannot be changed for user: #{mail}"
//        return
//    }

//    // create a new token for password recovery
//    token = Token::Recovery.new(user_id : user.id) if (token.save) {
//      UserMailer.password_lost(token)
//          .deliver_now flash[:notice] = l(
//                                          : notice_account_lost_email_sent) redirect_to action
//          : 'login',
//                       back_url : home_url return
//    }
//  }
}

// User self-registration
void register_() {
//  return self_registration_disabled unless allow_registration ?

//                                                              this->user = invited_user

//                                                              if (request.get ?) {
//      registration_through_invitation!
//    else
//      if ( Setting.email_login?) {
//        params[:user][:login] = params[:user][:mail]
//      }

//      self_registration!
//  }
}

bool allow_registration () {
//  allow = Setting.self_registration ? && !OpenProject::Configuration.disable_password_login
//      ?

//      invited = session[:invitation_token]
//      .present
//      ? get = request.get ? && allow post = (request.post ? || request.patch
//                                             ?) && (session[:auth_source_registration] || allow)

//                                                       invited ||
//                                             get || post
}

bool allow_lost_password_recovery () {
//  Setting.lost_password ? &&!OpenProject::Configuration.disable_password_login ?
}

// Token based account activation
void activate() {
//    token = ::Token::Invitation.find_by_plaintext_value(params[:token])

//    if ( token.nil? || token.user.nil?) {
//      invalid_token_and_redirect
//    } else if ( token.expired?) {
//      handle_expired_token token
//    } else if ( token.user.invited?) {
//      activate_by_invite_token token
//    } else if ( Setting.self_registration?) {
//      activate_self_registered token else invalid_token_and_redirect
//    }
}

//void handle_expired_token(token) {
//  send_activation_email !Token::Invitation.create !(user
//                                                    : token.user)

//      flash[:warning] = I18n.t : warning_registration_token_expired, email
//      : token.user.mail

//            redirect_to home_url
//}

//void activate_self_registered(token) {
//  return if (enforce_activation_user_limit(user : token.user)) {
//    user = token.user

//    if ( not user.registered?) {
//      if ( user.active?) {
//        flash[:notice] = I18n.t(
//                           : notice_account_already_activated) else flash
//        [:error] = I18n.t(
//                     : notice_activation_failed)
//      }

//      redirect_to home_url else user.activate

//          if (user.save){token.destroy flash[:notice] = I18n.t(
//                                                          : notice_account_activated) else flash
//                         [:error] = I18n.t(
//                                      : notice_activation_failed)}

//      redirect_to signin_path
//    }
//  }

//  void activate_by_invite_token(token) {
//    if (enforce_activation_user_limit(user : token.user)) { activate_invited token } return ;}

//    void activate_invited(token) {
//      session[:invitation_token] = token.value user =
//                                     token.user

//                                     if (user.auth_source &&
//                                         user.auth_source.auth_method_name == 'LDAP') {
//        activate_through_ldap user else activate_user user
//      }
//    }

//    void activate_user(user) {
//    if ( omniauth_direct_login?) {
//      direct_login user
//    } else if ( OpenProject::Configuration.disable_password_login?) {
//      flash[:notice] = I18n.t('account.omniauth_login')

//                           redirect_to signin_path else redirect_to account_register_path
//    }
//    }

//    void activate_through_ldap(user) {
//      session[:auth_source_registration] = {
//        login : user.login,
//        auth_source_id : user.auth_source_id
//      }

//                                         flash
//      [:notice] = I18n.t('account.auth_source_login', login
//                         : user.login)
//                      .html_safe

//                          redirect_to signin_path(username
//                                                  : user.login)
//    }

    // Process a password change form, used when the user is forced
    // to change the password.
    // When making changes here, also check MyController.change_password
    void change_password() {
//      // Retrieve user_id from session
//      this->user = User.find(flash[:_password_change_user_id])

//                  change_password_flow(user
//                                       : this->user, params
//                                       : params, show_user_name
//                                       : true) {
//        password_authentication(this->user.login, params[:new_password])
//      }
//      rescue ActiveRecord::RecordNotFound Rails.logger.error
//          "Failed to find user for change_password request: "
//          "#{flash[:_password_change_user_id]}" render_404
    }

    void auth_source_sso_failed() {
//    failure = session.delete :auth_source_sso_failure
//    user = failure[:user]

//    if ( user.try(:new_record?)) {
//      return onthefly_creation_failed user, login: user.login, auth_source_id: user.auth_source_id
//    }

//    show_sso_error_for user

//    flash.now[:error] = I18n.t(:error_auth_source_sso_failed, value: failure[:login]) +
//      ": " + String(flash.now[:error])

//    render action: 'login', back_url: failure[:back_url]
    }

   private:
    void check_auth_source_sso_failure() {
//      redirect_to home_url unless session[:auth_source_sso_failure].present ?
    }

//    void show_sso_error_for(user) {
//    if ( user.nil?) {
//      flash_and_log_invalid_credentials
//    } else if ( not user.active?) {
//      account_inactive user, flash_now : true
//    }
//    }

//    void registration_through_invitation !() {
//    session[:auth_source_registration] = nil

//    if ( this->user.nil?) {
//      this->user = User.new(language : Setting.default_language)
//    } else if ( user_with_placeholder_name?(this->user)) {
//      // force user to give their name
//      this->user.firstname = nil this->user.lastname = nil
//    }
//    }

    void self_registration() {
//    if ( this->user.nil?) {
//      this->user = User.new this->user.admin = false this->user.register
//    }

//    return if (enforce_activation_user_limit(user : user_with_email(this->user))) {
//      // Set consent if ( received from registration form) {
//    if ( consent_param?) {
//      this->user.consented_at = DateTime.now
//    }

//    if (session[:auth_source_registration]) {
//      // on-the-fly registration via omniauth or via auth source
//      if ( pending_omniauth_registration?) {
//        register_via_omniauth(
//            this->user, session,
//            permitted_params) else register_and_login_via_authsource(this->user, session,
//                                                                     permitted_params)
//      } else
//        this->user.attributes = permitted_params.user.transform_values { |val|
//        if ( val.is_a? String) {
//          val.strip!
//        }

//        val
//        }
//      this->user.login = params[:user][:login].strip if ( params[:user][:login].present?) {
//        this->user.password = params[:user][:password] this->user.password_confirmation = params[:user]
//        [:password_confirmation]

//            register_user_according_to_setting this->user
//      }
    }

//    void user_with_placeholder_name ? (user) {
//      user.firstname == user.login and user.login == user.mail
//    }

//    void direct_login(user) {
//    if ( flash.empty?) {
//      ps = {}.tap {
//        | p | p[:origin] = params[:back_url] if (params[:back_url]) {}

//        redirect_to direct_login_provider_url(ps)
//      } else if ( Setting.login_required?) {
//        error = user.active ? || flash[:error] instructions = error ?: after_error
//                                               : : after_registration

//                                                       render : exit,
//        locals : {
//        instructions:
//          instructions
//        }
//      }
//    }

    void logout_user() {
//    if ( User.current.logged?) {
//      cookies.delete OpenProject::Configuration['autologin_cookie_name'] Token::AutoLogin
//          .where(user_id
//                 : current_user.id)
//          .delete_all this->logged_user = nil
//    }
    }

    void authenticate_user() {
//    if ( OpenProject::Configuration.disable_password_login?) {
//      render_404 else password_authentication(params[:username], params[:password])
//    }
    }

    void password_authentication(std::string username, std::string password) {
//    user = User.try_to_login(username, password, session)
//    if ( user.nil?) {
//      // login failed, now try to find out why and { the appropriate thing
//      user = User.find_by_login(username)
//      if ( user and user.check_password?(password)) {
//        // correct password
//        if ( not user.active?) {
//          account_inactive(user, flash_now : true)
//        } else if (user.force_password_change) {
//          return if (redirect_if_password_change_not_allowed(user)) {
//            render_password_change(user,
//                                   I18n.t(
//                                       : notice_account_new_password_forced),
//                                   show_user_name
//                                   : true)
//          } else if ( user.password_expired?) {
//            return if (redirect_if_password_change_not_allowed(user)) {
//              render_password_change(user,
//                                     I18n.t(
//                                         : notice_account_password_expired, days
//                                         : Setting.password_days_valid.to_i),
//                                     show_user_name
//                                     : true) else flash_and_log_invalid_credentials
//            }
//          } else if ( user and user.invited?) {
//            invited_account_not_activated(user) else
//                // incorrect password
//                flash_and_log_invalid_credentials
//          }
//    } else if ( user.new_record?) {
//      onthefly_creation_failed(user, login
//                               : user.login, auth_source_id
//                               : user.auth_source_id) else
//          // Valid user
//          successful_authentication(user)
//    }
      }

//      void successful_authentication(user, reset_stages : true) {
//    stages = authentication_stages reset: reset_stages

//    if ( stages.empty?) {
//      // setting params back_url to be used by redirect_after_login
//      params[:back_url] = session.delete :back_url if ( session.include?(:back_url)) {
//        if (session[:finish_registration]) {
//          finish_registration !user else login_user !user
//        } else
//          stage = stages.first

//                      session[:authenticated_user_id] = user.id

//                                                            redirect_to stage.path
//      }
//    }

//    void login_user !(user) {
//      // Valid user
//    this->logged_user = user
//    // generate a key and set cookie if ( autologin) {
//    if ( params[:autologin] && Setting.autologin?) {
//      set_autologin_cookie(user)
//    }

//    call_hook(:controller_account_success_authentication_after, user: user)

//    redirect_after_login(user)
//    }

//    void set_autologin_cookie(user) {
//      token = Token::AutoLogin.create(user
//                                      : user) cookie_options = {
//        value : token.plain_value,
//        expires : 1.year.from_now,
//        path : OpenProject::Configuration['autologin_cookie_path'],
//        secure : OpenProject::Configuration['autologin_cookie_secure'],
//        httponly : true
//      } cookies[OpenProject::Configuration['autologin_cookie_name']] = cookie_options
//    }

//    void login_user_if_active(user) {
//    if ( user.active?) {
//      successful_authentication(user) else account_inactive(user, flash_now
//                                                            : false) redirect_to signin_path
//    }
//    }

//    void send_activation_email(token) {
//        UserMailer.user_signed_up(token).deliver_now
//    }

//    void pending_auth_source_registration ? () {
//      session[:auth_source_registration] && !pending_omniauth_registration ?
//    }

//    void pending_omniauth_registration ? () { Hash(session[:auth_source_registration]) [:omniauth] }

//    void register_and_login_via_authsource(_user, session, permitted_params) {
//      this->user.attributes = permitted_params.user this->user.activate this->user.login =
//          session[:auth_source_registration]
//      [:login] this->user.auth_source_id = session
//      [:auth_source_registration]
//      [:auth_source_id]

//          if (this->user.save) {
//        session[:auth_source_registration] = nil this->logged_user = this->user flash
//        [:notice] = I18n.t(
//                      : notice_account_activated) redirect_to controller : '/my',
//        action : 'account'
//      }
//      // Otherwise render register view again
//    }

    // Onthefly creation failed, display the registration form to fill/fix attributes
//    void onthefly_creation_failed(user, auth_source_options = {}) {
//      this->user = user session[:auth_source_registration] = auth_source_options unless
//                                                                auth_source_options.empty
//                                                            ? render action
//                                                            : 'register'
//    }

    // Register a user depending on Setting.self_registration
//    void register_user_according_to_setting(user, opts = {}, &block) {
//    if ( user.invited?) { return register_automatically(user, opts, &block) ;}
//    case Setting.self_registration
//    when '1'
//      register_by_email_activation(user, opts, &block)
//    when '3'
//      register_automatically(user, opts, &block)
//    else
//      register_manually_by_administrator(user, opts, &block)
//    }
//  }

  // Register a user for email activation.
  //
  // Pass a block for behavior when a user fails to save
//   void register_by_email_activation(user, _opts = {}) {
//    token = Token::Invitation.new(user: user)

//    if ( user.save and token.save) {
//        send_activation_email !token flash[:notice] = I18n.t(
//                                                        : notice_account_register_done)

//                                                          redirect_to action : 'login'
//      } else if ( block_given?) {
//        yield
//      }
//    }

    // Automatically register a user
    //
    // Pass a block for behavior when a user fails to save
//    void register_automatically(user, opts = {}) {
//    if ( user_limit_reached?) {
//      show_user_limit_activation_error !send_activation_limit_notification_about user

//          return redirect_back fallback_location : signin_path
//    }

//    // Automatic activation
//    user.activate

//        if (user.save) {
//      stages = authentication_stages after_activation : true

//                                                        run_registration_stages stages,
//      user, opts
//    } else if ( block_given?) {
//      yield
//    }
//    }

//    void run_registration_stages(stages, user, opts) {
//    if ( stages.empty?) {
//      finish_registration !user,
//          opts else stage = stages.first

//                                session[:authenticated_user_id] = user.id session
//      [:finish_registration] = opts

//                                   redirect_to stage.path
//    }
//    }

//    void finish_registration !(user, opts = Hash(session.delete( : finish_registration))) {
//      this->logged_user = user user.update last_login_on
//          : Time.now

//            if (auth_hash =
//                    opts[:omni_auth_hash]){OpenProject::OmniAuth::Authorization.after_login !user,
//                                           auth_hash, self}

//            flash[:notice] = I18n.t(
//                               : notice_account_registered_and_logged_in) redirect_after_login user
//    }

    // Manual activation by the administrator
    //
    // Pass a block for behavior when a user fails to save
//    void register_manually_by_administrator(user, _opts = {}) {
//      if (user.save) {
//        // Sends an email to the administrators
//        admins = User.admin.active admins.each{
//            | admin |
//            UserMailer.account_activation_requested(admin, user).deliver_now} account_pending
//    } else if ( block_given?) {
//      yield
//    }
//    }

    void self_registration_disabled() {
//      flash[:error] = I18n.t('account.error_self_registration_disabled') redirect_to signin_url
    }

    // Call if ( an account is inactive - either registered or locked) {
//    void account_inactive(user, flash_now : true) {
//    if ( user.registered?) {
//      account_not_activated(flash_now
//                            : flash_now) else flash_and_log_invalid_credentials(flash_now
//                                                                                : flash_now)
//    }
//    }

    // Log an attempt to log in to an account in "registered" state and show a flash message.
    void account_not_activated(bool flash_now = true) {
//      flash_error_message(log_reason : 'NOT ACTIVATED', flash_now : flash_now) {
//        if (Setting.self_registration == '1') {
//          'account.error_inactive_activation_by_mail' else 'account.error_inactive_manual_activation'
//        }
//      }
    }

//    void invited_account_not_activated(user) {
//      flash_error_message(log_reason : 'invited, NOT ACTIVATED', flash_now : false) {
//        'account.error_inactive_activation_by_mail'
//      }
//    }

    void account_pending() {
//      flash[:notice] = l(
//                         : notice_account_pending)
//                     // Set back_url to make sure user is not redirected to an external login page
//                     // when registering via the external service. This also redirects the user
//                     // to the original page where the user clicked on the omniauth login link for a
//                     // provider.
//                     redirect_to action : 'login',
//      back_url : params
//      [:back_url]
    }

    void invited_user() {
//      if (session.include ?: invitation_token) {
//        token = Token::Invitation.find_by_plaintext_value session[:invitation_token]

//            token.user
//      }
    }

    void disable_api() {
//      // Changing this to not use api_request? to determine whether a request is an API
//      // request can have security implications regarding CSRF. See handle_unverified_request
//      // for more information.
//    head 410 if ( api_request?) {
  }

    void invalid_token_and_redirect() {
//      flash[:error] = I18n.t(
//                        : notice_account_invalid_token)

//                          redirect_to home_url
    }
    };
}
}
