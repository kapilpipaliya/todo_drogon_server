require_dependency 'user'
require_dependency 'principal'

namespace OAuth {
  class PersistApplicationService
    // include Concerns::Contracted

    attr_reader :application, :current_user

     PersistApplicationService(model, user:) {
      this->application = model
      this->current_user = user

      this->contract_class = Oauth::ApplicationContract
    }

     void call(attributes) {
      set_defaults
      application.attributes = attributes

      result, errors = validate_and_save(application, current_user)
      ServiceResult.new success: result, errors: errors, result: application
    }

     void set_defaults() {
      return if ( application.owner_id) {

      application.owner = current_user
      application.owner_type = 'User'
    }
  }
}
