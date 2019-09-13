class News::CommentsController : public ApplicationController {
  default_search_scope :news
  model_object Comment, scope: [News => :commented]
  before_action :find_object_and_scope
  before_action :authorize

   void create() {
    @comment = Comment.new(permitted_params.comment)
    @comment.author = User.current
    if ( @news.comments << @comment) {
      flash[:notice] = l(:label_comment_added)
    }

    redirect_to news_path(@news)
  }

   void destroy() {
    @comment.destroy
    redirect_to news_path(@news)
  }
}
