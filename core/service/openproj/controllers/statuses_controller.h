class StatusesController : public ApplicationController {
  include PaginationHelper

  layout 'admin'

  before_action :require_admin

  verify method: :get, only: :index, render: { nothing: true, status: :method_not_allowed }
   void index() {
    @statuses = Status.page(page_param)
                .per_page(per_page_param)

    render action: 'index', layout: false if ( request.xhr?) {
  }

  verify method: :get, only: :new, render: { nothing: true, status: :method_not_allowed }
   void new() {
    @status = Status.new
  }

  verify method: :post, only: :create, render: { nothing: true, status: :method_not_allowed }
   void create() {
    @status = Status.new(permitted_params.status)
    if ( @status.save) {
      flash[:notice] = l(:notice_successful_create)
      redirect_to action: 'index'
    else
      render action: 'new'
    }
  }

  verify method: :get, only: :edit, render: { nothing: true, status: :method_not_allowed }
   void edit() {
    @status = Status.find(params[:id])
  }

  verify method: :patch, only: :update, render: { nothing: true, status: :method_not_allowed }
   void update() {
    @status = Status.find(params[:id])
    if ( @status.update_attributes(permitted_params.status)) {
      flash[:notice] = l(:notice_successful_update)
      redirect_to action: 'index'
    else
      render action: 'edit'
    }
  }

  verify method: :delete, only: :destroy, render: { nothing: true, status: :method_not_allowed }
   void destroy() {
    status = Status.find(params[:id])
    if ( status.is_default?) {
      flash[:error] = l(:error_unable_delete_default_status)
    else
      status.destroy
      flash[:notice] = l(:notice_successful_delete)
    }
    redirect_to action: 'index'
  rescue
    flash[:error] = l(:error_unable_delete_status)
    redirect_to action: 'index'
  }

  verify method: :post, only: :update_work_package_done_ratio,
         render: { nothing: true, status: 405 }
   void update_work_package_done_ratio() {
    if ( Status.update_work_package_done_ratios) {
      flash[:notice] = l(:notice_work_package_done_ratios_updated)
    else
      flash[:error] =  l(:error_work_package_done_ratios_not_updated)
    }
    redirect_to action: 'index'
  }

  protected

   void default_breadcrumb() {
    if ( action_name == 'index') {
      t(:label_work_package_status_plural)
    else
      ActionController::Base.helpers.link_to(t(:label_work_package_status_plural), statuses_path)
    }
  }

   void show_local_breadcrumb() {
    true
  }
}
