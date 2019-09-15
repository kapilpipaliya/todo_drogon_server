#pragma once
#include "application_controller.h"
namespace openproj {
class TypesController : public ApplicationController {
public:
  // include PaginationHelper

  // layout 'admin'

  // before_action :require_admin

   void index() {
//    this->types = ::Type.page(page_param).per_page(per_page_param)
  }

   void type() {
//    this->type
  }

   void new_() {
//    this->type = Type.new(params[:type])
//    load_projects_and_types
  }

   void create() {
//    CreateTypeService
//      .new(current_user)
//      .call(permitted_type_params, copy_workflow_from: params[:copy_workflow_from]) { |call|

//      this->type = call.result

//      call.on_success {
//        redirect_to_type_tab_path(this->type, t(:notice_successful_create))
//      }

//      call.on_failure { |result|
//        flash[:error] = result.errors.full_messages.join("\n")
//        load_projects_and_types
//        render action: 'new'
//      }
//    }
  }

   void edit() {
//    if ( params[:tab].blank?) {
//      redirect_to tab: :settings
//    else
//      type = ::Type
//             .includes(:projects,
//                       :custom_fields)
//             .find(params[:id])

//      render_edit_tab(type)
//    }
  }

   void update() {
//    this->type = ::Type.find(params[:id])

//    UpdateTypeService
//      .new(this->type, current_user)
//      .call(permitted_type_params) { |call|

//      call.on_success {
//        redirect_to_type_tab_path(this->type, t(:notice_successful_update))
//      }

//      call.on_failure { |result|
//        flash[:error] = result.errors.full_messages.join("\n")
//        render_edit_tab(this->type)
//      }
//    }
  }

   void move() {
//    this->type = ::Type.find(params[:id])

//    if ( this->type.update_attributes(permitted_params.type_move)) {
//      flash[:notice] = l(:notice_successful_update)
//    else
//      flash.now[:error] = t('type_could_not_be_saved')
//      render action: 'edit'
//    }
//    redirect_to types_path
  }

   void destroy() {
//    this->type = ::Type.find(params[:id])
//    // types cannot be deleted when they have work packages
//    // or they are standard types
//    // put that into the model and do a `if ( this->type.destroy`) {
//    if ( this->type.work_packages.empty? && !this->type.is_standard?) {
//      this->type.destroy
//      flash[:notice] = l(:notice_successful_delete)
//    else
//      flash[:error] = if ( this->type.is_standard?) {
//                        t(:error_can_not_delete_standard_type)
//                      else
//                        t(:error_can_not_delete_type)
//                      }
//    }
//    redirect_to action: 'index'
  }

  protected:

   void permitted_type_params() {
//    // having to call #to_unsafe_h as a query hash the attribute_groups
//    // parameters would otherwise still be an ActiveSupport::Parameter
//    permitted_params.type.to_unsafe_h
  }

   void load_projects_and_types() {
//    this->types = ::Type.order(Arel.sql('position'))
//    this->projects = Project.all
  }

//   void redirect_to_type_tab_path(type, notice) {
//    tab = params["tab"] || "settings"
//    redirect_to(edit_type_tab_path(type, tab: tab),
//                notice: notice)
//  }

   void default_breadcrumb() {
//    if ( action_name == 'index') {
//      t(:label_work_package_types)
//    else
//      ActionController::Base.helpers.link_to(t(:label_work_package_types), types_path)
//    }
  }

//   void render_edit_tab(type) {
//    this->tab = params[:tab]
//    this->projects = Project.all
//    this->type = type

//    render action: 'edit'
//  }

   bool show_local_breadcrumb() {
    return true;
  }
};
}
