#pragma once
#include <string>
namespace openproj {
namespace controller {
namespace Concerns {
namespace UserInvitation {
//  namespace Events {
//    class << self {
//       void user_invited() {
//        "user_invited"
//      }

//       void user_reinvited() {
//        "user_reinvited"
//      }
//    }
//  }

//  module_function

  //
  // Creates an invited user with the given email address.
  //
  // @param email E-Mail address the invitation is sent to.
  // @param login User"s login (optional)
  // @param first_name The user"s first name (optional)
  // @param last_name The user"s last name (optional)
  //
  // this->yield [user] Allows modifying the created user before saving it.
  //
  // @return The invited user. If the invitation failed, calling `#registered?`
  //         on the returned user will yield `false`. Check for validation errors
  //         in that case.
//   void invite_new_user(email:, login: nil, first_name: nil, last_name: nil) {
//    user = User.new mail: email,
//                    login: login,
//                    firstname: first_name,
//                    lastname: last_name,
//                    status: Principal::STATUSES[:invited]

//    assign_user_attributes(user)

//    if ( block_given?) { yield user ;}

//    invite_user! user
//  }

  //
  // For the given user with at least the mail attribute set,
  // derives login and first name
  //
  // The default login is the email address.
//   void assign_user_attributes(user) {
//    placeholder = placeholder_name(user.mail)

//    user.login = user.login.presence || user.mail
//    user.firstname = user.firstname.presence || placeholder.first
//    user.lastname = user.lastname.presence || placeholder.last
//    user.language = user.language.presence || Setting.default_language
//  }

  //
  // Sends a new invitation to the user with a new token.
  //
  // @param user_id [Integer] ID of the user to be re-invited.
  // @return [Token] The new token used for the invitation.
//   void reinvite_user(user_id) {
//    clear_tokens user_id

//    Token::Invitation.create!(user_id: user_id).tap { |token|
//      OpenProject::Notifications.send Events.user_reinvited, token
//    }
//  }

//   void clear_tokens(user_id) {
//    Token::Invitation.where(user_id: user_id).delete_all
//  }

  //
  // Creates a placeholder name for the user based on their email address.
  // For the unlikely case that the local or domain part of the email address
  // are longer than 30 characters they will be trimmed to 27 characters and an
  // elipsis will be appended.
//   void placeholder_name(email) {
//    first, last = email.split("this->").map { |name| trim_name(name) }

//    [first, "this->" + last]
//  }

   std::string trim_name(std::string name) {
//    if ( name.size > 30) {
//      name[0..26] + "..."
//    else
//      name
//    }
  }

  //
  // Invites the given user. An email will be sent to their email address
  // containing the token necessary for the user to register.
  //
  // Validates and saves the given user. The invitation will fail if ( the user is invalid.) {
  //
  // @return The invited user or nil if ( the invitation failed.) {
//   void invite_user!(user) {
//    user, token = user_invitation user

//    if ( token) {
//      OpenProject::Notifications.send(Events.user_invited, token)

//      user
//    }
//  }

  //
  // Creates an invited user with the given email address.
  // If no first and last is given it will default to "OpenProject User"
  // for the first name and "To-be" for the last name.
  // The default login is the email address.
  //
  // @return Returns the user and the invitation token required to register.
//   void user_invitation(user) {
//    User.transaction {
//      user.invite

//      if ( user.valid?) {
//        token = Token::Invitation.create! user: user
//        user.save!

//        return [user, token]
//      }
//    }

//    [user, nil]
//  }
}
}
}
}
