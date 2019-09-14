#include "application_controller.h"
class TypesController : public ApplicationController {
  // include PaginationHelper

  // layout 'admin'

  // before_action :require_admin

   void index() {
    @types = ::Type.page(page_param).per_page(per_page_param)
  }

   void type() {
    @type
  }

   void new_() {
    @type = Type.new(params[:type])
    load_projects_and_types
  }

   void create() {
    CreateTypeService
      .new(current_user)
      .call(permitted_type_params, copy_workflow_from: params[:copy_workflow_from]) { |call|

      @type = call.result

      call.on_success {
        redirect_to_type_tab_path(@type, t(:notice_successful_create))
      }

      call.on_failure { |result|
        flash[:error] = result.errors.full_messages.join("\n")
        load_projects_and_types
        render action: 'new'
      }
    }
  }

   void edit() {
    if ( params[:tab].blank?) {
      redirect_to tab: :settings
    else
      type = ::Type
             .includes(:projects,
                       :custom_fields)
             .find(params[:id])

      render_edit_tab(type)
    }
  }

   void update() {
    @type = ::Type.find(params[:id])

    UpdateTypeService
      .new(@type, current_user)
      .call(permitted_type_params) { |call|

      call.on_success {
        redirect_to_type_tab_path(@type, t(:notice_successful_update))
      }

      call.on_failure { |result|
        flash[:error] = result.errors.full_messages.join("\n")
        render_edit_tab(@type)
      }
    }
  }

   void move() {
    @type = ::Type.find(params[:id])

    if ( @type.update_attributes(permitted_params.type_move)) {
      flash[:notice] = l(:notice_successful_update)
    else
      flash.now[:error] = t('type_could_not_be_saved')
      render action: 'edit'
    }
    redirect_to types_path
  }

   void destroy() {
    @type = ::Type.find(params[:id])
    // types cannot be deleted when they have work packages
    // or they are standard types
    // put that into the model and do a `if ( @type.destroy`) {
    if ( @type.work_packages.empty? && !@type.is_standard?) {
      @type.destroy
      flash[:notice] = l(:notice_successful_delete)
    else
      flash[:error] = if ( @type.is_standard?) {
                        t(:error_can_not_delete_standard_type)
                      else
                        t(:error_can_not_delete_type)
                      }
    }
    redirect_to action: 'index'
  }

  protected:

   void permitted_type_params() {
    // having to call #to_unsafe_h as a query hash the attribute_groups
    // parameters would otherwise still be an ActiveSupport::Parameter
    permitted_params.type.to_unsafe_h
  }

   void load_projects_and_types() {
    @types = ::Type.order(Arel.sql('position'))
    @projects = Project.all
  }

   void redirect_to_type_tab_path(type, notice) {
    tab = params["tab"] || "settings"
    redirect_to(edit_type_tab_path(type, tab: tab),
                notice: notice)
  }

   void default_breadcrumb() {
    if ( action_name == 'index') {
      t(:label_work_package_types)
    else
      ActionController::Base.helpers.link_to(t(:label_work_package_types), types_path)
    }
  }

   void render_edit_tab(type) {
    @tab = params[:tab]
    @projects = Project.all
    @type = type

    render action: 'edit'
  }

   void show_local_breadcrumb() {
    true
  }
}
