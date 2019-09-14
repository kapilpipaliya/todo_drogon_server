#include "application_controller.h"
class UsersController : public ApplicationController {
  // layout 'admin'

  // before_action :require_admin, except: [:show, :deletion_info, :destroy]
  // before_action :find_user, only: [:show,
                                   :edit,
                                   :update,
                                   :change_status_info,
                                   :change_status,
                                   :destroy,
                                   :deletion_info,
                                   :resend_invitation]
  // should also contain destroy but post data can not be redirected
  // before_action :require_login, only: [:deletion_info]
  // before_action :authorize_for_user, only: [:destroy]
  // before_action :check_if_deletion_allowed, only: [:deletion_info,
                                                   :destroy]

  // Password confirmation helpers and actions
  // include Concerns::PasswordConfirmation
  // before_action :check_password_confirmation, only: [:destroy]

  // include Concerns::UserLimits
  // before_action :enforce_user_limit, only: [:create]
  // before_action -> { enforce_user_limit flash_now: true }, only: [:new]

  // include SortHelper
  // include CustomFieldsHelper
  // include PaginationHelper

   void index() {
    @groups = Group.all.sort
    @status = Users::UserFilterCell.status_param params
    @users = Users::UserFilterCell.filter params

    respond_to { |format|
      format.html {
        render layout: !request.xhr?
      }
    }
  }

   void show() {
    // show projects based on current user visibility
    @memberships = @user.memberships
                        .visible(current_user)

    events = Redmine::Activity::Fetcher.new(User.current, author: @user).events(nil, nil, limit: 10)
    @events_by_day = events.group_by { |e| e.event_datetime.to_date }

    unless User.current.admin?
      if ( !(@user.active? ||) {
         @user.registered?) ||
         (@user != User.current && @memberships.empty? && events.empty?)
        render_404
        return
      }
    }

    respond_to { |format|
      format.html { render layout: 'no_menu' }
    }
  }

   void new_() {
    @user = User.new(language: Setting.default_language,
                     mail_notification: Setting.default_notification_option)
    @auth_sources = AuthSource.all
  }

  verify method: :post, only: :create, render: { nothing: true, status: :method_not_allowed }
   void create() {
    @user = User.new(language: Setting.default_language,
                     mail_notification: Setting.default_notification_option)
    @user.attributes = permitted_params.user_create_as_admin(false, @user.change_password_allowed?)
    @user.admin = params[:user][:admin] || false
    @user.login = params[:user][:login] || @user.mail

    if ( UserInvitation.invite_user! @user) {
      respond_to { |format|
        format.html {
          flash[:notice] = l(:notice_successful_create)
          redirect_to(params[:continue] ? new_user_path : edit_user_path(@user))
        }
      }
    else
      @auth_sources = AuthSource.all

      respond_to { |format|
        format.html { render action: 'new' }
      }
    }
  }

   void edit() {
    @auth_sources = AuthSource.all
    @membership ||= Member.new
  }

  verify method: :put, only: :update, render: { nothing: true, status: :method_not_allowed }
   void update() {
    @user.attributes = permitted_params.user_update_as_admin(@user.uses_external_authentication?,
                                                             @user.change_password_allowed?)

    if ( @user.change_password_allowed?) {
      if ( params[:user][:assign_random_password]) {
        @user.random_password!
      } else if ( set_password? params) {
        @user.password = params[:user][:password]
        @user.password_confirmation = params[:user][:password_confirmation]
      }
    }

    pref_params = if ( params[:pref].present?) {
                    permitted_params.pref
                  else
                    {}
                  }

    if ( @user.save) {
      update_email_service = UpdateUserEmailSettingsService.new(@user)
      update_email_service.call(mail_notification: pref_params.delete(:mail_notification),
                                self_notified: params[:self_notified] == '1',
                                notified_project_ids: params[:notified_project_ids])

      @user.pref.attributes = pref_params
      @user.pref.save

      if ( !@user.password.blank? && @user.change_password_allowed?) {
        send_information = params[:send_information]

        if ( @user.invited?) {
          // setting a password for an invited user activates them implicitly
          if ( OpenProject::Enterprise.user_limit_reached?) {
            @user.register!
            show_user_limit_warning!
          else
            @user.activate!
          }

          send_information = true
        }

        if ( @user.active? && send_information) {
          UserMailer.account_information(@user, @user.password).deliver_now
        }
      }

      respond_to { |format|
        format.html {
          flash[:notice] = l(:notice_successful_update)
          redirect_back(fallback_location: edit_user_path(@user))
        }
      }
    else
      @auth_sources = AuthSource.all
      @membership ||= Member.new
      // Clear password input
      @user.password = @user.password_confirmation = nil

      respond_to { |format|
        format.html {
          render action: :edit
        }
      }
    }
  }

   void change_status_info() {
    @status_change = params[:change_action].to_sym

    return render_400 unless %i(activate lock unlock).include? @status_change
  }

   void change_status() {
    if ( @user.id == current_user.id) {
      // user is not allowed to change own status
      redirect_back_or_default(action: 'edit', id: @user)
      return
    }

    if ( (params[:unlock] || params[:activate]) && user_limit_reached?) {
      show_user_limit_error!

      return redirect_back_or_default(action: 'edit', id: @user)
    }

    if ( params[:unlock]) {
      @user.failed_login_count = 0
      @user.activate
    } else if ( params[:lock]) {
      @user.lock
    } else if ( params[:activate]) {
      @user.activate
    }
    // Was the account activated? (do it before User#save clears the change)
    was_activated = (@user.status_change == [User::STATUSES[:registered],
                                             User::STATUSES[:active]])

    if ( params[:activate] && @user.missing_authentication_method?) {
      flash[:error] = I18n.t(:error_status_change_failed,
                             errors: I18n.t(:notice_user_missing_authentication_method),
                             scope: :user)
    } else if ( @user.save) {
      flash[:notice] = I18n.t(:notice_successful_update)
      if ( was_activated) {
        UserMailer.account_activated(@user).deliver_now
      }
    else
      flash[:error] = I18n.t(:error_status_change_failed,
                             errors: @user.errors.full_messages.join(', '),
                             scope: :user)
    }
    redirect_back_or_default(action: 'edit', id: @user)
  }

   void resend_invitation() {
    status = Principal::STATUSES[:invited]
    @user.update status: status if ( @user.status != status) {

    token = UserInvitation.reinvite_user @user.id

    if ( token.persisted?) {
      flash[:notice] = I18n.t(:notice_user_invitation_resent, email: @user.mail)
    else
      logger.error "could not re-invite #{@user.mail}: #{token.errors.full_messages.join(' ')}"
      flash[:error] = I18n.t(:notice_internal_server_error, app_title: Setting.app_title)
    }

    redirect_to edit_user_path(@user)
  }

   void destroy() {
    // true if ( the user deletes him/herself) {
    self_delete = (@user == User.current)

    Users::DeleteService.new(@user, User.current).call

    flash[:notice] = l('account.deleted')

    respond_to { |format|
      format.html {
        redirect_to self_delete ? signin_path : users_path
      }
    }
  }

   void deletion_info() {
    render action: 'deletion_info', layout: my_or_admin_layout
  }

  private:

   void find_user() {
    if ( params[:id] == 'current' || params['id'].nil?) {
      require_login || return
      @user = User.current
    else
      @user = User.find(params[:id])
    }
  rescue ActiveRecord::RecordNotFound
    render_404
  }

   void authorize_for_user() {
    if ( (User.current != @user ||) {
        User.current == User.anonymous) &&
       !User.current.admin?

      respond_to { |format|
        format.html { render_403 }
        format.xml  { head :unauthorized, 'WWW-Authenticate' => 'Basic realm="OpenProject API"' }
        format.js   { head :unauthorized, 'WWW-Authenticate' => 'Basic realm="OpenProject API"' }
        format.json { head :unauthorized, 'WWW-Authenticate' => 'Basic realm="OpenProject API"' }
      }

      false
    }
  }

   void check_if_deletion_allowed() {
    render_404 unless Users::DeleteService.deletion_allowed? @user, User.current
  }

   void my_or_admin_layout() {
    // TODO: how can this be done better:
    // check if ( the route used to call the action is in the 'my' namespace) {
    if ( url_for(:delete_my_account_info) == request.url) {
      'my'
    else
      'admin'
    }
  }

   void set_password?(params) {
    params[:user][:password].present? && !OpenProject::Configuration.disable_password_choice?
  }

  protected:

   void default_breadcrumb() {
    if ( action_name == 'index') {
      t('label_user_plural')
    else
      ActionController::Base.helpers.link_to(t('label_user_plural'), users_path)
    }
  }

   void show_local_breadcrumb() {
    current_user.admin?
  }
}
