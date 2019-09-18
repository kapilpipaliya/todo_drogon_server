#pragma once
#include "base.h"
namespace openproj {
namespace models {
namespace CustomActions {
namespace Actions {
class Status : public CustomActions::Actions::Base {
  // include CustomActions::Actions::Strategies::Associated

   void key() {
//    :status
  }

//   void required?() {
//    true
//  }

  private:

   void associated() {
//    Status
//      .select(:id, :name)
//      .order(:name)
//      .map { |u| [u.id, u.name] }
  }
};
}
}
}
}