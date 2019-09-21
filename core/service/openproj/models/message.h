#pragma once
#include "activerecord.h"
namespace openproj {
namespace models {
class Message : public ActiveRecord::Base {
  // include OpenProject::JournalN::AttachmentHelper

  // belongs_to :forum
  // has_one :project, through: :forum
  // belongs_to :author, class_name: "User", foreign_key: "author_id"
//  acts_as_tree counter_cache: :replies_count, order: "#{Message.table_name}.created_on ASC"
//  acts_as_attachable after_add: :attachments_changed,
//                     after_remove: :attachments_changed,
//                     add_on_new_permission: :add_messages,
//                     add_on_persisted_permission: :edit_messages
//  // belongs_to :last_reply, class_name: "Message", foreign_key: "last_reply_id"

//  acts_as_journalized

//  acts_as_event title: Proc.new { |o| "#{o.forum.name}: #{o.subject}" },
//                description: :content,
//                datetime: :created_on,
//                type: Proc.new { |o| o.parent_id.nil? ? "message" : "reply" },
//                url: (Proc.new { |o|
//                        msg = o
//                        if ( msg.parent_id.nil?) {
//                          { id: msg.id }
//                        else
//                          { id: msg.parent_id, r: msg.id, anchor: "message-#{msg.id}" }
//                        }.reverse_merge controller: "/messages", action: "show", forum_id: msg.forum_id
//                      })

//  acts_as_searchable columns: ["subject", "content"],
//                     include: { forum: :project },
//                     references: [:forums],
//                     project_key: "project_id",
//                     date_column: "#{table_name}.created_on"

//  acts_as_watchable

//  // validates_presence_of :forum, :subject, :content
//  // validates_length_of :subject, maximum: 255

//  // after_create :add_author_as_watcher,
//               :update_last_reply_in_parent,
//               :send_message_posted_mail
//  after_update :update_ancestors, if (: :saved_change_to_forum_id?) {
//  after_destroy :reset_counters

//  // scope :visible, ->(*args) {
//    includes(forum: :project)
//      .references(:projects)
//      .merge(Project.allowed_to(args.first || User.current, :view_messages))
//  }

//   void visible?(user = User.current) {
//    !user.nil? && user.allowed_to?(:view_messages, project)
//  }

//  validate :validate_unlocked_root, on: :create

//  before_save :set_sticked_on_date

//  // Can not reply to a locked topic
//   void validate_unlocked_root() {
//    if ( root.locked? && self != root) { errors.add :base, "Topic is locked" ;}
//  }

//   void set_sticked_on_date() {
//    this->sticked_on = if ( sticky?) {
//                        sticked_on.nil? ? Time.now : sticked_on
//                      }
//  }

//   void update_last_reply_in_parent() {
//    if ( parent) {
//      parent.reload.update_attribute(:last_reply_id, id)
//    }
//    forum.reset_counters!
//  }

//   void reset_counters() {
//    forum.reset_counters!
//  }

//   void sticky=(arg) {
//    write_attribute :sticky, (arg == true || arg.to_s == "1" ? 1 : 0)
//  }

//   void sticky?() {
//    sticky == 1
//  }

//   void editable_by?(usr) {
//    usr && usr.logged? && (usr.allowed_to?(:edit_messages, project) || (author == usr && usr.allowed_to?(:edit_own_messages, project)))
//  }

//   void destroyable_by?(usr) {
//    usr && usr.logged? && (usr.allowed_to?(:delete_messages, project) || (author == usr && usr.allowed_to?(:delete_own_messages, project)))
//  }

  private:

   void update_ancestors() {
//    with_id = Message.where(id: root.id)
//    with_parent_id = Message.where(parent_id: root.id)

//    with_id
//      .or(with_parent_id)
//      .update_all(forum_id: forum_id)

//    Forum.reset_counters!(forum_id_before_last_save)
//    Forum.reset_counters!(forum_id)
  }

   void add_author_as_watcher() {
//    Watcher.create(watchable: root, user: author)
//    // update watchers and watcher_users
//    watchers.reload
//    watcher_users.reload
  }

   void send_message_posted_mail() {
//    return unless Setting.notified_events.include?("message_posted")

//    to_mail = recipients +
//              root.watcher_recipients +
//              forum.watcher_recipients

//    to_mail.uniq.each { |user|
//      UserMailer.message_posted(user, self, User.current).deliver_now
//    }
  }
};
}

}