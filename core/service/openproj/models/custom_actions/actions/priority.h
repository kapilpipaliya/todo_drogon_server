#pragma once
#include "../../custom_actions/actions/base.h"
namespace openproj {
namespace models {
namespace CustomActions {
namespace Actions {
class Priority : public CustomActions::Actions::Base {
  // include CustomActions::Actions::Strategies::Associated

   void associated() {
//    IssuePriority
//      .select(:id, :name)
//      .order(:name)
//      .map { |p| [p.id, p.name] }
  }

//   void required?() {
//    true
//  }

   void key() {
//    :priority
  }
};
}
}
}
}