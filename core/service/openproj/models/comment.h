#ifndef OPENPROJ_MODELS_COMMENT_H
#define OPENPROJ_MODELS_COMMENT_H


#include "activerecord.h"
#include "Comments.h"

namespace openproj {

namespace models {

class Comment : public openproj::models::ActiveRecord::Base, public drogon_model::openproject6::Comments {
  public:
    // belongs_to :commented, polymorphic: true, counter_cache: true
    // belongs_to :author, class_name: "User", foreign_key: "author_id"
    // validates :commented, :author, :comments, presence: true
    // after_create :send_news_comment_added_mail
    inline void text() {
    //    comments
      };

    //   void post!() {
    //    save!
    //  }
   private:
    inline void send_news_comment_added_mail() {
    //    return unless Setting.notified_events.include?("news_comment_added")
    
    //    return unless commented.is_a?(News)
    
    //    recipients = commented.recipients + commented.watcher_recipients
    //    recipients.uniq.each { |user|
    //      UserMailer.news_comment_added(user, self, User.current).deliver_now
    //    }
      };

};

} // namespace openproj::models

} // namespace openproj
#endif
