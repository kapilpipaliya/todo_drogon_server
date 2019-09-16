#pragma once
#include "base.h"
namespace openproj {
namespace CustomActions {
namespace Actions {
class Type : public CustomActions::Actions::Base {
  // include CustomActions::Actions::Strategies::Associated

//  PRIORITY = 20

   void key() {
//    :type
  }

//   void required?() {
//    true
//  }

   void priority() {
//    PRIORITY
  }

  private:

   void associated() {
//    ::Type
//      .select(:id, :name)
//      .order(:position)
//      .map { |u| [u.id, u.name] }
  }
};
}
}
}
