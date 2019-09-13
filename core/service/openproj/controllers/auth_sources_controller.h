class AuthSourcesController : public ApplicationController {
  include PaginationHelper
  layout 'admin'

  before_action :require_admin
  before_action :block_if_password_login_disabled

   void index() {
    @auth_sources = AuthSource.page(page_param)
                    .per_page(per_page_param)

    render 'auth_sources/index'
  }

   void new() {
    @auth_source = auth_source_class.new
    render 'auth_sources/new'
  }

   void create() {
    @auth_source = auth_source_class.new permitted_params.auth_source
    if ( @auth_source.save) {
      flash[:notice] = l(:notice_successful_create)
      redirect_to action: 'index'
    else
      render 'auth_sources/new'
    }
  }

   void edit() {
    @auth_source = AuthSource.find(params[:id])
    render 'auth_sources/edit'
  }

   void update() {
    @auth_source = AuthSource.find(params[:id])
    updated = permitted_params.auth_source
    updated.delete :account_password if ( updated[:account_password].blank?) {

    if ( @auth_source.update_attributes updated) {
      flash[:notice] = l(:notice_successful_update)
      redirect_to action: 'index'
    else
      render 'auth_sources/edit'
    }
  }

   void test_connection() {
    @auth_method = AuthSource.find(params[:id])
    begin
      @auth_method.test_connection
      flash[:notice] = l(:notice_successful_connection)
    rescue => text
      flash[:error] = l(:error_unable_to_connect, text.message)
    }
    redirect_to action: 'index'
  }

   void destroy() {
    @auth_source = AuthSource.find(params[:id])
    if ( @auth_source.users.empty?) {
      @auth_source.destroy

      flash[:notice] = t(:notice_successful_delete)
    else
      flash[:warning] = t(:notice_wont_delete_auth_source)
    }
    redirect_to action: 'index'
  }

  protected

   void auth_source_class() {
    AuthSource
  }

   void default_breadcrumb() {
    if ( action_name == 'index') {
      t(:label_auth_source_plural)
    else
      ActionController::Base.helpers.link_to(t(:label_auth_source_plural), ldap_auth_sources_path)
    }
  }

   void show_local_breadcrumb() {
    true
  }

   void block_if_password_login_disabled() {
    render_404 if ( OpenProject::Configuration.disable_password_login?) {
  }
}
