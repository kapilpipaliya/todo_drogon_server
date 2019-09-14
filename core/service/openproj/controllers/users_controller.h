#include "application_controller.h"
class UsersController : public ApplicationController {
public:
  // layout 'admin'

  // before_action :require_admin, except: [:show, :deletion_info, :destroy]
  // before_action :find_user, only: [:show,
//                                   :edit,
//                                   :update,
//                                   :change_status_info,
//                                   :change_status,
//                                   :destroy,
//                                   :deletion_info,
//                                   :resend_invitation]
  // should also contain destroy but post data can not be redirected
  // before_action :require_login, only: [:deletion_info]
  // before_action :authorize_for_user, only: [:destroy]
  // before_action :check_if_deletion_allowed, only: [:deletion_info,
//                                                   :destroy]

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
//    this->groups = Group.all.sort
//    this->status = Users::UserFilterCell.status_param params
//    this->users = Users::UserFilterCell.filter params

//    respond_to { |format|
//      format.html {
//        render layout: !request.xhr?
//      }
//    }
  }

   void show() {
//    // show projects based on current user visibility
//    this->memberships = this->user.memberships
//                        .visible(current_user)

//    events = Redmine::Activity::Fetcher.new(User.current, author: this->user).events(nil, nil, limit: 10)
//    this->events_by_day = events.group_by { |e| e.event_datetime.to_date }

//    unless User.current.admin?
//      if ( !(this->user.active? ||) {
//         this->user.registered?) ||
//         (this->user != User.current && this->memberships.empty? && events.empty?)
//        render_404
//        return
//      }
//    }

//    respond_to { |format|
//      format.html { render layout: 'no_menu' }
//    }
  }

   void new_() {
//    this->user = User.new(language: Setting.default_language,
//                     mail_notification: Setting.default_notification_option)
//    this->auth_sources = AuthSource.all
  }

//  verify method: :post, only: :create, render: { nothing: true, status: :method_not_allowed }
//   void create() {
//    this->user = User.new(language: Setting.default_language,
//                     mail_notification: Setting.default_notification_option)
//    this->user.attributes = permitted_params.user_create_as_admin(false, this->user.change_password_allowed?)
//    this->user.admin = params[:user][:admin] || false
//    this->user.login = params[:user][:login] || this->user.mail

//    if ( UserInvitation.invite_user! this->user) {
//      respond_to { |format|
//        format.html {
//          flash[:notice] = l(:notice_successful_create)
//          redirect_to(params[:continue] ? new_user_path : edit_user_path(this->user))
//        }
//      }
//    else
//      this->auth_sources = AuthSource.all

//      respond_to { |format|
//        format.html { render action: 'new' }
//      }
//    }
//  }

   void edit() {
//    this->auth_sources = AuthSource.all
//    this->membership ||= Member.new
  }

//  verify method: :put, only: :update, render: { nothing: true, status: :method_not_allowed }
//   void update() {
//    this->user.attributes = permitted_params.user_update_as_admin(this->user.uses_external_authentication?,
//                                                             this->user.change_password_allowed?)

//    if ( this->user.change_password_allowed?) {
//      if ( params[:user][:assign_random_password]) {
//        this->user.random_password!
//      } else if ( set_password? params) {
//        this->user.password = params[:user][:password]
//        this->user.password_confirmation = params[:user][:password_confirmation]
//      }
//    }

//    pref_params = if ( params[:pref].present?) {
//                    permitted_params.pref
//                  else
//                    {}
//                  }

//    if ( this->user.save) {
//      update_email_service = UpdateUserEmailSettingsService.new(this->user)
//      update_email_service.call(mail_notification: pref_params.delete(:mail_notification),
//                                self_notified: params[:self_notified] == '1',
//                                notified_project_ids: params[:notified_project_ids])

//      this->user.pref.attributes = pref_params
//      this->user.pref.save

//      if ( !this->user.password.blank? && this->user.change_password_allowed?) {
//        send_information = params[:send_information]

//        if ( this->user.invited?) {
//          // setting a password for an invited user activates them implicitly
//          if ( OpenProject::Enterprise.user_limit_reached?) {
//            this->user.register!
//            show_user_limit_warning!
//          else
//            this->user.activate!
//          }

//          send_information = true
//        }

//        if ( this->user.active? && send_information) {
//          UserMailer.account_information(this->user, this->user.password).deliver_now
//        }
//      }

//      respond_to { |format|
//        format.html {
//          flash[:notice] = l(:notice_successful_update)
//          redirect_back(fallback_location: edit_user_path(this->user))
//        }
//      }
//    else
//      this->auth_sources = AuthSource.all
//      this->membership ||= Member.new
//      // Clear password input
//      this->user.password = this->user.password_confirmation = nil

