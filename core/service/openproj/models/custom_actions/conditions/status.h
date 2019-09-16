#pragma once
#include "base.h"
namespace openproj {
namespace CustomActions {
namespace Conditions {
class Status : public CustomActions::Conditions::Base {
   void key() {
//    :status
  }

  private:

   void associated() {
//    ::Status
//      .select(:id, :name)
//      .order(:name)
//      .map { |u| [u.id, u.name] }
  }
};
}
}
}
