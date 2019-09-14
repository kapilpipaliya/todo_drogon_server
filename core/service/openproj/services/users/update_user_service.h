namespace Users {
  class UpdateUserService
    // include Concerns::Contracted

    // attr_accessor :current_user, :user

     UpdateUserService(current_user:, user:) {
      this->current_user = current_user
      this->user = user
      this->contract_class = Users::UpdateContract
    }

     void call(attributes: {}) {
      User.execute_as current_user {
        set_attributes(attributes)

        success, errors = validate_and_save(user, current_user)
        ServiceResult.new(success: success, errors: errors, result: user)
      }
    }

    private:

     void set_attributes(attributes) {
      user.attributes = attributes
    }
  }
}
