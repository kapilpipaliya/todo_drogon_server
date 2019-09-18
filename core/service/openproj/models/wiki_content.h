#pragma once
#include "activerecord.h"
//#include "zlib"

namespace openproj {
namespace models {
class WikiContent : public ActiveRecord::Base {
  // belongs_to :page, class_name: 'WikiPage', foreign_key: 'page_id'
  // belongs_to :author, class_name: 'User', foreign_key: 'author_id'
  // validates_length_of :comments, maximum: 255, allow_nil: true

  // attr_accessor :comments

//  before_save :comments_to_journal_notes
//  // after_create :send_content_added_mail
//  after_update :send_content_updated_mail, if (: :saved_change_to_text?) {

//  acts_as_journalized

//  acts_as_event type: 'wiki-page',
//                title: Proc.new { |o| "#{l(:label_wiki_edit)}: #{o.journal.journable.page.title} (##{o.journal.journable.version})" },
//                url: Proc.new { |o| { controller: '/wiki', action: 'show', id: o.journal.journable.page, project_id: o.journal.journable.page.wiki.project, version: o.journal.journable.version } }

   void activity_type() {
//    'wiki_edits'
  }

//   void visible?(user = User.current) {
//    page.visible?(user)
//  }

   void project() {
//    page.project
  }

   void attachments() {
//    page.nil? ? [] : page.attachments
  }

//   void text=(value) {
//    super value.presence || ''
//  }

  // Returns the mail adresses of users that should be notified
   void recipients() {
//    notified = project.notified_users
//    notified.select { |user| visible?(user) }
  }

  // FIXME: Deprecate
   void versions() {
//    journals
  }

  // REVIEW
   void version() {
//    last_journal.nil? ? 0 : last_journal.version
  }

  private:

   void comments_to_journal_notes() {
//    add_journal author, comments
  }

   void send_content_added_mail() {
//    return unless Setting.notified_events.include?('wiki_content_added')

//    create_recipients.uniq.each { |user|
//      UserMailer.wiki_content_added(user, self, User.current).deliver_now
//    }
  }

   void send_content_updated_mail() {
//    return unless Setting.notified_events.include?('wiki_content_updated')

//    update_recipients.uniq.each { |user|
//      UserMailer.wiki_content_updated(user, self, User.current).deliver_now
//    }
  }

   void create_recipients() {
//    recipients +
//      page.wiki.watcher_recipients
  }

   void update_recipients() {
//    recipients +
//      page.wiki.watcher_recipients +
//      page.watcher_recipients
  }
};
}
}