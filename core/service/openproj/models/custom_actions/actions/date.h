#pragma once
#include "base.h"
namespace openproj {
namespace CustomActions {
namespace Actions {
class Date : public CustomActions::Actions::Base {
  // include CustomActions::Actions::Strategies::Date

   void key() {
//    :date
  }

//   void apply(work_package) {
//    work_package.start_date = date_to_apply
//    work_package.due_date = date_to_apply
//  }
};
}
}
}
