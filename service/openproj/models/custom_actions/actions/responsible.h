#pragma once
#include "../../custom_actions/actions/base.h"
namespace openproj {
namespace models {
namespace CustomActions {
namespace Actions {
class Responsible : public CustomActions::Actions::Base {
  // include CustomActions::Actions::Strategies::Associated

//   void associated() {
//    User
//      .active_or_registered
//      .select(:id, :firstname, :lastname, :type)
//      .order_by_name
//      .map { |u| [u.id, u.name] }
//  }

//   void required?() {
//    false
//  }

   void key() {
//    :responsible
  }
};
}
}
}
}