#include "application_controller.h"
class WorkflowsController : public ApplicationController {
public :
  // layout 'admin'

  // before_action :require_admin

  // before_action :find_roles, except: :update
  // before_action :find_types, except: :update

  // before_action :find_role, only: :update
  // before_action :find_type, only: :update

  // before_action :find_optional_role, only: :edit
  // before_action :find_optional_type, only: :edit

   void show() {
//    this->workflow_counts = Workflow.count_by_type_and_role
  }

   void edit() {
//    this->used_statuses_only = params[:used_statuses_only] != '0'

//    statuses_for_form

//    if ( this->type && this->role && this->statuses.any?) {
//      workflows_for_form
//    }
  }

   void update() {
//    call = Workflows::BulkUpdateService
//           .new(role: this->role, type: this->type)
//           .call(params['status'])

//    if ( call.success?) {
//      flash[:notice] = I18n.t(:notice_successful_update)
//      redirect_to action: 'edit', role_id: this->role, type_id: this->type
//    }
  }

   void copy() {
//    if ( params[:source_type_id].blank? || params[:source_type_id] == 'any') {
//      this->source_type = nil
//    else
//      this->source_type = ::Type.find_by(id: params[:source_type_id].to_i)
//    }
//    if ( params[:source_role_id].blank? || params[:source_role_id] == 'any') {
//      this->source_role = nil
//    else
//      this->source_role = Role.find_by(id: params[:source_role_id].to_i)
//    }

//    this->target_types = params[:target_type_ids].blank? ? nil : ::Type.where(id: params[:target_type_ids])
//    this->target_roles = params[:target_role_ids].blank? ? nil : Role.where(id: params[:target_role_ids])

//    if ( request.post?) {
//      if ( params[:source_type_id].blank? || params[:source_role_id].blank? || (this->source_type.nil? && this->source_role.nil?)) {
//        flash.now[:error] = l(:error_workflow_copy_source)
//      } else if ( this->target_types.nil? || this->target_roles.nil?) {
//        flash.now[:error] = l(:error_workflow_copy_target)
//      else
//        Workflow.copy(this->source_type, this->source_role, this->target_types, this->target_roles)
//        flash[:notice] = l(:notice_successful_update)
//        redirect_to action: 'copy', source_type_id: this->source_type, source_role_id: this->source_role
//      }
//    }
  }

   void default_breadcrumb() {
//    if ( action_name == 'edit') {
//      t('label_workflow')
//    else
//      ActionController::Base.helpers.link_to(t('label_workflow'), url_for(controller: '/workflows', action: 'edit'))
//    }
  }

   bool show_local_breadcrumb() {
    return true;
  }

  private:

   void statuses_for_form() {
//    this->statuses = if ( this->type && this->used_statuses_only && this->type.statuses.any?) {
//                  this->type.statuses
//                else
//                  Status.all
//                }
  }

   void workflows_for_form() {
//    workflows = Workflow.where(role_id: this->role.id, type_id: this->type.id)
//    this->workflows = {}
//    this->workflows['always'] = workflows.select { |w| !w.author && !w.assignee }
//    this->workflows['author'] = workflows.select(&:author)
//    this->workflows['assignee'] = workflows.select(&:assignee)
  }

   void find_roles() {
//    this->roles = Role.order(Arel.sql('builtin, position'))
  }

   void find_types() {
//    this->types = ::Type.order(Arel.sql('position'))
  }

   void find_role() {
//    this->role = Role.find(params[:role_id])
  }

   void find_type() {
//    this->type = ::Type.find(params[:type_id])
  }

   void find_optional_role() {
//    this->role = Role.find_by(id: params[:role_id])
  }

   void find_optional_type() {
//    this->type = ::Type.find_by(id: params[:type_id])
  }
};
