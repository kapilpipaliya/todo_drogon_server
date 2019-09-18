#pragma once
#include "../../../queries/base_order.h"
namespace openproj {
namespace models {
namespace Queries {
namespace Versions {
namespace Orders {
class NameOrder : public openproj::models::Queries::BaseOrder {
//  this->model = Version

   void key() {
//    :name
  }

  private:

   void order() {
//    ordered = Version.order_by_name

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