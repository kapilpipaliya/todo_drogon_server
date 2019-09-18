#pragma once
#include "activerecord.h"
namespace openproj {
namespace models {
class Forum : public ActiveRecord::Base {
  // belongs_to :project
  // has_many :topics, -> {
//    where("#{Message.table_name}.parent_id IS NULL")
//      .order("#{Message.table_name}.sticky DESC")
//  }, class_name: 'Message'
//  // has_many :messages, -> {
//    order("#{Message.table_name}.sticky DESC")
//  }, dependent: :destroy
  // belongs_to :last_message, class_name: 'Message', foreign_key: :last_message_id
//  acts_as_list scope: :project_id
//  acts_as_watchable permission: :view_messages

  // validates_presence_of :name, :description
  // validates_length_of :name, maximum: 30
  // validates_length_of :description, maximum: 255

//   void visible?(user = User.current) {
//    !user.nil? && user.allowed_to?(:view_messages, project)
//  }

//   void to_s() {
//    name
//  }

//   void reset_counters!() {
//    this->class.reset_counters!(id)
//  }

  // Updates topics_count, messages_count and last_message_id attributes for +forum_id+
//   void reset_counters!(forum_id) {
//    forum_id = forum_id.to_i
//    where(id: forum_id)
//      .update_all("topics_count = (SELECT COUNT(*) FROM #{Message.table_name} WHERE forum_id=#{forum_id} AND parent_id IS NULL)," +
//               " messages_count = (SELECT COUNT(*) FROM #{Message.table_name} WHERE forum_id=#{forum_id})," +
//               " last_message_id = (SELECT MAX(id) FROM #{Message.table_name} WHERE forum_id=#{forum_id})")
//  }
};
}

}