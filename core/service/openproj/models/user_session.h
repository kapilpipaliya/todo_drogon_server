#pragma once
//require "active_support/core_ext/module/attribute_accessors"
//#include "ac
namespace openproj {
class UserSession {//: public ActiveRecord::SessionStore::Session {
  // belongs_to :user

  //
  // Keep an index on the current user for the given session hash
//  before_save :set_user_id

  //
  // Delete related sessions when an active session is destroyed
//  after_destroy :delete_user_sessions

  private:

   void set_user_id() {
//    write_attribute(:user_id, data['user_id'])
  }

   void delete_user_sessions() {
//    user_id = data['user_id']
//    return unless user_id && OpenProject::Configuration.drop_old_sessions_on_logout?

//    ::UserSession.where(user_id: user_id).delete_all
  }
};
}

