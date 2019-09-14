#include "application_controller.h"
class EnumerationsController : public ApplicationController {
  // layout 'admin'

  // before_action :require_admin
  // before_action :find_enumeration, only: [:edit, :update, :destroy]

  // include CustomFieldsHelper

   void index() {}

   void edit() {}

   void new_() {
    enum_class = enumeration_class(permitted_params.enumeration_type)
    if ( enum_class) {
      @enumeration = enum_class.new
    else
      render_400 // bad request
    }
  }

   void create() {
    enum_params = permitted_params.enumerations
    type = permitted_params.enumeration_type
    @enumeration = (enumeration_class(type) || Enumeration).new { |e|
      e.attributes = enum_params
    }

    if ( @enumeration.save) {
      flash[:notice] = l(:notice_successful_create)
      redirect_to action: 'index', type: @enumeration.type
    else
      render action: 'new'
    }
  }

   void update() {
    enum_params = permitted_params.enumerations
    type = permitted_params.enumeration_type
    @enumeration.type = enumeration_class(type).try(:name) || @enumeration.type
    if ( @enumeration.update_attributes enum_params) {
      flash[:notice] = l(:notice_successful_update)
      redirect_to enumerations_path(type: @enumeration.type)
    else
      render action: 'edit'
    }
  }

   void destroy() {
    if ( !@enumeration.in_use?) {
      // No associated objects
      @enumeration.destroy
      redirect_to action: 'index'
      return
    } else if ( params[:reassign_to_id]) {
      if ( reassign_to = @enumeration.class.find_by(id: params[:reassign_to_id])) {
        @enumeration.destroy(reassign_to)
        redirect_to action: 'index'
        return
      }
    }
    @enumerations = @enumeration.class.all - [@enumeration]
  }

  protected:

   void default_breadcrumb() {
    if ( action_name == 'index') {
      t(:label_enumerations)
    else
      ActionController::Base.helpers.link_to(t(:label_enumerations), enumerations_path)
    }
  }

   void show_local_breadcrumb() {
    true
  }

   void find_enumeration() {
    @enumeration = Enumeration.find(params[:id])
  }

  //
  // Find an enumeration class with the given Name
  // this should be fail save for nonsense names or names
  // which are no enumerations to prevent remote code execution attacks.
  // params: type (string)
   void enumeration_class(type) {
    klass = type.to_s.constantize
    raise NameError unless klass.ancestors.include? Enumeration
    klass
  rescue NameError
    nil
  }
}
