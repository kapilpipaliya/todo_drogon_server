#pragma once
#include "application_controller.h"
namespace openproject {
class ForumsController : public ApplicationController {
public:
//  default_search_scope :messages
  // before_action :find_project_by_project_id,
//                :authorize
  // before_action :new_forum, only: %i[new create]
  // before_action :find_forum, only: %i[show edit update move destroy]
  // accept_key_auth :show

  // include SortHelper
  // include WatchersHelper
  // include PaginationHelper
  // include OpenProject::ClientPreferenceExtractor

   void index() {
//    this->forums = this->project.forums
//    if ( this->forums.empty?) { render_404 ;}
//    // show the forum if ( there is only one) {
//    if ( this->forums.size == 1) {
//      this->forum = this->forums.first
//      show
//    }
  }

//  current_menu_item [:index, :show] {
//    :forums
//  }

   void show() {
//    sort_init 'updated_on', 'desc'
//    sort_update 'created_on' => "#{Message.table_name}.created_on",
//                'replies' => "#{Message.table_name}.replies_count",
//                'updated_on' => "#{Message.table_name}.updated_on"

//    respond_to { |format|
//      format.html {
//        set_topics
//        this->message = Message.new
//        render action: 'show', layout: !request.xhr?
//      }
//      format.json {
//        set_topics

//        render template: 'messages/index'
//      }
//      format.atom {
//        this->messages = this->forum
//                    .messages
//                    .order(["#{Message.table_name}.sticked_on ASC", sort_clause].compact.join(', '))
//                    .includes(:author, :forum)
//                    .limit(Setting.feeds_limit.to_i)

//        render_feed(this->messages, title: "#{this->project}: #{this->forum}")
//      }
//    }
  }

   void set_topics() {
//    this->topics =  this->forum
//               .topics
//               .order(["#{Message.table_name}.sticked_on ASC", sort_clause].compact.join(', '))
//               .includes(:author, last_reply: :author)
//               .page(page_param)
//               .per_page(per_page_param)
  }

   void new_() {}

   void create() {
//    if ( this->forum.save) {
//      flash[:notice] = l(:notice_successful_create)
//      redirect_to_settings_in_projects
//    else
//      render :new
//    }
  }

   void edit() {}

   void update() {
//    if ( this->forum.update_attributes(permitted_params.forum)) {
//      flash[:notice] = l(:notice_successful_update)
//      redirect_to_settings_in_projects
//    else
//      render :edit
//    }
  }

   void move() {
//    if ( this->forum.update_attributes(permitted_params.forum_move)) {
//      flash[:notice] = t(:notice_successful_update)
//    else
//      flash.now[:error] = t('forum_could_not_be_saved')
//      render action: 'edit'
//    }
//    redirect_to_settings_in_projects(this->forum.project_id)
  }

   void destroy() {
//    this->forum.destroy
//    flash[:notice] = l(:notice_successful_delete)
//    redirect_to_settings_in_projects
  }

  private:

//   void redirect_to_settings_in_projects(id = this->project) {
//    redirect_to controller: '/project_settings', action: 'show', id: id, tab: 'forums'
//  }

   void find_forum() {
//    this->forum = this->project.forums.find(params[:id])
//  rescue ActiveRecord::RecordNotFound
//    render_404
  }

   void new_forum() {
//    this->forum = Forum.new(permitted_params.forum?)
//    this->forum.project = this->project
  }
};
}
