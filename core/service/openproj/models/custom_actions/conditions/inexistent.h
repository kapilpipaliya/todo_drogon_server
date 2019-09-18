#pragma once
#include "../../custom_actions/conditions/base.h"
namespace openproj {
namespace models {
namespace CustomActions {
namespace Conditions {
class Inexistent : public CustomActions::Conditions::Base {
   void key() {
//    :inexistent
  }

//   void validate(errors) {
//    errors.add :conditions, :does_not_exist
//  }
};
}
}
}
}