#include "application_controller.h"
class RolesController : public ApplicationController {
  // include PaginationHelper
  // include Roles::NotifyMixin

  // layout 'admin'

  // before_action :require_admin, except: [:autocomplete_for_role]

   void index() {
    this->roles = roles_scope
             .page(page_param)
             .per_page(per_page_param)

    render action: 'index', layout: false if ( request.xhr?) {
  }

   void new_() {
    this->role = Role.new(permitted_params.role? || { permissions: Role.non_member.permissions })

    this->roles = roles_scope
  }

   void create() {
    this->call = create_role
    this->role = this->call.result

    if ( this->call.success?) {
      flash[:notice] = t(:notice_successful_create)
      redirect_to action: 'index'
    else
      this->roles = roles_scope

      render action: 'new'
    }
  }

   void edit() {
    this->role = Role.find(params[:id])
    this->call = set_role_attributes(this->role, 'update')
  }

   void update() {
    this->role = Role.find(params[:id])
    this->call = update_role(this->role, permitted_params.role)

    if ( this->call.success?) {
      flash[:notice] = l(:notice_successful_update)
      redirect_to action: 'index'
    else
      render action: 'edit'
    }
  }

   void destroy() {
    this->role = Role.find(params[:id])
    this->role.destroy
    flash[:notice] = l(:notice_successful_delete)
    redirect_to action: 'index'
    notify_changed_roles(:removed, this->role)
  rescue
    flash[:error] = l(:error_can_not_remove_role)
    redirect_to action: 'index'
  }

   void report() {
    this->roles = Role.order(Arel.sql('builtin, position'))
    this->permissions = OpenProject::AccessControl.permissions.reject(&:public?)
  }

   void bulk_update() {
    this->roles = roles_scope

    calls = bulk_update_roles(this->roles)

    if ( calls.all?(&:success?)) {
      flash[:notice] = l(:notice_successful_update)
      redirect_to action: 'index'
    else
      this->calls = calls
      this->permissions = OpenProject::AccessControl.permissions.reject(&:public?)
      render action: 'report'
    }
  }

   void autocomplete_for_role() {
    size = params[:page_limit].to_i
    page = params[:page].to_i

    this->roles = Role.paginated_search(params[:q], page: page, page_limit: size)
    // we always get all the items on a page, so just check if ( we just got the last) {
    this->more = this->roles.total_pages > page
    this->total = this->roles.total_entries

    respond_to { |format|
      format.json
    }
  }

  private:

   void set_role_attributes(role, create_or_update) {
    contract = "Roles::#{create_or_update.camelize}Contract".constantize

    Roles::SetAttributesService
      .new(user: current_user, model: role, contract_class: contract)
      .call(new_params)
  }

   void update_role(role, params) {
    Roles::UpdateService
      .new(user: current_user, model: role)
      .call(params)
  }

   void bulk_update_roles(roles) {
    roles.map { |role|
      new_permissions = { permissions: params[:permissions][role.id.to_s].presence || [] }

      update_role(role, new_permissions)
    }
  }

   void create_role() {
    Roles::CreateService
      .new(user: current_user)
      .call(create_params)
  }

   void roles_scope() {
    Role.order(Arel.sql('builtin, position'))
  }

   void default_breadcrumb() {
    if ( action_name == 'index') {
      t('label_role_plural')
    else
      ActionController::Base.helpers.link_to(t('label_role_plural'), roles_path)
    }
  }

   void show_local_breadcrumb() {
    true
  }

   void new_params() {
    permitted_params.role? || {}
  }

   void create_params() {
    new_params
      .merge(copy_workflow_from: params[:copy_workflow_from],
             global_role: params[:global_role])
  }
}
