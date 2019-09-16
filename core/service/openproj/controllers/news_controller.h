#pragma once
#include "application_controller.h"
namespace openproj {
namespace controller {
class NewsController : public ApplicationController {
public:
  // include PaginationHelper
  // include Concerns::Layout

//  default_search_scope :news

  // before_action :find_news_object, except: %i[new create index]
  // before_action :find_project_from_association, except: %i[new create index]
  // before_action :find_project, only: %i[new create]
  // before_action :authorize, except: [:index]
  // before_action :find_optional_project, only: [:index]
  // accept_key_auth :index

   void index() {
//    scope = this->project ? this->project.news : News.all

//    this->newss = scope.merge(News.latest_for(current_user, count: 0))
//                  .page(page_param)
//                  .per_page(per_page_param)

//    respond_to { |format|
//      format.html {
//        render layout: layout_non_or_no_menu
//      }
//      format.atom {
//        render_feed(this->newss,
//                    title: (this->project ? this->project.name : Setting.app_title) + ": #{l(:label_news_plural)}")
//      }
//    }
  }

//  current_menu_item :index {
//    :news
//  }

   void show() {
//    this->comments = this->news.comments
//    if ( User.current.wants_comments_in_reverse_order?) {this->comments.reverse_order}
  }

   void new_() {
//    this->news = News.new(project: this->project, author: User.current)
  }

   void create() {
//    this->news = News.new(project: this->project, author: User.current)
//    this->news.attributes = permitted_params.news
//    if ( this->news.save) {
//      flash[:notice] = l(:notice_successful_create)
//      redirect_to controller: '/news', action: 'index', project_id: this->project
//    else
//      render action: 'new'
//    }
  }

   void edit() {}

   void update() {
//    this->news.attributes = permitted_params.news
//    if ( this->news.save) {
//      flash[:notice] = l(:notice_successful_update)
//      redirect_to action: 'show', id: this->news
//    else
//      render action: 'edit'
//    }
  }

   void destroy() {
//    this->news.destroy
//    flash[:notice] = l(:notice_successful_delete)
//    redirect_to action: 'index', project_id: this->project
  }

  private:

   void find_news_object() {
//    this->news = this->object = News.find(params[:id].to_i)
//  rescue ActiveRecord::RecordNotFound
//    render_404
  }

   void find_project() {
//    this->project = Project.find(params[:project_id])
//  rescue ActiveRecord::RecordNotFound
//    render_404
  }

   void find_optional_project() {
//    return true unless params[:project_id]
//    this->project = Project.find(params[:project_id])
//    authorize
//  rescue ActiveRecord::RecordNotFound
//    render_404
  }
};
}
}