//      respond_to { |format|
//        format.html {
//          render action: :edit
//        }
//      }
//    }
//  }

   void change_status_info() {
//    this->status_change = params[:change_action].to_sym

//    return render_400 unless %i(activate lock unlock).include? this->status_change
  }

   void change_status() {
//    if ( this->user.id == current_user.id) {
//      // user is not allowed to change own status
//      redirect_back_or_default(action: 'edit', id: this->user)
//      return
//    }

//    if ( (params[:unlock] || params[:activate]) && user_limit_reached?) {
//      show_user_limit_error!

//      return redirect_back_or_default(action: 'edit', id: this->user)
//    }

//    if ( params[:unlock]) {
//      this->user.failed_login_count = 0
//      this->user.activate
//    } else if ( params[:lock]) {
//      this->user.lock
//    } else if ( params[:activate]) {
//      this->user.activate
//    }
//    // Was the account activated? (do it before User#save clears the change)
//    was_activated = (this->user.status_change == [User::STATUSES[:registered],
//                                             User::STATUSES[:active]])

//    if ( params[:activate] && this->user.missing_authentication_method?) {
//      flash[:error] = I18n.t(:error_status_change_failed,
//                             errors: I18n.t(:notice_user_missing_authentication_method),
//                             scope: :user)
//    } else if ( this->user.save) {
//      flash[:notice] = I18n.t(:notice_successful_update)
//      if ( was_activated) {
//        UserMailer.account_activated(this->user).deliver_now
//      }
//    else
//      flash[:error] = I18n.t(:error_status_change_failed,
//                             errors: this->user.errors.full_messages.join(', '),
//                             scope: :user)
//    }
//    redirect_back_or_default(action: 'edit', id: this->user)
  }

   void resend_invitation() {
//    status = Principal::STATUSES[:invited]
//    if ( this->user.status != status) { this->user.update status: status ;}

//    token = UserInvitation.reinvite_user this->user.id

//    if ( token.persisted?) {
//      flash[:notice] = I18n.t(:notice_user_invitation_resent, email: this->user.mail)
//    else
//      logger.error "could not re-invite #{this->user.mail}: #{token.errors.full_messages.join(' ')}"
//      flash[:error] = I18n.t(:notice_internal_server_error, app_title: Setting.app_title)
//    }

//    redirect_to edit_user_path(this->user)
  }

   void destroy() {
//    // true if ( the user deletes him/herself) {
//    self_delete = (this->user == User.current)

//    Users::DeleteService.new(this->user, User.current).call

//    flash[:notice] = l('account.deleted')

//    respond_to { |format|
//      format.html {
//        redirect_to self_delete ? signin_path : users_path
//      }
//    }
  }

   void deletion_info() {
//    render action: 'deletion_info', layout: my_or_admin_layout
  }

  private:

   void find_user() {
//    if ( params[:id] == 'current' || params['id'].nil?) {
//      require_login || return
//      this->user = User.current
//    else
//      this->user = User.find(params[:id])
//    }
//  rescue ActiveRecord::RecordNotFound
//    render_404
  }

   void authorize_for_user() {
//    if ( (User.current != this->user ||) {
//        User.current == User.anonymous) &&
//       !User.current.admin?

//      respond_to { |format|
//        format.html { render_403 }
//        format.xml  { head :unauthorized, 'WWW-Authenticate' => 'Basic realm="OpenProject API"' }
//        format.js   { head :unauthorized, 'WWW-Authenticate' => 'Basic realm="OpenProject API"' }
//        format.json { head :unauthorized, 'WWW-Authenticate' => 'Basic realm="OpenProject API"' }
//      }

//      false
//    }
  }

   void check_if_deletion_allowed() {
//    render_404 unless Users::DeleteService.deletion_allowed? this->user, User.current
  }

   void my_or_admin_layout() {
//    // TODO: how can this be done better:
//    // check if ( the route used to call the action is in the 'my' namespace) {
//    if ( url_for(:delete_my_account_info) == request.url) {
//      'my'
//    else
//      'admin'
//    }
  }

//   void set_password?(params) {
//    params[:user][:password].present? && !OpenProject::Configuration.disable_password_choice?
//  }

  protected:

   void default_breadcrumb() {
//    if ( action_name == 'index') {
//      t('label_user_plural')
//    else
//      ActionController::Base.helpers.link_to(t('label_user_plural'), users_path)
//    }
  }

   bool show_local_breadcrumb() {
//    current_user.admin?
  }
};
