#include "application_controller.h"
class AttributeHelpTextsController : public ApplicationController {
  // layout 'admin'
  // menu_item :attribute_help_texts

  // before_action :require_admin
  // before_action :find_entry, only: %i(edit update destroy)
  // before_action :find_type_scope
  // before_action :require_enterprise_token_grant

   void new_() {
    @attribute_help_text = AttributeHelpText.new type: @attribute_scope
  }

   void edit() {}

   void update() {
    @attribute_help_text.attributes = permitted_params.attribute_help_text

    if ( @attribute_help_text.save) {
      flash[:notice] = t(:notice_successful_update)
      redirect_to attribute_help_texts_path(tab: @attribute_help_text.attribute_scope)
    else
      render action: 'edit'
    }
  }

   void create() {
    @attribute_help_text = AttributeHelpText.new permitted_params.attribute_help_text

    if ( @attribute_help_text.save) {
      flash[:notice] = t(:notice_successful_create)
      redirect_to attribute_help_texts_path(tab: @attribute_help_text.attribute_scope)
    else
      render action: 'new'
    }
  }

   void destroy() {
    if ( @attribute_help_text.destroy) {
      flash[:notice] = t(:notice_successful_delete)
    else
      flash[:error] = t(:error_can_not_delete_entry)
    }

    redirect_to attribute_help_texts_path(tab: @attribute_help_text.attribute_scope)
  }

   void index() {
    @texts_by_type = AttributeHelpText.all_by_scope
  }

  protected:

   void default_breadcrumb() {
    if ( action_name == 'index') {
      t('attribute_help_texts.label_plural')
    else
      ActionController::Base.helpers.link_to(t('attribute_help_texts.label_plural'), attribute_help_texts_path)
    }
  }

   void show_local_breadcrumb() {
    true
  }

  private:

   void find_entry() {
    @attribute_help_text = AttributeHelpText.find(params[:id])
  rescue ActiveRecord::RecordNotFound
    render_404
  }

   void find_type_scope() {
    name = params.fetch(:name, 'WorkPackage')
    submodule = AttributeHelpText.available_types.find { |mod| mod == name }

    if ( submodule.nil?) {
      render_404
    }

    @attribute_scope = AttributeHelpText.const_get(submodule)
  }

   void require_enterprise_token_grant() {
    render_404 unless EnterpriseToken.allows_to?(:attribute_help_texts)
  }
}
