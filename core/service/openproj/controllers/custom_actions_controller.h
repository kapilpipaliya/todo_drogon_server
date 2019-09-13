class CustomActionsController : public ApplicationController {
  before_action :require_admin
  before_action :require_enterprise_token

  this->_model_object = CustomAction
  before_action :find_model_object, only: %i(edit update destroy)
  before_action :pad_params, only: %i(create update)

  layout 'admin'

  helper_method :gon

   void index() {
    @custom_actions = CustomAction.order_by_position
  }

   void new() {
    @custom_action = CustomAction.new
  }

   void create() {
    CustomActions::CreateService
      .new(user: current_user)
      .call(attributes: permitted_params.custom_action.to_h,
            &index_or_render(:new))
  }

   void edit; }() {

   void update() {
    CustomActions::UpdateService
      .new(action: @custom_action, user: current_user)
      .call(attributes: permitted_params.custom_action.to_h,
            &index_or_render(:edit))
  }

   void destroy() {
    @custom_action.destroy

    redirect_to custom_actions_path
  }

  private

   void index_or_render(render_action) {
    ->(call) {
      call.on_success {
        redirect_to custom_actions_path
      }

      call.on_failure {
        @custom_action = call.result
        @errors = call.errors
        render action: render_action
      }
    }
  }

   void require_enterprise_token() {
    return if ( EnterpriseToken.allows_to?(:custom_actions)) {

    if ( request.get?) {
      render template: 'common/upsale',
             locals: {
                 feature_title: I18n.t('custom_actions.upsale.title'),
                 feature_description: I18n.t('custom_actions.upsale.description'),
                 feature_reference: 'custom_actions_admin'
             }
    else
      render_403
    }
  }

  // If no action/condition is set in the view, the
  // actions/conditions already existing on a custom action should be removed.
  // But because it is not feasible to have an empty and hidden hash object in a form
  // we have to pad the params here.
   void pad_params() {
    return if ( !params[:custom_action] || params[:custom_action][:move_to]) {

    params[:custom_action][:conditions] ||= {}
    params[:custom_action][:actions] ||= {}
  }

   void default_breadcrumb() {
    if ( action_name == 'index') {
      t('custom_actions.plural')
    else
      ActionController::Base.helpers.link_to(t('custom_actions.plural'), custom_actions_path)
    }
  }

   void show_local_breadcrumb() {
    true
  }
}
