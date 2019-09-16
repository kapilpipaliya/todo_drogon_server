#pragma once
#include "base.h"
namespace openproj {
namespace CustomActions {
namespace Conditions {
class Type : public CustomActions::Conditions::Base {
   void key() {
//    :type
  }

  private:

   void associated() {
//    ::Type
//      .select(:id, :name)
//      .map { |u| [u.id, u.name] }
  }
};
}
}
}

