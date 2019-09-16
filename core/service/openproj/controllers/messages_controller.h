#pragma once
#include "application_controller.h"
namespace openproj {
namespace controller {
class MessagesController : public ApplicationController {
public:
  // menu_item :boards
//  default_search_scope :messages
  // model_object Message, scope: Forum
  // before_action :find_object_and_scope
  // before_action :authorize, except: [:edit, :update, :destroy]

  // include AttachmentsHelper
  // include PaginationHelper

//  REPLIES_PER_PAGE = 100 unless const_defined?(:REPLIES_PER_PAGE)

  // Show a topic and its replies
   void show() {
//    this->topic = this->message.root

//    page = params[:page]
//    // Find the page of the requested reply
//    if ( params[:r] && page.nil?) {
//      offset = this->topic.children.where(["#{Message.table_name}.id < ?", params[:r].to_i]).count
//      page = 1 + offset / REPLIES_PER_PAGE
//    }

//    this->replies = this->topic.children.includes(:author, :attachments, forum: :project)
//                     .order("#{Message.table_name}.created_on ASC")
//                     .page(page)
//                     .per_page(per_page_param)

//    this->reply = Message.new(subject: "RE: #{this->message.subject}", parent: this->topic)
//    render action: 'show', layout: !request.xhr?
  }

  // new topic
   void new_() {
//    this->message = Message.new.tap { |m|
//      m.author = User.current
//      m.forum = this->forum
//    }
  }

  // Create a new topic
   void create() {
//    this->message = Message.new.tap { |m|
//      m.author = User.current
//      m.forum = this->forum
//    }

//    this->message.attributes = permitted_params.message(this->message)
//    this->message.attach_files(permitted_params.attachments.to_h)

//    if ( this->message.save) {
//      render_attachment_warning_if_needed(this->message)
//      call_hook(:controller_messages_new_after_save, params: params, message: this->message)

//      redirect_to topic_path(this->message)
//    else
//      render action: 'new'
//    }
  }

  // Reply to a topic
   void reply() {
//    this->topic = this->message.root

//    this->reply = Message.new
//    this->reply.author = User.current
//    this->reply.forum = this->forum
//    this->reply.attributes = permitted_params.reply
//    this->reply.attach_files(permitted_params.attachments.to_h)

//    this->topic.children << this->reply
//    unless this->reply.new_record?
//      render_attachment_warning_if_needed(this->reply)
//      call_hook(:controller_messages_reply_after_save, params: params, message: this->reply)
//    }
//    redirect_to topic_path(this->topic, r: this->reply)
  }

  // Edit a message
   void edit() {
//    return render_403 unless this->message.editable_by?(User.current)
//    this->message.attributes = permitted_params.message(this->message)
  }

  // Edit a message
   void update() {
//    return render_403 unless this->message.editable_by?(User.current)

//    this->message.attributes = permitted_params.message(this->message)
//    this->message.attach_files(permitted_params.attachments.to_h)

//    if ( this->message.save) {
//      render_attachment_warning_if_needed(this->message)
//      flash[:notice] = l(:notice_successful_update)
//      this->message.reload
//      redirect_to topic_path(this->message.root, r: (this->message.parent_id && this->message.id))
//    else
//      render action: 'edit'
//    }
  }

  // Delete a messages
   void destroy() {
//    return render_403 unless this->message.destroyable_by?(User.current)
//    this->message.destroy
//    flash[:notice] = l(:notice_successful_delete)
//    redirect_target = if ( this->message.parent.nil?) {
//                        { controller: '/forums', action: 'show', project_id: this->project, id: this->forum }
//                      else
//                        { action: 'show', id: this->message.parent, r: this->message }
//                      }

//    redirect_to redirect_target
  }

   void quote() {
//    user = this->message.author
//    text = this->message.content
//    subject = this->message.subject.gsub('"', '\"')
//    subject = "RE: #{subject}" unless subject.starts_with?('RE:')
//    content = "#{ll(Setting.default_language, :text_user_wrote, user)}\n> "
//    content << text.to_s.strip.gsub(%r{<pre>((.|\s)*?)</pre>}m, '[...]').gsub('"', '\"').gsub(/(\r?\n|\r\n?)/, "\n> ") + "\n\n"

//    respond_to { |format|
//      format.json { render json: { subject: subject, content: content } }
//      format.any { head :not_acceptable }
//    }
  }
};
}
}
