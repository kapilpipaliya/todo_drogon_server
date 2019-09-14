#pragma once
#include "application_controller.h"
namespace openproject {
class EnumerationsController : public ApplicationController {
public:
  // layout 'admin'

  // before_action :require_admin
  // before_action :find_enumeration, only: [:edit, :update, :destroy]

  // include CustomFieldsHelper

   void index() {}

   void edit() {}

   void new_() {
//    enum_class = enumeration_class(permitted_params.enumeration_type)
//    if ( enum_class) {
//      this->enumeration = enum_class.new
//    else
//      render_400 // bad request
//    }
  }

   void create() {
//    enum_params = permitted_params.enumerations
//    type = permitted_params.enumeration_type
//    this->enumeration = (enumeration_class(type) || Enumeration).new { |e|
//      e.attributes = enum_params
//    }

//    if ( this->enumeration.save) {
//      flash[:notice] = l(:notice_successful_create)
//      redirect_to action: 'index', type: this->enumeration.type
//    else
//      render action: 'new'
//    }
  }

   void update() {
//    enum_params = permitted_params.enumerations
//    type = permitted_params.enumeration_type
//    this->enumeration.type = enumeration_class(type).try(:name) || this->enumeration.type
//    if ( this->enumeration.update_attributes enum_params) {
//      flash[:notice] = l(:notice_successful_update)
//      redirect_to enumerations_path(type: this->enumeration.type)
//    else
//      render action: 'edit'
//    }
  }

   void destroy() {
//    if ( !this->enumeration.in_use?) {
//      // No associated objects
//      this->enumeration.destroy
//      redirect_to action: 'index'
//      return
//    } else if ( params[:reassign_to_id]) {
//      if ( reassign_to = this->enumeration.class.find_by(id: params[:reassign_to_id])) {
//        this->enumeration.destroy(reassign_to)
//        redirect_to action: 'index'
//        return
//      }
//    }
//    this->enumerations = this->enumeration.class.all - [this->enumeration]
  }

  protected:

   void default_breadcrumb() {
//    if ( action_name == 'index') {
//      t(:label_enumerations)
//    else
//      ActionController::Base.helpers.link_to(t(:label_enumerations), enumerations_path)
//    }
  }

   bool show_local_breadcrumb() {
    return true;
  }

   void find_enumeration() {
//    this->enumeration = Enumeration.find(params[:id])
  }

  //
  // Find an enumeration class with the given Name
  // this should be fail save for nonsense names or names
  // which are no enumerations to prevent remote code execution attacks.
  // params: type (string)
//   void enumeration_class(type) {
//    klass = type.to_s.constantize
//    raise NameError unless klass.ancestors.include? Enumeration
//    klass
//  rescue NameError
//    nil
//  }
};
}
