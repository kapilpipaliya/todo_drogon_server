#pragma once
//
// Implements the deletion of a user.
namespace openproj {
namespace service {
namespace Users {
  class DeleteService {
  public:
//    attr_reader :user, :actor

//     DeleteService(user, actor) {
//      this->user = user
//      this->actor = actor
//    }

    //
    // Deletes the given user if allowed.
    //
    // @return True if the user deletion has been initiated, false otherwise.
     void call() {
//      if ( deletion_allowed?) {
//        // as destroying users is a lengthy process we handle it in the background
//        // and lock the account now so that no action can be performed with it
//        user.lock!
//        Delayed::Job.enqueue DeleteUserJob.new(user.id), priority: ::ApplicationJob.priority_number(:low)

//        if ( self_delete?) { logout! ;}

//        true
//      else
//        false
//      }
    }

    //
    // Checks if a given user may be deleted by another one.
    //
    // @param user [User] User to be deleted.
    // @param actor [User] User who wants to delete the given user.
//     void deletion_allowed?(user, actor) {
//      if ( actor == user) {
//        Setting.users_deletable_by_self?
//      else
//        actor.admin? && actor.active? && Setting.users_deletable_by_admins?
//      }
//    }

    private:

     bool deletion_allowed() {
//      this->class.deletion_allowed? user, actor
    }

     bool self_delete() {
//      user == actor
    }

     void logout() {
//      User.current = nil
    }
  };
}
}
}
