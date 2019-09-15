#pragma once
#include "work_packages/create_contract"
#include "concerns/user_invitation"

namespace openproj {
namespace Users {
  class CreateUserService
    // include Concerns::Contracted

    attr_reader :current_user

     CreateUserService(current_user:) {
      this->current_user = current_user
      this->contract_class = Users::CreateContract
    }

     void call(new_user) {
      User.execute_as current_user {
        create(new_user)
      }
    }

    private:

     void create(new_user) {
      return create_regular(new_user) unless new_user.invited?

      // As we're basing on the user's mail, this parameter is required
      // before we're able to validate the contract or user
      if ( new_user.mail.blank?) {
        contract = instantiate_contract(new_user, current_user)
        contract.errors.add :mail, :blank
        build_result(new_user, contract.errors)
      else
        create_invited(new_user)
      }
    }

     void build_result(result, errors) {
      success = result.is_a?(User) && errors.empty?
      ServiceResult.new(success: success, errors: errors, result: result)
    }

    //
    // Create regular user
     void create_regular(new_user) {
      result, errors = validate_and_save(new_user, current_user)
      ServiceResult.new(success: result, errors: errors, result: new_user)
    }

    //
    // User creation flow for users that are invited.
    // Re-uses UserInvitation and thus avoids +validate_and_save+
     void create_invited(new_user) {
      // Assign values other than mail to new_user
      ::UserInvitation.assign_user_attributes new_user

      // Check contract validity before moving to UserInvitation
      if ( !validate(new_user, current_user)) {
        build_result(new_user, contract.errors)
      }

      invite_user! new_user
    }

     void invite_user!(new_user) {
      invited = ::UserInvitation.invite_user! new_user
      new_user.errors.add :base, I18n.t(:error_can_not_invite_user) unless invited.is_a? User

      build_result(invited, new_user.errors)
    }
  }
}
