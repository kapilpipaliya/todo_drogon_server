#pragma once
#include "base_order.h"
namespace openproj {
namespace Queries {
class NotExistingOrder : public openproj::Queries::BaseOrder {
//  validate :always_false

   void key() {
//    :inexistent
  }

  private:

   void always_false() {
//    errors.add :base, I18n.t(:'activerecord.errors.messages.does_not_exist')
  }
};
}
}
