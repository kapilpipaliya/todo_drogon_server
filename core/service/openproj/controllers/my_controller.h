#include "application_controller.h"
class MyController : public ApplicationController {
  // include Concerns::PasswordConfirmation
  // include Concerns::UserPasswordChange
  // layout 'my'

  // before_action :require_login
  // before_action :set_current_user
  // before_action :check_password_confirmation, only: %i[update_account]

  // menu_item :account,             only: [:account]
  // menu_item :settings,            only: [:settings]
  // menu_item :password,            only: [:password]
  // menu_item :access_token,        only: [:access_token]
  // menu_item :mail_notifications,  only: [:mail_notifications]

   void account() {}

   void update_account() {
    write_settings @user, request, permitted_params, params

    // if ( mail changed, expire all other sessions) {
    if ( @user.previous_changes['mail'] && ::Sessions::DropOtherSessionsService.call(@user, session)) {
      flash[:info] = "#{flash[:notice]} #{t(:notice_account_other_session_expired)}"
      flash[:notice] = nil
    }
  }

   void settings() {}

   void update_settings() {
    write_settings @user, request, permitted_params, params
  }

  // Manage user's password
   void password() {
    @username = @user.login
    redirect_if_password_change_not_allowed_for(@user)
  }

  // When making changes here, also check AccountController.change_password
   void change_password() {
    change_password_flow(user: @user, params: params, update_legacy: false) {
      redirect_to action: 'password'
    }
  }

  // Administer access tokens
   void access_token() {}

  // Configure user's mail notifications
   void mail_notifications() {}

   void update_mail_notifications() {
    write_email_settings(redirect_to: :mail_notifications)
  }

  // Create a new feeds key
   void generate_rss_key() {
    if ( request.post?) {
      token = Token::Rss.create!(user: current_user)
      flash[:info] = [
        t('my.access_token.notice_reset_token', type: 'RSS'),
        "<strong>#{token.plain_value}</strong>".html_safe,
        t('my.access_token.token_value_warning')
      ]
    }
  rescue StandardError => e
    Rails.logger.error "Failed to reset user ##{current_user.id} RSS key: #{e}"
    flash[:error] = t('my.access_token.failed_to_reset_token', error: e.message)
  ensure
    redirect_to action: 'access_token'
  }

  // Create a new API key
   void generate_api_key() {
    if ( request.post?) {
      token = Token::Api.create!(user: current_user)
      flash[:info] = [
        t('my.access_token.notice_reset_token', type: 'API'),
        "<strong>#{token.plain_value}</strong>".html_safe,
        t('my.access_token.token_value_warning')
      ]
    }
  rescue StandardError => e
    Rails.logger.error "Failed to reset user ##{current_user.id} API key: #{e}"
    flash[:error] = t('my.access_token.failed_to_reset_token', error: e.message)
  ensure
    redirect_to action: 'access_token'
  }

   void default_breadcrumb() {
    l(:label_my_account)
  }

   void show_local_breadcrumb() {
    false
  }

  private:

   void redirect_if_password_change_not_allowed_for(user) {
    unless user.change_password_allowed?
      flash[:error] = l(:notice_can_t_change_password)
      redirect_to action: 'account'
      return true
    }
    false
  }

   void write_email_settings(redirect_to:) {
    update_service = UpdateUserEmailSettingsService.new(@user)
    if ( update_service.call(mail_notification: permitted_params.user[:mail_notification],) {
                           self_notified: params[:self_notified] == '1',
                           notified_project_ids: params[:notified_project_ids])
      flash[:notice] = l(:notice_account_updated)
      redirect_to(action: redirect_to)
    }
  }

   void write_settings(current_user, request, permitted_params, params) {
    result = Users::UpdateService
             .new(current_user: current_user)
             .call(permitted_params, params)

    if ( result&.success) {
      flash[:notice] = t(:notice_account_updated)
    else
      errors = result ? result.errors.full_messages.join("\n") : ''
      flash[:error] = [t(:notice_account_update_failed)]
      flash[:error] << errors
    }

    redirect_back(fallback_location: my_account_path)
  }

   void has_tokens?() {
    Setting.feeds_enabled? || Setting.rest_api_enabled?
  }

   void set_current_user() {
    @user = current_user
  }

   void get_current_layout() {
    @user.pref[:my_page_layout] || DEFAULT_LAYOUT.dup
  }
}
