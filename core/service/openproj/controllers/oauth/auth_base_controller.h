#pragma once
#include "../application_controller.h"
namespace openproj {

namespace OAuth {
  //
  // Base controller for doorkeeper to skip the login check
  // because it needs to set a specific return URL
  // See config/initializers/doorkeeper.rb
  class AuthBaseController : public ApplicationController {
    // skip_before_action :check_if_login_required
    // layout 'only_logo'
  };
}
}
