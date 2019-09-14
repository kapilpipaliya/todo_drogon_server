#include "application_controller.h"
class GroupsController : public ApplicationController {
  // include GroupsHelper
  // layout 'admin'

  // before_action :require_admin
  // before_action :find_group, only: [:destroy,
//                                    :show, :create_memberships, :destroy_membership,
//                                    :edit_membership]

  // GET /groups
  // GET /groups.xml
   void index() {
//    this->groups = Group.order(Arel.sql('lastname ASC'))

//    respond_to { |format|
//      format.html // index.html.erb
//      format.xml  { render xml: this->groups }
//    }
  }

  // GET /groups/1
  // GET /groups/1.xml
   void show() {
//    respond_to { |format|
//      format.html // show.html.erb
//      format.xml  { render xml: this->group }
//    }
  }

  // GET /groups/new
  // GET /groups/new.xml
   void new_() {
//    this->group = Group.new

//    respond_to { |format|
//      format.html // new.html.erb
//      format.xml  { render xml: this->group }
//    }
  }

  // GET /groups/1/edit
   void edit() {
//    this->group = Group.includes(:members, :users).find(params[:id])

//    set_filters_for_user_autocompleter
  }

  // POST /groups
  // POST /groups.xml
   void create() {
//    this->group = Group.new permitted_params.group

//    respond_to { |format|
//      if ( this->group.save) {
//        flash[:notice] = l(:notice_successful_create)
//        format.html { redirect_to(groups_path) }
//        format.xml  { render xml: this->group, status: :created, location: this->group }
//      else
//        format.html { render action: 'new' }
//        format.xml  { render xml: this->group.errors, status: :unprocessable_entity }
//      }
//    }
  }

  // PUT /groups/1
  // PUT /groups/1.xml
   void update() {
//    this->group = Group.includes(:users).find(params[:id])

//    respond_to { |format|
//      if ( this->group.update_attributes(permitted_params.group)) {
//        flash[:notice] = l(:notice_successful_update)
//        format.html { redirect_to(groups_path) }
//        format.xml  { head :ok }
//      else
//        format.html { render action: 'edit' }
//        format.xml  { render xml: this->group.errors, status: :unprocessable_entity }
//      }
//    }
  }

  // DELETE /groups/1
  // DELETE /groups/1.xml
   void destroy() {
//    this->group.destroy

//    respond_to { |format|
//      flash[:notice] = l(:notice_successful_delete)
//      format.html { redirect_to(groups_url) }
//      format.xml  { head :ok }
//    }
  }

   void add_users() {
//    this->group = Group.includes(:users).find(params[:id])
//    this->users = User.includes(:memberships).where(id: params[:user_ids])
//    this->group.users << this->users

//    I18n.t :notice_successful_update
//    redirect_to controller: '/groups', action: 'edit', id: this->group, tab: 'users'
  }

   void remove_user() {
//    this->group = Group.includes(:users).find(params[:id])
//    this->group.users.delete(User.includes(:memberships).find(params[:user_id]))

//    I18n.t :notice_successful_update
//    redirect_to controller: '/groups', action: 'edit', id: this->group, tab: 'users'
  }

   void create_memberships() {
//    membership_params = permitted_params.group_membership
//    membership_id = membership_params[:membership_id]

//    if ( membership_id.present?) {
//      key = :membership
//      this->membership = Member.find(membership_id)
//    else
//      key = :new_membership
//      this->membership = Member.new(principal: this->group)
//    }

//    service = ::Members::EditMembershipService.new(this->membership, save: true, current_user: current_user)
//    result = service.call(attributes: membership_params[key])

//    if ( result.success?) {
//      flash[:notice] = I18n.t :notice_successful_update
//    else
//      flash[:error] = result.errors.full_messages.join("\n")
//    }
//    redirect_to controller: '/groups', action: 'edit', id: this->group, tab: 'memberships'
  }

//  alias :edit_membership :create_memberships

   void destroy_membership() {
//    membership_params = permitted_params.group_membership
//    Member.find(membership_params[:membership_id]).destroy

//    flash[:notice] = I18n.t :notice_successful_delete
//    redirect_to controller: '/groups', action: 'edit', id: this->group, tab: 'memberships'
  }

  protected:

   void find_group() {
//    this->group = Group.find(params[:id])
  }

   void default_breadcrumb() {
//    if ( action_name == 'index') {
//      t('label_group_plural')
//    else
//      ActionController::Base.helpers.link_to(t('label_group_plural'), groups_path)
//    }
  }

    bool show_local_breadcrumb() {
        return true;
    }
};
