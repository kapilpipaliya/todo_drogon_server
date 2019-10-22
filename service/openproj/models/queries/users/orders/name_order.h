#pragma once
#include "../../../queries/base_order.h"
namespace openproj {
namespace models {
namespace Queries {
namespace Users {
namespace Orders {
class NameOrder : public openproj::models::Queries::BaseOrder {
//  this->model = User

   void key() {
//    :name
  }

  private:

   void order() {
//    ordered = User.order_by_name

//    if ( direction == :desc) {
//      ordered = ordered.reverse_order
//    }

//    ordered
  }
};
}
}
}
}
}