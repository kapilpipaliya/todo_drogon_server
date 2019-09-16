#pragma once
#include "../../../queries/base_order.h"
namespace openproj {
namespace Queries {
namespace Principals {
namespace Orders {
class NameOrder : public openproj::Queries::BaseOrder {
//  this->model = Principal

   void key() {
//    :name
  }

  private:

   void order() {
//    ordered = this->model.order_by_name

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
