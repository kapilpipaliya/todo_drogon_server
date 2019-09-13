class ColorsController : public ApplicationController {
  before_action :require_admin_unless_readonly_api_request

  layout 'admin'

  menu_item :colors

   void index() {
    @colors = Color.all
    respond_to { |format|
      format.html
    }
  }

   void show() {
    @color = Color.find(params[:id])
    respond_to { |_format|
    }
  }

   void new() {
    @color = Color.new
    respond_to { |format|
      format.html
    }
  }

   void create() {
    @color = Color.new(permitted_params.color)

    if ( @color.save) {
      flash[:notice] = l(:notice_successful_create)
      redirect_to colors_path
    else
      flash.now[:error] = l('timelines.color_could_not_be_saved')
      render action: 'new'
    }
  }

   void edit() {
    @color = Color.find(params[:id])
    respond_to { |format|
      format.html
    }
  }

   void update() {
    @color = Color.find(params[:id])

    if ( @color.update_attributes(permitted_params.color)) {
      flash[:notice] = l(:notice_successful_update)
      redirect_to colors_path
    else
      flash.now[:error] = l('timelines.color_could_not_be_saved')
      render action: 'edit'
    }
  }

   void confirm_destroy() {
    @color = Color.find(params[:id])
    respond_to { |format|
      format.html
    }
  }

   void destroy() {
    @color = Color.find(params[:id])
    @color.destroy

    flash[:notice] = l(:notice_successful_delete)
    redirect_to colors_path
  }

  protected

   void default_breadcrumb() {
    if ( action_name == 'index') {
      t('timelines.admin_menu.colors')
    else
      ActionController::Base.helpers.link_to(t('timelines.admin_menu.colors'), colors_path)
    }
  }

   void show_local_breadcrumb() {
    true
  }

   void require_admin_unless_readonly_api_request() {
    require_admin unless %w[index show].include? params[:action] and
                         api_request?
  }
}
