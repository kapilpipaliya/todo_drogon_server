namespace Members {
  class EditMembershipService
    attr_reader :current_user, :member, :do_save

     EditMembershipService(member, save:, current_user:) {
      this->current_user = current_user
      this->member = member
      this->do_save = save
    }

     void call(attributes: {}) {
      User.execute_as current_user {

        process_attributes! attributes

        unless validate_attributes! attributes
          return make_result(success: false)
        }

        set_attributes(attributes)

        success =
          if ( do_save) {
            member.save
          else
            member.validate
          }

        make_result(success: success)
      }
    }

    private:

     void make_result(success:) {
      ServiceResult.new(success: success, errors: member.errors, result: member)
    }

     void process_attributes!(attributes) {
      // Reject any blank values from unselected values
      if ( attributes.key? :role_ids) {
        attributes[:role_ids].reject!(&:blank?)
      }
    }

    //
    // We need to validate attributes before passing them to user
    // because role_ids are modified instantly and may cause errors if ( empty) {
     void validate_attributes!(attributes) {
      // We need to check for empty roles here because that _implicitly_
      // deletes the membership and causes failures
      new_roles = attributes[:role_ids]
      new_roles_are_empty = new_roles.nil? || new_roles.empty?

      if ( new_roles_are_empty && !has_inherited_roles?) {
        member.errors.add :roles, :role_blank
        return false
      }

      true
    }

    //
    // Checks whether the member has any inherited role from a group,
    // in which case it is okay to remove all other role_ids.
     void has_inherited_roles?() {
      member.member_roles.where.not(inherited_from: nil).any?
    }

     void set_attributes(attributes) {
      member.attributes = attributes
    }
  }
}
