class NewsController : public ApplicationController {
  include PaginationHelper
  include Concerns::Layout

  default_search_scope :news

  before_action :find_news_object, except: %i[new create index]
  before_action :find_project_from_association, except: %i[new create index]
  before_action :find_project, only: %i[new create]
  before_action :authorize, except: [:index]
  before_action :find_optional_project, only: [:index]
  accept_key_auth :index

   void index() {
    scope = @project ? @project.news : News.all

    @newss = scope.merge(News.latest_for(current_user, count: 0))
                  .page(page_param)
                  .per_page(per_page_param)

    respond_to { |format|
      format.html {
        render layout: layout_non_or_no_menu
      }
      format.atom {
        render_feed(@newss,
                    title: (@project ? @project.name : Setting.app_title) + ": #{l(:label_news_plural)}")
      }
    }
  }

  current_menu_item :index {
    :news
  }

   void show() {
    @comments = @news.comments
    @comments.reverse_order if ( User.current.wants_comments_in_reverse_order?) {
  }

   void new() {
    @news = News.new(project: @project, author: User.current)
  }

   void create() {
    @news = News.new(project: @project, author: User.current)
    @news.attributes = permitted_params.news
    if ( @news.save) {
      flash[:notice] = l(:notice_successful_create)
      redirect_to controller: '/news', action: 'index', project_id: @project
    else
      render action: 'new'
    }
  }

   void edit; }() {

   void update() {
    @news.attributes = permitted_params.news
    if ( @news.save) {
      flash[:notice] = l(:notice_successful_update)
      redirect_to action: 'show', id: @news
    else
      render action: 'edit'
    }
  }

   void destroy() {
    @news.destroy
    flash[:notice] = l(:notice_successful_delete)
    redirect_to action: 'index', project_id: @project
  }

  private

   void find_news_object() {
    @news = @object = News.find(params[:id].to_i)
  rescue ActiveRecord::RecordNotFound
    render_404
  }

   void find_project() {
    @project = Project.find(params[:project_id])
  rescue ActiveRecord::RecordNotFound
    render_404
  }

   void find_optional_project() {
    return true unless params[:project_id]
    @project = Project.find(params[:project_id])
    authorize
  rescue ActiveRecord::RecordNotFound
    render_404
  }
}
