#pragma once
//require_dependency "user"
//require_dependency "principal"

namespace openproj {
namespace service {
namespace OAuth {
  class PersistApplicationService {
  public:
    // include Concerns::Contracted

//    attr_reader :application, :current_user

//     PersistApplicationService(model, user:) {
//      this->application = model
//      this->current_user = user

//      this->contract_class = Oauth::ApplicationContract
//    }

//     void call(attributes) {
//      set_defaults
//      application.attributes = attributes

//      result, errors = validate_and_save(application, current_user)
//      ServiceResult.new success: result, errors: errors, result: application
//    }

//     void set_defaults() {
//      if ( application.owner_id) { return ;}

//      application.owner = current_user
//      application.owner_type = "User"
//    }
  };
}
}
}
