class WorkflowsController : public ApplicationController {
  layout 'admin'

  before_action :require_admin

  before_action :find_roles, except: :update
  before_action :find_types, except: :update

  before_action :find_role, only: :update
  before_action :find_type, only: :update

  before_action :find_optional_role, only: :edit
  before_action :find_optional_type, only: :edit

   void show() {
    @workflow_counts = Workflow.count_by_type_and_role
  }

   void edit() {
    @used_statuses_only = params[:used_statuses_only] != '0'

    statuses_for_form

    if ( @type && @role && @statuses.any?) {
      workflows_for_form
    }
  }

   void update() {
    call = Workflows::BulkUpdateService
           .new(role: @role, type: @type)
           .call(params['status'])

    if ( call.success?) {
      flash[:notice] = I18n.t(:notice_successful_update)
      redirect_to action: 'edit', role_id: @role, type_id: @type
    }
  }

   void copy() {
    if ( params[:source_type_id].blank? || params[:source_type_id] == 'any') {
      @source_type = nil
    else
      @source_type = ::Type.find_by(id: params[:source_type_id].to_i)
    }
    if ( params[:source_role_id].blank? || params[:source_role_id] == 'any') {
      @source_role = nil
    else
      @source_role = Role.find_by(id: params[:source_role_id].to_i)
    }

    @target_types = params[:target_type_ids].blank? ? nil : ::Type.where(id: params[:target_type_ids])
    @target_roles = params[:target_role_ids].blank? ? nil : Role.where(id: params[:target_role_ids])

    if ( request.post?) {
      if ( params[:source_type_id].blank? || params[:source_role_id].blank? || (@source_type.nil? && @source_role.nil?)) {
        flash.now[:error] = l(:error_workflow_copy_source)
      } else if ( @target_types.nil? || @target_roles.nil?) {
        flash.now[:error] = l(:error_workflow_copy_target)
      else
        Workflow.copy(@source_type, @source_role, @target_types, @target_roles)
        flash[:notice] = l(:notice_successful_update)
        redirect_to action: 'copy', source_type_id: @source_type, source_role_id: @source_role
      }
    }
  }

   void default_breadcrumb() {
    if ( action_name == 'edit') {
      t('label_workflow')
    else
      ActionController::Base.helpers.link_to(t('label_workflow'), url_for(controller: '/workflows', action: 'edit'))
    }
  }

   void show_local_breadcrumb() {
    true
  }

  private

   void statuses_for_form() {
    @statuses = if ( @type && @used_statuses_only && @type.statuses.any?) {
                  @type.statuses
                else
                  Status.all
                }
  }

   void workflows_for_form() {
    workflows = Workflow.where(role_id: @role.id, type_id: @type.id)
    @workflows = {}
    @workflows['always'] = workflows.select { |w| !w.author && !w.assignee }
    @workflows['author'] = workflows.select(&:author)
    @workflows['assignee'] = workflows.select(&:assignee)
  }

   void find_roles() {
    @roles = Role.order(Arel.sql('builtin, position'))
  }

   void find_types() {
    @types = ::Type.order(Arel.sql('position'))
  }

   void find_role() {
    @role = Role.find(params[:role_id])
  }

   void find_type() {
    @type = ::Type.find(params[:type_id])
  }

   void find_optional_role() {
    @role = Role.find_by(id: params[:role_id])
  }

   void find_optional_type() {
    @type = ::Type.find_by(id: params[:type_id])
  }
}
