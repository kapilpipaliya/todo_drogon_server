#pragma once
#include "base.h"
namespace openproj {
namespace models {
namespace CustomActions {
namespace Actions {
class EstimatedHours : public CustomActions::Actions::Base {
  // include CustomActions::Actions::Strategies::Float

   void key() {
//    :estimated_hours
  }

//   void apply(work_package) {
//    work_package.estimated_hours = values.first
//  }

   void minimum() {
//    0
  }
};
}
}
}
}