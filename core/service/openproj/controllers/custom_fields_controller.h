#include "application_controller.h"
class CustomFieldsController : public ApplicationController {
  // layout 'admin'

  // before_action :require_admin
  // before_action :find_custom_field, only: %i(edit update destroy move delete_option)
  // before_action :prepare_custom_option_position, only: %i(update create)
  // before_action :find_custom_option, only: :delete_option

   void index() {
    // loading wp cfs exclicity to allow for eager loading
    this->custom_fields_by_type = CustomField.all.where.not(type: 'WorkPackageCustomField').group_by { |f| f.class.name }
    this->custom_fields_by_type['WorkPackageCustomField'] = WorkPackageCustomField.includes(:types).all

    this->tab = params[:tab] || 'WorkPackageCustomField'
  }

   void new_() {
    this->custom_field = careful_new_custom_field permitted_params.custom_field_type
  }

   void create() {
    this->custom_field = careful_new_custom_field permitted_params.custom_field_type, get_custom_field_params

    if ( this->custom_field.save) {
      flash[:notice] = l(:notice_successful_create)
      call_hook(:controller_custom_fields_new_after_save, custom_field: this->custom_field)
      redirect_to custom_fields_path(tab: this->custom_field.class.name)
    else
      render action: 'new'
    }
  }

   void edit() {}

   void update() {
    this->custom_field.attributes = get_custom_field_params

    if ( this->custom_field.save) {
      flash[:notice] = t(:notice_successful_update)
      call_hook(:controller_custom_fields_edit_after_save, custom_field: this->custom_field)
      redirect_back_or_default edit_custom_field_path(id: this->custom_field.id)
    else
      render action: 'edit'
    }
  }

   void destroy() {
    begin
      this->custom_field.destroy
    rescue
      flash[:error] = l(:error_can_not_delete_custom_field)
    }
    redirect_to custom_fields_path(tab: this->custom_field.class.name)
  }

   void delete_option() {
    if ( this->custom_option.destroy) {
      num_deleted = delete_custom_values! this->custom_option

      flash[:notice] = I18n.t(
        :notice_custom_options_deleted, option_value: this->custom_option.value, num_deleted: num_deleted
      )
    else
      flash[:error] = this->custom_option.errors.full_messages
    }

    redirect_to edit_custom_field_path(id: this->custom_field.id)
  }

  private:

   void get_custom_field_params() {
    custom_field_params = permitted_params.custom_field

    if ( !EnterpriseToken.allows_to?(:multiselect_custom_fields)) {
      custom_field_params.delete :multi_value
    }

    custom_field_params
  }

   void find_custom_option() {
    this->custom_option = CustomOption.find params[:option_id]
  rescue ActiveRecord::RecordNotFound
    render_404
  }

   void delete_custom_values!(custom_option) {
    CustomValue
      .where(custom_field_id: custom_option.custom_field_id, value: custom_option.id)
      .delete_all
  }

   void prepare_custom_option_position() {
    return unless params[:custom_field][:custom_options_attributes]

    index = 0

    params[:custom_field][:custom_options_attributes].each { |_id, attributes|
      attributes[:position] = (index = index + 1)
    }
  }

   void careful_new_custom_field(type, params = {}) {
    cf = begin
      if ( type.to_s =~ /.+CustomField\z/) {
        klass = type.to_s.constantize
        if ( klass.ancestors.include? CustomField) { klass.new(params) ;}
      }
    rescue NameError => e
      Rails.logger.error "#{e.message}:\n#{e.backtrace.join("\n")}"
      nil
    }
    redirect_to custom_fields_path unless cf
    cf
  }

   void find_custom_field() {
    this->custom_field = CustomField.find(params[:id])
  rescue ActiveRecord::RecordNotFound
    render_404
  }

  protected:

   void default_breadcrumb() {
    if ( action_name == 'index') {
      t('label_custom_field_plural')
    else
      ActionController::Base.helpers.link_to(t('label_custom_field_plural'), custom_fields_path)
    }
  }

   void show_local_breadcrumb() {
    true
  }
}
