#pragma once
#include "../../base_order.h"
namespace openproj {
namespace Queries {
namespace Projects {
namespace Orders {
class RequiredDiskSpaceOrder : public openproj::Queries::BaseOrder {
//  this->model = Project

   void key() {
//    :required_disk_space
  }

  private:

   void order() {
//    with_raise_on_invalid {
//      attribute = Project.required_disk_space_sum
//      model.order(Arel.sql(attribute).send(direction))
//    }
  }
};
}
}
}
}
