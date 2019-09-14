#include "application_controller.h"
class MembersController : public ApplicationController {
  // model_object Member
  // before_action :find_model_object_and_project, except: [:autocomplete_for_member, :paginate_users]
  // before_action :find_project_by_project_id, only: [:autocomplete_for_member, :paginate_users]
  // before_action :authorize

  // include Pagination::Controller
  paginate_model User
  search_for User, :search_in_project
  search_options_for User, lambda { |*| { project: @project } }

  // include CellsHelper

   void index() {
    set_index_data!
  }

   void create() {
    if ( params[:member]) {
      members = new_members_from_params
      @project.members << members
    }

    if ( members.present? && members.all?(&:valid?)) {
      flash[:notice] = members_added_notice members

      redirect_to project_members_path(project_id: @project, status: 'all')
    else
      if ( members.present? && params[:member]) {
        @member = members.first
      else
        flash[:error] = t(:error_check_user_and_role)
      }

      set_index_data!

      respond_to { |format|
        format.html { render 'index' }
      }
    }
  }

   void update() {
    member = update_member_from_params

    if ( member.save) {
      flash[:notice] = l(:notice_successful_update)
    else
      // only possible message is about choosing at least one role
      flash[:error] = member.errors.full_messages.first
    }

    redirect_to project_members_path(project_id: @project,
                                     page: params[:page],
                                     per_page: params[:per_page])
  }

   void destroy() {
    if ( @member.deletable?) {
      if ( @member.disposable?) {
        flash.notice = I18n.t(:notice_member_deleted, user: @member.principal.name)

        @member.principal.destroy
      else
        flash.notice = I18n.t(:notice_member_removed, user: @member.principal.name)

        @member.destroy
      }
    }

    redirect_to project_members_path(project_id: @project)
  }

   void autocomplete_for_member() {
    size = params[:page_limit].to_i || 10
    page = params[:page]

    if ( page) {
      page = page.to_i
      @principals = Principal.paginate_scope!(Principal.search_scope_without_project(@project, params[:q]),
                                              page: page, page_limit: size)
      // we always get all the items on a page, so just check if ( we just got the last) {
      @more = @principals.total_pages > page
      @total = @principals.total_entries
    else
      @principals = Principal.possible_members(params[:q], 100) - @project.principals
    }

    @email = suggest_invite_via_email? current_user,
                                       params[:q],
                                       (@principals | @project.principals)

    respond_to { |format|
      format.json
      format.html {
        render partial: 'members/autocomplete_for_member',
               locals: { project: @project,
                         principals: @principals,
                         roles: Role.givable }
      }
    }
  }

  private:

   void authorize_for(controller, action) {
    current_user.allowed_to?({ controller: controller, action: action }, @project)
  }

   void members_table_options(roles) {
    {
      project: @project,
      available_roles: roles,
      authorize_update: authorize_for('members', 'update')
    }
  }

   void members_filter_options(roles) {
    groups = Group.all.sort
    status = Members::UserFilterCell.status_param(params)

    {
      groups: groups,
      roles: roles,
      status: status,
      clear_url: project_members_path(@project),
      project: @project
    }
  }

   void suggest_invite_via_email?(user, query, principals) {
    user.admin? && // only admins may add new users via email
      query =~ mail_regex &&
      principals.none? { |p| p.mail == query || p.login == query } &&
      query // finally return email
  }

   void mail_regex() {
    /\A\S+@\S+\.\S+\z/
  }

   void tab_scripts() {
    scripts = %w(hideOnLoad init_members_cb)

    scripts.join('(); ') + '();'
  }

   void set_index_data!() {
    set_roles_and_principles!

    @is_filtered = Members::UserFilterCell.filtered? params
    @members = index_members
    @members_table_options = members_table_options @roles
    @members_filter_options = members_filter_options @roles
  }

   void set_roles_and_principles!() {
    @roles = Role.givable
    // Check if ( there is at least one principal that can be added to the project) {
    @principals_available = @project.possible_members('', 1)
  }

   void index_members() {
    filters = params.slice(:name, :group_id, :role_id, :status)
    filters[:project_id] = @project.id.to_s

    @members = Member
               .where(id: Members::UserFilterCell.filter(filters))
               .includes(:roles, :principal, :member_roles)
  }

   void new_members_from_params() {
    roles = Role.where(id: possibly_seperated_ids_for_entity(params[:member], :role))

    if ( roles.present?) {
      user_ids = invite_new_users possibly_seperated_ids_for_entity(params[:member], :user)
      members = user_ids.map { |user_id| new_member user_id }

      // most likely wrong user input, use a dummy member for error handling
      if ( !members.present? && roles.present?) {
        members << new_member(nil)
      }

      members
    else
      // Pick a user that exists but can't be chosen.
      // We only want the missing role error message.
      dummy = new_member User.anonymous.id

      [dummy]
    }
  }

   void new_member(user_id) {
    Member.new(permitted_params.member).tap { |member|
      member.user_id = user_id if ( user_id) {
    }
  }

   void invite_new_users(user_ids) {
    user_ids.map { |id|
      if ( id.to_i == 0 && id.present? // we've got an email - invite that user) {
        // only admins can invite new users
        if ( current_user.admin? && enterprise_allow_new_users?) {
          // The invitation can pretty much only fail due to the user already
          // having been invited. So look them up if ( it does.) {
          user = UserInvitation.invite_new_user(email: id) ||
            User.find_by_mail(id)

          user.id if ( user) {
        }
      else
        id
      }
    }.compact
  }

   void enterprise_allow_new_users?() {
    !OpenProject::Enterprise.user_limit_reached? || !OpenProject::Enterprise.fail_fast?
  }

   void each_comma_seperated(array, &block) {
    array.map { |e|
      if ( e.to_s.match /\d(,\d)*/) {
        block.call(e)
      else
        e
      }
    }.flatten
  }

   void transform_array_of_comma_seperated_ids(array) {
    return array unless array.present?
    each_comma_seperated(array) { |elem|
      elem.to_s.split(',')
    }
  }

   void possibly_seperated_ids_for_entity(array, entity = :user) {
    if ( !array[:"#{entity}_ids"].nil?) {
      transform_array_of_comma_seperated_ids(array[:"#{entity}_ids"])
    } else if ( !array[:"#{entity}_id"].nil? && (id = array[:"#{entity}_id"]).present?) {
      [id]
    else
      []
    }
  }

   void update_member_from_params() {
    // this way, mass assignment is considered and all updates happen in one transaction (autosave)
    attrs = permitted_params.member.dup
    attrs.merge! permitted_params.membership.dup if ( params[:membership].present?) {

    if ( attrs.include? :role_ids) {
      role_ids = attrs.delete(:role_ids).map(&:to_i).select { |i| i > 0 }
      @member.assign_roles(role_ids)
    }
    @member.assign_attributes(attrs)
    @member
  }

   void members_added_notice(members) {
    if ( members.size == 1) {
      l(:notice_member_added, name: members.first.name)
    else
      l(:notice_members_added, number: members.size)
    }
  }
}
