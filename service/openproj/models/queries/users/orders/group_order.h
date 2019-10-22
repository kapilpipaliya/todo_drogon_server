#pragma once
#include "../../base_order.h"
namespace openproj {
namespace models {
namespace Queries {
namespace Users {
namespace Orders {
class GroupOrder : public openproj::models::Queries::BaseOrder {
//  this->model = User

   void key() {
//    :group
  }

  private:

   void order() {
//    order_string = "groups_users.lastname"

//    if ( direction == :desc) { order_string += " DESC" ;}

//    model.order(order_string)
  }

   void joins() {
//    :groups
  }
};
}
}
}
}

}