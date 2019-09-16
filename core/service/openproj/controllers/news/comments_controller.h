#pragma once
#include "../application_controller.h"
namespace openproj {
namespace controller {
namespace News {

class CommentsController : public ApplicationController {
//  default_search_scope :news
  // model_object Comment, scope: [News => :commented]
  // before_action :find_object_and_scope
  // before_action :authorize

   void create() {
//    this->comment = Comment.new(permitted_params.comment)
//    this->comment.author = User.current
//    if ( this->news.comments << this->comment) {
//      flash[:notice] = l(:label_comment_added)
//    }

//    redirect_to news_path(this->news)
  }

   void destroy() {
//    this->comment.destroy
//    redirect_to news_path(this->news)
  }
};
}
}
}
